#pragma once
#include "../Animation/Animation.h"
#include "../Collision/CollisionParameter.h"
#include "../Map/MapParameter.h"

// アニメーションタイプ
enum PlayerAnimationType
{
	PLAYER_ANIM_IDLE,
	PLAYER_ANIM_RUN,
	PLAYER_ANIM_JUMP,
	PLAYER_ANIM_FALL,
	PLAYER_ANIM_LANDING,
	PLAYER_ANIM_MAX,
	PLAYER_ANIM_NONE = -1
};









//プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (50.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (100.0f)

//プレイヤーサイズ
#define PLAYER_WIDTH (1)
#define PLAYER_HEIGHT (1)

// プレイヤーデータ
struct PlayerData
{
	int handle;                                 //画像ハンドル
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	Body body;
	bool isAir;									// 空中にいるか
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	bool hitFlg;                                //ヒットフラグ
	float drawOffsetX;							// 描画位置補正
	float drawOffsetY;							// 描画位置補正
	AnimationData animation[PLAYER_ANIM_MAX];	// アニメーション
	PlayerAnimationType playAnim;				// 再生中のアニメーション
};

// 関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();
