#ifndef __SPR_TEST_DATA_H__
#define __SPR_TEST_DATA_H__

#define SPR_TEST_WIDTH   8
#define SPR_TEST_HEIGHT  8
#define SPR_TEST_FRAMES  2
static u16 g_spr_test_frame_duration[SPR_TEST_FRAMES] = {
  200,
  200,
};
static u8 g_spr_test_pixels[SPR_TEST_FRAMES][(SPR_TEST_WIDTH >> 3)*SPR_TEST_HEIGHT] = {
  {
    0b00001000,
    0b00011000,
    0b00111110,
    0b01111110,
    0b01111110,
    0b00111110,
    0b00011000,
    0b00001000,
  },
  {
    0b00010000,
    0b00110000,
    0b01111111,
    0b11111111,
    0b11111111,
    0b01111111,
    0b00110000,
    0b00010000,
  }
};

#endif/*__SPR_TEST_DATA_H__*/