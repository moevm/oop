import {createServer, Server} from 'http';
import * as io from 'socket.io';
import {SocketController} from './socketController';

const nativeoop = require("bindings")("nativeoop");
console.log(nativeoop.Start("Hello1"));
console.log(nativeoop.Update("Hello2"));
console.log(nativeoop.Signal("Hello3"));
console.log(nativeoop.Destroy("Hello4"));

export class SocketServer {
    public static readonly PORT:number = 2222;
    private socketController:SocketController;
    private httpConnection:Server;
    private socketHandler:SocketIO.Server;

    constructor() {
        this.httpConnection = createServer();
        this.socketHandler = io(this.httpConnection);
        this.socketController = new SocketController(this.socketHandler);
        this.listen();
    }

    private listen() : void {
        this.httpConnection.listen(SocketServer.PORT, () => {
            console.log("Server listening at port %d", SocketServer.PORT);
        });
    }
}