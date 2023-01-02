#include "operation.h"
#include <math.h>

//執行Operation中的函數物件:也就是執行運算
double OperationApply(Operation *operation){
    //判斷operator是否有指派
    if(operation->operator){
        //有operator-->直接執行
        return operation->operator(operation->left,operation->right);
    }else{
        //沒有operator--->回傳0.0
        return 0.0;
    }
}

/*四則運算*/
double Plus(double left,double right){
    return left+right;
}
double Minus(double left,double right){
    return left-right;
}
double Multiply(double left,double right){
    return left*right;
}
double Divide(double left,double right){
    //檢查除數不為0--->誤差:小於10^-6
    if(fabs(right-0.0)<pow(10,-6)){
        return 0.0;
    }else{
        return left/right;
    }
}