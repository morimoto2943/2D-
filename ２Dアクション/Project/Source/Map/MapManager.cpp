#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"


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
