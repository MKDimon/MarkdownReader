import QtQuick 2.15
import QtGraphicalEffects 1.15

Rectangle {
    id: buttonRoot
    color: "transparent"
    radius: 4
    opacity: mouseArea.containsMouse ? 0.8 : 1

    signal clicked

    property alias icon: iconItem.path

    Item {
        id: iconItem
        anchors.fill: parent

        property color color: Constants.secondaryElement
        property string path: ""

        Image {
            id: iconImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: iconItem.path
            visible: false // Скрываем исходное изображение, чтобы отображалась только закрашенная маска
        }

        ColorOverlay {
            anchors.fill: parent
            source: iconImage
            color: iconItem.color
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: buttonRoot.clicked();
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
