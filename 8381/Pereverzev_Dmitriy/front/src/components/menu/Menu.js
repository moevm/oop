import React, { Component } from 'react';
import MenuButton from './MenuButton.js';


import './menu.css';


class Menu extends Component {
    constructor(props) {
        super(props);
        this.state = {
            menuType: props.type,
            items: []
        }
    }

    componentDidMount() {
        fetch(`/components/menu/menu${this.state.menuType}.json`)
            .then(res => res.json())
            .then(items => this.setState({ items }, () => console.log("items:", items)))
    }


    render() {
        return (
            <div className={"menu" + this.state.menuType} style={{ height: this.state.items.length * 150 }}>
                <h3>Menu</h3>
                {this.state.items.map((elem) =>
                    <MenuButton key={elem.id} text={elem.title} href={elem.href} menuType={this.state.menuType} />
                )}
            </div>
        )
    };
}


export default Menu;
