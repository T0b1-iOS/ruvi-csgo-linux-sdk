//
//  ruvi base
//

#pragma once

// includes
#include <functional>
#include "../memory/memory.hh"
#include "../utils/utlvector.hh"
#include "sdk/indices.hh"

class convar {
private:
  using callback_t = void (*)(convar *cvar, const char *p_old_value,
                              float old_value);

public:
  float get_float() { return memory::vfunc<idx::CV_GET_FLOAT, float>(this); }

  int get_int() { return memory::vfunc<idx::CV_GET_INT, int>(this); }

  void set_value(const char *value) {
    return memory::vfunc<idx::CV_SET_STR_VAL, void>(this, value);
  }

  void set_value(float value) { return memory::vfunc<idx::CV_SET_FL_VAL, void>(this, value); }

  void set_value(int value) { return memory::vfunc<idx::CV_SET_INT_VAL, void>(this, value); }

public:
  char pad0[0x4];
  convar *next;
  int registered;
  char *name;
  char *help_string;
  int flags;
  char pad1[0x4];
  convar *parent;
  char *default_value;
  char *string;
  int string_length;
  float float_value;
  int int_value;
  int has_min;
  float min;
  int has_max;
  float max;
  utl_vector<callback_t> callback;
};

class i_cvar {
public:
  void register_con_command(convar *command) {
    return memory::vfunc<idx::CV_REG_CMD, void>(this, command);
  }

  void un_register_con_command(convar *command) {
    return memory::vfunc<idx::CV_UNREG_CMD, void>(this, command);
  }

  convar *find_var(const char *name) {
    return memory::vfunc<idx::CV_FIND_VAR, convar *>(this, name);
  }

  convar *spoof(convar *cvar, const std::string_view new_name) {

    un_register_con_command(cvar);
    cvar->name = const_cast<char *>(new_name.data());
    register_con_command(cvar);

    return cvar;
  }

  void console_color_printf(const int color[4], const std::string_view message, ...) {
    return memory::vfunc<idx::CV_CON_COL_PRINT, void>(this, std::ref(color), message.data());
  }
};