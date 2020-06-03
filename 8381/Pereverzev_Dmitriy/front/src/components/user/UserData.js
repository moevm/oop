import React, { Component } from 'react';
import "./user.css"



class UserData extends Component {
    constructor(props) {
        super(props);
        this.defaultName = this.defaultName.bind(this);
        this.newName = this.newName.bind(this);
        this.handleClick = this.handleClick.bind(this);

        this.state = {
            name: localStorage.getItem("userName") || "null"
        }



    }

    defaultName() {
        let name = '';
        while (name.length < 10) name += "abcdefghijklmnopqrstuvwxyz1234567890"[Math.floor(Math.random() * 36)];
        localStorage.setItem("userName", name);
        return name;

    }

    componentDidMount() {
        if (!localStorage.getItem("userName")) {
            let name = this.defaultName()
            localStorage.setItem("userName", name)
            this.setState({ name });
            console.log(name)
        }
    }

    handleClick() {
        this.newName();
    }

    newName() {
        let newName = this.refs.nameInput.value
        if (newName) {
            localStorage.setItem("userName", newName)
            this.setState({ name: newName }, () => console.log(newName));
        }
        else
            alert("wrong format")


    }



    render() {
        return (
            <div className="userData">
                <h3>User Data</h3>
                <div className="userName">
                    <label>User name now: {this.state.name}</label>
                    <hr width="80%" />
                    <label>Change user name</label>

                    <div>
                        <input ref="nameInput" type="text" maxLength="255" />
                        <button onClick={this.handleClick}>Change name</button>
                    </div>

                </div>


            </div>
        )
    };
}


export default UserData;
