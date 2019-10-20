/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class container final : public fgui::element {
	public:
		container();

		// draw the element
		void draw() override;

		// set the container state (this will be used for windows)
		void set_state(const fgui::state &state) noexcept {

			m_opened = state;
		}

		// returns the state of the container
		fgui::state get_state() const noexcept {

			return m_opened;
		}

		// save all elements inside a config file
		void save_config(const std::string_view file_name);

		// add a new control in the container
		void add_control(const std::shared_ptr<fgui::element> &control, int page_index = -1, bool manual_size = false);

		// set whether or not the scrollbar should be used
		void set_scrollbar_state(const fgui::state &state) noexcept {

			m_scrollable = state;
		}

		// enable/disable the resizeable option of the container
		void set_resize_state(const fgui::state &state) noexcept {

			m_resizeable = state;
		}

		// enable/disable the hidden state of the container (hover to unhide)
		void set_hidden_state(const fgui::state &state) noexcept{

			m_hideable = state;
		}

		// returns true if the container has a scrollbar
		fgui::state get_scrollbar_state() const noexcept {

			return m_scrollable;
		}

		// get the amount that a element is suposed to move according with the scrollbar
		int get_scroll_offset() const noexcept {

			return m_scroll_offset;
		}

		// call a function when the window is opened
		void set_function(const std::function<void()> &callback) noexcept {
			
			m_callback = callback;
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

		int m_scroll_offset, m_bottom_element_pos;
		fgui::state m_opened, m_scrollable, m_resizeable, m_hideable;
		bool m_dragging_container, m_size_changing, m_dragging_scrollbar;
		std::vector<std::shared_ptr<fgui::element>> m_elements;
		std::function<void()> m_callback;
	};
}