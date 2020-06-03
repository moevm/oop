import React, { Component } from 'react';
import {
    HashRouter,
    Switch,
    Route,
    Link
} from "react-router-dom";
import Menu from "./components/menu/Menu.js"
import Field from "./components/field/Field.js"
import UserData from "./components/user/UserData.js"
import NewRoom from "./components/newRoom/NewRoom.js"
import RoomTable from "./components/roomTable/RoomTable.js"
import GameRoom from "./components/gameRoom/GameRoom.js"
import socket from "./WebSocket.js"




let rows = 15, cols = 3,
    objects = Array(rows).fill(Array(cols).fill('o').map((e, i) => e + (i % 2 + 1))),
    landscape = Array(rows).fill(Array(cols).fill('l').map((e, i) => e + (i % 2 + 1)));


class App extends Component {

    constructor(props) {
        super(props);
        let newID = `USER${(+new Date()).toString(16)}`;
        this.state = {
            saved: false,
            user: {
                ID: localStorage.getItem("userID") || (() => {
                    localStorage.setItem("userID", newID)
                    return newID
                })(),
                name: localStorage.getItem("userName") || localStorage.getItem("userID")
            }
        }
    }

    componentDidMount() {
        socket.on("toC", data => {
            console.log("client ok")

        })
        console.log('kek app');

    }



    render() {
        return (
            <HashRouter >
                <div>
                    <ul>
                        <li>
                            <Link to="/">Menu</Link>
                        </li>
                    </ul>

                    <Switch>
                        <Route path="/start">
                            <Field
                                rows={landscape.length}
                                columns={landscape[0].length}
                                landscape={landscape}
                                objects={objects}
                            />
                        </Route>

                        <Route path="/menu">
                            <Menu type="Start" />
                        </Route>

                        <Route path="/userData">
                            <UserData />
                        </Route>

                        <Route path="/newRoom">
                            <NewRoom /* ws={this.ws} */ />
                        </Route>

                        <Route path="/rooms">
                            <RoomTable />
                        </Route>

                        <Route path="/game">
                            <GameRoom />
                        </Route>

                        <Route path="/">
                            <Menu type="Start" />
                        </Route>

                    </Switch>
                </div>
            </HashRouter  >
        );
    }
}


export default App;
