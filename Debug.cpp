#include "stdafx.h"
#include <string>
#include "Debug.h"

void Debug::text (HDC hdc, int x, int y, COLORREF color, std::string string, int number)
  {
  Debug::text (hdc, x, y, color, string, std::to_string (number));
  }

void Debug::text (HDC hdc, int x, int y, COLORREF color, std::string string1, std::string string2)
  {
  Debug::text (hdc, x, y, color, string1 + string2);
  }

void Debug::text (HDC hdc, int x, int y, COLORREF color, std::string string)
  {
  Debug::text (hdc, x, y, color, string.c_str ());
  }

void Debug::text (HDC hdc, int x, int y, COLORREF color, LPCSTR string1, LPCSTR string2)
  {
  Debug::text (hdc, x, y, color, Debug::string_combine (string1, string2));
  }

void Debug::text (HDC hdc, int x, int y, COLORREF color, LPCSTR string)
  {
  SetTextColor (hdc, color);
  TextOutA (hdc, x, y, string, strlen (string));
  }

LPCSTR Debug::string_combine (LPCSTR string1, LPCSTR string2)
  {
  const int max_length = 100;
  char new_string[max_length];
  strcpy_s (new_string, string1);
  strcat_s (new_string, string2);
  return new_string;
  }
