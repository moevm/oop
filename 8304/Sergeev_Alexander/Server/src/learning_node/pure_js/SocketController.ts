import {SocketEvent} from './Constants';

export class SocketController {
    private socketHandler: SocketIO.Server;

    constructor(handler: SocketIO.Server) {
        this.socketHandler = handler;
        this.listen();
    }

    private listen(){
        this.socketHandler.on(SocketEvent.CONNECT, (socket:any) => {
            console.log("New player connected!");

            socket.on(SocketEvent.DISCONNECT, (socket:any) => {
                console.log("Player disconnected!");
            });

            socket.on(SocketEvent.SAY_HI, (data: any) => {
                console.log("player says: " + data.msg);
                
                this.socketHandler.sockets.emit(SocketEvent.SAY_HI, data);
                //socket.broadcast.emit(SocketEvent.SAY_HI, data.msg);
            });
        });
    }
}