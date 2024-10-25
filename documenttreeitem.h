#ifndef DOCUMENTTREEITEM_H
#define DOCUMENTTREEITEM_H

#include <QString>
#include <QList>

class DocumentTreeItem {
public:
    // Конструктор по умолчанию
    DocumentTreeItem() = default;

    // Конструктор для инициализации элемента
    DocumentTreeItem(const QString &name, const QString &filePath, bool isDir, int level)
        : m_name(name), m_filePath(filePath), m_isDir(isDir), m_loaded(false), m_level(level) {}

    // Копирующий конструктор и оператор присваивания
    DocumentTreeItem(const DocumentTreeItem &) = default;
    DocumentTreeItem &operator=(const DocumentTreeItem &) = default;

    // Методы доступа
    const QString &name() const { return m_name; }
    const QString &filePath() const { return m_filePath; }
    bool isDir() const { return m_isDir; }
    bool isLoaded() const { return m_loaded; }
    int level() const { return m_level; }

    // Устанавливаем дочерние элементы
    void setChildren(const QList<DocumentTreeItem> &children) {
        m_children = children;
        m_loaded = true;
    }

    bool operator==(const DocumentTreeItem& item1) {
        return this->m_name == item1.m_name && this->m_filePath == item1.m_filePath
               && this->m_loaded == item1.m_loaded && this->m_isDir == item1.m_isDir;
    }

    const QList<DocumentTreeItem> &children() const { return m_children; }

private:
    QString m_name;                       // Имя файла или папки
    QString m_filePath;                   // Полный путь к файлу или папке
    bool m_isDir;                         // Является ли элемент директорией
    bool m_loaded;                        // Загружены ли дочерние элементы (для Lazy Load)
    int m_level;
    QList<DocumentTreeItem> m_children;   // Список дочерних элементов
};

#endif // DOCUMENTTREEITEM_H
