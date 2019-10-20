##
## project settings
## 

# cmake minimum version
cmake_minimum_required(VERSION 2.8)

# project name
project(ruvi)

# enable c++ 17
set(CMAKE_CXX_STANDARD 17)

#include directories (including fgui library includes)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/FGUI)

# link fgui library (uncomment this if you are going to use the library instead of the source files)
#link_directories(${CMAKE_SOURCE_DIR}/src/FGUI)

# disable warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-narrowing")

# cheat source files
add_library(ruvi SHARED
        
        # cheat
        src/core/entry.cc
        src/core/hooks/hooks.cc
        src/core/interfaces/interfaces.cc
        src/menu/menu.cc
        src/sdk/input/input.cc
        src/sdk/memory/memory.cc
        src/sdk/netvars/netvars.cc
        src/sdk/render/render.cc
        
        # framework // remove this if you are going to use the library
        src/FGUI/FGUI/controls/button.cc
        src/FGUI/FGUI/controls/checkbox.cc
        src/FGUI/FGUI/controls/colorlist.cc
        src/FGUI/FGUI/controls/colorpicker.cc
        src/FGUI/FGUI/controls/combobox.cc
        src/FGUI/FGUI/controls/container.cc
        src/FGUI/FGUI/controls/element.cc
        src/FGUI/FGUI/controls/keybinder.cc
        src/FGUI/FGUI/controls/label.cc
        src/FGUI/FGUI/controls/listbox.cc
        src/FGUI/FGUI/controls/multibox.cc
        src/FGUI/FGUI/controls/slider.cc
        src/FGUI/FGUI/controls/spinner.cc
        src/FGUI/FGUI/controls/tabs.cc
        src/FGUI/FGUI/controls/textbox.cc
        src/FGUI/FGUI/handler/handler.cc
        src/FGUI/FGUI/notifications/notifications.cc)

# link fgui library against the project (uncomment this if you are going to use the library instead of the source files)
#target_link_libraries(ruvi fgui)
