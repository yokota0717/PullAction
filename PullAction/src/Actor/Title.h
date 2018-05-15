#pragma once
#include "Game.h"
#include "../Easing/Easing.h"

class Title :public Object {
public:
	Title(const string& name, Object::Status status);

	void init();
	void update();
	void updatePause();
	void updateSleep();
	void updateDestroy();
	void render();
	void renderPause();
	void renderSleep();
	void renderDestroy();
	int receiveMsg(std::weak_ptr<Object> sender, const string& msg);
};

class Logo :public Object {
public:
	Logo(const string& name, Object::Status status);

	void init();
	void update();
	void updatePause();
	void updateSleep();
	void updateDestroy();
	void render();
	void renderPause();
	void renderSleep();
	void renderDestroy();

private:
	Easing ease;
};