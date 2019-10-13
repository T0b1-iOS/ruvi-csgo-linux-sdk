//
//  ruvi base
//

// includes
#include "../memory/memory.hh"
#include "../vector/vector.hh"
#include "sdk/indices.hh"

class c_client_class;

class i_client_networkable {
public:
  virtual ~i_client_networkable(){};

  void release() { return memory::vfunc<idx::NETWORKABLE_RELEASE, void>(this); }

  c_client_class *get_client_class() {
    return memory::vfunc<idx::GET_CLIENT_CLASS, c_client_class *>(this);
  }

  bool is_dormant() { return memory::vfunc<idx::IS_DORMANT, bool>(this); }

  int get_index() { return memory::vfunc<idx::GET_INDEX, int>(this); }

  void set_destroyed_on_recreate_entities() {
    return memory::vfunc<idx::SET_DESTROYED_ON_REC_ENT, void>(this);
  }
};