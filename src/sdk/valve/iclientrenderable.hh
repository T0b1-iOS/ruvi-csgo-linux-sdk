//
//  ruvi base
//

#pragma once

// includes
#include <functional>
#include "../memory/memory.hh"
#include "../vector/vector.hh"
#include "sdk/indices.hh"

struct model_t;
class matrix3x4_t;

class i_client_renderable {
public:
  virtual ~i_client_renderable(){};

  model_t *get_model() { return memory::vfunc<idx::GET_MDL, model_t *>(this); }

  int draw_model(int flags, unsigned char alpha) {
    return memory::vfunc<idx::DRAW_MDL, int>(this, flags, alpha);
  }

  bool setup_bones(matrix3x4_t *bone_matrix, int max_bones, int bone_mask,
                   float curtime = 0) {
    return memory::vfunc<idx::SETUP_BONES, bool>(this, bone_matrix, max_bones, bone_mask,
                                   curtime);
  }

  void get_render_bounds(vector3d &mins, vector3d &maxs) {
    return memory::vfunc<idx::GET_RENDER_BOUNDS, void>(this, std::ref(mins), std::ref(maxs));
  }
};