pragma Singleton
import QtQuick 2.15

QtObject {
    readonly property font font: Qt.font({
                                        family: "Helvetica",
                                        pointSize: 13
                                    });

    readonly property color primaryBackround: "#333333"
    readonly property color secondaryBackground: "#191919"
    readonly property color primaryText: "#FFFFFF"
    readonly property color secondaryText: "#A2A7A7"
    readonly property color firstButton: "#000000"
    readonly property color firstPanel: "#262626"
    readonly property color secondPanel: "#121212"
    readonly property color firstElement: "#FFFFFF"
    readonly property color secondaryElement: "#A2A7A7"
    readonly property color selectedElement: "#3A3A3A"
    readonly property color videoFoneColor: "#24404c"

    readonly property string add_new_folder: "qrc:/add_new_folder.svg"
}
