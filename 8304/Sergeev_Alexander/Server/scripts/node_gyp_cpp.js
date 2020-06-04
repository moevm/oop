const fs = require('fs');
function searchCpp(path) {
    return fs.readdirSync(path).map(f => {
        const p = path + '/' + f;
        if (fs.lstatSync(p).isDirectory()) return searchCpp(p);
        else if (p.includes('.cpp')) return (p);
        else return '';
    }).join(' ');
}
console.log(searchCpp('./src/native'));
