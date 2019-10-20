//
//  ruvi base
//

// includes
#include "menu.hh"
#include "FGUI/dependencies/definitions.hh"

#ifdef _WIN32
#define WINDOW_TITLE "Ruvi for Counter-Strike: Global Offensive(Win32 Edition)"
#else
#define WINDOW_TITLE "Ruvi for Counter-Strike: Global Offensive"
#endif

void menu::on_entry_point() {

  // default fonts
  fgui::element_font title_font = { "Verdana Bold", 11, fgui::external::font_flags::ANTIALIAS | fgui::external::font_flags::SHADOW, true };
  fgui::element_font element_font = { "Verdana", 11, fgui::external::font_flags::ANTIALIAS, false };

  // initialize notifications
  REGISTER_NOTIFICATIONS(0,0,title_font);

  // initialize the main window
  ADD_WINDOW(vars::container["#window"], 50, 50, WINDOW_TITLE, 560, 450, fgui::external::key_code::KEY_HOME, title_font, true);

  // initialize the input system
  REGISTER_CURSOR(fgui::cursor_type::ARROW, fgui::input_state::UNLOCKED);

  REGISTER_TAB(vars::tabs["#tab_panel"], 7, 1, fgui::tab_layout::HORIZONTAL, title_font, vars::container["#window"], -1);

  ADD_TAB(vars::tabs["#tab_panel"], "Aimbot"); {
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Visuals"); {
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Misc"); {
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Colors"); {
  }

  ADD_TAB(vars::tabs["#tab_panel"], "Settings"); {
  }

  //
  // see https://github.com/iFloody/fgui/wiki for more info about the framework
  //
}
