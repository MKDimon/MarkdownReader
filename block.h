#ifndef BLOCK_H
#define BLOCK_H

#include <QString>
#include <QMap>

class Block {
public:
    QString type;             // Тип блока: "warning", "video", "text" и т.д.
    QString content;          // Содержимое блока (может быть текст, путь к видео и т.д.)
    QMap<QString, QString> params;  // Дополнительные параметры, если есть

    // Конструктор
    Block(const QString &blockType, const QString &blockContent)
        : type(blockType), content(blockContent) {}

    // Функция для рендеринга блока в текстовом виде (для отладки)
    virtual QString renderAsText() const {
        return "Block Type: " + type + "\nContent: " + content + "\n";
    }

    // Виртуальный деструктор, чтобы поддерживать полиморфизм
    virtual ~Block() = default;

    // Дополнительные функции, если нужны
};

#endif // BLOCK_H
