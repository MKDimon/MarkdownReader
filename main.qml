import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import test.cadabra 1.0

Window {
    width: 420
    height: 780
    visible: true
    title: qsTr("Markdown Reader")
    color: Constants.primaryBackround

    property real heightCoefficient: 0.5

    Column {
        id: baseColumn
        anchors.fill: parent
        spacing: 5

        FolderDialog {
            id: changeRootFolderDialog

            onAccepted: {
                documentModel.loadRootDirectory(currentFolder)
            }
        }

        Row {
            id: settingsPanelRow
            height: fileNameRect.height
            spacing: 5

            IconButton {
                id: changeRootButton
                icon: Constants.add_new_folder
                height: parent.height
                width: 50
                onClicked: {
                    changeRootFolderDialog.open()
                }
            }

            Rectangle {
                id: fileNameRect
                anchors.margins: 5
                width: baseColumn.width - 60
                height: Math.max(fileNameText.contentHeight + 10, 50)
                radius: 4

                color: Constants.firstPanel

                TextEdit {
                    id: fileNameText
                    anchors.margins: 5
                    anchors.fill: parent
                    readOnly: true
                    width: parent.width
                    text: activeFile.filePath
                    font: Constants.font
                    wrapMode: Text.WordWrap
                    color: Constants.secondaryText
                }
            }
        }

        SplitView {
            id: splitter
            height: parent.height - settingsPanelRow.height - 2 * 5
            width: parent.width
            orientation: Qt.Vertical // Вертикальная ориентация (один блок над другим)
            //spacing: 0  // Убираем стандартное расстояние между компонентами

            // Кастомый Divider

            handle: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                color: Constants.secondaryBackground
                border.color: Constants.secondaryElement

                Text {
                    anchors.centerIn: parent
                    text: "|||"
                    font: Constants.font
                    color: Constants.secondaryText
                }
            }

            // Верхний блок (Иерархия файлов)
            Rectangle {
                id: filesRect
                anchors.margins: 5
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                color: Constants.firstPanel
                clip: true
                SplitView.preferredHeight: parent.height / 2

                SearchRow {
                    id: filesSearchRow
                    width: parent.width
                    anchors.top: parent.top
                    height: 50
                    anchors.margins: 5

                    onSearch: (text) => {
                                  documentModel.search(text)
                              }
                }

                ListView {
                    id: filesListView
                    anchors {
                        right: parent.right
                        left: parent.left
                        top: filesSearchRow.bottom
                        bottom: parent.bottom
                    }
                    anchors.topMargin: 5
                    clip: true
                    model: DocumentTreeModel {
                        id: documentModel
                    }

                    spacing: 5

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

                    delegate: Rectangle {
                        id: fileRect
                        width: parent ? parent.width : 0
                        radius: 2
                        anchors.left: if (parent) parent.left
                        anchors.leftMargin: 5
                        anchors.right: if (parent) parent.right
                        anchors.rightMargin: 5

                        height: 20
                        color: Constants.secondaryBackground

                        Text {
                            anchors.fill: parent
                            anchors.leftMargin: 5
                            id: fileName
                            text: '● '.repeat(model.level) + model.name
                            color: Constants.secondaryText
                            font: Constants.font
                        }

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                if (model.isDir) {
                                    documentModel.loadChildrenForItem(index)
                                } else {
                                    activeFile.filePath = model.path
                                }
                            }
                        }
                    }
                }

            }

            // Нижний блок (Просмотр активного файла)
            Rectangle {
                id: activeFileView
                color: "transparent"
                SplitView.preferredHeight: parent.height / 2
                clip: true

                ActiveFileComponent {
                    id: activeFile
                    anchors.fill: parent
                }
            }

        }
    }
}
