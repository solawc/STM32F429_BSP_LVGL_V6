#include "lvgl_task.h"


void lv_label_test(void)
{   
    lv_obj_t *scr = lv_scr_act();

    lv_obj_t *label_1 = lv_label_create(scr,NULL);
    lv_obj_set_pos(label_1,50,50);
    lv_label_set_body_draw(label_1,true);
    lv_label_set_style(label_1,LV_LABEL_STYLE_MAIN,&lv_style_plain_color);

    // lv_label_set_text(label_1,"hi HJH\nYou are so strong!");
    // lv_label_set_array_text(label_1,name,sizeof((name)-1));
    // lv_label_set_long_mode(label_1,LV_LABEL_LONG_EXPAND);
    // lv_label_set_long_mode(label_1,LV_LABEL_LONG_BREAK);
    lv_label_set_long_mode(label_1,LV_LABEL_LONG_SROLL);
    lv_obj_set_size(label_1,100,50);
    lv_label_set_recolor(label_1,true);
    lv_label_set_text(label_1,"#00ff00 hi HJH#,#ff0000 You are so strong!#");

}

lv_style_t my_style;
void lv_style_test(void)
{


}

