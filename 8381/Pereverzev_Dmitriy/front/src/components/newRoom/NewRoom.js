import React, { Component } from 'react';
import { Link } from "react-router-dom";

import socket from "../../WebSocket.js"

import "./newRoom.css"



class NewRoom extends Component {
    constructor(props) {
        super(props);
        this.handleClick = this.handleClick.bind(this);
        this.genName = this.genName.bind(this);
        this.createRoom = this.createRoom.bind(this)

        this.state = {
            name: 'edit name',
            row: '50',
            column: '50',
            rule: '1',
        }



    }

    componentDidMount() {
    }

    genName() {
        let room = '';
        while (room.length < 10) room += "abcdefghijklmnopqrstuvwxyz1234567890"[Math.floor(Math.random() * 36)];
        this.refs.roomInput.value = room
        this.handleClick("name");
    }

    handleClick(elem) {
        switch (elem) {
            case "row": {
                this.setState({ row: this.refs.rowsInput.value })
                break
            }
            case "column": {
                this.setState({ column: this.refs.columnsInput.value })
                break
            }
            case "name": {
                this.setState({ name: this.refs.roomInput.value })
                break
            }
            case "rule": {
                this.setState({ rule: this.refs.ruleInput.value })
                break
            }
            default: {
                console.log("none")
                break
            }
        }
    }


    async createRoom() {
        socket.emit("command", {
            task: 0,
            params: {
                roomID: "ROOM" + Date.now(),
                roomName: this.state.name,
                editorID: localStorage.getItem("userID"),
                rule: parseInt(this.state.rule),
                fieldInfo: {
                    rowsQuantity: parseInt(this.state.row),
                    columnsQuantity: parseInt(this.state.column),
                    maximumObjectsQuantity: 100,
                }
            }
        }
        )

    }


    render() {
        return (
            <div className="newGame">
                <h3>New Game</h3>
                <div className="newGameConf">
                    <hr width="80%" />
                    <div>
                        <p>Room name: {this.state.name}</p>
                        <input ref="roomInput" type="text" maxLength="255" onChange={() => { this.handleClick("name") }} />
                        <button onClick={this.genName}>Generate Name</button>

                    </div>
                    <div>
                        <label>Number of rows: {this.state.row}</label>
                        <p>1 <input ref="rowsInput" type="range" min={10} max={100} onChange={() => { this.handleClick("row") }} /> 100</p>
                    </div>

                    <div>
                        <label>Number of columns: {this.state.column}</label>
                        <p>1 <input ref="columnsInput" type="range" min={10} max={100} onChange={() => { this.handleClick("column") }} /> 100</p>

                    </div>
                    <div>
                        <label>Rule: {this.state.rule}</label>
                        <p>0 <input ref="ruleInput" type="range" min={0} max={1} onChange={() => { this.handleClick("rule") }} /> 1</p>

                    </div>

                    <hr width="40%" />

                    <Link to="/rooms" onClick={this.createRoom}>Generate Room</Link>
                </div>
            </div>
        )
    };
}


export default NewRoom;
