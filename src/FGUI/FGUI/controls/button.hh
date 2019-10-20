/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <vector>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class button final : public fgui::element {
	public:
		button();

		// draw the element
		void draw() override;

		// set the function that the button will call when clicked
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
		std::function<void()> m_callback;
	};
}