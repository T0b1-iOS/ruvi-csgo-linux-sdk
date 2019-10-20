/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <vector>
#include <algorithm>

// framework includes
#include "element.hh"

namespace fgui {

	class combobox final : public fgui::element {
	public:
		combobox();

		// draw the element
		void draw() override;
		
		// add a new entry in the combobox
		void add_item(const std::string_view item, const int &value = 0) noexcept {

			m_info.push_back({ item, value }); 
		}

		// clear all entries of the combobox
		void clear_items() noexcept {

			m_info.clear();
		}

		// this will trigger a function when the user selects a new item
		void set_function(const std::function<void()> &callback) noexcept {
			
			m_callback = callback;
		}

		// select a specific entry of the combobox
		void set_index(int index) noexcept {

			m_index = index;
		}

		// get the index of the current selected entry
		int get_index() const noexcept {

			return m_index;
		}

		// get the value of the selected item
		int get_value() const noexcept {

			return m_info[m_index].value;
		}

		// sets a custom state for the combobox (if the dropdown list is opened or not)
		void set_state(fgui::state state) {

			m_opened = state;
		}

		// returns the current state of the combobox (if the dropdown list is opened or not)
		fgui::state get_state() const noexcept {
			
			return m_opened;
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
		fgui::state m_opened;
		std::function<void()> m_callback;
		std::vector<fgui::detail::item_info> m_info;
	};
}
