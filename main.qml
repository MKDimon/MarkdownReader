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
        anchors.fill: parent
        spacing: 5

        FolderDialog {
            id: changeRootFolderDialog

            onAccepted: {
                console.log(currentFolder)
                documentModel.loadRootDirectory(currentFolder)
            }
        }

        Row {
            id: settingsPanelRow

            IconButton {
                id: changeRootButton
                icon: Constants.add_new_folder
                height: 50
                width: 50
                onClicked: {
                    changeRootFolderDialog.open()
                }
            }
        }

        SplitView {
            id: splitter
            height: parent.height - changeRootButton.height
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
                    //elide: Text.ElideMiddle
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
                SplitView.minimumHeight: 100


                ListView {
                    id: filesListView
                    anchors.fill: parent
                    anchors.topMargin: 5
                    clip: true
                    model: DocumentTreeModel {
                        id: documentModel
                    }

                    spacing: 5

                    delegate: Rectangle {
                        id: fileRect
                        width: parent ? parent.width : 0
                        radius: 2
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        anchors.right: parent.right
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
                                    activeFile.setFile(model.path)
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
                SplitView.minimumHeight: 100
                clip: true

                ActiveFileComponent {
                    id: activeFile
                    anchors.fill: parent
                }
            }

        }
    }
}
