#include "Cursor.h"

Cursor::Cursor(const std::string& name, Object::Status status):
	Object(name,status)
{}

void Cursor::init() {
	image = game->grafac->GetGraph("./resource/image/card.png");
	pos = Math::Vec(10, 10);
	src = Math::Box2D(300.0f*6.0f, 400.0f, 300.0f, 400.0f);
}
void Cursor::update() {}
void Cursor::updatePause() {}
void Cursor::render() {
	draw = Math::Box2D(pos.x, pos.y, 150.0f, 400.0f);		//�Ȃ���y����1/2�����c�c�H�H�H�H�H
	DrawImage(draw, src, image);
}
void Cursor::renderPause() {}
