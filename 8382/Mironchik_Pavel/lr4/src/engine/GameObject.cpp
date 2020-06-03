#include <iostream>
#include <string>

#include <GAME/engine/GameObject.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <GAME/log/Log.hpp>

int GameObject::CUR_ID = 0;

GameObject::GameObject() {

}

GameObject::GameObject(const GameObject& from) {
	setTangible(from.isTangible());
	setFocusable(from.isFocusable());
	setFocused(from.isFocused());
	occupiedCell = from.occupiedCell;
}

int GameObject::id() const {
	return _id;
}

void GameObject::attach(GameBoard *board) {
	this->board = board;
	onAttach();
}

void GameObject::detach() {
	onDetach();
	this->board = nullptr;
}

bool GameObject::onClick(sf::Vector2i& cell) {
	return false;
}


bool GameObject::onKeyPressed(sf::Event key) {
	return false;
}

bool GameObject::isAttached() const {
	return board != nullptr;
}

sf::Vector2i& GameObject::getOccupiedCell() const {
	return occupiedCell;
}

void GameObject::setOccupiedCell(sf::Vector2i cell) {
	sf::Vector2i prevCell = this->occupiedCell;
	this->occupiedCell = cell;

	if (board != nullptr)
		board->moveObject(id(), prevCell, occupiedCell);
}

GameBoard* GameObject::getBoard() const {
	return board;
}

void GameObject::fillLogInfo(LogInfo& info) {
	info.name = "GameObject";
	info.params.push_back(pair<string, string>("isAttached", isAttached() ? "1" : "0"));
}