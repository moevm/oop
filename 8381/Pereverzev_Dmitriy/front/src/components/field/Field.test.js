import React, { Component } from 'react';
import CellContainer from './cell/CellContainer.js';
import PinchZoomPan from '../pinchZoomPan/PinchZoomPan.js';
import socket from "../../WebSocket.js"
import "./field.css";

const BASE_WIDTH = window.innerWidth / 20


class Field extends Component {
    _isMounted = false;
    scale = 1
    constructor(props) {
        super(props);
        
        
        this.addOnWheel = this.addOnWheel.bind(this);
        this.remOnWheel = this.remOnWheel.bind(this);
        this.state = {
            roomID: props.id,
            form: {
                size: /* props.step || */ BASE_WIDTH,
                rows: props.rows || 0,
                columns: props.columns || 0,
            },
            content: {
                landscapes: props.landscape || [[]],
                objects: props.objects || [[]]
            }
        }
        console.log(props);
        socket.on("firstFieldBuildToC", (data) => {
            if (this._isMounted) {
                console.log("field update: ")
                console.log(data)
                this.refs.mainField.style.height = (BASE_WIDTH * data.rows) + "px"
                this.refs.mainField.style.width = (BASE_WIDTH * data.columns) + "px"
                this.setState({
                    form: {
                        rows: data.rows,
                        columns: data.columns,
                    },
                    content: {
                        landscapes: data.landscape,
                        objects: data.objects,
                    }
                })
            }

        })

    }

    addOnWheel() {
        this.handler = (e) => {

            var delta = e.deltaY || e.detail || e.wheelDelta;

            

            if (delta > 0) {
                if (this.scale <= 2)
                    this.scale += 0.01;
            }
            else {
                if (this.scale >= 0.5)
                    this.scale -= 0.01;
            }
            
            clearTimeout(this.timer_1);

            this.timer_1 = setTimeout(() => {
            /*                      */console.log(`matrix(${this.scale}, 0, 0, ${this.scale}, ${BASE_WIDTH * this.state.form.columns * (this.scale - 1) / 2 || 0}, ${BASE_WIDTH * this.state.form.rows * (this.scale - 1) / 2 || 0})`);
                this.refs.mainField.style.transform = `matrix(${this.scale}, 0, 0, ${this.scale}, ${BASE_WIDTH * this.state.form.columns * (this.scale - 1) / 2 || 0}, ${BASE_WIDTH * this.state.form.rows * (this.scale - 1) / 2 || 0})`;
            }, 20)

            
            
            
            
            

            console.log("$$$$$$$$$$$$$$$$$$")
            console.log(this.refs.mainField.style.height)
            
            
            
            
            
            
            
            
            
            
            
            e.preventDefault();
        }
        if (this.refs.mainField.addEventListener) {
            if ('onwheel' in document) {
                
                this.refs.mainField.addEventListener("wheel", this.handler);
            } else if ('onmousewheel' in document) {
                
                this.refs.mainField.addEventListener("mousewheel", this.handler);
            } else {
                
                this.refs.mainField.addEventListener("MozMousePixelScroll", this.handler);
            }
        }
    }

    remOnWheel() {
        if (this.refs.mainField.removeEventListener) {
            if ('onwheel' in document) {
                
                this.refs.mainField.removeEventListener("wheel");
            } else if ('onmousewheel' in document) {
                
                this.refs.mainField.removeEventListener("mousewheel");
            } else {
                
                this.refs.mainField.removeEventListener("MozMousePixelScroll");
            }
        }
    }



    componentDidMount() {
        console.log("#field mount: #")

        this._isMounted = true;
        socket.emit("firstFieldBuildToS", { roomID: this.state.roomID })
        
    }
    componentWillUnmount() {
        this._isMounted = false;
        
    }



    render() {
        debugger


        var cells = [];
        debugger
        if (this.state.form.rows > 0 && this.state.form.columns > 0) {

            for (let i = 0; i < this.state.form.rows; i++)
                for (let j = 0; j < this.state.form.columns; j++) {
                    cells.push(<CellContainer
                        size={BASE_WIDTH}
                        key={i + "_" + j}
                        id={i + "_" + j}
                        landscape={this.state.content.landscapes[i][j] || "_empty"}
                        object={this.state.content.objects[i][j] || "_empty"}
                    />);
                }
        }

        return (
            
            
            
            
            
            
            
            
            
            
            
            
            
            

            
            
            
            
            (
                <div className="fieldBox unselectable" >
                    <div className="field" ref="mainField" >
                        {cells}
                    </div>
                </div>
            )



        )

    };
}


export default Field;

