#pragma once
#include <exception>


class myexcept : public std::exception {
	char *message;
public:
	myexcept(char *message) {
		this->message = message;
	}
	char *what() {
		return message;
	}
};

class NoSection : public myexcept {
public:
	NoSection(char*error) :myexcept(error) {};
};

class NoParam : public myexcept {
public:
	NoParam(char*error) :myexcept(error) {};
};

class NoFile : public myexcept {
public:
	NoFile(char*error) :myexcept(error) {};
};