#ifndef WARNINGBLOCK_H
#define WARNINGBLOCK_H

#include "block.h"

class WarningBlock : public Block {
public:
    // Конструктор
    WarningBlock(const QString &blockContent, const QString &warningSeverity)
        : Block(warningSeverity, blockContent) {}

    // Переопределение метода renderAsText для предупреждений
    QString renderAsText() const override {
        return "Warning (" + type + "):\n" + content + "\n";
    }
};

#endif // WARNINGBLOCK_H
