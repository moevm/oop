const fs = require("fs");
const path = require("path");
const http = require('http');
const https = require('https');
const WebSocket = require("ws");
const query = require("cli-interact").getYesNo;
const nativeoop = require("bindings")("nativeoop");
const isWin = process.platform === "win32"; // https://stackoverflow.com/a/8684009/9398364

// Default data

if (!fs.existsSync("database.json")) {
    fs.writeFileSync("database.json", JSON.stringify({
        users : [ "NPC" ]
    }, null, 2));
}

if (!fs.existsSync("config.json")) {
    fs.writeFileSync("config.json", JSON.stringify({
        title: "Best Game Server",
        version: 106,
        ssl_key_linux: "../privkey.pem",
        ssl_cert_linux: "../fullchain.pem",
        ssl_key_win: "D:/openssl.key",
        ssl_cert_win: "D:/openssl.crt",
        port: 1109,
        delta_time: 1111,
        chat_capacity: 100,
        root_folder: "./root/",
        
    }, null, 2));
}

// Server

console.log("Server is loading...");

const database = JSON.parse(fs.readFileSync("database.json", "utf8"));
console.log(`Database loaded. ${Object.keys(database.users).length} users was registred so far.`);

const config = JSON.parse(fs.readFileSync("config.json", "utf8"));
console.log(`Config of ${config.title} was loaded. Opening ${config.port} port. Server tick every ${config.delta_time} ms`);
nativeoop.Start(JSON.stringify(config));
//********************************************************************************** */
// TEMP
// const wsstest = new WebSocket.Server({port: 1108});
// wsstest.on("connection", function connection(ws) {
//     console.log("RECIEVED TEST");
// });
//********************************************************************************** */
const requestListener = function (req, res) {
    res.writeHead(200);
    res.end('Hello, World!');
}
const httpServer = http.createServer(requestListener);
httpServer.listen(1107);
//********************************************************************************** */
// var handler2 = function (req, res) {
//     res.writeHead(200, {'Content-Type': 'text/plain'});
//     res.end('Панки хой\n');
// };
// const httpsPublic = https.createServer({
//     cert: fs.readFileSync(isWin ? config.ssl_cert_win : config.ssl_cert_linux, "utf8"),
//     key: fs.readFileSync(isWin ? config.ssl_key_win : config.ssl_key_linux, "utf8")
// });
// httpsPublic.addListener("request", handler2);
// httpsPublic.listen(443);
//********************************************************************************** */
var handler = function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end('Hello World\n');
};
const httpsServerTest = https.createServer({
    cert: fs.readFileSync(isWin ? config.ssl_cert_win : config.ssl_cert_linux, "utf8"),
    key: fs.readFileSync(isWin ? config.ssl_key_win : config.ssl_key_linux, "utf8")
});
httpsServerTest.addListener("request", handler);
httpsServerTest.listen(1108);
//********************************************************************************** */
// TEMP

const httpsServer = https.createServer({
    cert: fs.readFileSync(isWin ? config.ssl_cert_win : config.ssl_cert_linux),
    key: fs.readFileSync(isWin ? config.ssl_key_win : config.ssl_key_linux)
});
httpsServer.listen(config.port);

const connections = {};
const wss = new WebSocket.Server({ server: httpsServer });

console.time("uptime");
console.log(`-=${config.title} has started=-`);

wss.on("connection", function connection(ws) {
    console.log("RECIEVED")
    ws.on("message", function incoming(message) {
        Signal(ws, message);
    });
});

wss.on("close", function connection(ws) {
    // TODO remove connections with value ws or maybe check ws.readyState === WebSocket.OPEN
    //nativeoop.OnDisconnect(connections where player_uid : ws)
    console.log(`${ws} close`);
});

wss.on("error", function connection(ws) {
    console.log(`${ws} error`);
});


function Signal(ws, message) {
    let messageJson = JSON.parse(message);
    console.log(JSON.stringify(messageJson, null, 2));

    if (messageJson.version != config.version) {
        console.log(`! Message with version ${messageJson.version} from player ${messageJson.sender}`);
        ws.send(JSON.stringify({type: "out_connect", error: "Please download the latest version of the game"}));
        return;
    }

    if (!messageJson.hasOwnProperty("sender")) {
        if (!messageJson.hasOwnProperty("nickname")) {
            console.log(`! Message from unknown socket: ${message}`);
            ws.send(JSON.stringify({type: "out_connect", error: "Please send your nickname and then uid"}));
            return;
        }

        let nickname = messageJson.nickname;
        if (nickname == "") {
            console.log(`! Message from unknown socket: ${message} with empty nickname`);
            ws.send(JSON.stringify({type: "out_connect", error: "Please send your nickname and then uid"}));
            return;
        }
        if (!database.users.includes(nickname)) {
            // Register
            database.users.push(nickname);
        }

        ws.send(JSON.stringify({type: "out_connect", users: database.users})); // SecurEEty
        return;
    }
    // Login
    connections[messageJson.sender] = ws;

    // Logic
    let response = nativeoop.Signal(JSON.stringify(messageJson));
    ws.send(response);

    // TODO temporary
    //let responseJson = JSON.parse(response);
    //console.log(
    //    `signal ${message} \nRESPONSE\n ${JSON.stringify(responseJson, null, 2)} \n`
    //);
    // TODO
}

const GameLoop = function () {
    let response = nativeoop.Update();
    let responseObj = JSON.parse(response);

    // Server handling:
    config.delta_time = responseObj.delta_time;
    //console.log(`Loop ${config.delta_time}`);

    // Broadcast handling:
    wss.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(JSON.stringify(responseObj.broadcast));
        }
    });

    // Players handling:

    console.log("=====" + JSON.stringify(responseObj));
    for (let sessionId in responseObj.players_sessions) {
        for (let playerId in responseObj.players_sessions[sessionId]) {
            if (connections.hasOwnProperty(playerId)) {
                console.log(`\nsending ${JSON.stringify(responseObj.players_sessions[sessionId][playerId])}\n`)
                connections[playerId].send(JSON.stringify(responseObj.players_sessions[sessionId][playerId]))
            }
            else {
                console.log(`${playerId} (session ${sessionId}) doesn't connected`);
            }
        }
    }

    setTimeout(GameLoop, config.delta_time);
};

setTimeout(GameLoop, config.delta_time);

console.log("Server is working. Ctrl+C to stop the server");

function Stop() {
    console.log("Saving database...");
    fs.writeFileSync("database.json", JSON.stringify(database, null, 2));
    
    console.log("Saving config...");
    fs.writeFileSync("config.json", JSON.stringify(config, null, 2));
    
    console.timeLog("uptime")
    console.log(`-=${config.title} has stopped=-`);
    process.exit(0);
}

process.on('SIGINT', Stop);
process.on('SIGQUIT', Stop);
process.on('SIGTERM', Stop);