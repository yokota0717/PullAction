#pragma once
#include "Game.h"
#include "Card.h"
#include "Cursor.h"

class Board :public Object {
public:
	Board(std::string name, Object::Status status = Object::Status::pause);

	void init() override;
	void update() override;
	void updatePause() override;
	void render() override;
	void renderPause() override;

	int receiveMsg(std::weak_ptr<Object> receiver, const std::string& msg) override;
};