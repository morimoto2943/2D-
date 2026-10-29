#include "DxLib.h"
#include "Animation.h"
#include "AnimationParameter.h"


AnimationData g_AnimationData[ANIMATION_MAX] = { 0 };

// エフェクトの画像ハンドル
int g_AnimationEffectHandle[ANIMATION_TYPE_MAX];

// エフェクト初期化
void InitAnimationEffect()
{
	AnimationData* effect = g_AnimationData;
	for (int i = 0; i < ANIMATION_MAX; i++, effect++)
	{
		effect->active = false;
		effect->handle = 0;
		effect->nowFrame = 0;
		effect->frameNum = 0;
		effect->frameWidth = 0;
		effect->frameHeight = 0;
		effect->timer = 0;
		effect->posX = 0.0f;
		effect->posY = 0.0f;
	}
}

// エフェクトロード
void LoadAnimationEffect()
{
	g_AnimationEffectHandle[PLAYER_RIGHT_WOOK] = LoadGraph("Data/Player/右移動.png");
	g_AnimationEffectHandle[PLAYER_LEFT_WOOK] = LoadGraph("Data/Effect/PlayerDead.png");
	g_AnimationEffectHandle[PLAYER_JUMP] = LoadGraph("Data/Effect/EnemyDead.png");
	
}

// エフェクトステップ
void StepAnimationEffect()
{
	AnimationData* effect = g_AnimationData;
	for (int i = 0; i < ANIMATION_MAX; i++, effect++)
	{
		if (!effect->active)continue;



		if (effect->timer <= 0)
		{
			effect->nowFrame++;

			effect->timer = effect->interval;

			if (effect->nowFrame >= effect->frameNum)
			{
				effect->active = false;

				continue;
			}
		}


		effect->timer--;

	}
}

// エフェクト更新
void UpdateAnimationEffect()
{
}

// エフェクト描画
void DrawAnimationEffect()
{
	AnimationData* effect = g_AnimationData;
	for (int i = 0; i < ANIMATION_MAX; i++, effect++)
	{
		// 未使用のエフェクトは処理しない
		if (!effect->active)continue;

		// 1コマ分の横幅（effect->frameWidth）と
		// 現在のコマ数（effect->nowFrame）から、
		// 切り取る部分を計算する
		int srcX = effect->nowFrame * effect->frameWidth;
		int srcY = 0.0f;


		// DrawRectGraph関数で描画すべきコマの部分だけ描画する
		DrawRectGraph((int)effect->posX, (int)effect->posY, srcX, srcY, effect->frameWidth, effect->frameHeight, effect->handle, TRUE);

	}
}

// エフェクト終了
void FinAnimationEffect()
{
	for (int i = 0; i < ANIMATION_TYPE_MAX; i++)
	{
		DeleteGraph(g_AnimationEffectHandle[i]);
	}
}

// エフェクト再生
void PlayAnimation(AnimationType type, float posX, float posY, int interval)
{
	// マスターパラム取得
	AnimationMasterParameter param = ANIM_MASTER_PARAM[type];

	AnimationData* effect = g_AnimationData;
	for (int i = 0; i < ANIMATION_MAX; i++, effect++)
	{
		// 未使用のエフェクトを探す
		if (!effect->active)
		{
			// アクティブ
			effect->active = true;

			// 座標設定
			effect->posX = posX;
			effect->posY = posY;

			// インターバル設定
			effect->interval = interval;

			// タイマー設定
			effect->timer = effect->interval;

			// 画像ハンドル
			effect->handle = g_AnimationEffectHandle[type];

			// 0コマ目にする
			effect->nowFrame = 0;

			// コマ数
			effect->frameNum = param.frameNum;

			// 1コマのサイズ
			effect->frameWidth = param.frameWidth;
			effect->frameHeight = param.frameHeight;

			break;
		}
	}
}
