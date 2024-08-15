#ifndef _LED_MATRIX
#define _LED_MATRIX
#include <rtthread.h>

typedef struct RGBColor_TypeDef
{
    uint8_t G;
    uint8_t R;
    uint8_t B;
} RGBColor_TypeDef; // 颜色结构体

extern const RGBColor_TypeDef DARK;
extern const RGBColor_TypeDef GREEN;
extern const RGBColor_TypeDef RED;
extern const RGBColor_TypeDef BLUE;
extern const RGBColor_TypeDef WHITE;

extern void Set_LEDColor(uint16_t LedId, RGBColor_TypeDef Color);
extern void RGB_Reflash(void);
extern void led_matrix_rst();

extern void led_matrix_fill(RGBColor_TypeDef Color);
extern void led_matrix_show_color(uint8_t r, uint8_t g, uint8_t b);
extern void LED_AllRed(void);
extern void LED_AllGreen(void);
extern void LED_AllBlue(void);
extern void LED_MulticColour(void);
extern void LED_Set(uint16_t id, RGBColor_TypeDef Color);

#endif
