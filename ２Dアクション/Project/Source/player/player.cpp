#include "DxLib.h"
#include "player.h"
#include "../Input/Input.h"

#define PLAYER_JUMP_POWER (12.0f)

#define PLAyER_GRAVITYY (0.4f)

PlayerData g_PlayerData = { 0 };



void InitPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/プレイヤー待機.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	g_PlayerData.moveY = PLAYER_MOVE_SPEED;

}

void LoadPlayer()
{
	
}

void StartPlayer()
{

}

void StepPlayer()
{

}

void UpdatePlayer()
{
	//右入力
	if (IsInputKey(KEY_D))
	{
		g_PlayerData.posX += g_PlayerData.moveX;
	}
	//左入力
	if (IsInputKey(KEY_A))
	{
		g_PlayerData.posX -= g_PlayerData.moveX;
	}

	//ジャンプ
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.moveY = -PLAYER_JUMP_POWER;
	}

	g_PlayerData.hitFlg = false;


	if (IsInputKey(KEY_D))//右移動
	{
		g_PlayerData.handle = LoadGraph("Data/Player/プレイヤー待機.png");
	}
	else if (IsInputKey(KEY_A))//左移動
	{
		g_PlayerData.handle = LoadGraph("Data/Player/プレイヤー待機.png");
	}
	else if (IsTriggerKey(KEY_Z))//ジャンプ
	{
		g_PlayerData.handle = LoadGraph("Data/Player/プレイヤー待機.png");
	}
	else//ニュートラル
	{
		g_PlayerData.handle = LoadGraph("Data/Player/プレイヤー待機.png");
	}

}

void DrawPlayer()
{
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

