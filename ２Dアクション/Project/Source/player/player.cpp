#include "DxLib.h"
#include "player.h"
#include "../Input/Input.h"
#include "../Animation/Animation.h"
#include "../Map/MapManager.h"
#include "../Camera/Camera.h"

struct PlayerAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
	float offsetX; // ★ このアニメーション専用のX方向のズレ補正
	float offsetY; // ★ このアニメーション専用のY方向のズレ補正
};

// プレイヤー設定関連 
#define PLAYER_RADIUS	(36.0f)
#define PLAYER_DEFAULT_POS_X (100.0f)
#define PLAYER_DEFAULT_POS_Y (100.0f)
#define PLAYER_MOVE_SPEED (3.0f)
#define PLAYER_WIDTH (20)
#define PLAYER_HEIGHT (44)


const PlayerAnimationParam PLAYER_ANIM_PARAM[PLAYER_ANIM_MAX] =
{
	{ 8, 1, 87, 147,  0.0f,   0.0f }, // 待機 (基準)
	{ 5, 7, 73, 115,  0.0f,  16.0f }, // 走る
	{ 12, 5, 82, 174,  15.0f, -20.0f }, // ★ジャンプ: 右へ15ピクセル、上へ20ピクセルずらす
	{ 8, 5, 71, 117,  30.0f, 0.0f }, // ★落下: 右へ30ピクセル、下へ0ピクセルずらす
	{ 8, 5, 96,  117,  0.0f,   0.0f }, // 着地
	{ 8, 3, 165, 120, 0.0f, 10.0f }, //攻撃
};

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)

// 重力
#define PLAYER_GRAVITY (0.4f)

// 地面吸いつき力
#define PLAYER_GROUND_SNAP (3.0f)

// 描画位置補正
#define PLAYER_DRAW_OFFSET_X (-40)
#define PLAYER_DRAW_OFFSET_Y (-85)

// 落下判定になるY移動量
#define PLAYER_FALL_Y_MOVE (1.6f)

// キャラクターの周囲何マスまでチェックするか
#define PLAYER_CHECK_ROUND_NUM (4)

#define PLAYER_ATTACK (1.0f)

PlayerData g_PlayerData = { 0 };

void StartPlayerAnimation(PlayerAnimationType anim);	// アニメーション再生
void UpdatePlayerAnimation();							// アニメーション更新

void InitPlayer()
{
	g_PlayerData.playAnim = PLAYER_ANIM_NONE;
	g_PlayerData.body = {};
	g_PlayerData.active = false;

	// 攻撃判定の初期化
	g_PlayerData.attackBox.active = false;
	g_PlayerData.attackBox.offsetX = 0.0f;
	g_PlayerData.attackBox.offsetY = 0.0f;
	g_PlayerData.attackBox.width = 0.0f;
	g_PlayerData.attackBox.height = 0.0f;

	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		InitAnimation(&g_PlayerData.animation[i]);
	}
}

void LoadPlayer()
{
	g_PlayerData.animation[PLAYER_ANIM_IDLE].handle = LoadGraph("Data/player/プレイヤー待機.png");
	g_PlayerData.animation[PLAYER_ANIM_RUN].handle = LoadGraph("Data/player/右移動.png");
	g_PlayerData.animation[PLAYER_ANIM_JUMP].handle = LoadGraph("Data/player/ジャンプ.png");
	g_PlayerData.animation[PLAYER_ANIM_FALL].handle = LoadGraph("Data/player/落下.png");
	g_PlayerData.animation[PLAYER_ANIM_LANDING].handle = LoadGraph("Data/player/着地.png");
	g_PlayerData.animation[PLAYER_ANIM_ATTACK].handle = LoadGraph("Data/player/3レイヤー.png");
}

void StartPlayer()
{
	g_PlayerData.active = true;

	// 初期位置
	g_PlayerData.body.pos.x = PLAYER_DEFAULT_POS_X;
	g_PlayerData.body.pos.y = PLAYER_DEFAULT_POS_Y;

	// サイズ
	g_PlayerData.body.width = PLAYER_WIDTH;
	g_PlayerData.body.height = PLAYER_HEIGHT;

	// 待機アニメーションから開始する
	StartPlayerAnimation(PLAYER_ANIM_IDLE);
}

void StepPlayer()
{
	if (!g_PlayerData.active)
	{
		return;
	}

	// 前回の座標を記憶
	g_PlayerData.body.prevPos.x = g_PlayerData.body.pos.x;
	g_PlayerData.body.prevPos.y = g_PlayerData.body.pos.y;

	// X移動量は毎回リセットする
	g_PlayerData.body.move.x = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.body.move.y += PLAYER_GRAVITY;

	// ★【対策】落下速度の上限（クランプ）を設定する
	// ※ブロックの厚みより小さい値（例: 10.0f ? 15.0f程度）に制限します
	float maxFallSpeed = 10.0f;
	if (g_PlayerData.body.move.y > maxFallSpeed)
	{
		g_PlayerData.body.move.y = maxFallSpeed;
	}

	// 左入力
	if (IsInputKey(KEY_A))
	{
		g_PlayerData.body.move.x = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_D))
	{
		g_PlayerData.body.move.x = PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = false;
	}
	// スペース入力（ジャンプ）
	if (IsTriggerKey(KEY_SPACE)) // KEY_INPUT_SPACE から KEY_SPACE に変更
	{
		// ★ 追加：空中にいなければ（地上にいるときだけ）ジャンプする
		if (!g_PlayerData.body.isAir)
		{
			g_PlayerData.body.move.y = -PLAYER_JUMP_POWER;
			// ジャンプした瞬間は強制的に空中フラグを立てる
			g_PlayerData.body.isAir = true;
		}
	}

	if (IsTriggerKey(KEY_Z))
	{
		// すでに攻撃中でなければ攻撃を開始
		if (g_PlayerData.playAnim != PLAYER_ANIM_ATTACK || !g_PlayerData.animation[PLAYER_ANIM_ATTACK].active)
		{
			StartPlayerAnimation(PLAYER_ANIM_ATTACK);

			// 攻撃判定を有効化
			g_PlayerData.attackBox.active = true;
			g_PlayerData.attackBox.width = 115.0f;   // 攻撃判定の幅
			g_PlayerData.attackBox.height = 115.0f;  // 攻撃判定の高さ
			g_PlayerData.attackBox.offsetY = -70.0f; // プレイヤー中心からのYオフセット

			// 向き（isTurn）によって判定の位置を左右に反転
			if (g_PlayerData.isTurn)
			{
				// 左向きのとき
				g_PlayerData.attackBox.offsetX = -115.0f;
			}
			else
			{
				// 右向きのとき
				g_PlayerData.attackBox.offsetX = 20.0f;
			}
		}
	}
}

void UpdatePlayer()
{
	// アニメーション更新
	UpdatePlayerAnimation();

	// ① 足場ブロックに乗っている場合の移動量を反映
	if (g_PlayerData.body.groundBlock != NULL)
	{
		g_PlayerData.body.pos.x += g_PlayerData.body.groundBlock->move.x;
		g_PlayerData.body.pos.y += g_PlayerData.body.groundBlock->move.y;
	}

	// ==========================================
	// ★【追加】移動量（move）を実際の座標（pos）に足し込む
	// ==========================================
	g_PlayerData.body.pos.x += g_PlayerData.body.move.x;
	g_PlayerData.body.pos.y += g_PlayerData.body.move.y;

	// ② 【重要】移動・衝突判定を行う「直前」に、一旦空中フラグを true にする
	g_PlayerData.body.isAir = true;

	// ③ マップとの衝突判定解決（ここで NormalBlock なら isAir = false になる）
	ResolveMapCollision(&g_PlayerData.body, PLAYER_CHECK_ROUND_NUM);

	// ④ 地面吸着処理など
	if (!g_PlayerData.body.isAir)
	{
		// 必要であれば吸着処理
	}
}

void DrawPlayer()
{
	// カメラ取得
	CameraData camera = GetCamera();

	// 現在のアニメーションパラメータを取得
	PlayerAnimationType animType = g_PlayerData.playAnim;
	PlayerAnimationParam animParam = PLAYER_ANIM_PARAM[animType];

	// 共通オフセット ＋ そのアニメーション固有のオフセットを合算
	float drawX = g_PlayerData.body.pos.x + PLAYER_DRAW_OFFSET_X + animParam.offsetX - camera.posX;
	float drawY = g_PlayerData.body.pos.y + PLAYER_DRAW_OFFSET_Y + animParam.offsetY - camera.posY;

	// ★ 左向きのとき、画像サイズの違いによる反転ズレをアニメーションごとに補正する
	if (g_PlayerData.isTurn)
	{
		if (animType == PLAYER_ANIM_ATTACK)
		{
			drawX -= 80.0f; // 攻撃の補正値（必要に応じて調整）
		}
		else if (animType == PLAYER_ANIM_JUMP)
		{
			drawX -= 10.0f;  // ジャンプの左向き補正（※ズレる場合は数値を変更してください）
		}
		else if (animType == PLAYER_ANIM_FALL)
		{
			drawX -= 20.0f;  // 落下の左向き補正（※ズレる場合は数値を変更してください）
		}
	}

	// アニメーション描画
	AnimationData* animData = &g_PlayerData.animation[animType];
	DrawAnimation(animData, VGet(drawX, drawY, 0.0f), g_PlayerData.isTurn);

	// デバッグ用：当たり判定のボックス
	float boxX = g_PlayerData.body.pos.x - camera.posX;
	float boxY = g_PlayerData.body.pos.y - camera.posY;
	DrawBox((int)boxX, (int)boxY, (int)(boxX + g_PlayerData.body.width), (int)(boxY + g_PlayerData.body.height), GetColor(0, 255, 0), FALSE);

	if (g_PlayerData.attackBox.active)
	{
		float atkBoxX = g_PlayerData.body.pos.x + g_PlayerData.attackBox.offsetX - camera.posX;
		float atkBoxY = g_PlayerData.body.pos.y + g_PlayerData.attackBox.offsetY - camera.posY;

		DrawBox(
			(int)atkBoxX,
			(int)atkBoxY,
			(int)(atkBoxX + g_PlayerData.attackBox.width),
			(int)(atkBoxY + g_PlayerData.attackBox.height),
			GetColor(255, 0, 0),
			FALSE
		);
	}

}

void FinPlayer()
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		DeleteGraph(g_PlayerData.animation[i].handle);
	}
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

void StartPlayerAnimation(PlayerAnimationType anim)
{
	// 再生中のアニメーションであれば何もしない
	// ※ただし、攻撃アニメーションを連打できるようにしたい場合はこのガードを調整するか、
	//  同じアニメーションの再開を許可する処理にしてください。
	if (anim == g_PlayerData.playAnim && g_PlayerData.animation[anim].active) return;

	// 再生中アニメーション設定
	g_PlayerData.playAnim = anim;

	// 再生に必要なデータを取得
	AnimationData* animData = &g_PlayerData.animation[anim];
	PlayerAnimationParam animParam = PLAYER_ANIM_PARAM[anim];

	// ★ 攻撃や着地などの非ループアニメーションは isLoop を false にする
	bool isLoop = true;
	if (anim == PLAYER_ANIM_ATTACK || anim == PLAYER_ANIM_LANDING)
	{
		isLoop = false;
	}

	// アニメーション再生
	StartAnimation(animData, g_PlayerData.body.pos, animParam.interval, animParam.frameNum, animParam.width, animParam.height, isLoop);
}

void UpdatePlayerAnimation()
{
	PlayerAnimationType animType = g_PlayerData.playAnim;
	AnimationData* animData = &g_PlayerData.animation[animType];

	// ★ 攻撃アニメーション中で、まだアニメーションが終了していない（activeがtrue）場合
	// は、他のアニメーションに上書きさせずにアニメーションの更新だけ行う
	if (animType == PLAYER_ANIM_ATTACK && animData->active)
	{
		UpdateAnimation(animData);
		return;
	}

	if (animType == PLAYER_ANIM_ATTACK && animData->active)
	{
		UpdateAnimation(animData);
		return;
	}
	else
	{
		// 攻撃アニメーション中でなければ、攻撃判定を無効にする
		g_PlayerData.attackBox.active = false;
	}

	// --- 以下、通常の移動や空中判定に応じたアニメーション切り替え ---
	// 地上にいるか
	if (!g_PlayerData.body.isAir)
	{
		// 横に移動していれば走っている
		if (g_PlayerData.body.move.x < 0.0f || g_PlayerData.body.move.x > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_RUN);
		}
		else
		{
			StartPlayerAnimation(PLAYER_ANIM_IDLE);
		}
	}
	// 空中にいる
	else
	{
		// 上昇していればジャンプアニメーション
		if (g_PlayerData.body.move.y < 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_JUMP);
		}
		// 下降していれば落下アニメーション
		else if (g_PlayerData.body.move.y > 0.0f)
		{
			StartPlayerAnimation(PLAYER_ANIM_FALL);
		}
	}

	// アニメーション更新
	animType = g_PlayerData.playAnim;
	animData = &g_PlayerData.animation[animType];
	UpdateAnimation(animData);
}

