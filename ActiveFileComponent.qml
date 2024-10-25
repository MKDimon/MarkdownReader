import QtQuick 2.15
import QtMultimedia 5.15
import QtQuick.Controls 2.15
import test.cadabra 1.0

Item {
    id: activeFileItem

    property alias filePath: markdownProcessor.filePath

    BlockModel {
        id: blockModel
    }

    Rectangle {
        id: blocksListRect
        anchors.fill: parent
        anchors.margins: 5
        radius: 2
        clip: true

        color: Constants.firstPanel

        SearchRow {
            id: activeFileSearchRow
            width: parent.width
            anchors.top: parent.top
            height: 50
            anchors.margins: 5

            onSearch: (text) => {
                          if (blocksListView.currentIndex === -1)  {
                              blocksListView.currentIndex = 0
                          }

                          var index = blockModel.searchWithIndex(text, blocksListView.currentIndex)
                          blocksListView.currentIndex = index
                      }
        }

        ListView {
            id: blocksListView
            model: blockModel
            anchors {
                right: parent.right
                left: parent.left
                top: activeFileSearchRow.bottom
                topMargin: 5
                bottom: parent.bottom
            }
            clip: true
            spacing: 5

            onCurrentIndexChanged: {
                blocksListView.positionViewAtIndex(currentIndex, blocksListView.Beginning)
            }

            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                width: 10
                active: hovered || pressed
                hoverEnabled: true
                orientation: Qt.Vertical
                anchors {
                    right: parent.right
                    rightMargin: 5
                    verticalCenter: parent.verticalCenter
                }
                background: Rectangle {
                    implicitWidth: 10
                    color: "transparent"
                    radius: 5
                }
                contentItem: Rectangle {
                    width: 10
                    color: Constants.secondaryElement
                    radius: 5
                }
            }

            delegate: Item {
                width: blockLoader.item.width
                anchors.left: {
                    if (parent) {
                        parent.left
                    }
                }
                anchors.leftMargin: 5
                height: blockLoader.item.implicitHeight

                Loader {
                    id: blockLoader
                    anchors.fill: parent

                    sourceComponent: blockComponentChooser(model.type) // Функция выбора компонента

                    onLoaded: {
                        item.content = model.content; // Передаем контент (путь к видео)
                    }
                }
            }
        }
    }

    Component {
        id: warningComponent
        Item {
            id: warningItem
            property var content
            width: parent.width

            implicitHeight: warningTextColumn.height

            Row {
                spacing: 5
                anchors.fill: parent
                anchors.leftMargin: 10

                Rectangle {
                    id: warningColumn
                    width: 10
                    height: warningTextColumn.height
                    color: "orange"  // Полоса сбоку для блока предупреждения
                }

                Column {
                    id: warningTextColumn
                    anchors.leftMargin: 15
                    width: parent.width - 20
                    spacing: 5

                    TextEdit {
                        id: warningText
                        readOnly: true
                        text: "⚠ WARNING"
                        color: "orange"
                        font: Constants.font
                        //font.bold: true
                    }

                    TextEdit {
                        id: warningContentText
                        readOnly: true
                        text: warningItem.content  // Текст предупреждения
                        wrapMode: Text.WordWrap
                        width: parent.width - 40
                        textFormat: TextEdit.MarkdownText
                        font: Constants.font
                        color: Constants.secondaryText
                    }
                }
            }
        }
    }

    Component {
        id: tipComponent
        Item {
            id: tipItem
            property var content
            width: parent.width

            implicitHeight: tipTextColumn.height

            Row {
                spacing: 5
                anchors.fill: parent
                anchors.leftMargin: 10

                Rectangle {
                    id: tipColumn
                    width: 10
                    height: tipTextColumn.height
                    color: "green"  // Полоса сбоку для блока предупреждения
                }

                Column {
                    id: tipTextColumn
                    anchors.leftMargin: 15
                    width: parent.width - 20
                    spacing: 5

                    TextEdit {
                        id: tipText
                        readOnly: true
                        text: "💡 Tip"
                        //font.bold: true
                        color: "green"
                        font: Constants.font
                    }

                    TextEdit {
                        id: tipContentText
                        readOnly: true
                        text: tipItem.content  // Текст предупреждения
                        wrapMode: Text.WordWrap
                        width: parent.width - 40
                        textFormat: TextEdit.MarkdownText
                        font: Constants.font
                        color: Constants.secondaryText
                    }
                }
            }
        }
    }

    Component {
        id: importantComponent
        Item {
            id: importantItem
            property var content
            width: parent.width

            implicitHeight: importantTextColumn.height

            Row {
                spacing: 5
                anchors.fill: parent
                anchors.leftMargin: 10

                Rectangle {
                    id: importantColumn
                    width: 10
                    height: importantTextColumn.height
                    color: "purple"  // Полоса сбоку для блока предупреждения
                }

                Column {
                    id: importantTextColumn
                    anchors.leftMargin: 15
                    width: parent.width - 20
                    spacing: 5

                    TextEdit {
                        id: importantText
                        readOnly: true
                        text: "📩 Important"
                        //font.bold: true
                        color: "purple"
                        font: Constants.font
                    }

                    TextEdit {
                        id: importantContentText
                        readOnly: true
                        text: importantItem.content  // Текст предупреждения
                        wrapMode: Text.WordWrap
                        width: parent.width - 40
                        textFormat: TextEdit.MarkdownText
                        font: Constants.font
                        color: Constants.secondaryText
                    }
                }
            }
        }
    }

    Component {
        id: noteComponent
        Item {
            id: noteItem
            property var content
            width: parent.width

            implicitHeight: noteTextColumn.height

            Row {
                spacing: 5
                anchors.fill: parent
                anchors.leftMargin: 10

                Rectangle {
                    id: noteColumn
                    width: 10
                    height: noteTextColumn.height
                    color: "blue"  // Полоса сбоку для блока предупреждения
                }

                Column {
                    id: noteTextColumn
                    anchors.leftMargin: 15
                    width: parent.width - 20
                    spacing: 5

                    TextEdit {
                        id: noteText
                        readOnly: true
                        text: "📝 Note"
                        //font.bold: true
                        color: "blue"
                        font: Constants.font
                    }

                    TextEdit {
                        id: noteContentText
                        readOnly: true
                        text: noteItem.content  // Текст предупреждения
                        wrapMode: Text.WordWrap
                        width: parent.width - 40
                        textFormat: TextEdit.MarkdownText
                        font: Constants.font
                        color: Constants.secondaryText
                    }
                }
            }
        }
    }

    Component {
        id: cautionComponent
        Item {
            id: cautionItem
            property var content
            width: parent.width

            implicitHeight: cautionTextColumn.height

            Row {
                spacing: 5
                anchors.fill: parent
                anchors.leftMargin: 10

                Rectangle {
                    id: cautionColumn
                    width: 10
                    height: cautionTextColumn.height
                    color: "red"  // Полоса сбоку для блока предупреждения
                }

                Column {
                    id: cautionTextColumn
                    anchors.leftMargin: 15
                    width: parent.width - 20
                    spacing: 5

                    TextEdit {
                        id: cautionText
                        readOnly: true
                        text: "❗ Caution"
                        //font.bold: true
                        color: "red"
                        font: Constants.font
                    }

                    TextEdit {
                        id: cautionContentText
                        readOnly: true
                        text: cautionItem.content  // Текст предупреждения
                        wrapMode: Text.WordWrap
                        width: parent.width - 40
                        textFormat: TextEdit.MarkdownText
                        font: Constants.font
                        color: Constants.secondaryText
                    }
                }
            }
        }
    }

    // Определение компонентов для каждого типа блока
    Component {
        id: videoBlockComponent

        Rectangle {
            id: videoRect
            property var content
            implicitHeight: 200
            width: implicitHeight * 2
            color: Constants.videoFoneColor

            VideoOutput {
                id: video
                height: parent.implicitHeight
                anchors.fill: parent
                fillMode: VideoOutput.PreserveAspectFit

                MediaPlayer {
                    source: videoRect.content // Путь к видеофайлу
                    autoPlay: true
                    videoOutput: video
                }
            }
        }
    }

    Component {
        id: textBlockComponent
        TextEdit  {
            height: implicitHeight
            property var content
            readOnly: true
            text: content
            textFormat: TextEdit.MarkdownText
            anchors.bottomMargin: 5
            font: Constants.font
            color: Constants.secondaryText
        }
    }

    MarkdownProcessor {
        id: markdownProcessor
        blockModel: blockModel
    }

    // Функция выбора компонента на основе типа блока
    function blockComponentChooser(blockType, content) {
        switch (blockType) {
        case "video":
            return videoBlockComponent;
        case "text":
            return textBlockComponent;
        case "warning":
            return warningComponent;
        case "tip":
            return tipComponent;
        case "caution":
            return cautionComponent;
        case "important":
            return importantComponent;
        case "note":
            return noteComponent;

        default:
            return textBlockComponent; // По умолчанию текстовый блок
        }
    }
}
