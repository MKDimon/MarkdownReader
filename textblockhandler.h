#ifndef TEXTBLOCKHANDLER_H
#define TEXTBLOCKHANDLER_H

#include "customblockhandler.h"

class TextBlockHandler : public CustomBlockHandler {
public:
    bool matches(const QString &line) const override;

    QSharedPointer<Block> processBlock(QTextStream &stream, const QString &line) const override;
};

#endif // TEXTBLOCKHANDLER_H
