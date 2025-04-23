#pragma once
#include "Enemy.h"
#include "Player.h"
#include "GameSetting.h"
/// <summary>
/// Playerを見つけたらまっすぐ進む敵クラス
/// </summary>
class StraightLineEnemy :
    public Enemy
{
private:
	int hStraightLineEnemyModel_;

    bool lockedOn_ = false;
    XMFLOAT3 targetPos_;
    float speed_ = STRAIGHT_LINE_ENEMY_SPEED; // 進行速度
    float stopRadius_ = STRAIGHT_LINE_ENEMY_STOP_RADIUS; // 到達半径速度
public:
	StraightLineEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
    Player* player_ = nullptr;
	//　Playerを見つけたら、見つけた時点でのPlayerのポジションに向かってまっすぐ進む敵クラスを実装したい
};