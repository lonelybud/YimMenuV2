#include "core/frontend/manager/SubmenuMenuCategory.hpp"

namespace YimMenu::Submenus
{
	class VehicleEditorCategory : public SubmenuMenuCategory
	{
		int current_veh      = 0;
		std::string veh_name = "";
		bool preparing_veh   = false;
		bool is_bennys = false;
		int selected_slot = -1;

		std::map<int, int32_t> owned_mods{};
		std::map<int, std::string> slot_display_names{};
		std::map<int, std::map<int, std::string>> mod_display_names{};

		std::map<std::string, std::vector<int>> front_wheel_map{};
		std::map<std::string, std::vector<int>> rear_wheel_map{};
		int front_wheel_stock_mod = -1;
		int rear_wheel_stock_mod  = -1;

		void prepare_vehicle();

	public:
		VehicleEditorCategory() :
		    SubmenuMenuCategory("vehicleEditor")
		{
		}

		void Draw() override;
	};
}