

const my_game = require('./gameCPP/build/Release/my_game_cpp.node');

const gameTest = new my_game.UIFacade();
var roomID = "ROOM" + Date.now();

console.log(gameTest.sendRequest({
    task: 0,
    params: {
        roomID: roomID,
        roomName: "KoKoKo33",
        editorID: "EDITOR1234567890",
        rule: 1,
        fieldInfo: {
            rowsQuantity: 8,
            columnsQuantity: 8,
            maximumObjectsQuantity: 100,
        }
    }
}))
console.log("-------------addU---------------");


console.log(gameTest.sendRequest({
    task: 1,
    params: {
        roomID: roomID,
        playerInfo: {
            playerID: "USER1234567890",
            playerName: "Banana12"
        }
    }
}))


console.log('1 created');

console.log(gameTest.sendRequest({
    task: 1,
    params: {
        roomID: roomID,
        playerInfo: {
            playerID: "USER123456789011111",
            playerName: "Banana121111"
        }
    }
}))



console.log(JSON.stringify(gameTest.sendRequest({
    task: 2,
    params: {
        roomID: roomID,
        playerID: "USER1234567890",
        objectType: 0,
        combatObjectInfo: {
            x: 1,
            y: 1,
            combatObjectType: 0,
        }
    }
})))



console.log(JSON.stringify(gameTest.sendRequest({
    task: 2,
    params: {
        roomID: roomID,
        playerID: "USER123456789011111",
        objectType: 0,
        combatObjectInfo: {
            x: 2,
            y: 2,
            combatObjectType: 0,
        }
    }
})))
































console.log(gameTest.sendRequest({
    task: 2,
    params: {
        roomID: roomID,
        playerID: "USER1234567890",
        objectType: 0,
        combatObjectInfo: {
            x: 2,
            y: 1,
            combatObjectType: 3,
        }
    }
}))



console.log(gameTest.sendRequest({
    task: 2,
    params: {
        roomID: roomID,
        editorID: "EDITOR1234567890",
        objectType: 1,
        neutralObjectInfo: {
            x: 1,
            y: 2,
            neutralObjectType: 7,
        }
    }
}))

























































































console.log("---------------SAVE-------------");

console.log(gameTest.sendRequest({
    task: 6,
    params: {
        roomID: roomID,
        editorID: "EDITOR1234567890",
    }
}))


console.log("---------------LOAD------------");
console.log((gameTest.sendRequest({
    task: 7,
    params: {
        roomID: roomID,
        editorID: "EDITOR1234567890",
        saveID: 0,
    }
})).map(elem => { console.log(JSON.stringify(elem)); console.log("_________________________"); }))

console.log("---------------SAVE-------------");

console.log(gameTest.sendRequest({
    task: 6,
    params: {
        roomID: roomID,
        editorID: "EDITOR1234567890",
    }
}))

console.log(JSON.stringify(gameTest.sendRequest({
    task: 5,
    params: {
        roomID: roomID,
    }
})))
















