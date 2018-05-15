#include "Title.h"
#include <iostream>

Title::Title(const string& name, Object::Status status)
	:
	Object(name, status)
{}

void Title::init() {
	draw = Math::Box2D(0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	src = Math::Box2D(0, 0, 620, 439);
	image = game->grafac->GetGraph("back.jpg");

	insertAsChild(new Logo("Logo", Object::Status::run));
}
void Title::update() {
	if (game->mouse.DownLeft()) {
		postMsg(game->root->getObjectFromChildren("Field"), "GameStart");
		pauseAll();
	}
}
void Title::updatePause(){}
void Title::updateSleep(){}
void Title::updateDestroy(){}
void Title::render(){
	DrawImage(draw, src, image);
}
void Title::renderPause(){}
void Title::renderSleep(){}
void Title::renderDestroy(){}
int Title::receiveMsg(std::weak_ptr<Object> sender, const string& msg) {
	runAll();
	for (auto child : getChildren()) {
		child.lock()->init();
	}
	return 0;
}



Logo::Logo(const string& name, Object::Status status)
	:
	Object(name,status)
{}

void Logo::init() {
	pos = Math::Vec(-425.0f, (SCREEN_HEIGHT - 283.0f) / 2.0f - 100.0f);
	src = Math::Box2D(0, 0, 425, 283);
	image = game->grafac->GetGraph("title2.png");
	ease.init();
}
void Logo::update() {
	pos.x = ease.expo.Out(ease.Time(10), -425.0f, (SCREEN_WIDTH - 425.0f) / 2.0f + 425.0f, 10);
}
void Logo::updatePause(){}
void Logo::updateSleep(){}
void Logo::updateDestroy(){}
void Logo::render() {
	draw = Math::Box2D(pos.x, pos.y, 425.0f, 283.0f);
	DrawImage(draw, src, image);
}
void Logo::renderPause(){}
void Logo::renderSleep(){}
void Logo::renderDestroy(){}
