import React, { Component } from 'react';
import CellContainer from './cell/CellContainer.js';

import socket from "../../WebSocket.js"
import "./field.css";
import { array } from 'prop-types';

const BASE_WIDTH = window.innerWidth / 20;


class Field extends Component {
    _isMounted = false;
    scale = 1
    cells = Array()

    constructor(props) {

        super(props);
        this.cells = Array()
        
        this.state = {
            cells: (() => {
                let cells = [];
                props.field.forEach((row, rowI) =>
                    row.forEach((cell, cellI) =>
                        cells[rowI * props.field.length + cellI] = < CellContainer
                            size={BASE_WIDTH}
                            key={"CellContainer" + rowI + "_" + cellI}
                            id={rowI + "_" + cellI}
                            x={rowI}
                            y={cellI}
                            landscape={cell.landscape}
                            object={cell.object.type}
                        />
                    ));
                return cells;
            })(),
            roomID: props.id,
            form: {
                size: /* props.step || */ BASE_WIDTH,
                rows: props.field.length,
                columns: props.field[0].length,
            },
            
            /* {
                landscapes: props.landscape || [[]],
                objects: props.objects || [[]]
            } */
        }




        socket.on("object updated", (data) => {
            console.log("object updated");
            console.log(data);
            debugger
            
            
            
            
            
            
            
            
            
            
            if (this._isMounted) {

                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                this.setState(prevState => {
                    

                    
                    prevState.cells[data.objectInfo.x * this.state.form.rows + data.objectInfo.y] = < CellContainer
                        size={BASE_WIDTH}
                        key={"CellContainer" + data.objectInfo.x + "_" + data.objectInfo.y}
                        id={data.objectInfo.x + "_" + data.objectInfo.y}
                        x={data.objectInfo.x}
                        y={data.objectInfo.y}
                        landscape={/* props.field[data.objectInfo.x][data.objectInfo.y].landscape */0}
                        object={/* data.objectInfo.objectType */1}
                    />
                    return prevState
                })
            }

        })
        
        



        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        
        
        
        
        
        
        

        

        
        


        
        

        
        

        
        
        
        
        
        
        
        
        
        
        
        

        
        

        

        socket.emit("firstFieldBuildToS", { roomID: this.state.roomID })

    }

    componentDidMount() {


        this._isMounted = true;
        this.refs.mainField.style.height = (BASE_WIDTH * this.state.form.rows) + "px"
        this.refs.mainField.style.width = (BASE_WIDTH * this.state.form.columns) + "px"
        
    }
    componentWillUnmount() {


        this._isMounted = false;
    }

    
    
    

    
    
    
    
    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
    
    
    
    


    render() {

        


        

        
        
        

        
        
        
        
        
        
        
        
        
        
        
        


        return (

            <div key="fieldBoxKey" className="fieldBox unselectable" >
                <div key="fieldKey" className="field" ref="mainField" >
                    {/* {this.state.cells.map(elem => elem)} */}
                    {this.state.cells}
                    {/* 

                        this.state.fieldGrid.map((row, rowI) =>
                            row.map((cell, cellI) =>
                                <CellContainer
                                    size={BASE_WIDTH}
                                    key={"CellContainer" + rowI + "_" + cellI}
                                    id={rowI + "_" + cellI}
                                    x={rowI}
                                    y={cellI}
                                    landscape={cell.landscape}
                                    object={cell.object.type}
                                />
                            )
                        ) */
                    }

                </div>
            </div>
        )
    };
}


export default Field;

