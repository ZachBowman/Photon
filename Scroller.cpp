#include "stdafx.h"
#include "Scroller.h"

Scroller::Scroller () {}

Scroller::Scroller (int new_screen_width, int new_screen_height)
  {
  min_x = new_screen_width;
  min_y = new_screen_height;

  screen_width = new_screen_width;
  screen_height = new_screen_height;
  x = 0;
  y = 0;
  max_x = 0;
  max_y = 0;
  }

Scroller::Scroller (int new_screen_width, int new_screen_height, HBITMAP background)
  {
  BITMAP temp_bitmap;
  GetObject (background, sizeof (temp_bitmap), &temp_bitmap);
  min_x = new_screen_width > temp_bitmap.bmWidth ? 0 : new_screen_width - temp_bitmap.bmWidth;
  min_y = new_screen_height > temp_bitmap.bmHeight ? 0 : new_screen_height - temp_bitmap.bmHeight;

  screen_width = new_screen_width;
  screen_height = new_screen_height;
  x = 0;
  y = 0;
  max_x = 0;
  max_y = 0;
  }

Scroller::~Scroller ()
  {
  }
