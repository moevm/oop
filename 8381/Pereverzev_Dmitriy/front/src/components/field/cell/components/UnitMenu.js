import React from 'react';
import IconButton from '@material-ui/core/IconButton';
import Button from '@material-ui/core/IconButton';
import Menu from '@material-ui/core/Menu';
import MenuItem from '@material-ui/core/MenuItem';


const options = [
    "ARCH_TANK",
    "ARCH_DPS",
    "INF_TANK",
    "INF_DPS",
    "CAV_TANK",
    "CAV_DPS",
];

const ITEM_HEIGHT = 48;

export default function LongMenu(props) {
    const [anchorEl, setAnchorEl] = React.useState(null);
    const open = Boolean(anchorEl);

    const handleClick = (event) => {
        setAnchorEl(event.currentTarget);
    };

    const handleClose = (f) => {
        setAnchorEl(null);
        props.choose(f)

    };

    return (
        <div>
            {/* {`<<`} */}
            <Button
                aria-label="more"
                aria-controls="long-menu"
                aria-haspopup="true"
                onClick={handleClick}
            >
                +
            </Button>
            {/* {`>>`} */}

            <Menu
                id="long-menu"
                anchorEl={anchorEl}
                keepMounted
                open={open}
                onClose={handleClose}
                PaperProps={{
                    style: {
                        maxHeight: ITEM_HEIGHT * 4.5,
                        width: '20ch',
                    },
                }}
            >
                {options.map((option) => (
                    <MenuItem key={option} selected={option === 'ARCH_TANK'} onClick={() => { handleClose(option) }}>
                        {option}
                    </MenuItem>
                ))}
            </Menu>
        </div >
    );
}
