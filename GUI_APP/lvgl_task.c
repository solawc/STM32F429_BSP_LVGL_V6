#include "lvgl_task.h"

lv_task_t *task1 = NULL;

void task_led(lv_task_t *task)
{
    bsp_led_toggle(BSP_LED_B);
}

void led_task_start(void)
{
    task1 = lv_task_create(task_led,5000,LV_TASK_PRIO_LOW,NULL);
}


lv_obj_t *scr;
lv_obj_t *obj1 = NULL;
lv_obj_t *obj2 = NULL;
lv_obj_t *obj3 = NULL;
lv_style_t red_style;

void lv_obj_test_start(void)
{
    scr = lv_scr_act();
    obj1 = lv_obj_create(scr,NULL);
//    lv_style_copy(&red_style,&lv_style_plain_color);
//    red_style.body.main_color = LV_COLOR_RED;
//    red_style.body.grad_color = LV_COLOR_RED;
}

