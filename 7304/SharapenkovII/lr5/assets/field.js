function setImpLevel(x, y, perm) {
    let hex = document.getElementById(x + "-" + y)
    if(perm < 10)
        hex.classList.add("hexagon-lvl-1")
    else if(perm < 20)
        hex.classList.add("hexagon-lvl-2")
    else if(perm < 30)
        hex.classList.add("hexagon-lvl-3")
    else if(perm < 40)
        hex.classList.add("hexagon-lvl-4")
    else if(perm < 50)
        hex.classList.add("hexagon-lvl-5")
    else if(perm < 60)
        hex.classList.add("hexagon-lvl-6")
}

function clearField() {
    let field = document.getElementsByClassName("field")[0]

    for(let i = 0; i < field.children.length; i++) {
        for(let j = 0; j < field.children[i].children.length; j++) {
            field.children[i].children[j].classList.remove("hexagon-picked")
        }
    } 
}



function showCurrentHexInfo(permeability) {
    let el = document.getElementById("picked-hex-info-imp")
    el.textContent = "Impediment: " + permeability
}

function showCurrentSecondHexInfo(permeability) {
    let el = document.getElementById("picked-second-hex-info-imp")
    el.textContent = "Impediment: " + permeability
}

function makeReachable(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.classList.add("hexagon-picked")
}

function setUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    let unit = document.createElement("div")
    unit.className = "unit"
    unit.style.backgroundColor = "black";
    hex.appendChild(unit)
}

function removeUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.removeChild(hex.children[0])
}

function showUnitInfo(attack, attack_type, health, energy, health_max, energy_max) {
    let el = document.getElementById("picked-unit-info")
    if(arguments.length == 0) {
        el.classList.add("hide")
        return
    } else {
        el.classList.remove("hide")
    }    

    el.children[1].textContent = "Attack: " + attack
    el.children[2].textContent = "Attack Type: " + attack_type
    el.children[3].textContent = "Health: " + health + "/" + health_max
    el.children[4].textContent = "Energy: " + energy + "/" + energy_max
}

function nextTurn(name) {
    let el = document.getElementById("current-turn-info")
    el.textContent = "Current turn: " + name
}

function updateNumOfMoves(num) {
    let el = document.getElementById("num-of-moves-info")
    el.textContent = "Number of moves: " + num
}

/*document.addEventListener('DOMContentLoaded', function(){ 
    createField(50)
}, false)*/

function createField(x) {
    let field = document.getElementsByClassName("field")[0]
    field.innerHTML = ""
    for(let i = 0; i < x; i++) {
        addFieldRow(field, x, i)
    }
}

function addFieldRow(field, x, y_coord) {
    let row = document.createElement("div")
    row.className = "hexagon-row"
    for(let i = 0; i < x; i++) {
        addFieldCell(row, i, y_coord)
    }
    field.appendChild(row)
}

function addFieldCell(row, x_coord, y_coord) {
    let cell = document.createElement("div")
    cell.className = "hexagon"
    cell.id = x_coord + "-" + y_coord
    cell.onclick = function() { 
            OnPickHex(x_coord, y_coord)
    }
    row.appendChild(cell)
}

function renderImp(x, y, imp_type) {
    let hex = document.getElementById(x + "-" + y)
    if(imp_type == "River") {
        hex.classList.add("hexagon-imp-river")
    } else if(imp_type == "Mountains") {
        hex.classList.add("hexagon-imp-mountains")
    } else if(imp_type == "Forest") {
        hex.classList.add("hexagon-imp-forest")
    } else if(imp_type == "Swamp") {
        hex.classList.add("hexagon-imp-swamp")
    } else if(imp_type == "Rain") {
        hex.classList.add("hexagon-imp-rain")
    } else if(imp_type == "Snow") {
        hex.classList.add("hexagon-imp-snow")
    } else if(imp_type == "Fog") {
        hex.classList.add("hexagon-imp-fog")
    }
}

function setUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    let unit = document.createElement("div")
    unit.className = "unit"
    unit.style.backgroundColor = "black";
    hex.appendChild(unit)
}

function removeUnit(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.removeChild(hex.children[0])
}

function renderUnit(x, y, unit_type, color) {
    let hex = document.getElementById(x + "-" + y)
    let unit = document.createElement("div")
    unit.style.backgroundColor = color;

    if(unit_type == "Archer") {
        unit.classList.add("hexagon-unit-archer")
    } else if(unit_type == "Tank") {
        unit.classList.add("hexagon-unit-tank")
    } else if(unit_type == "Knight") {
        unit.classList.add("hexagon-unit-knight")
    } else if(unit_type == "King") {
        unit.classList.add("hexagon-unit-king")
    } else if(unit_type == "Priest") {
        unit.classList.add("hexagon-unit-priest")
    } else if(unit_type == "Killer") {
        unit.classList.add("hexagon-unit-killer")
    }
    
    hex.appendChild(unit)
}

function makeReachable(x, y) {
    let hex = document.getElementById(x + "-" + y)
    hex.classList.add("hexagon-picked")
}