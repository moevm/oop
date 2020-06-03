import React, { Component } from 'react';
import { Link } from "react-router-dom";

class MenuButton extends Component {
    constructor(props) {
        super(props);
        this.state = {
            menuType: props.menuType,
            key: props.id,
            text: props.text,
            href: props.href,

        }
    }

    componentDidMount() {
    }

    render() {
        return (
            <Link key={"menuBtn_" + this.state.id} to={this.state.href} className={"menu" + this.state.menuType + "Btn"}>
                {this.state.text}
            </Link>
        )
    };
}


export default MenuButton;
