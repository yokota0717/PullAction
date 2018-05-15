#pragma once
#include "Game.h"

class Card :public Object {
public:
	Card(std::string name, Object::Status status = Object::Status::pause);

	void init() override;
	void update() override;
	void updatePause() override;
	void render() override;
	void renderPause() override;
};