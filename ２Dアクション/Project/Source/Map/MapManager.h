#pragma once

struct Body;
struct MapChipData;


void InitMap();
void LoadMap();
void StartMap();
void DrawMap();
void FinMap();

void ChceckMapPlayerCollision();


// 当たり判定関数
void ResolveMapCollision(Body* body, int range);	// 通常ブロック
void ResolveMapCollisionX(Body* body, int range);	// 通常ブロック
void ResolveMapCollisionY(Body* body, int range);	// 通常ブロック
