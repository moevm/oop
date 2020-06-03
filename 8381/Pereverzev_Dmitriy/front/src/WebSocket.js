import openSocket from 'socket.io-client';

// const socket = openSocket('http://localhost:3030');
const socket = openSocket('http://192.168.0.178:3030');

// exports.socket = socket

if (!localStorage.getItem("userID"))
    localStorage.setItem("userID", `USER${(+new Date()).toString(16)}`)

socket.on('disconnect', () => {
    console.log("disconnect");
    socket.open();
});
socket.on('connect_error', (error) => {
    console.log("connect_error: " + error);
    socket.open();
});

socket.on("toStart", (data) => {
    console.log(data.error);
    window.location.hash = ''

})

socket.on('connect', async () => {
    console.log("connect");
    await socket.emit("save", localStorage.getItem("userID"))

});

export default socket;