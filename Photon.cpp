// Photon

#include "stdafx.h"

#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

#include "Debug.h"
#include "Keyboard.h"
#include "Photon.h"
#include "Player2D.h"
#include "Scroller.h"
#include "Timing.h"
#include "Transparent_Bitmap.h"

Photon::Photon ()
  {
  small_width = 320;
  small_height = 200;
  Exit = false;

  graphics_render_method = render_bitblitting;
  graphics_use_buffer = true;
  graphics_small_background = false;
  graphics_stress_test = true;
  graphics_bitmap_stress_amount = 2000;

  timer = Timing (60);
  }

void Photon::Init (HWND Window)
  {
  RECT rect;
  GetClientRect (Window, &rect);
  screen_width = rect.right - rect.left;
  screen_height = rect.bottom - rect.top;

  hdc = GetDC (Window);
  hdc_buffer = CreateCompatibleDC (hdc);
  hdc_temp = CreateCompatibleDC (hdc);
  bitmap_buffer = CreateCompatibleBitmap (hdc, screen_width, screen_height);
  SelectObject (hdc_buffer, bitmap_buffer);

  player_bitmap = Transparent_Bitmap (L"Images/test_player.bmp", L"Images/test_player_mask1.bmp");
  background_bitmap = (HBITMAP) LoadImage (NULL, L"Images/test_background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

  GetObject (player_bitmap.sprite, sizeof (temp_bitmap), &temp_bitmap);
  int w = (graphics_render_method == render_bitblitting) ? temp_bitmap.bmWidth : 10;
  int h = (graphics_render_method == render_bitblitting) ? temp_bitmap.bmHeight : 20;
  player = Player2D (w, h);

  scroll = Scroller (screen_width, screen_height, background_bitmap);
    
  draw_rectangle (hdc, 0, 0, screen_width, screen_height, brush_light_grey);
  draw_rectangle (hdc_buffer, 0, 0, screen_width, screen_height, brush_light_grey);
  }

void Photon::Main_Loop ()
  {
  timer.Update ();

  // execute all functions for frames (unlimited speed)
  player.Get_Input ();
  Render ();

  // execute all functions for steps (limited speed)
  if (timer.is_step_ready ())
    {
    player.Update (scroll);
    timer.update_step ();
    }
  }

void Photon::Render ()
  {
  HDC destination;
  destination = graphics_use_buffer ? hdc_buffer : hdc;
  int w = graphics_small_background ? small_width : screen_width;
  int h = graphics_small_background ? small_height : screen_height;

  if (graphics_render_method == render_setpixel || graphics_render_method == render_setpixelv)
    {
    draw_rectangle (destination, 0, 0, w, h, color_black);
    draw_rectangle (destination, player.render_rect.left, player.render_rect.top, player.render_rect.right, player.render_rect.bottom, color_red);
    }

  else if (graphics_render_method == render_fillrect)
    {
    draw_rectangle (destination, 0, 0, w, h, brush_black);

    // test background
    draw_rectangle (destination, 0, 0, w, h / 3, brush_blue);
    draw_rectangle (destination, 0, h / 3, w, h / 3 * 2, brush_yellow);
    draw_rectangle (destination, 0, h / 3 * 2, w, h, brush_green);

    draw_rectangle (destination, player.render_rect.left, player.render_rect.top, player.render_rect.right, player.render_rect.bottom, brush_red);
    }
  else if (graphics_render_method == render_bitblitting)
    {
    draw_bitmap (background_bitmap, destination, scroll.x, scroll.y, w, h);
    player_bitmap.render (hdc_temp, destination, 0, 0, scroll.x + player.render_rect.left, scroll.y + player.render_rect.top);

    if (graphics_stress_test)
      {
      for (int i = 0; i < graphics_bitmap_stress_amount; i += 1)
        {
        draw_bitmap (player_bitmap.sprite, destination, 0, 0, w, h);
        }
      }
    }

  draw_debug (destination);

  if (graphics_use_buffer) BitBlt (hdc, 0, 0, w, h, hdc_buffer, 0, 0, SRCCOPY);
  }

void Photon::draw_rectangle (HDC destination, int x1, int y1, int x2, int y2, COLORREF color)
  {
  for (int y = y1; y <= y2; y += 1)
    {
    for (int x = x1; x <= x2; x += 1)
      {
      if (graphics_render_method == render_setpixel)
        {
        SetPixel (destination, x, y, color);
        }
      else if (graphics_render_method == render_setpixelv)
        {
        SetPixelV (destination, x, y, color);
        }
      }
    }
  }

void Photon::draw_rectangle (HDC destination, int x1, int y1, int x2, int y2, HBRUSH brush)
  {
  RECT rect;
  SetRect (&rect, x1, y1, x2, y2);
  FillRect (destination, &rect, brush);
  }

void Photon::draw_debug (HDC destination)
  {
  int w = graphics_small_background ? small_width : screen_width;
  Debug::text (destination, w - 120, 5, color_blue, "FPS: ", timer.frames_per_second);
  Debug::text (destination, w - 120, 25, color_blue, "MSPF: ", timer.milliseconds_per_frame);
  }

void Photon::draw_bitmap (HBITMAP bitmap, HDC destination, int dest_x, int dest_y, int source_width, int source_height)
  {
  // TODO: Use whichever size is smaller (screen or bitmap)
  // Must reconcile this with scrolling first.
  //GetObject (bitmap, sizeof (temp_bitmap), &temp_bitmap);
  //int w = (temp_bitmap.bmWidth < source_width) ? temp_bitmap.bmWidth : source_width;
  //int h = (temp_bitmap.bmHeight < source_height) ? temp_bitmap.bmHeight : source_height;
  //SelectObject (hdc_temp, bitmap);
  //BitBlt (destination, dest_x, dest_y, w, h, hdc_temp, 0, 0, SRCCOPY);

  GetObject (bitmap, sizeof (temp_bitmap), &temp_bitmap);
  SelectObject (hdc_temp, bitmap);
  BitBlt (destination, dest_x, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, hdc_temp, 0, 0, SRCCOPY);
  }
