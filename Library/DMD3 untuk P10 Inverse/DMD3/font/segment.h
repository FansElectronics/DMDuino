

/*
 *
 * new Font
 *
 *
 * File Name           : segment.h
 * Date                : 17.02.2017
 * Font size in bytes  : 1066
 * Font width          : 7
 * Font height         : -15
 * Font first char     : 48
 * Font last char      : 58
 * Font used chars     : 10
 *
 * by Aziz Kurosaki
 *
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#define SEGMENT_WIDTH 7
#define SEGMENT_HEIGHT 15

const static uint8_t segment[] PROGMEM  = {
    0x00, 0x00, // size
    0x07, // width
    0x0F, // height
    0x30, // first char
    0x0A, // char count
    
    // char widths
      
    // font data
    0x7E, 0x3D, 0x03, 0x03, 0x03, 0x3D, 0x7E, 0x7E, 0xBC, 0xC0, 0xC0, 0xC0, 0xBC, 0x7E, // 48
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7E, // 49
    0x00, 0x81, 0xC3, 0xC3, 0xC3, 0xBD, 0x7E, 0x7E, 0xBC, 0xC2, 0xC2, 0xC2, 0x80, 0x00, // 50
    0x00, 0x81, 0xC3, 0xC3, 0xC3, 0xBD, 0x7E, 0x00, 0x80, 0xC2, 0xC2, 0xC2, 0xBC, 0x7E,// 51
    0x7E, 0xBC, 0xC0, 0xC0, 0xC0, 0xBC, 0x7E, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3C, 0x7E, // 52
    0x7E, 0xBD, 0xC3, 0xC3, 0xC3, 0x81, 0x00, 0x00, 0x80, 0xC2, 0xC2, 0xC2, 0xBC, 0x7E, // 53
    0x7E, 0xBD, 0xC3, 0xC3, 0xC3, 0x81, 0x00, 0x7E, 0xBC, 0xC2, 0xC2, 0xC2, 0xBC, 0x7E, // 54
    0x00, 0x01, 0x03, 0x03, 0x03, 0x3D, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x7E, // 55
    0x7E, 0xBD, 0xC3, 0xC3, 0xC3, 0xBD, 0x7E, 0x7E, 0xBC, 0xC2, 0xC2, 0xC2, 0xBC, 0x7E, // 56
    0x7E, 0xBD, 0xC3, 0xC3, 0xC3, 0xBD, 0x7E, 0x00, 0x80, 0xC2, 0xC2, 0xC2, 0xBC, 0x7E // 57
    
};

#endif
