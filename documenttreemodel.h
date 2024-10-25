#ifndef DOCUMENTTREEMODEL_H
#define DOCUMENTTREEMODEL_H

#include <QAbstractItemModel>
#include <QString>
#include <QList>
#include <QVariant>
#include <QThreadPool>
#include <QRunnable>
#include <QFileInfoList>
#include <QFuture>
#include <QtConcurrent>

#include "documenttreeitem.h"

// Класс модели данных для документов
class DocumentTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    enum DocumentProp {
        NAME = Qt::UserRole + 1,
        PATH,
        IS_DIR,
        LEVEL
    };

    explicit DocumentTreeModel(QObject *parent = nullptr) : QAbstractItemModel(parent) {}

    // Метод для запуска парсинга корневой папки
    Q_INVOKABLE void loadRootDirectory(const QString &path) {
        beginResetModel();
        rootItems.clear();
        loadDirectory(QDir(QUrl(path).toLocalFile()));
        endResetModel();
    }

    void loadDirectory(const QDir &dir, const int level = 0) {
        QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);

        int insertIndex = rootItems.size();
        foreach (const QFileInfo &entry, entries) {
            if (entry.isDir()) {
                loadDirectory(QDir(entry.absoluteFilePath()), level + 1); // Рекурсивно загружаем дочерние папки
            } else if (entry.isFile() && entry.suffix() == "md") {
                rootItems.insert(insertIndex, DocumentTreeItem(entry.fileName(), entry.absoluteFilePath(), false, level));
            }
        }
    }

    // Реализация методов QAbstractItemModel

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override {
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

    QModelIndex parent(const QModelIndex &index) const override {
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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        if (!parent.isValid())
            return rootItems.size();

        DocumentTreeItem *parentItem = static_cast<DocumentTreeItem*>(parent.internalPointer());

        return parentItem->children().size();
    }

    int columnCount(const QModelIndex & = QModelIndex()) const override {
        return 1;  // В данной модели один столбец — название файла или папки
    }

    // Доступ к данным ячейки
    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid())
            return QVariant();

        DocumentTreeItem *item = static_cast<DocumentTreeItem*>(index.internalPointer());

        if (role == NAME) {
            return item->name();
        }
        if (role == PATH) {
            return item->filePath();
        }
        if (role == IS_DIR) {
            return item->isDir();
        }
        if (role == LEVEL) {
            return item->level();
        }

        return QVariant();
    }

protected:
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[NAME] = "name";
        roles[PATH] = "path";
        roles[IS_DIR] = "isDir";
        roles[LEVEL] = "level";
        return roles;
    }

private:
    QList<DocumentTreeItem> rootItems;
};

#endif // DOCUMENTTREEMODEL_H
