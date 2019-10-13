//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/indices.hh"

enum analog_code_t {
  ANALOG_CODE_INVALID = -1,
  MOUSE_X = 0,
  MOUSE_Y,
  MOUSE_XY, // invoked when either x or y changes
  MOUSE_WHEEL,
  ANALOG_CODE_LAST = 10,
};

class i_input_system {
public:
  bool is_button_down(int code) { return memory::vfunc<idx::INPUT_BTN_DOWN, bool>(this, code); }

  int get_analog_value(analog_code_t code) {
    return memory::vfunc<idx::INPUT_ANALOG_VAL, int>(this, code);
  }

  int get_analog_delta(analog_code_t code) {
    return memory::vfunc<idx::INPUT_ANALOG_DELTA, int>(this, code);
  }

  const char *button_code_to_string(int code) {
    return memory::vfunc<idx::INPUT_BTN_CODE_STR, const char *>(this, code);
  }
};