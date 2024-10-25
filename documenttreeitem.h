#ifndef DOCUMENTTREEITEM_H
#define DOCUMENTTREEITEM_H

#include <QString>
#include <QList>

class DocumentTreeItem {
public:
    DocumentTreeItem() = default;

    DocumentTreeItem(const QString &name, const QString &filePath, int level);

    DocumentTreeItem(const DocumentTreeItem&);
    DocumentTreeItem &operator=(const DocumentTreeItem&);

    const QString& name() const;
    const QString& filePath() const;
    bool isLoaded() const;
    int level() const;

    // Устанавливаем дочерние элементы
    void setChildren(const QList<DocumentTreeItem>& children);

    bool operator==(const DocumentTreeItem& item1);

    const QList<DocumentTreeItem>& children() const;

private:
    QString m_name;                       // Имя файла или папки
    QString m_filePath;                   // Полный путь к файлу или папке
    bool m_loaded;                        // Загружены ли дочерние элементы (для Lazy Load)
    int m_level;
    QList<DocumentTreeItem> m_children;   // Список дочерних элементов
};

#endif // DOCUMENTTREEITEM_H
