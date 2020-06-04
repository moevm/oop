# Ironsphere server #

[![Inline Docs](http://inch-ci.org/github/caxapexac/IronsphereServer.svg?branch=master)](http://inch-ci.org/github/caxapexac/IronsphereServer)
[![Circle CI](https://circleci.com/gh/caxapexac/IronsphereServer.svg?style=shield)](https://circleci.com/gh/caxapexac/IronsphereServer)
[![Dependencies](https://david-dm.org/caxapexac/IronsphereServer.svg)](https://david-dm.org/caxapexac/IronsphereServer)
[![DevDependencies](https://david-dm.org/caxapexac/IronsphereServer/dev-status.svg)](https://david-dm.org/caxapexac/IronsphereServer#get_info=devDependencies)
[![Known Vulnerabilities](https://snyk.io/test/github/caxapexac/IronsphereServer/badge.svg?targetFile=package.json)](https://snyk.io/test/github/caxapexac/IronsphereServer?targetFile=package.json)
[![Maintainability](https://api.codeclimate.com/v1/badges/af8d9995f5c480c73273/maintainability)](https://codeclimate.com/github/caxapexac/IronsphereServer/maintainability)
[![Test Coverage](https://api.codeclimate.com/v1/badges/af8d9995f5c480c73273/test_coverage)](https://codeclimate.com/github/caxapexac/IronsphereServer/test_coverage)
[![Contributions Welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/caxapexac/IronsphereServer/issues)

# Important (installing environment on Unix) #

1. You need `npm install -g node-gyp` to compile native addons ([repo](https://github.com/nodejs/node-gyp)). This package provides a CLI to generate boilerplate code which is used to compile C or C++ code into Native Addon or DLL with .node extension.
2. You need to install [Python](https://www.python.org/) v2.7, v3.5, v3.6, or v3.7 (node-gyp uses it)
3. You need `make`
4. You need `gcc`

# Important (installing environment on ~~MustDie~~ Windows) #
0. ~~Папей гавна~~
1. `npm install -g node-gyp`
2. Install `Python 2.7`
3. `npm install -g --production windows-build-tools` OR `npm install --global --production windows-build-tools --vs2019`
4. INSTEAD OF step 3 you can install [Visual Studio Build Tools](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools) then `npm config set msvs_version 2019`
5. [Full guide](https://spin.atomicobject.com/2019/03/27/node-gyp-windows/)
6. OR [another guide](https://futurestud.io/tutorials/how-to-build-nodegyp-to-run-bcrypt-on-windows)

# Importand (development) #

1. `npm run build` to rebuild server
2. OR `npm run build-logic` (change inside for linux) to rebuild logic as terminal executable

# Importand (TODO) #

- node-gyp into [cmake.js](https://github.com/cmake-js/cmake-js)

# Important (deploy) #
1. `nano /etc/ssh/sshd_config` edit port (security)
2. Restart the server
2. `npm install -g forever`
3. 

99. npm run start-prod

# Линки #

## Сертификаты ##
- [openssl (working)](https://helpcenter.gsx.com/hc/en-us/articles/115015960428-How-to-Generate-a-Self-Signed-Certificate-and-Private-Key-using-OpenSSL)
- [openssl other 1](https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs)
- [openssl other 2](https://medium.com/the-new-control-plane/generating-self-signed-certificates-on-windows-7812a600c2d8)
- [certbot](https://blog.zackad.dev/en/2017/08/19/create-websocket-with-nodejs.html)
- [ws examples](https://www.npmjs.com/package/ws)
- []()
- []()


## Алгоритмы
- [Алгоритмы + гексы](https://www.redblobgames.com/)
- []()
- []()

## Unity
- [Unity node socket.io](https://www.youtube.com/watch?v=J0udhTJwR88)
- [Netease pomelo Unity](https://github.com/NetEase/UnitySocketIO)
- [GH Colyseus Unity](https://github.com/colyseus/colyseus-unity3d)

## C#
- [.NET Networking](https://metanit.com/sharp/net/1.1.php)
- [NativeWebSocket (WebGL+)](https://github.com/endel/NativeWebSocket)
- []()

## Node js
- [Node js guide](https://learn.javascript.ru/screencast/nodejs)
- [Websockets js](https://learn.javascript.ru/websocket)
- [GH WebSocket](https://github.com/websockets/ws)
- [GH Netease pomelo Node](https://github.com/NetEase/pomelo)
- [GH Colyseus Node](https://github.com/colyseus/colyseus)
- [WebSocket OR Socket.io](https://stackoverflow.com/questions/10112178/differences-between-socket-io-and-websockets)
- [WebSocket, Socket.io guide](https://davidwalsh.name/websocket)
- [GH node-gyp (PITA)](https://github.com/nodejs/node-gyp)
- [GH Cmake.js (try later)](https://github.com/cmake-js/cmake-js)
- []()


## C++
- [GH NAPI](https://github.com/nodejs/node-addon-api)
- [GH NAPI Examples](https://github.com/nodejs/node-addon-examples)
- [GH acutest unit tests](https://github.com/mity/acutest/tree/master/include)
- [GH Modern cpp guide](https://github.com/AnthonyCalandra/modern-cpp-features)
- [GH String pool](https://github.com/GiovanniDicanio/StringPool)
- [String allocating](https://stackoverflow.com/questions/26130941/stdstring-allocations-are-my-current-bottleneck-how-can-i-optimize-with-a)
- [GH googletest](https://github.com/google/googletest)
- []()

## Other
- [Firebase pros/cons](https://crisp.write_chat/blog/why-you-should-never-use-firebase-realtime-database/)
- [Webpack config](https://webpack.js.org/configuration/#options)
- [Webpack online config](https://createapp.dev/webpack)
- [GH REST API MySQL Generator](https://github.com/o1lab/xmysql/)
- [Networking in games 1](https://youtu.be/EU81tjgoKoI)
- [Networking in games 2](https://youtu.be/K3Z1PY2vr3Q)


# Todo #

First Connect:
// Id
// Lobby
// Ok -> json


//Wait
Game Start:
// json -> Map, Meta, Loop()

Meta Loop:
// Chat

Loop:
// My Units + Visible Units

Game End:
// All Units, Meta

Disconnect:
// Exception
