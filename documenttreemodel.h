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
        LEVEL
    };

    explicit DocumentTreeModel(QObject *parent = nullptr);

    // Метод для запуска парсинга корневой папки
    Q_INVOKABLE void loadRootDirectory(const QString &path);

    Q_INVOKABLE void search(const QString& text);

    void loadDirectory(const QDir &dir, const int level = 0);

    // Реализация методов QAbstractItemModel

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override ;

    // Доступ к данным ячейки
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<DocumentTreeItem> rootItems;
    QList<DocumentTreeItem> nonSearchedItems;
};

#endif // DOCUMENTTREEMODEL_H
