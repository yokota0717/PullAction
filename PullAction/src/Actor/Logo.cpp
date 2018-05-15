#include "Logo.h"

Logo::Logo(std::string name, Object::Status status) :
	Object(name, status)
{}

void Logo::init() {
	image = game->grafac->GetGraph("./resource/image/title.png");
	pos = Math::Vec(float(SCREEN_WIDTH / 2 - 720 / 2), 100/*float(-120/2)*/);
	draw = Math::Box2D(pos.x, pos.y, 720, 180);
	src = Math::Box2D(0, 0, 240, 120);
}

void Logo::update() {
	if (game->kb.Down(ENTER)) {
		postMsg(game->root->getObjectFromChildren("Board"), "GameStart");
		pause();
	}
}
void Logo::updatePause() {}
void Logo::render() {
	DrawImage(draw, src, image);
}
void Logo::renderPause() {}

int Logo::receiveMsg(std::weak_ptr<Object> receiver, const std::string& msg) {
	run();
	return 0;
}
