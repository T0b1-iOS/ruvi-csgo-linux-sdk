//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/vector.hh"
#include <functional>
#include "sdk/indices.hh"

class iv_debug_overlay {
public:
  bool screen_position(const vector3d &in, vector3d &out) {
    return memory::vfunc<idx::SCREEN_POSITION, bool>(this, std::ref(in), std::ref(out));
  }
};