// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.2
// LVGL version: 8.2.0
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
void ui_event_Arc2( lv_event_t * e);
lv_obj_t *ui_Arc2;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Label2;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Arc2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_arc_set_text_value( ui_Label2, target, "", "%");
}
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x595A5A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Arc2 = lv_arc_create(ui_Screen1);
lv_obj_set_width( ui_Arc2, lv_pct(85));
lv_obj_set_height( ui_Arc2, lv_pct(85));
lv_obj_set_x( ui_Arc2, -1 );
lv_obj_set_y( ui_Arc2, 2 );
lv_obj_set_align( ui_Arc2, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Arc2,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Arc2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_add_flag( ui_Arc2, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_set_style_arc_width(ui_Arc2, 30, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(ui_Arc2, lv_color_hex(0x00FF5E), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_Arc2, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_Arc2, 30, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_Arc2, lv_color_hex(0x00FF5E), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Arc2, 255, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_Panel2 = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_Panel2, lv_pct(60));
lv_obj_set_height( ui_Panel2, lv_pct(60));
lv_obj_set_align( ui_Panel2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel2, 350, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x3D3D3D), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_Panel2, lv_color_hex(0x525151), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_grad_dir(ui_Panel2, LV_GRAD_DIR_VER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label2 = lv_label_create(ui_Screen1);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 200
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 200
lv_obj_set_x( ui_Label2, 2 );
lv_obj_set_y( ui_Label2, -2 );
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label2,"50%");
lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x00FF5E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label2, &ui_font_fotn2, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Arc2, ui_event_Arc2, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen1_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_Screen1);
}
