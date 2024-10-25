#ifndef WARNINGBLOCKHANDLER_H
#define WARNINGBLOCKHANDLER_H

#include "customblockhandler.h"

class WarningBlockHandler : public CustomBlockHandler {
private:
    mutable QString tag;
public:
    bool matches(const QString &line) const override;

    QSharedPointer<Block> processBlock(QTextStream &stream, const QString &line) const override;
};

#endif // WARNINGBLOCKHANDLER_H
