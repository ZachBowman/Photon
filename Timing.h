#pragma once
class Timing
  {
  public:
    Timing ();
    Timing (int steps_per_second);
    ~Timing ();

      void Update ();
      bool is_step_ready ();
      void update_step ();

      int frames_per_second;
      int milliseconds_per_frame;

    private:
      int current_tick;
      int last_second_tick;
      int last_frame_tick;  // last tick during which speed-unlimited features were updated (frames)
      int last_step_tick;  // last tick during which speed-limited game logic was updated (steps)
      int frames_this_second;
      int target_steps_per_second;
      int target_milliseconds_per_step;
  };
