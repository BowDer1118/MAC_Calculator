#include "unit_test_ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static UIContext *ui_context;
char *kOutputBuffer;

static void DisplayTextToBuffer(char *text){
    sprintf(ui_context->text_displayer,text);
}

static void UnitTestMain(){
    FILE *case_file = fopen("cases.txt", "r");
    //檢查開啟結果
    if(case_file){
        char key;
        char output_result[MAX_CHAR+1];
        //持續UnitTest
        while(fscanf(case_file," %c,%s",&key,output_result)!=EOF){
            //檢查輸入合法性
            if(HandleInput(ui_context->context,key)){
                if(strcmp(output_result,ui_context->text_displayer)==0){
                    printf("Input [%c]: Output: %s, OK\n",key,output_result);
                }else{
                    printf("Input [%c]: Output: %s, Expect: %s, ERROR\n",key,ui_context->text_displayer,output_result);
                }
            }else{
                fprintf(stderr,"Invalid input: %c\n",key);
            }
        }
        fclose(case_file);
    }else{
        perror("Open case file failed.");
    }
}

static void InitUnitTest(){
    kOutputBuffer= malloc(MAX_CHAR+1);
    ui_context= malloc(sizeof(UIContext));
    ui_context->text_displayer=kOutputBuffer;
    ui_context->context=CreateCalcContext();
    ui_context->context->display_text=DisplayTextToBuffer;
}


static void DestroyUnitTest(){
    DestroyCalcContext(&ui_context->context);
    free(ui_context->text_displayer);
    free(ui_context);
    ui_context=NULL;
}

int RunUnitTest(int argc,char **argv){
    InitUnitTest();
    UnitTestMain();
    DestroyUnitTest();
    return 0;
}