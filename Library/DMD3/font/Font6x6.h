

/*
 *
 * Font6x6
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Font6x6.h
 * Date                : 03.06.2018
 * Font size in bytes  : 4550
 * Font width          : 6
 * Font height         : -8
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
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

#ifndef FONT6X6_H
#define FONT6X6_H

#define FONT6X6_WIDTH 6
#define FONT6X6_HEIGHT -8

const static uint8_t Font6x6[] PROGMEM = {
    0x11, 0xC6, // size
    0x06, // width
    0x08, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x01, 0x06, 0x05, 0x06, 0x06, 0x06, 0x06, 0x03, 0x04, 0x04, 
    0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x04, 0x04, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x04, 0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x05, 0x06, 0x06, 0x04, 0x05, 0x06, 0x06, 0x08, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x05, 0x06, 0x07, 0x07, 0x05, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    
    // font data
    0x00, // 32
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 33
    0x00, 0x03, 0x00, 0x03, 0x00, // 34
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x00, 0x03, 0x00, // 39
    0x1E, 0x3F, 0x21, 0x00, // 40
    0x00, 0x21, 0x3F, 0x1E, // 41
    0x00, 0x05, 0x02, 0x05, 0x00, // 42
    0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, // 43
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 44
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 45
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 46
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0x1E, 0x3F, 0x21, 0x21, 0x3F, 0x1E, // 48
    0x00, 0x21, 0x3F, 0x3F, 0x20, 0x00, // 49
    0x31, 0x39, 0x29, 0x29, 0x2F, 0x26, // 50
    0x21, 0x25, 0x25, 0x25, 0x3F, 0x1A, // 51
    0x18, 0x1C, 0x12, 0x3F, 0x3F, 0x10, // 52
    0x27, 0x27, 0x25, 0x25, 0x3D, 0x19, // 53
    0x1E, 0x3F, 0x25, 0x25, 0x3D, 0x18, // 54
    0x01, 0x01, 0x31, 0x39, 0x0D, 0x07, // 55
    0x1A, 0x3F, 0x25, 0x25, 0x3F, 0x1A, // 56
    0x06, 0x2F, 0x29, 0x29, 0x3F, 0x1E, // 57
    0x00, 0x12, 0x12, 0x00, // 58
    0x00, 0x12, 0x32, 0x00, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x00, 0x12, 0x12, 0x12, 0x12, 0x00, // 61
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 64
    0x3E, 0x3F, 0x09, 0x09, 0x3F, 0x3E, // 65
    0x3F, 0x3F, 0x25, 0x25, 0x3F, 0x1A, // 66
    0x1E, 0x3F, 0x21, 0x21, 0x33, 0x12, // 67
    0x3F, 0x3F, 0x21, 0x21, 0x3F, 0x1E, // 68
    0x3F, 0x3F, 0x25, 0x25, 0x25, 0x21, // 69
    0x3F, 0x3F, 0x05, 0x05, 0x05, 0x01, // 70
    0x1E, 0x3F, 0x21, 0x29, 0x3B, 0x1A, // 71
    0x3F, 0x3F, 0x04, 0x04, 0x3F, 0x3F, // 72
    0x21, 0x3F, 0x3F, 0x21, // 73
    0x10, 0x30, 0x20, 0x21, 0x3F, 0x1F, // 74
    0x3F, 0x3F, 0x0C, 0x1E, 0x33, 0x21, // 75
    0x3F, 0x3F, 0x20, 0x20, 0x20, 0x20, // 76
    0x3F, 0x3F, 0x02, 0x04, 0x02, 0x3F, 0x3F, // 77
    0x3F, 0x3F, 0x02, 0x04, 0x3F, 0x3F, // 78
    0x1E, 0x3F, 0x21, 0x21, 0x3F, 0x1E, // 79
    0x3F, 0x3F, 0x09, 0x09, 0x0F, 0x06, // 80
    0x1E, 0x3F, 0x21, 0x29, 0x17, 0x2E, // 81
    0x3F, 0x3F, 0x09, 0x09, 0x3F, 0x36, // 82
    0x22, 0x27, 0x25, 0x25, 0x3D, 0x19, // 83
    0x01, 0x01, 0x3F, 0x3F, 0x01, 0x01, // 84
    0x1F, 0x3F, 0x20, 0x20, 0x3F, 0x1F, // 85
    0x0F, 0x1F, 0x20, 0x20, 0x1F, 0x0F, // 86
    0x1F, 0x3F, 0x20, 0x18, 0x20, 0x3F, 0x1F, // 87
    0x21, 0x12, 0x0C, 0x0C, 0x12, 0x21, // 88
    0x03, 0x0F, 0x38, 0x38, 0x0F, 0x03, // 89
    0x31, 0x39, 0x2D, 0x2D, 0x27, 0x23, // 90
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 91
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 92
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 93
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 95
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x10, 0x3A, 0x2A, 0x2A, 0x3E, 0x3C, // 97
    0x3F, 0x3F, 0x22, 0x22, 0x3E, 0x1C, // 98
    0x1C, 0x3E, 0x22, 0x22, 0x36, 0x14, // 99
    0x1C, 0x3E, 0x22, 0x22, 0x3F, 0x3F, // 100
    0x1C, 0x3E, 0x2A, 0x2A, 0x2E, 0x0C, // 101
    0x04, 0x3E, 0x3F, 0x05, 0x05, // 102
    0x0C, 0x9E, 0x92, 0x92, 0xFE, 0x7E, // 103
    0x3F, 0x3F, 0x04, 0x02, 0x3E, 0x3C, // 104
    0x24, 0x3D, 0x3D, 0x20, // 105
    0x80, 0x80, 0x84, 0xFD, 0x7D, // 106
    0x3F, 0x3F, 0x08, 0x14, 0x22, 0x22, // 107
    0x21, 0x3F, 0x3F, 0x20, 0x00, 0x00, // 108
    0x3E, 0x3E, 0x02, 0x3E, 0x3C, 0x02, 0x3E, 0x3C, // 109
    0x3E, 0x3E, 0x02, 0x02, 0x3E, 0x3C, // 110
    0x1C, 0x3E, 0x22, 0x22, 0x3E, 0x1C, // 111
    0x7E, 0x7E, 0x12, 0x12, 0x1E, 0x0C, // 112
    0x0C, 0x1E, 0x12, 0x7E, 0x7E, 0x40, // 113
    0x3E, 0x3E, 0x02, 0x02, 0x06, 0x04, // 114
    0x24, 0x2E, 0x2A, 0x2A, 0x3A, 0x12, // 115
    0x02, 0x1F, 0x3F, 0x22, 0x22, // 116
    0x1E, 0x3E, 0x20, 0x20, 0x3E, 0x3E, // 117
    0x06, 0x0E, 0x10, 0x20, 0x10, 0x0E, 0x06, // 118
    0x1E, 0x3E, 0x20, 0x18, 0x20, 0x3E, 0x1E, // 119
    0x22, 0x14, 0x08, 0x14, 0x22, // 120
    0x0E, 0x9E, 0x90, 0x90, 0xFE, 0x7E, // 121
    0x32, 0x3A, 0x2A, 0x2A, 0x2E, 0x26, // 122
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 123
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 124
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 125
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif