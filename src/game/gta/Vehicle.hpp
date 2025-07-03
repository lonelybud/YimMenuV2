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
		std::string GetPlateText();
		void SetPlateText(std::string_view text);
		std::map<int, int32_t> GetOwnedMods();

		// seats
		bool IsSeatFree(int seat);

		bool HasHydraulics();
		void RaiseHydraulicWheel(int wheelIndex, float raiseFactor);
		void LowerHydraulicWheel(int wheelIndex, float raiseFactor);

		// stance
		void LowerStance(bool lower);

		void BringToHalt(float distance = 1.0f, int duration = 1);
		bool SetOnGroundProperly();

		std::string GetFullName();
	};
}