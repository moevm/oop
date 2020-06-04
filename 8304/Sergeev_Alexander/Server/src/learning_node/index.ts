const http = require("http");
const WebSocket = require("ws");

const server = http.createServer();
const wss = new WebSocket.Server({ noServer: true });

wss.on("connection", function connection(ws, request, client) {
  ws.on("message", function message(msg) {
    console.log(`Received message ${msg} from user ${client}`);
  });
});

server.on("upgrade", function upgrade(request, socket, head) {
  authenticate(request, (err, client) => {
    if (err || !client) {
      socket.destroy();
      return;
    }

    wss.handleUpgrade(request, socket, head, function done(ws) {
      wss.emit("connection", ws, request, client);
    });
  });
});

server.listen(8080);
