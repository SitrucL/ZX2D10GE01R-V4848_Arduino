/*
 * Project ZX2D10GE01R-V4848 for Arduino
 * Description: The base project that can be used in the Arduino environment using the ZX2D10GE01R-V4848 device
 * Author: Eric Nam
 * Date: 03-18-2023
 */

// ** Prerequisites **
// ESP32 Arduino 2.0.7 based on ESP-IDF 4.4.4
// https://github.com/espressif/arduino-esp32

// LVGL version 8.3.5
// https://github.com/lvgl/lvgl

// GFX Library for Arduino 1.3.2
// https://github.com/moononournation/Arduino_GFX

// ZX2D10GE01R-V4848 for ESP-IDF
// https://github.com/wireless-tag-com/ZX2D10GE01R-V4848

#include <iostream>

#include <Arduino_GFX_Library.h>
#include "button.hpp"
#include "mt8901.hpp"
#include <lvgl.h>
#include "ui.h"
#include "ui_helpers.h"

#define ECO_O(y) (y > 0) ? -1 : 1
#define ECO_STEP(x) x ? ECO_O(x) : 0
#define GFX_BL 38

Arduino_DataBus *bus = new Arduino_SWSPI(
  GFX_NOT_DEFINED /* DC */, 21 /* CS */,
  47 /* SCK */, 41 /* MOSI */, GFX_NOT_DEFINED /* MISO */);
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  39 /* DE */, 48 /* VSYNC */, 40 /* HSYNC */, 45 /* PCLK */,
  10 /* R0 */, 16 /* R1 */, 9 /* R2 */, 15 /* R3 */, 46 /* R4 */,
  8 /* G0 */, 13 /* G1 */, 18 /* G2 */, 12 /* G3 */, 11 /* G4 */, 17 /* G5 */,
  47 /* B0 */, 41 /* B1 */, 0 /* B2 */, 42 /* B3 */, 14 /* B4 */,
  1 /* hsync_polarity */, 10 /* hsync_front_porch */, 10 /* hsync_pulse_width */, 10 /* hsync_back_porch */,
  1 /* vsync_polarity */, 14 /* vsync_front_porch */, 2 /* vsync_pulse_width */, 12 /* vsync_back_porch */);
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  480 /* width */, 480 /* height */, rgbpanel, 0 /* rotation */, true /* auto_flush */,
  bus, GFX_NOT_DEFINED /* RST */, st7701_type7_init_operations, sizeof(st7701_type7_init_operations));

static button_t *g_btn;
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_group_t *lv_group;
static lv_obj_t *lv_btn_1;
static lv_obj_t *lv_btn_2;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void encoder_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
  static int16_t cont_last = 0;
  //Negates the encoder count to reverse direction - default is clocwise decrease
  int16_t cont_now = -mt8901_get_count();

  if (cont_now < 0) {
    cont_now = 0;
  } else if (cont_now > 100) {
    cont_now = 100;
  }
  int16_t diff = ECO_STEP(cont_last - cont_now);

  data->enc_diff = ECO_STEP(cont_now - cont_last);
  cont_last = cont_now;

  // Set the arc value
  _ui_arc_increment(ui_Arc2, diff);

  // Get the arc value and print it along with the encoder reading
  uint16_t read_arc_value = lv_arc_get_value(ui_Arc2);
  std::cout << "Current: " << cont_now << " | Prev: " << cont_last << " | Diff: " << diff << "| read value: " << read_arc_value << "\n";

  // Update the input device state based on the button press
  if (button_isPressed(g_btn)) {
    data->state = LV_INDEV_STATE_PR;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}



void setup() {
  Serial.begin(115200);

  delay(1000);
  gfx->begin();
  gfx->fillScreen(BLACK);

  pinMode(GFX_BL, OUTPUT);
  digitalWrite(GFX_BL, HIGH);

  lv_init();

  // Hardware Button
  g_btn = button_attch(3, 0, 10);

  // Magnetic Encoder
  mt8901_init(5, 6);

  screenWidth = gfx->width();
  screenHeight = gfx->height();

  // Must to use PSRAM
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 32, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  if (!disp_draw_buf) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  } else {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 32);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = encoder_read;
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    //Sets default arc value
    lv_arc_set_value(ui_Arc2, 0);
    lv_event_send(ui_Arc2, LV_EVENT_VALUE_CHANGED, 0);
  }
}



void loop() {
  lv_timer_handler(); /* let the GUI do its work */
}

void init_lv_group() {
  // Print message to indicate initialization of the group
  std::cout << "INITIALISING GROUP\n";

  // Create a new LVGL group
  lv_group = lv_group_create();

  // Set the newly created group as the default group
  lv_group_set_default(lv_group);



  // Loop through all input devices
  lv_indev_t *cur_drv = NULL;
  for (;;) {
    cur_drv = lv_indev_get_next(cur_drv);
    // Exit the loop if there are no more input devices
    if (!cur_drv) {
      std::cout << "NO MORE INPUT DEVICES, EXITIGN\n";
      break;
    }
    std::cout << "STARTING LOOP\n";

    // Log out the name of each input device
    std::cout << "Input device name: " << cur_drv->driver->type << "\n";





    // Check if the input device is of type LV_INDEV_TYPE_ENCODER
    if (cur_drv->driver->type == LV_INDEV_TYPE_ENCODER) {
      // Print message to indicate setting of the group
      std::cout << "SETTING GROUP\n";

      // Set the LVGL group for this input device
      lv_indev_set_group(cur_drv, lv_group);
    }
  }
}
