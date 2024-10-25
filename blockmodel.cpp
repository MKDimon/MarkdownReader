#include "blockmodel.h"

BlockModel::BlockModel(QObject* parent) : QAbstractListModel(parent) {}

void BlockModel::initializeBlocks(const QList<QSharedPointer<Block>>& blocks) {
    beginResetModel();
    m_blocks.clear();
    m_allBlocks = blocks;
    endResetModel();
}

Q_INVOKABLE int BlockModel::searchWithIndex(const QString& text, const int index) {
    auto itBegin = m_allBlocks.begin() + index % m_allBlocks.size();
    auto end = m_allBlocks.end();
    auto curIt = itBegin;
    do {
        curIt += 1;
        if (curIt == end) {
            curIt = m_allBlocks.begin();
        }
    } while (!(*curIt)->content.contains(text)
             && !(*curIt)->type.contains(text)
             && curIt != itBegin);
    return curIt - m_allBlocks.begin();
}

int BlockModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return m_blocks.count();
}

QVariant BlockModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_blocks.count())
        return QVariant();

    const auto& block = m_blocks[index.row()];
    if (role == TypeRole)
        return block->type;
    else if (role == ContentRole)
        return block->content;

    return QVariant();
}

void BlockModel::clear() {
    beginResetModel();
    m_blocks.clear();
    m_allBlocks.clear();
    endResetModel();
}

QHash<int, QByteArray> BlockModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[ContentRole] = "content";
    return roles;
}

bool BlockModel::canFetchMore(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return m_blocks.size() < m_allBlocks.size();
}

void BlockModel::fetchMore(const QModelIndex& parent) {
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
