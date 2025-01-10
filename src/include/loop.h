#ifndef _LOOP_H_
#define _LOOP_H_

enum LoopType : u8 {
  LOOP_FORWARD = 0,
  LOOP_REVERSE,
  LOOP_PING_PONG,
  LOOP_PING_PONG_REVERSE,
};

struct Loop {
  LoopType type;
  u8 first_frame;
  u8 amount;
};

#endif/*_LOOP_H_*/
