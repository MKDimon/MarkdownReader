#ifndef CUSTOMBLOCKHANDLER_H
#define CUSTOMBLOCKHANDLER_H

#include <QString>
#include <QSharedPointer>
#include <QTextStream>
#include <QDebug>

#include "block.h"

class CustomBlockHandler {
public:
    virtual ~CustomBlockHandler() = default;

    // Проверяет, подходит ли строка для данного типа блока
    virtual bool matches(const QString &line) const = 0;

    // Обрабатывает строку(и) и возвращает блок
    virtual QSharedPointer<Block> processBlock(QTextStream &stream, const QString &line) const = 0;
};

#endif // CUSTOMBLOCKHANDLER_H
