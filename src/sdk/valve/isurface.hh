//
//  ruvi base
//

#pragma once

// includes
#include "sdk/memory/memory.hh"
#include "sdk/netvars/netvars.hh"
#include <functional>
#include "sdk/indices.hh"

// framework includes
#include <FGUI/dependencies/definitions.hh>

class i_surface {
public:
  OFFSET_PTR(bool, m_bClippingEnabled, offsets::CLIPPING_ENABLED);

  void draw_set_color(int red, int green, int blue, int alpha) {
    return memory::vfunc<idx::DRAW_SET_COLOR, void>(this, red, green, blue, alpha);
  }

  void draw_filled_rect(int x, int y, int width, int height) {
    return memory::vfunc<idx::DRAW_FILLED_RECT, void>(this, x, y, width, height);
  }

  void draw_outlined_rect(int x, int y, int width, int height) {
    return memory::vfunc<idx::DRAW_OUTLINED_RECT, void>(this, x, y, width, height);
  }

  void draw_line(int x1, int y1, int x2, int y2) {
    return memory::vfunc<idx::DRAW_LINE, void>(this, x1, y1, x2, y2);
  }

  void draw_set_texture_file(int texture_id, const char *texture_name,
                             int hardware_filter, bool force_reload = 0) {
    return memory::vfunc<idx::DRAW_SET_TEX_FILE, void>(this, texture_id, texture_name,
                                   hardware_filter, force_reload);
  }

  void draw_set_texture_rgba(int texture_id, unsigned const char *rgba_data,
                             int width, int height) {
    return memory::vfunc<idx::DRAW_SET_TEX_RGBA, void>(this, texture_id, rgba_data, width, height);
  }

  void draw_set_texture(int texture_id) {
    return memory::vfunc<idx::DRAW_SET_TEX, void>(this, texture_id);
  }

  void draw_textured_rect(int x, int y, int width, int height) {
    return memory::vfunc<idx::DRAW_TEX_RECT, void>(this, x, y, width, height);
  }

  bool is_texture_id_valid(int texture_id) {
    return memory::vfunc<idx::IS_TEX_ID_VALID, bool>(this, texture_id);
  }

  int create_new_texture_id(bool is_procedural) {
    return memory::vfunc<idx::CREATE_TEX_ID, int>(this, is_procedural);
  }

  void get_screen_size(int &width, int &height) {
    return memory::vfunc<idx::GET_SCREEN_SIZE, void>(this, std::ref(width), std::ref(height));
  }

  void unlock_cursor() { return memory::vfunc<idx::UNLOCK_CURSOR, void>(this); }

  unsigned long create_font() { return memory::vfunc<idx::CREATE_FONT, unsigned long>(this); }

  bool set_font_glyph_set(unsigned long font, const char *font_name, int tall,
                          int weight, int blur, int scanlines, int flags,
                          int min_range = 0, int max_range = 0) {
    return memory::vfunc<idx::SET_FONT_GLYPH_SET, bool>(this, font, font_name, tall, weight, blur,
                                   scanlines, flags, min_range, max_range);
  }

  void get_text_size(unsigned long font, const wchar_t *text, int &wide,
                     int &tall) {
    return memory::vfunc<idx::GET_TEXT_SIZE, void>(this, font, text, std::ref(wide),
                                   std::ref(tall));
  }

  void play_sound(const char *file_name) {
    return memory::vfunc<idx::PLAY_SOUND, void>(this, file_name);
  }

  void surface_get_cursor_pos(int &x, int &y) {
    return memory::vfunc<idx::SURFACE_GET_CURSOR_POS, void>(this, std::ref(x), std::ref(y));
  }

  void draw_outlined_circle(int x, int y, int radius, int segments) {
    return memory::vfunc<idx::DRAW_OUTLINED_CIRCLE, void>(this, x, y, radius, segments);
  }

  void draw_textured_polygon(int vertex_count, fgui::vertex *vertex,
                             bool clip_vertices = true) {
    return memory::vfunc<idx::DRAW_TEX_POLYGON, void>(this, vertex_count, vertex, clip_vertices);
  }

  void draw_filled_rect_fade(int x, int y, int w, int h, unsigned int alpha1,
                             unsigned int alpha2, bool is_horizontal) {
    return memory::vfunc<idx::DRAW_FILLED_RECT_FADE, void>(this, x, y, w, h, alpha1, alpha2,
                                    is_horizontal);
  }

  void get_clip_rect(int &x, int &y, int &w, int &h) {
    return memory::vfunc<idx::GET_CLIP_RECT, void>(this, x, y, w, h);
  }

  void set_clip_rect(int x, int y, int w, int h) {
    return memory::vfunc<idx::SET_CLIP_RECT, void>(this, x, y, w, h);
  }

  void disable_clipping(int state) {
    return memory::vfunc<idx::DISABLE_CLIPPING, void>(this, state);
  }

  void draw_colored_text(unsigned long font, int x, int y, int red, int green,
                         int blue, int alpha, const char *text) {
#ifndef _WIN32
    return memory::vfunc<idx::DRAW_COL_TEXT, void>(this, font, x, y, red, green, blue, alpha,
                                    text);
#else
	  using fn = void(__cdecl*)(void*, unsigned long, int, int, int, int, int, int, const char*, ...);
	  (*reinterpret_cast<fn * *>(this))[idx::DRAW_COL_TEXT](this, font, x, y, red, green, blue, alpha, text);
#endif
  }
};