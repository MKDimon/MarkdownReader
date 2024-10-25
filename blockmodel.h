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

    BlockModel(QObject* parent = nullptr) : QAbstractListModel(parent) {}

    void initializeBlocks(const QList<QSharedPointer<Block>>& blocks) {
        beginResetModel();
        m_blocks.clear();
        m_allBlocks = blocks;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_blocks.count();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid() || index.row() >= m_blocks.count())
            return QVariant();

        const auto& block = m_blocks[index.row()];
        if (role == TypeRole)
            return block->type;
        else if (role == ContentRole)
            return block->content;

        return QVariant();
    }

    void clear() {
        beginResetModel();
        m_blocks.clear();
        m_allBlocks.clear();
        endResetModel();
    }

protected:
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[TypeRole] = "type";
        roles[ContentRole] = "content";
        return roles;
    }

    bool canFetchMore(const QModelIndex& parent) const override {
        Q_UNUSED(parent)
        return m_blocks.size() < m_allBlocks.size();
    }

    void fetchMore(const QModelIndex& parent) override {
        Q_UNUSED(parent)

        // Загружаем дополнительные блоки (например, по 10 за раз)
        int loadedBlocks = m_blocks.size();
        int itemsToFetch = qMin(10, m_allBlocks.size() - loadedBlocks);
        beginInsertRows(QModelIndex(), loadedBlocks, loadedBlocks + itemsToFetch - 1);
        for (int i = 0; i < itemsToFetch; ++i) {
            m_blocks.append(m_allBlocks[loadedBlocks + i]);
        }
        endInsertRows();
    }

private:
    QList<QSharedPointer<Block>> m_blocks;        // Список загруженных блоков
    QList<QSharedPointer<Block>> m_allBlocks;     // Полный список блоков для отложенной загрузки
};

#endif // BLOCKMODEL_H
