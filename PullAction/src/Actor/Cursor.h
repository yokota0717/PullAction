#pragma once
#include "Game.h"

class Cursor :public Object {
public:
	Cursor(const std::string& name, Object::Status status = Object::Status::pause);

	void init() override;
	void update() override;
	void updatePause() override;
	void render() override;
	void renderPause() override;
};