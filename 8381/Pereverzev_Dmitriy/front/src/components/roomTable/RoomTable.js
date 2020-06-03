
import React, { Component } from 'react';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Paper from '@material-ui/core/Paper';
import { Link } from "react-router-dom";

import socket from "../../WebSocket.js"






class RoomTable extends Component {
    _isMounted = false;

    constructor(props) {
        super(props);
        this.handleClick = this.handleClick.bind(this);
        this.updateData = this.updateData.bind(this)
        this.state = {
            rows: {}
        }

        socket.on("tabel of GameRooms update", (data) => {
            console.log("tabel of GameRooms update")
            console.log(data)
            if (this._isMounted)
                this.setState({ rows: data })
            
            
            
        })
    }



    componentDidMount() {
        this._isMounted = true;
        this.updateData()

    }
    componentWillUnmount() {
        this._isMounted = false;
    }
    updateData() {
        socket.emit("command", { task: 8 })
    }

    handleClick(id, name) {

        
        
        
        
        

        socket.emit("command", {
            task: 1,
            params: {
                roomID: id,
                playerInfo: {
                    playerID: localStorage.getItem("userID"),
                    playerName: localStorage.getItem("userName"),
                }
            }
        })

    }


    render() {
        return (
            <div>
                <button onClick={this.updateData}>Update</button>

                <TableContainer component={Paper}>
                    <Table aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                <TableCell>Name</TableCell>
                                <TableCell align="right">ID</TableCell>
                                <TableCell align="right">Players</TableCell>
                                <TableCell align="right">size</TableCell>
                                <TableCell align="right">connect</TableCell>
                            </TableRow>
                        </TableHead>
                        <TableBody>
                            {Object.values(this.state.rows).map((elem) => {
                                return (
                                    <TableRow key={elem.roomID}>
                                        <TableCell component="th" scope="row"> {elem.roomName} </TableCell>
                                        <TableCell align="right">{elem.roomID}</TableCell>
                                        <TableCell align="right">{elem.players}</TableCell>
                                        <TableCell align="right">{elem.fieldSize}</TableCell>
                                        <TableCell align="right"><Link to={"/game/" + elem.roomID} onClick={() => { this.handleClick(elem.roomID, elem.roomName) }}>CON</Link></TableCell>
                                    </TableRow>
                                )
                            })}
                        </TableBody>
                    </Table>
                </TableContainer>
            </div>
        );
    };
}


export default RoomTable;
