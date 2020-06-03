import React from 'react';
// import Button from '@material-ui/core/Button';
import Menu from '@material-ui/core/Menu';
import MenuItem from '@material-ui/core/MenuItem';
import UnitMenu from './UnitMenu';
import socket from '../../../../WebSocket';
import { create } from 'domain';


export default function CellMenu(props) {
    const [anchorEl, setAnchorEl] = React.useState(props.event);

    let menu = false;


    const handleClick = (event) => {
        setAnchorEl(event.currentTarget);
    };

    const handleClose = () => {
        props.close();
        // setAnchorEl(null);
    };

    const CreateBase = () => {

        CreateUnit("BASE")

        handleClose()
    }
    const CreateUnit = (type) => {
        console.log(type)
        let uintType = 0;
        switch (type) {
            case "BASE":
                uintType = 0;
                break;
            case "ARCH_TANK":
                uintType = 1;
                break;
            case "ARCH_DPS":
                uintType = 2;
                break;
            case "INF_TANK":
                uintType = 3;
                break;
            case "INF_DPS":
                uintType = 4;
                break;
            case "CAV_TANK":
                uintType = 5;
                break;
            case "CAV_DPS":
                uintType = 6;
                break;
            default:
                uintType = 1;
        }

        socket.emit("command", {
            task: 2,
            params: {
                roomID: window.location.hash.replace(/#\/.*\//, ''),
                playerID: localStorage.getItem("userID"),
                objectType: 0,
                combatObjectInfo: {
                    x: props.x,
                    y: props.y,
                    combatObjectType: parseInt(uintType),
                }
            }
        })


        handleClose()
    }
    const MoveUnit = () => {

        handleClose()
    }


    const handleOpen = (event) => {
        this.setState({ menu: event.currentTarget });
    };


    return (
        <div>

            <Menu
                id="simple-menu"
                anchorEl={anchorEl}
                keepMounted
                open={Boolean(anchorEl)}
                onClose={handleClose}
            >
                <MenuItem onClick={CreateBase}>Create Base</MenuItem>

                <MenuItem >Create Unit<UnitMenu choose={CreateUnit} /></MenuItem>

            </Menu>

        </div>
    );
}
