#include "stdafx.h"
#include "Transparent_Bitmap.h"

Transparent_Bitmap::Transparent_Bitmap () {}

Transparent_Bitmap::Transparent_Bitmap (LPCWSTR source_path, LPCWSTR mask_path)
  {
  sprite = (HBITMAP) LoadImage (NULL, source_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  mask = (HBITMAP) LoadImage (NULL, mask_path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  }

Transparent_Bitmap::~Transparent_Bitmap ()
  {
  }

void Transparent_Bitmap::render (HDC temp_hdc, HDC dest_hdc, int source_x, int source_y, int dest_x, int dest_y)
  {
  GetObject (sprite, sizeof (temp_bitmap), &temp_bitmap);
  SelectObject (temp_hdc, sprite);
  BitBlt (dest_hdc, dest_x, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCINVERT);
  SelectObject (temp_hdc, mask);
  BitBlt (dest_hdc, dest_x, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCAND);
  SelectObject (temp_hdc, sprite);
  BitBlt (dest_hdc, dest_x, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCINVERT);

  //SelectObject (temp_hdc, sprite);
  //BitBlt (dest_hdc, dest_x, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCINVERT);
  //SelectObject (temp_hdc, mask);
  //BitBlt (dest_hdc, dest_x + 100, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCAND);
  //SelectObject (temp_hdc, sprite);
  //BitBlt (dest_hdc, dest_x + 200, dest_y, temp_bitmap.bmWidth, temp_bitmap.bmHeight, temp_hdc, 0, 0, SRCINVERT);
  }
