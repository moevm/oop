import QtQuick 2.0

Item {
    Loader {
        id: boardLoader
        asynchronous: true
        anchors.fill: parent
    }

    Text {
        id: backButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 20
        text: "Back"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                boardLoader.source = ""
                mainAppStackView.pop()
            }
        }
    }
    Text {
        id: loadButton
        anchors.top: backButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Load"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                boardLoader.item.populateBoard(newGameMenu._boardWidth, newGameMenu._boardHeight)
            }
        }
    }
    Text {
        id: debugSwitchButton
        anchors.top: loadButton.bottom
        anchors.right: parent.right
        anchors.leftMargin: 20
        text: "Debug"
        font.pointSize: 32
        font.bold: true
        color: "white"
        style: Text.Outline
        styleColor: "orange"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {parent.color = "orange"}
            onExited: {parent.color = "white"}
            onClicked: {
                if(window._DEBUG_ === false)
                    window._DEBUG_ = true
                else
                    window._DEBUG_ = false
            }
        }
    }

    /*Rectangle {
        width: parent.width
        height: 150
        anchors{horizontalCenter: parent.horizontalCenter; bottom: parent.bottom }
    }*/
    onVisibleChanged: {
        if(visible) {
            boardLoader.source = "Board.qml"
        }
    }
}
