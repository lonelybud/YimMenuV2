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
		m_Name  = std::format("{} ({})", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL( m_Data->VehicleModel)), m_Data->NumberPlateText.Data);
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

	std::unique_ptr<PersonalVehicles::PersonalVehicle> PersonalVehicles::GetCurrentImpl()
	{
		auto savedMPGlobals = g_SavedMPGlobals::Get();
		auto MPSV           = MPSV::Get();
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
				const auto model  = data->VehicleModel;

				if (STREAMING::IS_MODEL_A_VEHICLE(model))
				{
					auto veh = std::make_unique<PersonalVehicle>(i, data);
					m_PersonalVehicles.emplace(veh->GetName(), std::move(veh));
				}
			}
		}
	}
}