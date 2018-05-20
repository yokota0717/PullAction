#pragma once
#include "Game.h"

class Field :public Object {
public:
	Field(const string& name, Object::Status status);

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

class Ball :public Object {
	Math::Vec force;
	int ballID;
public:
	Ball(const string& name, const int i, Object::Status status);

	void init();
	void update();
	void updatePause();
	void updateSleep();
	void updateDestroy();
	void render();
	void renderPause();
	void renderSleep();
	void renderDestroy();

	void checkMove();
	bool checkHitBall();
	bool checkHitWallLeft();
	bool checkHitWallRight();
	bool checkHitWallTop();
	bool checkHitWallBottom();

	int receiveMsg(std::weak_ptr<Object> sender, const string& msg);
	int receiveMsg(std::weak_ptr<Object> sender, const Math::Vec arrow);
	Math::Circle collider;
};

class Puller :public Object {
	bool isOutScreen();
	bool isPulling;
	Math::Vec click;					//クリックしたときの座標
	Math::Vec now;						//現在のマウス座標
	Math::Vec pre;						//1フレーム前のマウス座標
	Math::Vec arrow;					//ひっぱる力の向きと大きさ
	float angle;						//クリック座標と現在座標のベクトルの成す角
	std::weak_ptr<Object> clickedBall;	//クリックされているボールを管理する

public:
	Puller(const string& name, Object::Status status);
	
	void init();
	void update();
	void render();
	int postMsg(std::weak_ptr<Object> receiver, const Math::Vec arrow);
};