#ifndef MAC_CALCULATOR_GUI_CALCULATOR_H
#define MAC_CALCULATOR_GUI_CALCULATOR_H
#include "operation.h"

//支援顯示13個字元(ex:-1.56805e+015)
#define MAX_CHAR 13

/*紀錄要顯示的字串結果*/
typedef struct {
    char input_buffer[MAX_CHAR+1]; //存放字串
    int input_buffer_position; //紀錄陣列當前使用量
    double result; //當前計算結果

    Operation previous_operation; //上一次的運算
    Operation current_operation; //當前的運算

    void (*display_text)(char*); //用來輸出字串的函數指標
}CalcContext;

//文字輸入時要做的動作
int HandleInput(CalcContext *context,char input_value);

//提供CalcContext物件
CalcContext *CreateCalcContext();
//銷毀CalcContext物件
void DestroyCalcContext(CalcContext **p_context);

#endif //MAC_CALCULATOR_GUI_CALCULATOR_H
