#ifndef VIDEOBLOCK_H
#define VIDEOBLOCK_H

#include "block.h"

class VideoBlock : public Block {
public:
    QString videoPath;  // Путь к видео

    // Конструктор
    VideoBlock(const QString &videoPath)
        : Block("video", videoPath), videoPath(videoPath) {}

    // Переопределение метода renderAsText для видео блоков
    QString renderAsText() const override {
        return "Video: " + videoPath + "\n";
    }
};

#endif // VIDEOBLOCK_H
