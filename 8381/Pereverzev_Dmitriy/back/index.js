

const my_game = require('./gameCPP/build/Release/my_game_cpp.node');
const game = new my_game.UIFacade();
var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var path = require('path');


const PORT = 3030;


app.use(express.static(path.join(__dirname, '/../front/build/')));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/../front/build/index.html');
});


http.listen(PORT, function () {
    console.log(`Serever started on PORT ${PORT}!`);
});

var clients = {}



io.on('connection', (socket) => {
    console.log("*User connected*")



    socket.emit("toStart", { error: "start there" })


    socket.on('save', (id) => {
        clients[id] = socket;
        console.log("*User saved: " + id + "*")

    });


    socket.on('command', (data) => {
        console.log(data);
        if (data.task == 1)
            socket.join(data.params.roomID);
        let res = game.sendRequest(data)
        console.log(res);
        res.map(elem => {
            emitManager(socket, elem);
        })
    });




    socket.on('disconnect', () => {                             
        console.log("*User disconnected*")
        let userID = getPlayerIDBySocket(socket)
        console.log("*User removed: " + userID + "*")
        delete clients[userID]

    })



})










/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

function getPlayerIDBySocket(socket) {
    for (const [key, value] of Object.entries(clients))
        if (value.id == socket.id)
            return key
}

function emitManager(socket, data) {
    console.log(data);
    if (data.eventType == "object updated")
        io.to(data.data.roomID).emit(data.eventType, data.data);
    if (data.eventType == "tabel of GameRooms update")
        io.emit(data.eventType, data.data);
    if (data.eventType == "get full room")
        socket.emit(data.eventType, data.data);
}


function getFullRoomInfo(socket, roomID) {
    game.sendRequest({
        task: 5,
        params: {
            roomID: roomID,
        }
    })
}

