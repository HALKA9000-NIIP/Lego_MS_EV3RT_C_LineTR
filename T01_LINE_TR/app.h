#include "target_test.h"

#ifndef STACK_SIZE
#define STACK_SIZE 4096
#endif /* STACK_SIZE */

/* 関数のプロトタイプ宣言 */
#ifndef TOPPERS_MACRO_ONLY
extern void main_task(intptr_t exinf);
extern void run_task(intptr_t exinf);
#endif /* TOPPERS_MACRO_ONLY */

/* 以下独自ヘッダ内容 */

/* カラーセンサ関係 */
#define BrackToGray 
#define GrayToBrack 
#define GrayToWhite 