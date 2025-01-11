#ifndef __MAP_DATA_H__
#define __MAP_DATA_H__

#define MAP_W      16
#define MAP_H      15
#define MAP_AMOUNT 4
static i8 g_map_surrounding[MAP_AMOUNT][4] = {
  { -1, 2, -1, 1, },
  { -1, 0, -1, -1, },
  { 3, -1, -1, 0, },
  { -1, -1, 2, -1, },
};
static u8 g_map_tiles[MAP_AMOUNT][(MAP_W >> 1)*MAP_H] = {
  {
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xe0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0xe0,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
  },
  {
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x30,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x30,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x00,
    0x0e,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
  },
  {
    0x03,
    0x30,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x03,
    0xe0,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x30,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0xe0,
    0x00,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
  },
  {
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x03,
    0x00,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x33,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x33,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x30,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x33,
    0x03,
    0x00,
    0x00,
    0x0e,
    0x00,
    0x00,
    0x30,
    0x33,
    0x03,
    0x30,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
    0x33,
  }
};

#endif/*__MAP_DATA_H__*/