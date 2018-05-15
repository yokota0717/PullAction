#include "Card.h"

Card::Card(std::string name, Object::Status status):
	Object(name, status)
{}

void Card::init() {
	static int cardnum = 0;
	image = game->grafac->GetGraph("./resource/image/card.png");
	pos = Math::Vec(float(10 + 160 * (cardnum % 6)), float(10 + 200 * (cardnum/ 6)));
	cardnum++;
}
void Card::update() {

}
void Card::updatePause() {}
void Card::render() {
	draw = Math::Box2D(pos.x, pos.y, 150, 200);
	src = Math::Box2D(300.0f * 6, 0.0f, 300.0f, 400.0f);
	DrawImage(draw, src, image);
}
void Card::renderPause(){}