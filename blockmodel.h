#ifndef BLOCKMODEL_H
#define BLOCKMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QDebug>

#include "block.h"

class BlockModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum BlockRoles {
        TypeRole = Qt::UserRole + 1,
        ContentRole
    };

    BlockModel(QObject* parent = nullptr);

    void initializeBlocks(const QList<QSharedPointer<Block>>& blocks);

    Q_INVOKABLE int searchWithIndex(const QString& text, const int index);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;

    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

    bool canFetchMore(const QModelIndex& parent) const override;

    void fetchMore(const QModelIndex& parent) override;

private:
    QList<QSharedPointer<Block>> m_blocks;        // Список загруженных блоков
    QList<QSharedPointer<Block>> m_allBlocks;     // Полный список блоков для отложенной загрузки
};

#endif // BLOCKMODEL_H
