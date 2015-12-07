#pragma once
#include "shared.hpp"
#include "client\client.hpp"
#include "client\client_types.hpp"

using namespace intercept::client::types;

namespace intercept {
	namespace sqf {
		namespace __uncategorized {
			/* potential namespace: */
			std::vector<std::string> action_keys(std::string user_action_);

			text action_keys_image(std::string user_action_);

			std::string action_keys_names(std::string user_action_);
			std::string action_keys_names(std::string user_action_, float max_keys_);
			std::string action_keys_names(std::string user_action_, float max_keys_, std::string input_device_priority_);

			std::vector<std::string> action_keys_names_array(std::string user_action_);
			std::vector<std::string> action_keys_names_array(std::string user_action_, float max_keys_);
			std::vector<std::string> action_keys_names_array(std::string user_action_, float max_keys_, std::string input_device_priority_);

			/* potential namespace: misc, missions */
			void activate_addons(std::vector<std::string> &addons_);

			/* potential namespace: camera */
			void add_cam_shake(float power_, float duration_, float frequency_);

			/* potential namespace: items, inventory, campaign */
			void add_item_pool(std::string item_name_, float item_count_);
			void add_magazine_pool(std::string mag_name_, float mag_count_);

			/* potential namespace: core, misc, world */
			void add_to_remains_collector(std::vector<object> objects_);

			/* potential namespace: medical, misc, unit */
			void ais_finish_heal(object &wounded_, object &medic_, bool medic_can_heal_);

			/* potential namespace: core, display, all */
			std::vector<control> all_controls(display display_); // @todo

			/* potential namespace: core, all */
			std::vector<object> all_mission_objects(std::string type_);

		}
	}
}