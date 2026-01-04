#pragma once
#include "core/util/Joaat.hpp"
#include "game/gta/Vehicle.hpp"

#include <set>

struct MPSV_Entry;

namespace YimMenu
{
	class PersonalVehicles
	{
	public:
		class PersonalVehicle
		{
			int m_Id;
			MPSV_Entry* m_Data;
			joaat_t m_Model;
			std::string m_Name;
			std::string m_Plate;

		public:
			PersonalVehicle(int id, MPSV_Entry* data);

			int GetId() const;
			MPSV_Entry* GetData();
			std::string GetName();

			bool Repair();
			bool Request();
			bool IsBlacklistedVehicle() const;
		};

		static std::unique_ptr<PersonalVehicle> GetCurrent()
		{
			return GetInstance().GetCurrentImpl();
		}

		static Vehicle GetCurrentHandle()
		{
			return GetInstance().GetCurrentHandleImpl();
		}

		static std::map<std::string, std::unique_ptr<PersonalVehicle>>& GetPersonalVehicles()
		{
			return GetInstance().m_PersonalVehicles;
		}

		static void RegisterVehicles()
		{
			GetInstance().RegisterVehiclesImpl();
		}

	private:
		static PersonalVehicles& GetInstance()
		{
			static PersonalVehicles instance;
			return instance;
		}

		std::unique_ptr<PersonalVehicle> GetCurrentImpl();
		Vehicle GetCurrentHandleImpl();;
		void RegisterVehiclesImpl();

		std::map<std::string, std::unique_ptr<PersonalVehicle>> m_PersonalVehicles;
		std::chrono::time_point<std::chrono::steady_clock> m_LastUpdate;
	};
}