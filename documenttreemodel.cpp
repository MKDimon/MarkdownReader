#include "documenttreemodel.h"

DocumentTreeModel::DocumentTreeModel(QObject *parent) : QAbstractItemModel(parent) {}

// Метод для запуска парсинга корневой папки
Q_INVOKABLE void DocumentTreeModel::loadRootDirectory(const QString &path) {
    beginResetModel();
    rootItems.clear();
    nonSearchedItems.clear();
    loadDirectory(QDir(QUrl(path).toLocalFile()));
    endResetModel();
}

Q_INVOKABLE void DocumentTreeModel::search(const QString& text) {
    beginResetModel();
    rootItems.append(nonSearchedItems);
    nonSearchedItems.clear();
    for (size_t i = 0; i < rootItems.size(); ++i) {
        if (!rootItems[i].name().contains(text)) {
            nonSearchedItems.append(rootItems[i]);
            rootItems.removeAt(i);
            i--;
        }
    }
    endResetModel();
}

void DocumentTreeModel::loadDirectory(const QDir &dir, const int level) {
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

    int insertIndex = rootItems.size();
    foreach (const QFileInfo &entry, entries) {
        if (entry.isDir()) {
            loadDirectory(QDir(entry.absoluteFilePath()), level + 1); // Рекурсивно загружаем дочерние папки
        } else if (entry.isFile() && entry.suffix() == "md") {
            rootItems.insert(insertIndex, DocumentTreeItem(entry.fileName(), entry.absoluteFilePath(), level));
        }
    }
}

// Реализация методов QAbstractItemModel

QModelIndex DocumentTreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {
        // Получаем корневой элемент
        const DocumentTreeItem &parentItem = rootItems[row];
        return createIndex(row, column, const_cast<DocumentTreeItem*>(&parentItem));
    } else {
        // Получаем дочерний элемент
        DocumentTreeItem *parentItem = static_cast<DocumentTreeItem*>(parent.internalPointer());
        const DocumentTreeItem &childItem = parentItem->children().at(row);
        return createIndex(row, column, const_cast<DocumentTreeItem*>(&childItem));
    }
}

QModelIndex DocumentTreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    DocumentTreeItem *childItem = static_cast<DocumentTreeItem*>(index.internalPointer());
    QString childPath = childItem->filePath();
    QString parentPath = QFileInfo(childPath).absolutePath();

    // Поиск родительского элемента
    for (int i = 0; i < rootItems.size(); ++i) {
        if (rootItems.at(i).filePath() == parentPath)
            return createIndex(i, 0, const_cast<DocumentTreeItem*>(&rootItems[i]));
    }

    return QModelIndex();
}

int DocumentTreeModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return rootItems.size();

    DocumentTreeItem *parentItem = static_cast<DocumentTreeItem*>(parent.internalPointer());

    return parentItem->children().size();
}


int DocumentTreeModel::columnCount(const QModelIndex&) const {
    return 1;
}

// Доступ к данным ячейки
QVariant DocumentTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    DocumentTreeItem *item = static_cast<DocumentTreeItem*>(index.internalPointer());

    if (role == NAME) {
        return item->name();
    }
    if (role == PATH) {
        return item->filePath();
    }
    if (role == LEVEL) {
        return item->level();
    }

    return QVariant();
}

QHash<int, QByteArray> DocumentTreeModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NAME] = "name";
    roles[PATH] = "path";
    roles[LEVEL] = "level";
    return roles;
}
