const fs = require('fs');

function findFiles(path, type) {
    return fs.readdirSync(path).map(f => {
        let p = path + '/' + f;
        return fs.lstatSync(p).isDirectory() ? findFiles(p, type) : p.match(type) ? p : '';
    }).join(' ');
}
console.log(findFiles("src", new RegExp((() =>
    process.argv.map((elem, index) => {
        return index >= 2 ? `(${elem}$)` : '';
    }).filter(Boolean).join('|')
)(), "mi")));
