#ifndef __SPR_TEST_DATA_H__
#define __SPR_TEST_DATA_H__

#define SPR_TEST_WIDTH   8
#define SPR_TEST_HEIGHT  8
#define SPR_TEST_FRAMES  3
static u16 g_spr_test_frame_duration[SPR_TEST_FRAMES] = {
  200,
  100,
  100,
};
static u8 g_spr_test_pixels[SPR_TEST_FRAMES][(SPR_TEST_WIDTH >> 3)*SPR_TEST_HEIGHT] = {
  {
    0b00111100,
    0b01111110,
    0b10011001,
    0b10111101,
    0b11111111,
    0b10000001,
    0b01111110,
    0b00111100,
  },
  {
    0b00000000,
    0b00111100,
    0b01111110,
    0b10011001,
    0b11111111,
    0b10000001,
    0b01111110,
    0b00111100,
  },
  {
    0b00000000,
    0b00111100,
    0b01111110,
    0b11111111,
    0b10011001,
    0b11111111,
    0b00000000,
    0b00111100,
  }
};

#endif/*__SPR_TEST_DATA_H__*/