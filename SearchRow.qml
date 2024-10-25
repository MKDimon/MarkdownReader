import QtQuick 2.15
import QtQuick.Controls 2.15

Row {
    id: searchRow
    height: 50
    spacing: 5

    property string title: "Поиск"

    signal search(input: string)

    IconButton {
        id: searchButton
        icon: Constants.search_icon
        height: parent.height
        width: parent.height
        onClicked: {
            console.log("Search")
            parent.search(searchTextField.text)
        }
    }

    TextField {
        id: searchTextField
        color: Constants.secondaryText
        placeholderText: qsTr(searchRow.title)
        placeholderTextColor: Constants.secondaryText
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter

        width: parent.width - searchButton.width - 10
        height: parent.height
        leftPadding: 5
        rightPadding: 0
        text: ""
        font: Constants.font

        background : Rectangle {
            color: Constants.secondaryBackground
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_Escape) {
                if (text !== "") {
                    text = ""
                }
            }
            else if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                search(text)
            }
        }
    }

}
