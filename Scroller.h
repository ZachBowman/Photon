#pragma once

class Scroller
  {
  public:
    Scroller ();
    Scroller (int screen_width, int screen_height);
    Scroller (int screen_width, int screen_height, HBITMAP background);
    ~Scroller ();

    int x, y;

    int min_x, max_x;
    int min_y, max_y;

    int screen_width, screen_height;

    int margin = 100;
  };

