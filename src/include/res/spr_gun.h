#ifndef __SPR_GUN_DATA_H__
#define __SPR_GUN_DATA_H__

#define SPR_GUN_W       8
#define SPR_GUN_H       8
#define SPR_GUN_FRAMES  3
static u8 g_spr_gun_pixels[SPR_GUN_FRAMES][(SPR_GUN_W >> 3)*SPR_GUN_H] = {
  {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001110,
    0b00011111,
    0b00000011,
    0b00000000,
    0b00000000,
  },
  {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00011000,
    0b00011000,
    0b00111000,
    0b00110000,
  },
  {
    0b00011000,
    0b00111000,
    0b00110000,
    0b00110000,
    0b00010000,
    0b00000000,
    0b00000000,
    0b00000000,
  }
};

#endif/*__SPR_GUN_DATA_H__*/