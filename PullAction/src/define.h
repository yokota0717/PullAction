#pragma once
#include "DxLib.h"
#include "Figure\Math.h"

const int SCREEN_WIDTH = 1280,
SCREEN_HEIGHT = 1080;

const int debugRed = GetColor(255, 50, 50);

//DX���C�u�����̕`��֐������b�s���O
void DrawImage(Math::Box2D draw, Math::Box2D src, int handle);
void DrawImageRotate(Math::Box2D draw, Math::Box2D src, int handle, float radian);