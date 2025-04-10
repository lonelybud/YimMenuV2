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
		void SetPlateText(std::string_view text);

		// seats
		bool IsSeatFree(int seat);
	};
}