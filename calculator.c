#include "calculator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//負責清空CalcContext中的buffer
static void ClearBuffer(CalcContext *context){
    context->input_buffer[0]='\0';
    context->input_buffer_position=0;
}

//負責清空CalcContext的內容
static void ClearAll(CalcContext *context){
    //清除buffer
    ClearBuffer(context);
    context->result=0;
    //將結構體內部資料清為0
    memset(&context->previous_operation,0,sizeof(Operation));
    memset(&context->current_operation,0,sizeof(Operation));
}

//格式化要輸出的字串
static void FormatOutput(CalcContext *context){
    if(context->result==-0.0){
        context->result=0.0;
    }
    //使用科學記號表示法(%g會自動選擇科學記號或正常輸出法)
    sprintf(context->input_buffer,"%.6g",context->result);
}

//輸出結果
static void DisplayOutput(CalcContext *context){
    FormatOutput(context);
    context->display_text(context->input_buffer);
    ClearBuffer(context);
}

//格式化輸入:排除不合法狀況
static void FormatInput(CalcContext *context){
    if(context->input_buffer_position==0){
        //沒有任何輸入
        context->input_buffer[0]='0';
        context->input_buffer[1]='\0';
        context->input_buffer_position=1;
    }else if(context->input_buffer_position==1){
        //一開始就輸入小數點
        if(context->input_buffer[0]=='.'){
            context->input_buffer[0]='0';
            context->input_buffer[1]='.';
            context->input_buffer[1]='\0';
            context->input_buffer_position=2;
        }
    }else if(context->input_buffer_position>1){
        char *p=context->input_buffer;
        //處理以0和.開頭的狀況
        if(p[0]=='0'&&p[1]!='.'){
            p[0]=p[1];
            p[1]='\0';
            context->input_buffer_position=1;
        }else if(p[context->input_buffer_position-1]=='.'){
            //最後一個數值為小數點-->去除新加入的小數點
            for(int i=0;i<context->input_buffer_position-1;i++){
                if(p[i]=='.'){
                    context->input_buffer_position--;
                    p[context->input_buffer_position]='\0';
                    break;
                }
            }
        }
    }
}

//輸出當前輸入的字串
static void DisplayInput(CalcContext *context){
    FormatInput(context);
    context->display_text(context->input_buffer);
}

static void ApplyInput(CalcContext *context,double *operand){
    if(context->input_buffer_position>0){
        //有新的輸入
        *operand=atof(context->input_buffer);
        ClearBuffer(context);
    }else{
        //沒有新的輸入-->上次的運算結果被保存
        *operand=context->result;
    }
}

static void ApplyInputToLeft(CalcContext *context){
    ApplyInput(context,&context->current_operation.left);
}

static void ApplyInputToRight(CalcContext *context){
    ApplyInput(context,&context->current_operation.right);
}


static void ApplyPreviousOperation(CalcContext *context){
    //執行運算
    context->result= OperationApply(&context->previous_operation);
}

static void ApplyCurrentOperation(CalcContext *context){
    //執行運算
    context->result= OperationApply(&context->current_operation);
    //將當前運算變成上一次的運算
    memcpy(&context->previous_operation,&context->current_operation,sizeof(Operation));
    memset(&context->current_operation,0,sizeof(Operation));
}



//文字輸入時要做的動作，輸入不合法就返回0
int HandleInput(CalcContext *context,char input_value){
    switch(input_value){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':{
                //還有位置可以接收輸入
                if(context->input_buffer_position<MAX_CHAR){
                    //存放輸入
                    context->input_buffer[context->input_buffer_position]=input_value;
                    context->input_buffer_position++;
                    context->input_buffer[context->input_buffer_position]='\0';
                }
                DisplayInput(context);
                break;
            }
        case '+':
            context->current_operation.operator=Plus;
            ApplyInputToLeft(context);
            break;
        case '-':
            context->current_operation.operator=Minus;
            ApplyInputToLeft(context);
            break;
        case '*':
            context->current_operation.operator=Multiply;
            ApplyInputToLeft(context);
            break;
        case '/':
            context->current_operation.operator=Divide;
            ApplyInputToLeft(context);
            break;
        case '=': //等號
            //如果有運算元
            if(context->current_operation.operator){
                ApplyInputToRight(context);
                ApplyCurrentOperation(context);
                DisplayOutput(context);
            }else if(context->previous_operation.operator){ //如果前一次有操作
                //拿上一次的結果來運算
                context->previous_operation.left=context->result;
                ApplyPreviousOperation(context);
                DisplayOutput(context);
            }else{
                printf("No Operation.\n");
            }
            break;
        case '%': //百分號
            //當前數值直接*0.01
            ApplyInputToLeft(context);
            context->current_operation.operator=Multiply;
            context->current_operation.right=0.01;
            ApplyCurrentOperation(context);
            DisplayOutput(context);
            break;
        case 'S': //正負號
            //當前數值直接*(-1)
            ApplyInputToLeft(context);
            context->current_operation.operator=Multiply;
            context->current_operation.right=-1;
            ApplyCurrentOperation(context);
            DisplayOutput(context);
            break;
        case 'C': //清除
            ClearAll(context);
            DisplayInput(context);
            break;
    }
    return 1;
}



//提供CalcContext物件
CalcContext *CreateCalcContext(){
    CalcContext *calcContext= malloc(sizeof(CalcContext));
    ClearAll(calcContext);
    calcContext->display_text=NULL;
    return calcContext;
}

//銷毀CalcContext物件
void DestroyCalcContext(CalcContext **p_context){
    free(*p_context);
    *p_context=NULL;
}