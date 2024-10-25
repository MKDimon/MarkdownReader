#include "documenttreeitem.h"

DocumentTreeItem::DocumentTreeItem(const QString &name, const QString &filePath, int level)
    : m_name(name), m_filePath(filePath), m_loaded(false), m_level(level) {}

DocumentTreeItem::DocumentTreeItem(const DocumentTreeItem &) = default;

DocumentTreeItem& DocumentTreeItem::operator=(const DocumentTreeItem &) = default;

// Методы доступа
const QString& DocumentTreeItem::name() const {
    return m_name;
}

const QString& DocumentTreeItem::filePath() const {
    return m_filePath;
}

bool DocumentTreeItem::isLoaded() const {
    return m_loaded;
}

int DocumentTreeItem::level() const {
    return m_level;
}

// Устанавливаем дочерние элементы
void DocumentTreeItem::setChildren(const QList<DocumentTreeItem>& children) {
    m_children = children;
    m_loaded = true;
}

bool DocumentTreeItem::operator==(const DocumentTreeItem& item1) {
    return this->m_name == item1.m_name && this->m_filePath == item1.m_filePath
           && this->m_loaded == item1.m_loaded;
}

const QList<DocumentTreeItem>& DocumentTreeItem::children() const {
    return m_children;
}
