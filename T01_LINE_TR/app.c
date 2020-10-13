#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// センサーポートを設定
#define color_sensor EV3_PORT_3

// 待機時間の設定 [msec]
const uint32_t WAIT_TIME_MS = 100;