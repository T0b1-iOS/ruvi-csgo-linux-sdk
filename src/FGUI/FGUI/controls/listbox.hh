/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <vector>

// framework includes
#include "element.hh"

namespace fgui {

	class listbox final : public fgui::element {
	public:
		listbox();

		// draw the element
		void draw() override;

		// add a new item in the element
	    void add_item(const std::string_view item, const int &value = 0) noexcept {

			m_info.push_back( {item, value } );
		}

		// returns the name of the selected item
		std::string_view get_item() const noexcept {

			return m_info[m_index].item;
		}

		// get the index of the selected item
		int get_index() const noexcept {

			return m_index;
		}

		// get the value of a selected item
		int get_value() const noexcept {

			return m_info[m_index].value;
		}

		// set a pre-selected item for the element
		void set_index(const int &index) noexcept {

			m_index = index;
		}

		// handle keyboard and mouse input
		void handle_input() override;

		// handle the element updates
		void update() override;

		// element tooltip
		void tooltip() override;

		// save the element state
		void save(nlohmann::json& json_module) override;

		// load the element state
		void load(const std::string_view file_name) override;
	private:

		std::size_t m_index;
		bool m_dragging;
		int m_slider_top;
		int m_item_height;
		std::vector<fgui::detail::item_info> m_info;
	};
}
