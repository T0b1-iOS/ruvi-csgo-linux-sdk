//
//  ruvi base
//

// includes
#include "sdk/memory/memory.hh"
#include "sdk/indices.hh"

class i_panel {
public:
	const char *get_name(unsigned long long vgui_panel) {
		return memory::vfunc<idx::PANEL_GET_NAME, const char *>(this, vgui_panel);
	}
};
