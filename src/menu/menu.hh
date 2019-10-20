//
//  ruvi base
//

#pragma once

// includes
#include <memory>

// framework includes
#include <FGUI/FGUI.hh>

namespace menu {

void on_entry_point();
}

namespace vars {

inline std::unordered_map<std::string, fgui::button*> button;
inline std::unordered_map<std::string, fgui::checkbox*>
    checkbox;
inline std::unordered_map<std::string, fgui::colorlist*>
    colorlist;
inline std::unordered_map<std::string, fgui::colorpicker*>
    colorpicker;
inline std::unordered_map<std::string, fgui::combobox*>
    combobox;
inline std::unordered_map<std::string, fgui::container*>
    container;
inline std::unordered_map<std::string, fgui::keybinder*>
    keybinder;
inline std::unordered_map<std::string, fgui::label*> label;
inline std::unordered_map<std::string, fgui::listbox*> listbox;
inline std::unordered_map<std::string, fgui::multibox*>
    multibox;
inline std::unordered_map<std::string, fgui::slider*> slider;
inline std::unordered_map<std::string, fgui::spinner*> spinner;
inline std::unordered_map<std::string, fgui::tabs*> tabs;
inline std::unordered_map<std::string, fgui::textbox*> textbox;
} // namespace vars