#ifndef ENEMIES_H
#define ENEMIES_H

const unsigned char PROGMEM OldManMask[] =
{
// width, height,
0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xf0, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xff, 0xff, 0xff, 0x03, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM OldManWalk[] =
{
// width, height,
24, 24,
0x00, 0x00, 0x00, 0x00, 0x1c, 0x36, 0xeb, 0x1d, 0xfe, 0x3e, 0xfe, 0xce, 0x06, 0x82, 0x82, 0x01, 0x03, 0x8e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x80, 0x80, 0xc0, 0xc0, 0xe0, 0x70, 0x33, 0x1e, 0xcd, 0x6b, 0x73, 0x33, 0x93, 0xc9, 0x8d, 0x3e, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xff, 0xfd, 0x01, 0xfc, 0x84, 0xc7, 0x7c, 0x33, 0x06, 0xf6, 0x77, 0x37, 0x07, 0xf3, 0x1c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM OldMan[] =
{
// width, height,
24, 24,
0x00, 0x00, 0x00, 0x00, 0x1c, 0x36, 0xeb, 0x1d, 0xfe, 0x3e, 0xfe, 0xce, 0x06, 0x82, 0x82, 0x01, 0x03, 0x8e, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x80, 0x80, 0xc0, 0x40, 0x60, 0x30, 0x93, 0x1e, 0xcd, 0xeb, 0xf3, 0xf3, 0x73, 0x29, 0x8d, 0x3e, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0xfe, 0x00, 0xfe, 0x02, 0xc3, 0xc7, 0x7c, 0x33, 0x07, 0xf4, 0x74, 0x36, 0x07, 0xf3, 0x1c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM OldManMaskRight[] =
{
// width, height,
0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf0, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x03, 0x03, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM OldManWalkRight[] =
{
// width, height,
24, 24,
0xf8, 0x8e, 0x03, 0x01, 0x82, 0x82, 0x06, 0xce, 0xfe, 0x3e, 0xfe, 0x1d, 0xeb, 0x36, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xe3, 0x3e, 0x8d, 0xc9, 0x93, 0x33, 0x73, 0x6b, 0xcd, 0x1e, 0x33, 0x70, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x07, 0x1c, 0xf3, 0x07, 0x37, 0x77, 0xf6, 0x06, 0x33, 0x7c, 0xc7, 0x84, 0xfc, 0x01, 0xfd, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM OldManRight[] =
{
// width, height,
24, 24,
0xf8, 0x8e, 0x03, 0x01, 0x82, 0x82, 0x06, 0xce, 0xfe, 0x3e, 0xfe, 0x1d, 0xeb, 0x36, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0xe3, 0x3e, 0x8d, 0x29, 0x73, 0xf3, 0xf3, 0xeb, 0xcd, 0x1e, 0x93, 0x30, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x07, 0x1c, 0xf3, 0x07, 0x36, 0x74, 0xf4, 0x07, 0x33, 0x7c, 0xc7, 0x03, 0x02, 0xfe, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const byte oldManWidth = 14;
const byte oldManHeight = 24;
const byte travelDistance = 50;

#endif