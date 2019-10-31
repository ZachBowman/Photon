#pragma once

class Transparent_Bitmap
  {
  public:
    Transparent_Bitmap ();
    Transparent_Bitmap (LPCWSTR source_path, LPCWSTR mask_path);
    ~Transparent_Bitmap ();
    void render (HDC temp_hdc, HDC dest_hdc, int source_x, int source_y, int dest_x, int dest_y);
    HBITMAP sprite;
    HBITMAP mask;

  private:
    BITMAP temp_bitmap;
  };
