#pragma once
#include "Entity.hpp"
#include "types/script/types.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	class Vehicle : public Entity
	{
	public:
		using Entity::Entity;

		static Vehicle Create(std::uint32_t model, rage::fvector3 coords, float heading = 0.0f);

		// health
		void Fix();

		// motion
		void BringToHalt(float distance = 1.0f, int duration = 1);

		// mods
		void Upgrade();
		std::string GetPlateText();
		void SetPlateText(std::string_view text);
		std::map<int, int32_t> GetOwnedMods();

		// seats
		bool IsSeatFree(int seat);
		int GetMaxNumOfPassengers();

		// doors
		void ToggleAllDoors(bool open);

		// Hydraulics
		bool HasHydraulics();
		void RaiseHydraulicWheel(int wheelIndex, float raiseFactor);
		void LowerHydraulicWheel(int wheelIndex, float raiseFactor);

		// stance
		void LowerStance(bool lower);

		// position
		bool SetOnGroundProperly();
		static Vector3 GetSpawnLocRelToPed(int ped, joaat_t hash);

		// description
		std::string GetFullName();
	};
}