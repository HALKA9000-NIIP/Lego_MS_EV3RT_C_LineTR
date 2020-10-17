#include "ev3api.h"
#include "app.h"
#include <math.h>

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// センサーポートを設定
#define color_sensor_right EV3_PORT_2
#define color_sensor_left EV3_PORT_3

#define R_motor EV3_PORT_B
#define L_motor EV3_PORT_C

#define black 30 //黒色の値を定義
#define white 73 //白色の値を定義

// 待機時間の設定 [msec]
const uint32_t WAIT_TIME_MS = 100;
FILE *file;
int now_val_left=0, now_val_right=0; //初期化
colorid_t now_color_left, now_color_right;
int left_inner_black,right_inner_black,left_inner_white,right_inner_white;
char conJudI[3]="";
int phase = 0;
long getTS(){}
char getRUS(){
    return "##";
}

void fileInit(char fileName[]){
    file = fopen(fileName,"a");
}
void fileEnd(){
    fclose(file);
}
void dataWrite(long time,char *runs,char *code, char *param){
    fprintf(file , "$ %d %ld %s : %s %s***\n" ,i++,time,runs,code,param);
}
int optMath(int rIn){
    //REFLECT 値の正規化
    int rMax=90;
    int rMin=50;
    double diffpd=45.5;
    double ruint=15;
    double rAve=(rMin+rMax)/2;
    double rDiff=rMax-rAve;
    double rCoss = acos((rIn-rAve)/rDiff);
    return (rCoss*ruint)+diffpd;
}
void optMeas(){
    //REFLECT 値と COLOR 値を取得
    now_val_left = optMath(ev3_color_sensor_get_reflect(color_sensor_left));
    now_val_right = optMath(ev3_color_sensor_get_reflect(color_sensor_right));
    now_color_left = optMath(ev3_color_sensor_get_color(color_sensor_left));
    now_color_right = optMath(ev3_color_sensor_get_color(color_sensor_right));
    dataWrite(getTS(),getRUS(),"col","reflect "+now_val_left+" left");
    dataWrite(getTS(),getRUS(),"col","reflect "+now_val_right+" right");
    dataWrite(getTS(),getRUS(),"col","color "+now_color_left+" left");
    dataWrite(getTS(),getRUS(),"col","color "+now_color_right+" right");
}

void conJud(int val_left,int val_right){
    left_inner_black=(val_left < black)?1:0;
    right_inner_black=(val_right < black)?1:0;
    left_inner_white=(val_left > white)?1:0;
    right_inner_white=(val_right > white)?1:0;

    if (left_inner_black==1)
    {
        conJudI="le";
    }else
    {
        if ((left_inner_black+right_inner_black+left_inner_white+right_inner_white)==2)
        {
            conJudI="le";
        }else
        {
            conJudI="st";
        }
    }
    
    
}
void cyclic_task(intptr_t exinf)
{

    int power, turn; int now_val = 0;int i=0;
    const int threshold = (black + white) / 2;
    power = 20;
    turn =0;
    


    while(1)
    {


        conJud(now_val_left,now_val_right);
        switch (conJudI)
        {
        case "le":
            /* code */
            break;
        case "ri":
            /* code */
            break;
        case "st":
            /* code */
            break;
        default:
            break;
        }


    }

    
}


void main_task(intptr_t unused) {
    fileInit("./d1015.txr");
/* モーターの設定 */
    ev3_motor_config( L_motor , LARGE_MOTOR );
    ev3_motor_config( R_motor , LARGE_MOTOR );
    /* センサーの設定 */
    ev3_sensor_config( color_sensor_right, COLOR_SENSOR );
    ev3_sensor_config( color_sensor_left, COLOR_SENSOR );
    /* タスクを開始する */
     ev3_sta_cyc(CYCHDR1);
     fileEnd();
}





