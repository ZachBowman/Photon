#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard ()
  {
  }

Keyboard::~Keyboard ()
  {
  }

void Keyboard::get_state ()
  {
  left = GetAsyncKeyState (VK_LEFT) & 0x8000;
  right = GetAsyncKeyState (VK_RIGHT) & 0x8000;
  up = GetAsyncKeyState (VK_UP) & 0x8000;
  down = GetAsyncKeyState (VK_DOWN) & 0x8000;
  }
