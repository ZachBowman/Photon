#pragma once

#include "Keyboard.h"
#include "Scroller.h"

class Player2D
  {
  public:
    Player2D ();
    Player2D (int player_width, int player_height);
    ~Player2D ();
    void Update (Scroller &scroll);
    void Get_Input ();
    void position_rect ();
    void handle_keyboard (Scroller &scroll);
    void move_left (Scroller &scroll);
    void move_right (Scroller &scroll);
    void move_up (Scroller &scroll);
    void move_down (Scroller &scroll);

    Keyboard keyboard;

    int x;
    int y;
    int width;
    int height;
    RECT render_rect;
    int move_speed;
  };
