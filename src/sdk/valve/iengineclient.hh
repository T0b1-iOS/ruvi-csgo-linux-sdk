//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/vector/vector.hh"
#include <functional>
#include "sdk/indices.hh"

struct player_info_t {
  int64_t __pad0;
  union {
    int64_t xuid;
    struct {
      int xuid_low;
      int xuid_high;
    };
  };
  char name[128];
  int userid;
  char guid[33];
  unsigned int steam3_id;
  char friendsname[128];
  bool is_fake_player;
  bool ishltv;
  unsigned int customfiles[4];
  unsigned char filesdownloaded;
};

class i_engine_client {
public:
  void get_screen_size(int &width, int &height) {
    return memory::vfunc<idx::ENGINE_GET_SCREEN_SIZE, void>(this, std::ref(width), std::ref(height));
  }

  bool get_player_info(int ent_num, player_info_t *info) {
    return memory::vfunc<idx::GET_PLAYER_INFO, bool>(this, ent_num, info);
  }

  int get_player_for_user_id(int user_id) {
    return memory::vfunc<idx::GET_PLAYER_USER_ID, int>(this, user_id);
  }

  int get_local_player() { return memory::vfunc<idx::GET_LOCAL_PLAYER, int>(this); }

  void get_view_angles(qangle *angles) {
    return memory::vfunc<idx::GET_VIEW_ANGLES, void>(this, angles);
  }

  void set_view_angles(qangle *angles) {
    return memory::vfunc<idx::SET_VIEW_ANGLES, void>(this, angles);
  }

  int get_max_clients() { return memory::vfunc<idx::GET_MAX_CLIENTS, int>(this); }

  bool is_in_game() { return memory::vfunc<idx::IS_IN_GAME, bool>(this); }

  bool is_connected() { return memory::vfunc<idx::IS_CONNECTED, bool>(this); }

  char const *get_map_name() { return memory::vfunc<idx::GET_MAP_NAME, char const *>(this); }

  bool is_taking_screenshot() { return memory::vfunc<idx::IS_TAKING_SS, bool>(this); }

  void execute_client_cmd(char const *command) {
    return memory::vfunc<idx::EXEC_CLIENT_CMD, void>(this, command);
  }

  void client_cmd_unrestricted(char const *command) {
    return memory::vfunc<idx::EXEC_CMD_UNRESTRICTED, void>(this, command);
  }
};
