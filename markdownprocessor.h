#ifndef MARKDOWNPROCESSOR_H
#define MARKDOWNPROCESSOR_H

#include <QObject>
#include <QString>

#include "blockmodel.h"

class MarkdownProcessor : public QObject {
    Q_OBJECT
    Q_PROPERTY(BlockModel* blockModel READ blockModel WRITE setBlockModel NOTIFY blockModelChanged FINAL)
    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

public:
    explicit MarkdownProcessor(QObject* parent = nullptr);

    QString filePath() const;
    void setFilePath(const QString& path);

    BlockModel* blockModel() const;
    void setBlockModel(BlockModel* model);

    QString content() const;

signals:
    void filePathChanged();
    void contentChanged();
    void blockModelChanged();

private:
    QString m_filePath;
    QString m_content;
    BlockModel* m_blockModel = nullptr;

    // Функция обработки файла
    void processFile();
    void parseMarkdown(QString& markdownText);
};

#endif // MARKDOWNPROCESSOR_H
