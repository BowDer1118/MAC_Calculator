#include "console_ui.h"
#include <stdlib.h>
#include <stdio.h>

UIContext *ui_context;

//控制台要輸出文字的方法
static void DisplayTextWithFile(char *text){
    //將text寫入text_displayer中(當前也就是stdout)
    fputs(text,ui_context->text_displayer);
    fputc('\n',ui_context->text_displayer);

    //沖洗緩衝區
    fflush(ui_context->text_displayer);
}

static void ConsoleMain(){
    int next_input=getchar();

    //檢查輸入
    while (next_input!=EOF&&next_input!='q'&&next_input!='Q'){ //按Q結束
        HandleInput(ui_context->context,next_input);
        next_input=getchar();
    }
    puts("Thank you");
}

//初始化控制台物件
static void InitConsole(){
    ui_context= malloc(sizeof(UIContext));
    ui_context->text_displayer=stdout;
    ui_context->context=CreateCalcContext();
    ui_context->context->display_text=DisplayTextWithFile;
}

//銷毀控制台物件
static void DestroyConsole(){
    DestroyCalcContext(&ui_context->context);
    free(ui_context);
    ui_context=NULL;
}

//啟動控制台UI
int RunConsoleUi(int argc,char **argv){
    InitConsole();
    ConsoleMain();
    DestroyConsole();
    return 0;
}