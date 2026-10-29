#pragma once
#include "AnimationParameter.h"

#define ANIMATION_MAX 255

// アニメーションデータ
struct AnimationData
{
	bool active;
	int handle;
	int nowFrame;
	int frameNum;
	int frameWidth;
	int frameHeight;
	int timer;
	int interval;
	float posX;
	float posY;
};

// 各関数の宣言
void InitAnimation();
void LoadAnimation();
void StepAnimation();
void UpdateAnimation();
void DrawAnimation();
void FinAnimation();

// アニメーション開始
void PlayAnimation(AnimationType type, float posX, float posY, int interval);

