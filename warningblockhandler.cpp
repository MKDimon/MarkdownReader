#include "warningblockhandler.h"

#include <QMap>

#include "warningblock.h"

static const QMap<QString, QString> types = {
    {"> [!WARNING]", "warning"},
    {"> [!CAUTION]", "caution"},
    {"> [!NOTE]", "note"},
    {"> [!TIP]", "tip"},
    {"> [!IMPORTANT]", "important"},
};

bool WarningBlockHandler::matches(const QString &line) const {
    for (const auto& type: types.keys()) {
        if (line.startsWith(type)) {
            tag = type;
            return true;
        }
    }
    return false;
}

QSharedPointer<Block> WarningBlockHandler::processBlock(QTextStream &stream, const QString &line) const {
    QString content = line.mid(tag.length()).trimmed();  // Извлекаем содержимое после [!WARNING]

    static const auto& isBeginningFromTag = [](const QList<QString>& tags, const QString& line) {
        return std::any_of(tags.begin(), tags.end(), [&line](const QString& tag) {
            return line.startsWith(tag);
        });
    };

    QString nextLine;
    auto pos = stream.pos();
    while (!stream.atEnd()) {
        nextLine = stream.readLine().trimmed();

        if (!nextLine.startsWith(">") || isBeginningFromTag(types.keys(), nextLine)) {
            stream.seek(pos);
            break;  // Прекращаем обработку, если следующая строка не является частью предупреждения
        }

        pos = stream.pos();
        content += "\n\n" + nextLine.mid(1).trimmed();
    }

    return QSharedPointer<WarningBlock>::create(content, types[tag]);
}
