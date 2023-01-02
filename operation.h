#ifndef MAC_CALCULATOR_GUI_OPERATION_H
#define MAC_CALCULATOR_GUI_OPERATION_H

/*紀錄運算的式子*/
typedef struct Operation{
    double left; //左數
    double right;//右數
    double (*operator)(double,double); //要做的運算
}Operation;

//執行Operation中的函數物件:也就是執行運算
double OperationApply(Operation *operation);

/*四則運算*/
double Plus(double left,double right);
double Minus(double left,double right);
double Multiply(double left,double right);
double Divide(double left,double right);
#endif //MAC_CALCULATOR_GUI_OPERATION_H
