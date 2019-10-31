#pragma once

#include "resource.h"
#include "Player2D.h"
#include "Scroller.h"
#include "Timing.h"
#include "Transparent_Bitmap.h"

enum GRAPHICS_RENDER_METHOD
  {
  render_setpixel,
  render_setpixelv,
  render_fillrect,
  render_bitblitting
  };

class Photon
  {
  public:
    Photon ();
    void Init (HWND Window);
    void Main_Loop ();
    void Render ();

    void draw_rectangle (HDC, int, int, int, int, COLORREF);
    void draw_rectangle (HDC, int, int, int, int, HBRUSH);
    void draw_debug (HDC destination);
    void draw_bitmap (HBITMAP bitmap, HDC destination, int x, int y, int width, int height);

    int window_width;
    int window_height;
    int screen_width;
    int screen_height;
    int small_width;
    int small_height;
    int background_width;
    int background_height;

    bool Exit;

    HDC hdc;
    HDC hdc_buffer;
    HDC hdc_temp;
    HBITMAP bitmap_buffer;

    Timing timer;
    Player2D player;
    Scroller scroll;

    Transparent_Bitmap player_bitmap;
    HBITMAP background_bitmap;
    
  private:
    BITMAP temp_bitmap;

    COLORREF color_red = RGB (192, 0, 0);
    COLORREF color_yellow = RGB (224, 224, 0);
    COLORREF color_green = RGB (0, 192, 0);
    COLORREF color_blue = RGB (0, 0, 192);
    COLORREF color_black = RGB (0, 0, 0);
    COLORREF color_white = RGB (255, 255, 255);
    COLORREF color_light_grey = RGB (192, 192, 192);

    HBRUSH brush_red = CreateSolidBrush (color_red);
    HBRUSH brush_yellow = CreateSolidBrush (color_yellow);
    HBRUSH brush_green = CreateSolidBrush (color_green);
    HBRUSH brush_blue = CreateSolidBrush (color_blue);
    HBRUSH brush_black = CreateSolidBrush (color_black);
    HBRUSH brush_white = CreateSolidBrush (color_white);
    HBRUSH brush_light_grey = CreateSolidBrush (color_light_grey);

    GRAPHICS_RENDER_METHOD graphics_render_method;
    bool graphics_use_buffer;
    bool graphics_small_background;
  };
