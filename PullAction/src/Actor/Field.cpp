#include "Field.h"
#include <iostream>

Field::Field(const string& name, Object::Status status)
	:
	Object(name, status)
{}

void Field::init() {
	draw = Math::Box2D(0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	src = Math::Box2D(0, 0, 1024, 1024);
	image = game->grafac->GetGraph("map.png");
	insertAsChild(new Puller("Puller", Object::Status::pause));
}
void Field::update() {
	if (game->kb.Down(SPACE)) {
		postMsg(game->root->getObjectFromChildren("Title"), "BackToTitle");
		pauseAll();
	}
}
void Field::updatePause() {}
void Field::updateSleep() {}
void Field::updateDestroy() {}
void Field::render() {
	DrawImage(draw, src, image);
}
void Field::renderPause() {}
void Field::renderSleep() {}
void Field::renderDestroy() {}

int Field::receiveMsg(std::weak_ptr<Object> sender, const string& msg) {
	runAll();
	for (auto child : getChildren()) {
		if (child.lock()->name() == "Puller") { continue; }
		child.lock()->init();
	}
	return 0;
}


Ball::Ball(const string& name, const int i, Object::Status status)
	:
	Object(name, status),
	ballID(i)
{}
void Ball::init() {
	pos = Math::Vec(200.0f + 300.0f * ballID, 600.0f);
	collider = Math::Circle(0.0f, 0.0f, 0.0f, 64.0f);
	src = Math::Box2D(128.0f * ballID, 0, 128.0f, 126.0f);
	image = game->grafac->GetGraph("ball.png");
}
void Ball::update() {
	Math::Vec dest = pos + force;	//予想移動先座標
	collider.center = Math::Vec(dest.x + 64.0f, dest.y + 64.0f);	//当たり判定も合わせて移動
	//壁とぶつかるか？
	if (checkHitWallLeft()) { dest.x = 0; force.x *= -1; }
	if (checkHitWallRight()) { dest.x = SCREEN_WIDTH - 1.0f - 128.0f; force.x *= -1; }
	if (checkHitWallTop()) { dest.y = 0; force.y *= -1; }
	if (checkHitWallBottom()) { dest.y = SCREEN_HEIGHT - 1.0f - 128.0f; force.y *= -1; }
	//他のボールとぶつかるか？
	std::vector<std::weak_ptr<Object>> others = getObjectsFromRoot(std::vector<string>({ "Ball" }));	//他のボールを検索


	//移動
	pos = dest;
	//移動力減衰
	force *= 0.96f;
}
void Ball::updatePause() {}
void Ball::updateSleep() {}
void Ball::updateDestroy() {}
void Ball::render() {
	draw = Math::Box2D(pos.x, pos.y, 128.0f, 128.0f);
	DrawImage(draw, src, image);
	if (game->DebugMode()) {
		DrawCircle((int)collider.center.x, (int)collider.center.y, (int)collider.r, debugRed, false, 5);
	}
}
void Ball::renderPause() {}
void Ball::renderSleep() {}
void Ball::renderDestroy() {}
bool Ball::checkHitWallLeft() {
	Math::Vec left(pos.x, pos.y + collider.r);
	if (left.x < 0) { return true; }
	return false;
}
bool Ball::checkHitWallRight() {
	Math::Vec right(pos.x + collider.r * 2.0f, pos.y + collider.r);
	if (right.x >= SCREEN_WIDTH) { return true; }
	return false;
}
bool Ball::checkHitWallTop() {
	Math::Vec top(pos.x + collider.r, pos.y);
	if (top.y < 0) { return true; }
	return false;
}
bool Ball::checkHitWallBottom() {
	Math::Vec bottom(pos.x + collider.r, pos.y + collider.r * 2.0f);
	if (bottom.y >= SCREEN_HEIGHT) { return true; }
	return false;
}
bool Ball::checkHitBall() {
	return false;
}
//void Ball::checkMove() {
//	Math::Vec prepos = pos;
//	//x軸
//	while (force.x != 0) {
//		if (force.x >= 1.0f) { pos.x += 1.0f; }
//		else if (force.x <= -1.0f) { pos.x -= 1.0f; }
//		else { pos.x += force.x; }
//		if (checkHitWallX()) { pos.x = prepos.x; force.x *= -1; }
//		force.x *= 0.96f;
//	}
//	//y軸
//	while (force.y != 0) {
//		if (force.y >= 1.0f) { pos.y += 1.0f; }
//		else if (force.y <= -1.0f) { pos.y -= 1.0f; }
//		else { pos.y += force.y; }
//		if (checkHitWallY()) { pos.y = prepos.y; force.y *= -1; }
//		force.y *= 0.96f;
//	}
//}
//bool Ball::checkHitWallX() {
//	Math::Vec left(pos.x, pos.y + collider.r);
//	Math::Vec right(pos.x + collider.r * 2.0f, pos.y + collider.r);
//	if (left.x < 0 || right.x >= SCREEN_WIDTH) { 
//		return true; }
//	return false;
//}
//bool Ball::checkHitWallY() {
//	Math::Vec top(pos.x + collider.r, pos.y);
//	Math::Vec bottom(pos.x + collider.r, pos.y + collider.r * 2.0f);
//	if (top.y < 0 || bottom.y >= SCREEN_HEIGHT) { 
//		return true; }
//	return false;
//}
int Ball::receiveMsg(std::weak_ptr<Object> sender, const string& msg) {
	return 0;
}
int Ball::receiveMsg(std::weak_ptr<Object> sender, const Math::Vec arrow) {
	force = arrow * 0.1f;
	return 0;
}


Puller::Puller(const string& name, Object::Status status)
	:
	Object(name, status)
{}
void Puller::init() {
	for (int i = 0; i < 3; ++i) {
		insertAsChild(new Ball("Ball" + to_string(i + 1), i, Object::Status::pause));
	}
	src = Math::Box2D(0, 0, 128, 128);
	image = game->grafac->GetGraph("arrow.png");
	isPulling = false;
}
bool Puller::isOutScreen() {
	return (now.x < 0
		|| now.x >= SCREEN_WIDTH
		|| now.y < 0
		|| now.y >= SCREEN_HEIGHT);
}
void Puller::update() {
	pre = now;
	now = game->mouse.getPos();
	//ボールを左クリックしたかチェック
	if (game->mouse.DownLeft()) {
		click = game->mouse.getPos();		//マウス座標を代入
		for (auto ball : getChildren()) {
			if (click.Hit(dynamic_pointer_cast<Ball>(ball.lock())->collider)) {	//マウス座標とボールの当たり判定
				clickedBall = ball;
				isPulling = true;				//ひっぱり中
			}
		}
	}
	if (isPulling) {						//ひっぱり中
		now = game->mouse.getPos();			//マウスの現在座標
		arrow = click - now;				//力の向きと大きさ
		angle = atan2(arrow.y, arrow.x);	//角度を計算
	}
	if (isPulling && game->mouse.UpLeft()) {//ひっぱり中に左クリック離した
		isPulling = false;
		angle = 0.0f;
		postMsg(clickedBall, arrow);
	}

}
void Puller::render() {
	draw = Math::Box2D(click.x, click.y, arrow.GetVecLen(), 128.0f);
	if (isPulling) {
		DrawImageRotate(draw, src, image, angle);
	}
}
int Puller::postMsg(std::weak_ptr<Object> receiver, Math::Vec arrow) {
	if (receiver.expired()) { return -1; }
	return receiver.lock()->receiveMsg(selfPtr(), arrow);
}
