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
void Field::updatePause(){}
void Field::updateSleep(){}
void Field::updateDestroy(){}
void Field::render() {
	DrawImage(draw, src, image);
}
void Field::renderPause(){}
void Field::renderSleep(){}
void Field::renderDestroy(){}

int Field::receiveMsg(std::weak_ptr<Object> sender, const string& msg) {
	runAll();
	for (auto child : getChildren()) {
		child.lock()->init();
	}
	return 0;
}


Ball::Ball(const string& name, Object::Status status)
	:
	Object(name,status)
{}
void Ball::init() {
	pos = Math::Vec(600, 600);
	collider = Math::Circle(0.0f, 0.0f, 0.0f, 64.0f);
	src = Math::Box2D(0, 0, 128.0f, 128.0f);
	image = game->grafac->GetGraph("ball.png");
}
void Ball::update(){
	pos += force;
	collider.center = Math::Vec(pos.x + 64.0f, pos.y + 64.0f);
	//反射
	Math::Vec top(collider.center.x, collider.center.y - collider.r);
	Math::Vec bottom(collider.center.x, collider.center.y + collider.r);
	Math::Vec left(collider.center.x - collider.r, collider.center.y);
	Math::Vec right(collider.center.x + collider.r, collider.center.y);
	if (top.y < 0) { pos.y = 0; force.y *= -1; }
	if (bottom.y >= SCREEN_HEIGHT) { pos.y = SCREEN_HEIGHT - 128.0f; force.y *= -1; }
	if (left.x < 0) { pos.x = 0; force.x *= -1; }
	if (right.x >= SCREEN_WIDTH) { pos.x = SCREEN_WIDTH - 128.0f; force.x *= -1; }
	collider.center = Math::Vec(pos.x + 64.0f, pos.y + 64.0f);	//どうにかしたい
	//減衰
	force *= 0.96f;
}
void Ball::updatePause(){}
void Ball::updateSleep(){}
void Ball::updateDestroy(){}
void Ball::render(){
	draw = Math::Box2D(pos.x, pos.y, 128.0f, 128.0f);
	DrawImage(draw, src, image);
	if (game->DebugMode()) {
		DrawCircle((int)collider.center.x, (int)collider.center.y, (int)collider.r, debugRed, false, 5);
	}
}
void Ball::renderPause(){}
void Ball::renderSleep(){}
void Ball::renderDestroy(){}
int Ball::receiveMsg(std::weak_ptr<Object> sender, const string& msg){
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
	insertAsChild(new Ball("Ball", Object::Status::pause));
	src = Math::Box2D(0, 0, 128, 128);
	image = game->grafac->GetGraph("arrow.png");
	isPulling = false;
}
bool Puller::isOutScreen() {
	return (now.x<0
		|| now.x>=SCREEN_WIDTH
		|| now.y<0
		|| now.y>=SCREEN_HEIGHT);
}
void Puller::update() {
	pre = now;
	now = game->mouse.getPos();
	//ボールを左クリックしたかチェック
	if (game->mouse.DownLeft()) {
		click = game->mouse.getPos();		//マウス座標を代入
		if(click.Hit(dynamic_pointer_cast<Ball>(getObjectFromRoot("Ball").lock())->collider)) {	//マウス座標とボールの当たり判定
			isPulling = true;				//ひっぱり中
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
		postMsg(getObjectFromChildren("Ball"), arrow);
	}

}
void Puller::render() {
	draw = Math::Box2D(click.x, click.y, arrow.GetVecLen(), 128.0f);
	if (isPulling) { 
		DrawImageRotate(draw, src, image, angle);
	}
}
int Puller::postMsg(std::weak_ptr<Object> receiver, Math::Vec arrow) {
	return receiver.lock()->receiveMsg(selfPtr(), arrow);
}
