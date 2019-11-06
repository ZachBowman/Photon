#include "stdafx.h"
#include "Timing.h"

Timing::Timing () {}

Timing::Timing (int steps_per_second)
  {
  target_steps_per_second = steps_per_second;
  target_milliseconds_per_step = 1000 / target_steps_per_second;
  last_step_tick = 0;
  }

Timing::~Timing () {}

void Timing::Update ()
  {
  current_tick = GetTickCount ();

  // mspf counter
  milliseconds_per_frame = current_tick - last_frame_tick;

  // fps counter
  if (current_tick >= last_second_tick + 1000)
    {
    frames_per_second = frames_this_second;
    frames_this_second = 0;
    last_second_tick = current_tick;
    }
  frames_this_second += 1;

  last_frame_tick = GetTickCount ();
  }

bool Timing::is_step_ready ()
  {
  return current_tick - last_step_tick > target_milliseconds_per_step;
  }

void Timing::update_step ()
  {
  last_step_tick = GetTickCount ();
  }
