#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "GameSetting.h"
/// <summary>
/// Playerを見つけたらまっすぐ進む敵クラス
/// </summary>
class StraightLineEnemy :
    public GameObject
{
private:
	int hStraightLineEnemyModel_;

    bool lockedOn_ = false;
    XMFLOAT3 targetPos_;
    float speed_ = 5.0f; // 進行速度
    float stopRadius_ = 0.5f; // 到達半径速度
public:
	StraightLineEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
    Player* player_ = nullptr;
	//　Playerを見つけたら、見つけた時点でのPlayerのポジションに向かってまっすぐ進む敵クラスを実装したい
};