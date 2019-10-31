#pragma once
class Keyboard
  {
  public:
    Keyboard ();
    ~Keyboard ();
    void get_state();

    bool left;
    bool right;
    bool up;
    bool down;
  };
