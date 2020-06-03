import React, { Component } from 'react';
import BaseObject from './components/BaseObject'
import Landscape from './components/Landscape'
import CellMenu from './components/CellMenu'



import "../field.css"





class CellContainer extends Component {
    constructor(props) {
        super(props);
        this.handleOpen = this.handleOpen.bind(this)
        this.handleClose = this.handleClose.bind(this)
        
        
        

        this.state = {
            id: props.id,
            form: {
                size: props.size /* || window.innerWidth / 10 */,
                x: props.x,
                y: props.y

            },
            content: {
                landscape: props.landscape,
                object: props.object
            },
            menu: false,

        }
    }
    componentDidUpdate() {
    }

    handleOpen = (event) => {
        this.setState({ menu: event.currentTarget });
    };

    handleClose = (event) => {
        this.setState({ menu: null });
    };

    /*     CreateBase() {
    
            socket.emit("CreateBase",{
                
            })
    
            this.handleClose()
        }
        CreateUnit() {
    
            socket.emit("CreateUnit",{
                
            })
    
            this.handleClose()
        }
        MoveUnit() {
    
            this.handleClose()
        }
    
        handleClose = () => {
            debugger
            this.setState({ anchorEl: null });
        }; */




    render() {
        const customKey = this.state.id.toString()


        return (
            <>
                <div key={customKey + "_"} id={this.props.id} className="cell" style={{ width: this.props.size, height: this.props.size }} onClick={this.handleOpen} >
                    <Landscape key={"landscape" + customKey.toString()} type={this.state.content.landscape} id={"landscape" + customKey.toString() + "id"} >

                        {<BaseObject key={"object" + customKey.toString()} type={this.props.object} id={"object" + customKey.toString() + "id"} size={this.props.size} />}
                    </Landscape>


                </div >
                {Boolean(this.state.menu) && <CellMenu x={this.props.x} y={this.props.y} close={this.handleClose} event={this.state.menu} />}
                {/* <Menu
                    id="simple-menu"
                    anchorEl={this.state.anchorEl}
                    keepMounted
                    open={Boolean(this.state.anchorEl)}
                    onClose={this.handleClose}
                >
                    <MenuItem onClick={this.handleClose}>Create Base</MenuItem>
                    <MenuItem onClick={this.handleClose}>Create Unit</MenuItem>
                    <MenuItem onClick={this.handleClose}>Move Unit</MenuItem>
                </Menu> */}
            </>
        )
    }
}


export default CellContainer;
