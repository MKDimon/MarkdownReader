#include "videoblockhandler.h"

#include "videoblock.h"

bool VideoBlockHandler::matches(const QString &line) const {
    return line.startsWith("[video src=");
}

QSharedPointer<Block> VideoBlockHandler::processBlock(QTextStream &stream, const QString &line) const {
    // Извлекаем путь к видео из тега
    int start = line.indexOf("\"") + 1;
    int end = line.lastIndexOf("\"");
    QString videoPath = line.mid(start, end - start);

    return QSharedPointer<VideoBlock>::create(videoPath);
}
