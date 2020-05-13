#pragma once
#include <exception>
#include <string>

class TypeInputException : public std::exception {
private:
	std::string err;

public:
	TypeInputException(std::string type) {
		err = "Expected data type " + type + " but another was received";
	}

	const char* what() const noexcept override {
		return err.c_str();
	}
};


class LogicException : public std::exception {
private:
	std::string err;

public:
	LogicException(std::string where, int what) {
		err = "Logic exception in " + where + " with incorrect data " + std::to_string(what);
	}

	LogicException(std::string where, std::string what) {
		err = "Logic exception in " + where + " with incorrect data " + what;
	}

	LogicException(std::string where, int what1, int what2) {
		err = "Logic exception in " + where + " with incorrect data " + std::to_string(what1) + " " + std::to_string(what2);
	}

	const char* what() const noexcept override {
		return err.c_str();
	}
};

