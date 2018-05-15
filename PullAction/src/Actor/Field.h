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
public:
	Ball(const string& name, Object::Status status);

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
	int receiveMsg(std::weak_ptr<Object> sender, const Math::Vec arrow);

	Math::Circle collider;
	Math::Vec force;
};

class Puller :public Object {
	bool isOutScreen();
	bool isPulling;
	Math::Vec click;	//�N���b�N�����Ƃ��̍��W
	Math::Vec now;		//���݂̃}�E�X���W
	Math::Vec pre;		//1�t���[���O�̃}�E�X���W
	Math::Vec arrow;	//�Ђ��ς�͂̌����Ƒ傫��
	float angle;		//�N���b�N���W�ƌ��ݍ��W�̃x�N�g���̐����p

public:
	Puller(const string& name, Object::Status status);
	
	void init();
	void update();
	void render();
	int postMsg(std::weak_ptr<Object> receiver, const Math::Vec arrow);
};