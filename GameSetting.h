#pragma once
//-------------------------------------
// Player設定
//-------------------------------------
#define PLAYER_SPEED					  0.1f // Playerの移動速度
#define PLAYER_ROTATE_SPEED				  0.05f // Playerの回転速度
#define PLAYER_HP_NUMBER_DIGITS_MIN_ARRAY 0 // PlayerのHPの桁数の最小桁数の配列
#define PLAYER_HP_NUMBER_DIGITS_MAX_ARRAY 1 // PlayerのHPの桁数の最大桁数の配列
#define PLAYER_HP_NUMBER_DIGITS_MIN       1 // PlayerのHPの桁数の最小桁数
#define PLAYER_HP_MIN                     0 // PlayerのHPの最小値
#define PLAYER_HP_MAX                   999 // PlayerのHPの最大値
#define PLAYER_HP_DOWN					  1 // PlayerのHPの減少値
#define PLAYER_HP_INIT					  5 // PlayerのHPの初期値					      5 // PlayerのHPの初期値
#define PLAYER_RADIUS					  0.5f //Playerの半径（当たり判定用）
#define PLAYER_INIT_INVINCIBLE_TIMER_MIN  0.0f //無敵時間の初期値
//-------------------------------------
// HP関連
//-------------------------------------
#define CHAR_MIN_INDEX    0
#define CHAR_PER_ROW     16   // 1行あたりの文字数（char.pngの横方向）
#define CHAR_TOTAL_COUNT 94   // 利用可能な文字数

//-------------------------------------
// Enemy関連
//-------------------------------------

//-------------------------------------
// 螺旋状に動く敵
//-------------------------------------
#define SPIRAL_ENEMY_MAX				6 // 螺旋状に動く敵の最大数
#define SPIRAL_ENEMY_ANGLE				0.0f // 螺旋運動の角度
#define SPIRAL_ENEMY_ANGULAR_SPEED		1.5f // 螺旋運動の角度の増加スピード　1秒間に何ラジアン回転するか
#define SPIRAL_ENEMY_RADIUS			   30.0f // 螺旋運動の半径　Playerからの距離
#define SPIRAL_ENEMY_RADIAL_SPEED		5.0f // 螺旋運動の半径の減少スピード　1秒間に何メートル近づくか
#define SPIRAL_ENEMY_TIME_SINCE_ENTERED	0.0f // Playerの範囲に入ってからの経過時間
#define SPIRAL_ENEMY_PROXIMITY_RADIUS   5.0f // Enemyがこの範囲に入ったら、enteredProximity_をtrueにしてタイマーがスタート
#define SPIRAL_ENEMY_DISAPPEAR_AFTER    2.0f // Playerの範囲に入ってから何秒後に消えるか　timeSinceEntered_がこの値以上になったら敵を消滅させる

#define SPIRAL_ENEMY_MINIMUM_VALUE 20.0f// ランダムの下限値。半径が最低でもこれになる
#define SPIRAL_ENEMY_MAXIMUM_VALUE 20.0f// ランダムの幅です。rand() の結果を0～1に正規化した上で、この幅だけプラスされる
#define SPIRAL_ENEMY_MIN_RADIUS     0.5f // PlayerとEnemyの最低半径

//-------------------------------------
// 直線的に動く敵
//-------------------------------------
#define STRAIGHT_LINE_ENEMY_MAX            6 // 直線的に動く敵の最大数
#define STRAIGHT_LINE_ENEMY_SPEED          5.0f // 敵の進行速度
#define STRAIGHT_LINE_ENEMY_STOP_RADIUS    0.5f  // 到達半径速度
#define STRAIGHT_LINE_ENEMY_MINIMUM_VALUE 20.0f// ランダムの下限値。半径が最低でもこれになる
#define STRAIGHT_LINE_ENEMY_MAXIMUM_VALUE 15.0f// ランダムの幅　rand() の結果を0～1に正規化した上で、この幅だけプラスされる



//-------------------------------------
// その他
//-------------------------------------
#define INVALID_MODEL_HANDLE 0 // assert(hModel_ >= 0)モデルの読み込みが成功しているかを判定するための基準値
#define INVALID_IMAGE_HANDLE 0 // assert(hPict_ >= 0)画像の読み込みが成功しているかを判定するための基準値
#define INVALID_OBJECT_HANDLE -1 // 基準値画像やモデルの番号は０以上（０も含む）の値になるので-1

//-------------------------------------
// マジックナンバーを防ぐための応急処置
//-------------------------------------
#define FLOAT_ZERO_THRESHOLD 0.0001f // しきい値
#define ZERO                 0.0f    // 0の定義 マジックナンバー防ぐため
#define ONE                  1.0f    // 1の定義 マジックナンバー防ぐため
#define TWO_DEGREES          2.0f    // 2度の定義 マジックナンバー防ぐため
#define FIVE_DEGREES         5.0f    // 5度の定義 マジックナンバー防ぐため
#define ALPHA_OPAQUE       255.0f    // 完全不透明