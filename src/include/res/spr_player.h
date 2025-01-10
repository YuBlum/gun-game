#ifndef __SPR_PLAYER_DATA_H__
#define __SPR_PLAYER_DATA_H__

#define SPR_PLAYER_W       8
#define SPR_PLAYER_H       8
#define SPR_PLAYER_FRAMES  6

#include "include/loop.h"
#define SPR_PLAYER_LOOP_AMOUNT 2
#define SPR_PLAYER_LOOP_IDLE 0
#define SPR_PLAYER_LOOP_WALK 1
static Loop g_spr_player_loop[SPR_PLAYER_LOOP_AMOUNT] = {
  { .type = LOOP_PING_PONG, .first_frame = 0, .amount = 3, },
  { .type = LOOP_FORWARD, .first_frame = 3, .amount = 3, },
};
static u16 g_spr_player_frame_duration[SPR_PLAYER_FRAMES] = {
  300,
  100,
  200,
  100,
  100,
  100,
};
static u8 g_spr_player_pixels[SPR_PLAYER_FRAMES][(SPR_PLAYER_W >> 3)*SPR_PLAYER_H] = {
  {
    0b01111100,
    0b10110010,
    0b10110010,
    0b01111100,
    0b00001110,
    0b00001111,
    0b00001111,
    0b00011011,
  },
  {
    0b01111100,
    0b10110010,
    0b10110010,
    0b10110010,
    0b01111110,
    0b00001111,
    0b00001111,
    0b00011011,
  },
  {
    0b00000000,
    0b01111100,
    0b10110010,
    0b10110010,
    0b01111100,
    0b00001110,
    0b00001111,
    0b00011011,
  },
  {
    0b01111100,
    0b10110010,
    0b10110010,
    0b01111100,
    0b00001110,
    0b00011111,
    0b00110011,
    0b00000001,
  },
  {
    0b00000000,
    0b01111100,
    0b10110010,
    0b10110010,
    0b01111100,
    0b00001110,
    0b00001111,
    0b00011011,
  },
  {
    0b01111100,
    0b10110010,
    0b10110010,
    0b01111100,
    0b00011100,
    0b00011110,
    0b00011110,
    0b00001100,
  }
};

#endif/*__SPR_PLAYER_DATA_H__*/