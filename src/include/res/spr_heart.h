#ifndef __SPR_HEART_DATA_H__
#define __SPR_HEART_DATA_H__

#define SPR_HEART_W       8
#define SPR_HEART_H       8
#define SPR_HEART_FRAMES  1
static u8 g_spr_heart_pixels[SPR_HEART_FRAMES][(SPR_HEART_W >> 3)*SPR_HEART_H] = {
  {
    0b00000000,
    0b00110110,
    0b00111110,
    0b00111110,
    0b00011100,
    0b00001000,
    0b00000000,
    0b00000000,
  }
};

#endif/*__SPR_HEART_DATA_H__*/