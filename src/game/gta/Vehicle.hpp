#pragma once
#include "Entity.hpp"

namespace YimMenu
{
	class Vehicle : public Entity
	{
	public:
		using Entity::Entity;

		static Vehicle Create(std::uint32_t model, rage::fvector3 coords, float heading = 0.0f);

		void Fix();

		// mods
		void Upgrade();
		void SetPlateText(const char* plate);
		bool is_bennys();
		std::map<int, int32_t> get_owned_mods();
	
		// seats
		bool IsSeatFree(int seat);
	};
}