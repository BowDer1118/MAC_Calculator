#include "gtk_ui.h"
#include <stdlib.h>
#include <gtk/gtk.h>

//定義MACRO輔助綁定按鈕與事件

#define input_0 "0"
#define input_1 "1"
#define input_2 "2"
#define input_3 "3"
#define input_4 "4"
#define input_5 "5"
#define input_6 "6"
#define input_7 "7"
#define input_8 "8"
#define input_9 "9"
#define input_plus "+"
#define input_minus "-"
#define input_multiply "*"
#define input_divide "/"
#define input_equal "="
#define input_clear "C"
#define input_sign "S"
#define input_percent "%"
#define input_point "."

#define BIND_BUTTON(builder, input_value) \
{GtkButton* button_input_##input_value = (GtkButton *) gtk_builder_get_object(builder, "input_"#input_value); \
g_signal_connect(button_input_##input_value, "clicked", G_CALLBACK(OnInputButtonClicked), input_##input_value);}

static UIContext *ui_context;

//輸出資訊到GUI上
static void DisplayTextWithGtkLabel(char *text){
    gtk_label_set_text(ui_context->text_displayer,text);
}

//按鈕被點擊的事件
static void OnInputButtonClicked(void *widget,void *data){
    HandleInput(ui_context->context,((char*)data)[0]);
}

//初始化Gtk的GUI
static void GTKUIMain(int argc,char *argv[]){
    //初始化gtk
    gtk_init(&argc,&argv);
    GError *error=NULL;

    //載入Css
    GtkCssProvider *css_provider=gtk_css_provider_new();
    if(gtk_css_provider_load_from_path(css_provider,"calculator.css",&error)==0){
        g_printerr("Error loading css file: %s\n",error->message);
        g_clear_error(&error);
        return;
    }

    //載入GUI介面
    GtkBuilder *builder=gtk_builder_new();
    if(gtk_builder_add_from_file(builder,"calculator.ui",&error)==0){
        g_printerr("Error loading layout file: %s\n",error->message);
        g_clear_error(&error);
        return;
    }

    //獲取視窗物件
    GtkWindow *window=(GtkWindow *) gtk_builder_get_object(builder,"window");
    //載入CSS到視窗中
    gtk_style_context_add_provider_for_screen(gtk_window_get_screen(window),css_provider,GTK_STYLE_PROVIDER_PRIORITY_USER);
    //綁定事件
    g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
    //指定label為輸出位置
    ui_context->text_displayer=(GtkLabel*) gtk_builder_get_object(builder,"display");

    //獲取按鈕物件並綁定事件
//    GtkButton *button_input_0=(GtkButton*) gtk_builder_get_object(builder,"input_0");
//    g_signal_connect(button_input_0,"clicked",G_CALLBACK(OnInputButtonClicked),"0");
    BIND_BUTTON(builder, 0)
    BIND_BUTTON(builder, 1)
    BIND_BUTTON(builder, 2)
    BIND_BUTTON(builder, 3)
    BIND_BUTTON(builder, 4)
    BIND_BUTTON(builder, 5)
    BIND_BUTTON(builder, 6)
    BIND_BUTTON(builder, 7)
    BIND_BUTTON(builder, 8)
    BIND_BUTTON(builder, 9)
    BIND_BUTTON(builder, plus)
    BIND_BUTTON(builder, minus)
    BIND_BUTTON(builder, multiply)
    BIND_BUTTON(builder, divide)
    BIND_BUTTON(builder, equal)
    BIND_BUTTON(builder, clear)
    BIND_BUTTON(builder, sign)
    BIND_BUTTON(builder, percent)
    BIND_BUTTON(builder, point)

    HandleInput(ui_context->context,'0');
    //啟動GUI
    gtk_main();

    //釋放記憶體
    g_object_unref(builder);
    gtk_style_context_remove_provider_for_screen(gtk_window_get_screen(window),css_provider);
    g_object_unref(css_provider);
}

//初始化控制台物件
static void InitGTKUI(){
    ui_context= malloc(sizeof(UIContext));
    ui_context->context=CreateCalcContext();
    ui_context->context->display_text=DisplayTextWithGtkLabel;
}

//銷毀控制台物件
static void DestroyGTKUI(){
    DestroyCalcContext(&ui_context->context);
    free(ui_context);
    ui_context=NULL;
}

//啟動控制台UI
int RunGtkUI(int argc,char *argv[]){
    InitGTKUI();
    GTKUIMain(argc,argv);
    DestroyGTKUI();
    return 0;
}