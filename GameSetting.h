//-------------------------------------
// Player設定
//-------------------------------------
//#define PLAYER_SPEED 0.1f // Playerの移動速度
//#define PLAYER_ROTATE_SPEED 0.05f // Playerの回転速度
//-------------------------------------
// Enemy関連
//-------------------------------------

//-------------------------------------
// 螺旋状に動く敵
//-------------------------------------
#define SPIRAL_ENEMY_MAX 6 // 螺旋状に動く敵の最大数
#define SPIRAL_ENEMY_ANGLE 0.0f // 螺旋運動の角度
#define SPIRAL_ENEMY_ANGULAR_SPEED 1.5f // 螺旋運動の角度の増加スピード　1秒間に何ラジアン回転するか
#define SPIRAL_ENEMY_RADIUS 30.0f // 螺旋運動の半径　Playerからの距離
#define SPIRAL_ENEMY_RADIAL_SPEED 5.0f // 螺旋運動の半径の減少スピード　1秒間に何メートル近づくか
#define SPIRAL_ENEMY_TIME_SINCE_ENTERED 0.0f // Playerの範囲に入ってからの経過時間
#define SPIRAL_ENEMY_PROXIMITY_RADIUS 5.0f // Enemyがこの範囲に入ったら、enteredProximity_をtrueにしてタイマーがスタート
#define SPIRAL_ENEMY_DISAPPEAR_AFTER 2.0f // Playerの範囲に入ってから何秒後に消えるか　timeSinceEntered_がこの値以上になったら敵を消滅させる

#define SPIRAL_ENEMY_MINIMUM_VALUE 20.0f// ランダムの下限値。半径が最低でもこれになる
#define SPIRAL_ENEMY_MAXIMUM_VALUE 20.0f// ランダムの幅です。rand() の結果を0～1に正規化した上で、この幅だけプラスされる
#define SPIRAL_ENEMY_MIN_RADIUS 0.5f // PlayerとEnemyの最低半径

//-------------------------------------
// 直線的に動く敵
//-------------------------------------
#define STRAIGHT_LINE_ENEMY_MAX 6 // 直線的に動く敵の最大数
#define STRAIGHT_LINE_ENEMY_SPEED 5.0f // 敵の進行速度
#define STRAIGHT_LINE_ENEMY_STOP_RADIUS 0.5f  // 到達半径速度
#define STRAIGHT_LINE_ENEMY_MINIMUM_VALUE 20.0f// ランダムの下限値。半径が最低でもこれになる
#define STRAIGHT_LINE_ENEMY_MAXIMUM_VALUE 15.0f// ランダムの幅　rand() の結果を0～1に正規化した上で、この幅だけプラスされる

//-------------------------------------
// その他
//-------------------------------------
#define INVALID_MODEL_HANDLE 0 // assert(hModel_ >= 0)モデルの読み込みが成功しているかを判定するための基準値
#define FLOAT_ZERO_THRESHOLD 0.0001f // しきい値

