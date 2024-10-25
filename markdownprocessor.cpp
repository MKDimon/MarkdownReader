#include "markdownprocessor.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextStream>
#include <cmark.h>

#include "blockhandlers.h"

static const QList<QSharedPointer<CustomBlockHandler>> blockHandlers = {
    QSharedPointer<WarningBlockHandler>::create(),
    QSharedPointer<VideoBlockHandler>::create(),
    QSharedPointer<TextBlockHandler>::create()
};


MarkdownProcessor::MarkdownProcessor(QObject *parent)
    : QObject{parent}
{}

QString MarkdownProcessor::filePath() const { return m_filePath; }

void MarkdownProcessor::setFilePath(const QString& path) {
    if (m_filePath != path) {
        m_filePath = path;
        emit filePathChanged();
        processFile(); // Обрабатываем файл сразу при изменении пути
    }
}

QString MarkdownProcessor::content() const { return m_content; }

BlockModel* MarkdownProcessor::blockModel() const {
    return m_blockModel;
}

void MarkdownProcessor::setBlockModel(BlockModel* model) {
    m_blockModel = model;
    emit blockModelChanged();
}

void MarkdownProcessor::processFile() {
    if (m_filePath.isEmpty()) return;

    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file:" << m_filePath;
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QString markdownContent = in.readAll();
    file.close();

    if (m_blockModel) {
        parseMarkdown(markdownContent);
        emit contentChanged();
    }
}

void MarkdownProcessor::parseMarkdown(QString& markdownText) {
    QList<QSharedPointer<Block>> blocks;
    QTextStream stream(&markdownText);
    QString line;

    while (!stream.atEnd()) {
        line = stream.readLine();
        bool handled = false;

        for (const auto &handler : blockHandlers) {
            if (handler->matches(line)) {
                auto block = handler->processBlock(stream, line);
                blocks.append(block);
                handled = true;
                break;
            }
        }

        // Если строка не обработана, обрабатываем как обычный текстовый блок
        if (!handled) {
            blocks.append(QSharedPointer<Block>::create("text", line));
        }
    }

    m_blockModel->initializeBlocks(blocks);
}
