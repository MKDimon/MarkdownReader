#include "textblockhandler.h"

static const QString type = "text";

bool TextBlockHandler::matches(const QString &line) const {
    // Текстовый блок может быть любой строкой, которая не является специальным блоком
    return true;
}

QSharedPointer<Block> TextBlockHandler::processBlock(QTextStream &stream, const QString &line) const {
    return QSharedPointer<Block>::create(type, line.trimmed());
}
