#pragma once

#include <string.h>

class Debug
  {
  public:
    static void text (HDC hdc, int x, int y, COLORREF color, std::string string, int number);
    static void text (HDC hdc, int x, int y, COLORREF color, std::string string1, std::string string2);
    static void text (HDC hdc, int x, int y, COLORREF color, std::string string);
    static void text (HDC hdc, int x, int y, COLORREF color, LPCSTR string1, LPCSTR string2);
    static void text (HDC hdc, int x, int y, COLORREF color, LPCSTR string1);
    static LPCSTR string_combine (LPCSTR string1, LPCSTR string2);
  };

