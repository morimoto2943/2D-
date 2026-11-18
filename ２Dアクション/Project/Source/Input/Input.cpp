#include "DxLib.h"
#include "Input.h"

// 入力ビットフラグ
int g_InputState = 0;
// 前回の入力ビット
int g_PrevInputState = 0;

void InitInput()
{
	g_InputState = 0;
	g_PrevInputState = 0;
}

void UpdateInput()
{
	// 前回の入力を覚えておく
	g_PrevInputState = g_InputState;

	// 入力状態をクリア
	g_InputState = 0;

	// ==========================================
	// キーボードの入力判定
	// ==========================================
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		g_InputState |= KEY_UP;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		g_InputState |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		g_InputState |= KEY_LEFT;
		g_InputState |= KEY_A; // Player.cppがKEY_Aを見ているため両方立てる
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		g_InputState |= KEY_RIGHT;
		g_InputState |= KEY_D; // Player.cppがKEY_Dを見ているため両方立てる
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		g_InputState |= KEY_Z;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		g_InputState |= KEY_SPACE;
	}

	// 単独のW, A, S, Dキー自体もフラグとして立てたい場合
	if (CheckHitKey(KEY_INPUT_W)) { g_InputState |= KEY_W; }
	if (CheckHitKey(KEY_INPUT_A)) { g_InputState |= KEY_A; }
	if (CheckHitKey(KEY_INPUT_S)) { g_InputState |= KEY_S; }
	if (CheckHitKey(KEY_INPUT_D)) { g_InputState |= KEY_D; }

	// ==========================================
	// ゲームパッド（コントローラー）の入力判定
	// ==========================================
	int padState = GetJoypadInputState(DX_INPUT_PAD1);

	if (padState & PAD_INPUT_UP) { g_InputState |= KEY_UP; }
	if (padState & PAD_INPUT_DOWN) { g_InputState |= KEY_DOWN; }
	if (padState & PAD_INPUT_LEFT) { g_InputState |= KEY_LEFT; g_InputState |= KEY_A; }
	if (padState & PAD_INPUT_RIGHT) { g_InputState |= KEY_RIGHT; g_InputState |= KEY_D; }
	if (padState & PAD_INPUT_2) { g_InputState |= KEY_SPACE; } // ジャンプ
	if (padState & PAD_INPUT_1) { g_InputState |= KEY_Z; }     // 攻撃
}

void DrawInput()
{
}

void FinInput()
{
}

bool IsInputKey(InputKey key)
{
	return g_InputState & key;
}

bool IsTriggerKey(InputKey key)
{
	return (g_InputState & key) && !(g_PrevInputState & key);
}