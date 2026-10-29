#pragma once

// エフェクトの種類
enum AnimationType
{
	PLAYER_RIGHT_WOOK,
	PLAYER_LEFT_WOOK,
	PLAYER_JUMP,
	ANIMATION_TYPE_MAX
};



struct AnimationMasterParameter
{
	int frameNum;		// フレーム数
	int frameWidth;		// 1コマの横幅
	int frameHeight;	// 1コマの縦幅
};
const AnimationMasterParameter ANIM_MASTER_PARAM[ANIMATION_TYPE_MAX] =
{
	12, 16, 16,	// PLAYER_RIGHT_WOOK
	12, 64, 64,	// PLAYER_LEFT_WOOK
	3,  32, 32,	// PLAYER_JUMP
};