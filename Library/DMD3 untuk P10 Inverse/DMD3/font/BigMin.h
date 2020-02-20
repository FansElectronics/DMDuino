

/*
 *
 * BigMin
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : BigMin.h
 * Date                : 12.05.2018
 * Font size in bytes  : 1073
 * Font width          : 6
 * Font height         : -16
 * Font first char     : 48
 * Font last char      : 59
 * Font used chars     : 11
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef BIGMIN_H
#define BIGMIN_H

#define BIGMIN_WIDTH 6
#define BIGMIN_HEIGHT -16

const static uint8_t BigMin[] PROGMEM = {
    0x04, 0x31, // size
    0x06, // width
    0x10, // height
    0x30, // first char
    0x0B, // char count
    
    // char widths
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 
    
    // font data
    0xFC, 0xFE, 0x02, 0x82, 0xFE, 0xFC, 0x3F, 0x7F, 0x46, 0x41, 0x7F, 0x3F, // 48
    0x02, 0x02, 0xFE, 0xFE, 0x00, 0x00, 0x40, 0x40, 0x7F, 0x7F, 0x40, 0x40, // 49
    0x0C, 0x0E, 0x02, 0x82, 0xFE, 0xFC, 0x7C, 0x7E, 0x47, 0x43, 0x41, 0x40, // 50
    0x0C, 0x8E, 0x82, 0x82, 0xFE, 0x7C, 0x30, 0x71, 0x41, 0x41, 0x7F, 0x3E, // 51
    0xE0, 0xF0, 0x1C, 0xFE, 0xFE, 0x00, 0x0F, 0x0F, 0x48, 0x7F, 0x7F, 0x48, // 52
    0xFE, 0xFE, 0x42, 0x42, 0xC2, 0x82, 0x30, 0x70, 0x40, 0x40, 0x7F, 0x3F, // 53
    0xFC, 0xFE, 0x82, 0x82, 0x8E, 0x0C, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, // 54
    0x02, 0x02, 0x82, 0xE2, 0x7A, 0x1E, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, // 55
    0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, // 56
    0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x30, 0x71, 0x41, 0x41, 0x7F, 0x3F, // 57
    0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x00, 0x00 // 58
    
};

#endif