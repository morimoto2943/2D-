#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Collision/Collision.h"
#include "../Collision/CollisionParameter.h"
#include "../player/player.h"


// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void ResolveMapchipX(Body* body, const MapChipData* mapchip);
void ResolveMapchipY(Body* body, const MapChipData* mapchip);
void PreviewSlope(Body* body, int range);

void InitMap()
{
	InitBlock();
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
}

void ChceckMapPlayerCollision()
{
	

}




void ResolveMapCollision(Body* body, int range)
{
	// 1. 全ブロックを取得する
	BlockData* blocks = GetBlocks();

	// 2. すべてのブロックとプレイヤーの当たり判定をチェックする
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (!blocks[i].active)
		{
			continue; // 非アクティブなブロックはスキップ
		}

		// 3. プレイヤーとブロックの矩形同士が当たっているか判定
		if (CheckSquareSquare(body->pos, (float)body->width, (float)body->height,
			blocks[i].pos, blocks[i].width, blocks[i].height))
		{
			// 4. 下降中（落下中）にブロックの上に着地した場合の処理
			if (body->move.y > 0.0f)
			{
				// プレイヤーのY座標をブロックの上面にピタッと合わせる
				body->pos.y = blocks[i].pos.y - (float)body->height;

				// 落下速度をリセット
				body->move.y = 0.0f;

				// 着地したので空中フラグを false にする
				body->isAir = false;

				// 乗っている足場ブロックを記録
				body->groundBlock = &blocks[i];
			}
			// 5. 上昇中（ジャンプ中）に頭がブロックの下側にぶつかった場合の処理
			else if (body->move.y < 0.0f)
			{
				// プレイヤーのY座標をブロックの底面に合わせる
				body->pos.y = blocks[i].pos.y + blocks[i].height;

				// 上への移動量をリセット（頭打ち）
				body->move.y = 0.0f;
			}
		}
	}
}

void ResolveMapCollisionX(Body* body, int range)
{
	
	
}

void ResolveMapCollisionY(Body* body, int range)
{
	
	
}

/// <summary>
/// X軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipX(Body* body, const MapChipData* mapchip)
{
	
}

/// <summary>
/// Y軸の衝突解決
/// </summary>
/// <param name="body">当たり判定ボディ</param>
/// <param name="mapchip">マップチップ</param>
void ResolveMapchipY(Body* body, const MapChipData* mapchip)
{
	
}

void PreviewSlope(Body* body, int range)
{
	
	
}
