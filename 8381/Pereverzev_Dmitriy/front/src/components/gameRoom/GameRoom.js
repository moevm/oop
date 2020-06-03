import React, { Component } from 'react';
import Field from '../field/Field.js';
import socket from "../../WebSocket.js"
import { lime } from '@material-ui/core/colors';



class GameRoom extends Component {
    _isMounted = false;
    constructor(props) {
        super(props);
        this.state = {
            name: '',
            id: window.location.hash.replace(/#\/.*\//, ''),
            field: [[{}]],
            players: []
        }
        socket.on("get full room", (data) => {
            console.log(data);
            // parse full room`s data
            //field
            let dataField = data.field;
            var field = new Array(dataField.rowsQuantity).fill([]);
            for (let row = 0; row < dataField.rowsQuantity; row++) {
                field[row] = new Array(dataField.columnsQuantity);
                for (let column = 0; column < dataField.columnsQuantity; column++) {
                    field[row][column] = {};
                    field[row][column].landscape = dataField.landscapes[row * dataField.columnsQuantity + column];
                    field[row][column].object = { type: "empty_" };
                }
            }
            dataField.resGens.concat(dataField.units).map(elem => {
                field[elem.x][elem.y].object = {
                    type: elem.objectType,
                    stats: elem.stats,
                    ID: elem.ID,
                }
            })

            var players = data.playersInfo.map(elem => {
                if (elem.base.ID != undefined)
                    field[elem.base.x][elem.base.y].object = {
                        type: elem.base.objectType,
                        stats: elem.base.stats,
                        ID: elem.base.ID,
                    }
                return {
                    resourceBag: elem.resourceBag,
                    playerName: elem.playerName,
                    playerID: elem.playerID,
                }
            })
            debugger;
            this._isMounted = true;
            this.setState({ field, players });

        })

        // })
        // // socket.emit("checkRoom", { roomID: window.location.hash.replace(/#\/.*\//, '') })

        // socket.on("gameRoomToCPlayers", (data) => {
        //     debugger
        //     if (this._isMounted)
        //         this.setState({ players: data.players })
        // })
        // socket.on("gameRoomToCFull", (data) => {

        // })
    }

    componentDidMount() {
        this._isMounted = true;
        socket.emit("command", {
            task: 5,
            params: {
                roomID: this.state.id,
            }
        })

    }

    componentWillUnmount() {
        this._isMounted = false;
        socket.emit("leaveTheRoom", { roomID: this.state.id })
    }

    render() {
        let playerList = []
        // debugger
        if (this.state.players)
            Object.values(this.state.players).forEach(elem =>
                playerList.push(
                    <li key={playerList.length}>
                        {elem}
                    </li>
                )
            )
        debugger;
        return (

            < div >
                <h1>Hello, {localStorage.getItem("userName")}</h1>
                <ul>
                    {this.state.players.map((elem, index) =>
                        <li key={index}>
                            {`${elem.playerName}#${elem.playerID}(${Object.values(elem.resourceBag).join('/')})`}
                        </li>
                    )}
                </ul>
                {this._isMounted ? <Field id={this.state.id} field={this.state.field} /> : ''}
            </div >






        )
    };
}


export default GameRoom;

