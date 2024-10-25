#ifndef VIDEOBLOCKHANDLER_H
#define VIDEOBLOCKHANDLER_H

#include "customblockhandler.h"

class VideoBlockHandler : public CustomBlockHandler {
public:
    bool matches(const QString &line) const override;

    QSharedPointer<Block> processBlock(QTextStream &stream, const QString &line) const override;
};

#endif // VIDEOBLOCKHANDLER_H
