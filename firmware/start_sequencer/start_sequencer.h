#define PPS_INT_PIN 2
#define PPS_INT 0
#define TRIGGER_INT_PIN 3
#define TRIGGER_INT 1
#define LCD_ENABLE 4
#define LCD_CONTRAST 5
#define LCD_BACKLIGHT 6
#define LCD_RS 7
#define HORN 8
#define CAMERA 9
#define BUTTON_BACKLIGHT 10
#define CDS_CELL A6
#define BUTTON_MATRIX A7
#define LCD_DB4 A0
#define LCD_DB5 A1
#define LCD_DB6 A2
#define LCD_DB7 A3

void pps_isr(void);
void trigger_isr(void);