#ifndef MAC_CALCULATOR_GUI_UI_H
#define MAC_CALCULATOR_GUI_UI_H
#include "calculator.h"
//定義UI通用的Interface

typedef struct {
    void *text_displayer; //資料要往哪裡輸出
    CalcContext *context;
}UIContext;

#endif //MAC_CALCULATOR_GUI_UI_H
