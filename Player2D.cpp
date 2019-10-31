#include "stdafx.h"
#include "Keyboard.h"
#include "Player2D.h"
#include "Scroller.h"

Player2D::Player2D ()
  {
  }

Player2D::Player2D (int player_width, int player_height)
  {
  x = 150;
  y = 150;
  width = player_width;
  height = player_height;
  move_speed = 2;
  }

Player2D::~Player2D ()
  {
  }

// per frame
void Player2D::Get_Input ()
  {
  keyboard.get_state ();
  }

// per step
void Player2D::Update (Scroller &scroll)
  {
  handle_keyboard (scroll);
  position_rect ();
  }

void Player2D::position_rect ()
  {
  render_rect.left = x - width / 2;
  render_rect.right = x + width / 2;
  render_rect.top = y - height;
  render_rect.bottom = y;
  }

void Player2D::handle_keyboard (Scroller &scroll)
  {
  if (keyboard.left) move_left (scroll);
  if (keyboard.right) move_right (scroll);
  if (keyboard.up) move_up (scroll);
  if (keyboard.down) move_down (scroll);
  }

void Player2D::move_left (Scroller &scroll)
  {
  x -= move_speed;

  // update scroll
  if (scroll.x + x < scroll.margin && scroll.x < scroll.max_x) scroll.x += move_speed;

  // collision detection
  if (scroll.x + x - (width / 2) < 0) x = width / 2;
  }

void Player2D::move_right (Scroller &scroll)
  {
  x += move_speed;

  // update scroll
  if (scroll.x + x > scroll.screen_width - scroll.margin && scroll.x > scroll.min_x) scroll.x -= move_speed;

  // collision detection
  if (scroll.x + x + (width / 2) > scroll.screen_width) x = scroll.screen_width - (width / 2) - scroll.x;
  }

void Player2D::move_up (Scroller &scroll)
  {
  y -= move_speed;

  // update scroll
  if (scroll.y + y - (height / 2) < scroll.margin && scroll.y < scroll.max_y) scroll.y += move_speed;

  // collision detection
  if (scroll.y + y - height < 0) y = height;
  }

void Player2D::move_down (Scroller &scroll)
  {
  y += move_speed;

  // update scroll
  if (scroll.y + y - (height / 2) > scroll.screen_height - scroll.margin && scroll.y > scroll.min_y) scroll.y -= move_speed;

  // collision detection
  if (scroll.y + y > scroll.screen_height) y = scroll.screen_height - scroll.y;
  }
