import QtQuick 2.0
import QtQuick 2.0
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.14
import game 1.0

Item {
    id: board
    anchors.fill: parent
    property int size_x: 10
    property int size_y: 10
    property int cell_size: 30
    signal loaded()
    property var state: {"invoking_cell": "empty", "target_cell": "empty"}
    property real transformScale: 1
    property real transformOriginX: 0
    property real transformOriginY: 0
    transform: Scale {origin.x: transformOriginX; origin.y: transformOriginY; xScale: transformScale; yScale: transformScale}
    function populateBoard(x, y) {
        size_x = x
        size_y = y
        console.log("abcdefg")
        UIConnector.initBoard(size_x, size_y, 10)
        for (let i = 0; i < board.size_y; i++) {
            for (let j = 0; j < board.size_x; j++) {
                var cell = UIConnector.getBoardUnitAtCell(j, i)
                var dict = {"_x": j, "_y": i, "_terrain_type": cell["terrain_unit"]["name"], "_pongo_type": cell["board_unit"]["name"]}
                if(cell["board_unit"]["hasStats"] === 1) {
                    dict["_hasStats"] = 1
                    dict["_health"] = cell["board_unit"]["stats"]["health"]
                    dict["_armor"] = cell["board_unit"]["stats"]["armor"]
                    dict["_attack"] = cell["board_unit"]["stats"]["attack"]
                }
                else {
                    dict["_hasStats"] = 0
                    dict["_health"] = 0
                    dict["_armor"] = 0
                    dict["_attack"] = 0
                }

                boardCellModel.append(dict)
            }
        }
        boardFrame.visible = true
        console.log("cells: " + boardGrid.count)
    }

    Connections {
        target: UIConnector
        onBoardChanged: {
            updateBoard()
        }
    }

    function updateBoard() {
        var cells = UIConnector.getUpdatedCells()
        cells.forEach(cell => {
                          var index = (cell["x"] + cell["y"]*board.size_x)
                          var mcell = boardCellModel.get(index)
                          mcell._terrain_type = cell["terrain_unit"]["name"]
                          mcell._pongo_type = cell["board_unit"]["name"]
                          if(cell["board_unit"]["name"] !== "empty" && cell["board_unit"]["hasStats"] === 1) {
                              mcell._hasStats = 1
                              mcell._health = cell["board_unit"]["stats"]["health"]
                              mcell._armor = cell["board_unit"]["stats"]["armor"]
                              mcell._attack = cell["board_unit"]["stats"]["attack"]
                          }
                          else {
                              mcell._hasStats = 0
                              mcell._health = 0
                              mcell._armor = 0
                              mcell._attack = 0
                          }
                          var bcell = boardGrid.itemAtIndex(index)
                          bcell.isSelected = false
                      }
                    )
    }

    function sendAction() {
        UIConnector.action(board.state)
        var index = (board.state["invoking_cell"]["x"] + board.state["invoking_cell"]["y"]*board.size_x)
        var bcell = boardGrid.itemAtIndex(index)
        bcell.isSelected = false
        board.state = {"invoking_cell": "empty", "target_cell": "empty"}
    }

    Rectangle {
        id: boardFrame
        visible: false
        width: parent.size_x * board.cell_size
        height: parent.size_y * board.cell_size
        //anchors {horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
        x: parent.width/2 - width/2
        y: parent.height/2 - height/2
        color: "white"
        //transform: Rotation {origin.x: window.width / 2; origin.y: window.height/2; angle: 20}    //ROFL
        GridView {
            BoardCellDelegate {
                id: boardCellDelegate
            }
            interactive: false
            anchors{fill: parent; horizontalCenter: parent.horizontalCenter; verticalCenter: parent.verticalCenter}
            id: boardGrid
            model: BoardCellModel {
                id: boardCellModel
            }
            delegate: boardCellDelegate
            cellHeight: board.cell_size
            cellWidth: board.cell_size
        }
    }
    MouseArea {
        anchors.fill: parent
        drag.filterChildren: true
        drag.target: boardFrame
        drag.axis: Drag.XAndYAxis
        propagateComposedEvents: true
        onClicked: {mouse.accepted = false}
        onPressed: {boardFrame.anchors.horizontalCenter = undefined; boardFrame.anchors.verticalCenter = undefined}
        onWheel: {
            board.transformOriginX = wheel.x
            board.transformOriginY = wheel.y
            if(wheel.angleDelta.y >= 0 && board.transformScale + wheel.angleDelta.y/900 <= 3)
                board.transformScale += wheel.angleDelta.y/900
            else if(wheel.angleDelta.y < 0 && board.transformScale - wheel.angleDelta.y/900 >= 0.5)
                board.transformScale += wheel.angleDelta.y/900
        }

    }
    Component.onCompleted: {
        loaded()
        console.log("wtf")
        //board.populateBoard()
    }
}
