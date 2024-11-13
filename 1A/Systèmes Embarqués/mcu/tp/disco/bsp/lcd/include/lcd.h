/**
 * @file lcd/include/lcd.h
 * @brief header file for alphanumeric LCD library 
 * @author hugo descoubes - copyleft
 */

/** @ingroup LCD */
/* @{ */
/** @defgroup ST7032I */
/** @ingroup ST7032I */
/* @{ */
#ifndef _LCD_H
#define _LCD_H

#include <common/include/common.h>
#include <common/include/delay.h>
#include <i2c1/include/i2c1.h>

/* API parameters */
#define LINE_NB                     2
#define COLUMN_NB                   16
#define DATA                        0x40
#define CMD                         0x00
#define LCD_I2C_DEV_ADD             0x3E
#define LCD_I2C_BAUDRATE            100000

/* commands listing */
#define CMD_DISPLAY_CLEAR            	  0x01
#define CMD_DISPLAY_ON                    0x0C
#define CMD_DISPLAY_OFF                   0x08
#define CMD_DISPLAY_SHIFT_L               0x18
#define CMD_DISPLAY_SHIFT_R               0x1C
#define CMD_CURSOR_HOME                   0x02
#define CMD_CURSOR_ON                     0x0E
#define CMD_CURSOR_OFF                    0x0C  
#define CMD_CURSOR_BLINK                  0x0F
#define CMD_CURSOR_SHIFT_L                0x10
#define CMD_CURSOR_SHIFT_R                0x14
#define CMD_CURSOR_SECOND_ROW             0xC0

/* API reference */

/**
 * @brief I2C driver for ST7032I LCD controller
 * @warning port specific function
 * @param add I2C controller address
 * @param cmd_or_data command (CMD) or data (DATA) selection
 * @param payload data to send
 */
void lcd_driver(uInt8_t add, uInt8_t cmd_or_data, uInt8_t payload);

/**
 * @brief lcd controller configuration
 * @li display panel : 2 lines, 5x8 dot per character 
 * @li pre-configuration : display on, clear display
 * cursor off, cursor blinking off, cursor position home
 * @warning port specific function 
 */
void lcd_init(void);

/**
 * @brief send character to lcd controller
 * @param data data to send
 */
void lcd_char(uInt8_t data);

/**
 * @brief send command to lcd controller
 * @param cmd command to send
 */
void lcd_cmd(uInt8_t cmd);

/**
 * @brief send characters string to lcd controller
 * @param str pointer to the string to send
 */
void lcd_string(const uInt8_t *str);

/**
 * @brief set cursor position
 * @param row line cursor position, 1 or 2
 * @param col column cursor position between 1 and 16
 */
void lcd_cursor(uInt8_t row, uInt8_t col);

#endif /*_LCD_H*/


















