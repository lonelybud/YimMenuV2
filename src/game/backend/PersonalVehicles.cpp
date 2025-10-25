#include "PersonalVehicles.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Stats.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "types/script/globals/MPSV.hpp"
#include "types/script/globals/FreemodeGeneral.hpp"
#include "types/script/globals/g_SavedMPGlobals.hpp"

#define MAX_GARAGE_NUM 33

namespace YimMenu
{
	PersonalVehicles::PersonalVehicle::PersonalVehicle(int id, MPSV_Entry* data) :
	    m_Id(id),
	    m_Data(data)
	{
		m_Model = m_Data->VehicleModel;
		m_Plate = m_Data->NumberPlateText;
		m_Name = std::format("{} ({})", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_Model)), m_Plate);
	}

	int PersonalVehicles::PersonalVehicle::GetId()
	{
		return m_Id;
	}

	MPSV_Entry* PersonalVehicles::PersonalVehicle::GetData()
	{
		return m_Data;
	}

	std::string PersonalVehicles::PersonalVehicle::GetName()
	{
		return m_Name;
	}

	bool PersonalVehicles::PersonalVehicle::Repair()
	{
		if (m_Data->PersonalVehicleFlags.IsSet(ePersonalVehicleFlags::DESTROYED) && m_Data->PersonalVehicleFlags.IsSet(ePersonalVehicleFlags::HAS_INSURANCE))
		{
			m_Data->PersonalVehicleFlags.Clear(ePersonalVehicleFlags::DESTROYED);
			m_Data->PersonalVehicleFlags.Clear(ePersonalVehicleFlags::IMPOUNDED);
			m_Data->PersonalVehicleFlags.Clear(ePersonalVehicleFlags::UNK2);
			return true;
		}

		return false;
	}

	bool PersonalVehicles::PersonalVehicle::Request()
	{
		if (auto freemodeGeneral = FreemodeGeneral::Get())
		{
			if (freemodeGeneral->RequestedPersonalVehicleId != -1)
				return false;

			// a pv already exists despawn it first.
			if (auto veh = GetCurrentHandle(); veh.IsValid())
				return false;

			ScriptMgr::Yield(100ms);

			freemodeGeneral->PersonalVehicleRequested = TRUE; // am_pi_menu also sets the field 956 but I guess we don't need that
			freemodeGeneral->Exec1Impound = FALSE;            // not really sure what this does
			freemodeGeneral->RequestedPersonalVehicleId = m_Id;

			ScriptMgr::Yield(100ms);

			*ScriptLocal("freemode"_J, 19447).At(176).As<int*>() = 0;

			return true;
		}

		return false;
	}

	std::unique_ptr<PersonalVehicles::PersonalVehicle> PersonalVehicles::GetCurrentImpl()
	{
		auto savedMPGlobals = g_SavedMPGlobals::Get();
		auto MPSV = MPSV::Get();
		if (savedMPGlobals && MPSV)
		{
			auto id = savedMPGlobals->Entries[0].GeneralSaved.LastSavedCar;
			auto data = &MPSV->Entries[id];
			return std::make_unique<PersonalVehicle>(id, data);
		}

		return nullptr;
	}

	Vehicle PersonalVehicles::GetCurrentHandleImpl()
	{
		if (auto freemodeGeneral = FreemodeGeneral::Get())
		{
			if (auto veh = freemodeGeneral->PersonalVehicleIndex; veh != -1)
				return Vehicle(veh);
		}

		return nullptr;
	}

	void PersonalVehicles::RegisterVehiclesImpl()
	{
		if (auto mpsv = MPSV::Get())
		{
			const auto arraySize = *(int*)mpsv;

			m_PersonalVehicles.clear();

			for (int i = 0; i < arraySize; i++)
			{
				if (i % 100 == 0)
					ScriptMgr::Yield();

				auto data = &MPSV::Get()->Entries[i];
				const auto model = data->VehicleModel;

				if (STREAMING::IS_MODEL_A_VEHICLE(model))
				{
					auto veh = std::make_unique<PersonalVehicle>(i, data);
					m_PersonalVehicles.emplace(veh->GetName(), std::move(veh));
				}
			}
		}
	}

	bool PersonalVehicles::PersonalVehicle::IsBlacklistedVehicle() const
	{
		switch (m_Model)
		{
		case "avenger"_J:
		case "avenger3"_J:
		case "hauler2"_J:
		case "phantom3"_J:
		case "trailersmall2"_J:
		case "khanjali"_J:
		case "chernobog"_J:
		case "riot2"_J:
		case "thruster"_J:
		case "brickade2"_J:
		case "manchez3"_J:
		case "terbyte"_J:
		case "speedo4"_J:
		case "mule4"_J:
		case "pounder2"_J:
		case "rcbandito"_J:
		case "minitank"_J: return true;
		}
		return false;
	}
}