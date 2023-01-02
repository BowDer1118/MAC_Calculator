#include <stdio.h>
#include <string.h>
#include "console_ui.h"
#include "unit_test_ui.h"
#include "gtk_ui.h"

int main(int argc,char *argv[]){
    printf("Input argument number:%d\n",argc);
    for(int i=0;i<argc;i++){
        puts(argv[i]);
    }

    //判斷輸入參數
    if(argc>1){
        //字串比對
        if(strcasecmp(argv[1],"console")==0){
            puts("Activate Console Mode");
            return RunConsoleUi(argc,argv);
        }else if(strcasecmp(argv[1],"ut")==0){
            puts("Activate Unit Test Mode");
            return RunUnitTest(argc,argv);
        }
    }

    //默認啟動GtkUI
    return RunGtkUI(argc,argv);
}
