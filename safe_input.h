#ifndef SAFE_INPUT_H
#define SAFE_INPUT_H
#include "my_define.h"

// チャタリング対策をした入力受け取り関数
// 離された時に発火する。
// 戻り値
//     スイッチON ：1
//     スイッチOFF：0

u8 safe_in_sw1();

u8 safe_in_sw2();

u8 safe_in_sw3();

#endif // include guard SAFE_INPUT_H