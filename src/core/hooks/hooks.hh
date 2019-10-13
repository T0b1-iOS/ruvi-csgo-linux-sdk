//
//  ruvi base
//

#pragma once

// includes
#include "core/interfaces/interfaces.hh"
#include "sdk/utils/vmthook.hh"

namespace hooks {

void on_entry_point();


#ifdef _WIN32
template<typename Sig>
struct sig;

template<typename R, typename Arg>
struct sig<R __thiscall(Arg)>
{
	using ret_type = R;
	using fn_type = R __fastcall (void*);
};

template<typename R, typename A, typename... Args>
struct sig<R __thiscall(A, Args...)>
{
	using ret_type = R;
	using fn_type = R __fastcall (void*, void*, Args...);
};

template<typename fn>
using hooked_fn = typename sig<fn>::fn_type;

#define ORIG_CALLING_CONV __thiscall
#else
template<typename fn>
using hooked_fn = fn;
#define ORIG_CALLING_CONV
#endif

struct paint {
  typedef void(ORIG_CALLING_CONV fn)(void *, paint_mode_t);
  static hooked_fn<fn> hooked;
  static fn *original;
};

struct in_key_event {
  typedef int(ORIG_CALLING_CONV fn)(void *, int, int, const char *);
  static hooked_fn<fn> hooked;
  static fn *original;
};

struct lock_cursor {
  typedef void(ORIG_CALLING_CONV fn)(void *);
  static hooked_fn<fn> hooked;
  static fn *original;
};

struct create_move {
  typedef bool(ORIG_CALLING_CONV fn)(void *, float, c_user_cmd *);
  static hooked_fn<fn> hooked;
  static fn *original;
};

struct frame_stage_notify {
  typedef void(ORIG_CALLING_CONV fn)(void *, client_frame_stage_t);
  static hooked_fn<fn> hooked;
  static fn *original;
};
} // namespace hooks