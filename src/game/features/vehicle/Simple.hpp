#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/util/strings.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/data/StackSizes.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "types/script/Timer.hpp"
#include "types/script/globals/MPSV.hpp"

namespace YimMenu::Features
{
	inline void EnterLastVehicle()
	{
		FiberPool::Push([] {
			if (auto last_veh = Self::GetPed().GetLastVehicle())
				Self::GetPed().SetInVehicle(last_veh);
		});
	}

	inline void RepairVehicle()
	{
		FiberPool::Push([] {
			if (Self::GetVehicle())
				Self::GetVehicle().Fix();
		});
	}

	inline void SpawnVehicle(std::string _model, bool spawn_in, bool max_upgade)
	{
		auto model = trimString(_model);

		if (!model.length())
		{
			Notifications::Show("Spawn Vehicle", "No model name provided.", NotificationType::Error);
			return;
		}

		FiberPool::Push([model, spawn_in, max_upgade] {
			Hash modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				auto veh = Vehicle::Create(modelHash, Self::GetPed().GetPosition(), Self::GetPed().GetHeading());

				if (spawn_in)
					Self::GetPed().SetInVehicle(veh);

				if (max_upgade)
					veh.Upgrade();
			}
			else
			{
				Notifications::Show("Spawn Vehicle", "Invalid model name provided.", NotificationType::Error);
			}
		});
	}

	inline void _ResetVehDeliveryCooldown()
	{
		ScriptGlobal(2685663).At(4344).At(251).At(7, 2).As<TIMER*>()->Destroy();
	}

	inline void ResetVehDeliveryCooldown()
	{
		FiberPool::Push([] {
			_ResetVehDeliveryCooldown();
		});
	}

	inline void CallMechanic()
	{
		FiberPool::Push([] {
			if (!*Pointers.IsSessionStarted || SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("AM_CONTACT_REQUESTS"_J) > 0)
			{
				Notifications::Show("Mechanic", "Not safe to call the mechanic at the moment.", NotificationType::Error);
				return;
			}

			if (auto freemode = Scripts::FindScriptThread("freemode"_J))
			{
				auto data                     = ScriptLocal(freemode, 8732);
				*data.At(3).As<int*>()        = 215;
				*data.At(3).At(16).As<int*>() = Self::GetPlayer().GetId();
				*data.At(3).At(1).As<int*>()  = 89;
				*data.At(2).As<int*>()        = "AM_CONTACT_REQUESTS"_J;

				while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("AM_CONTACT_REQUESTS"_J))
				{
					SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("AM_CONTACT_REQUESTS"_J);
					ScriptMgr::Yield();
				}

				auto args = data.At(3).As<void*>();
				if (auto id = BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS("AM_CONTACT_REQUESTS"_J, args, 21, eStackSizes::SCRIPT_XML))
				{
					if (auto thread = Scripts::FindScriptThreadByID(id))
					{
						*ScriptLocal(thread, 519).As<int*>() = 1;
						_ResetVehDeliveryCooldown();
					}
				}
				else
				{
					Notifications::Show("Mechanic", "Failed to call the mechanic.", NotificationType::Error);
				}

				SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("AM_CONTACT_REQUESTS"_J);
			}
		});
	}

	inline void FixAllVehicles()
	{
		FiberPool::Push([] {
			if (auto mpsv = MPSV::Get())
			{
				int count = 0;
				for (int i = 0; i < *(int*)mpsv; i++)
				{
					if (mpsv->Entries[i].PersonalVehicleFlags.IsSet(1) && mpsv->Entries[i].PersonalVehicleFlags.IsSet(2))
					{
						mpsv->Entries[i].PersonalVehicleFlags.Clear(1);
						mpsv->Entries[i].PersonalVehicleFlags.Clear(6);
						mpsv->Entries[i].PersonalVehicleFlags.Clear(16);
						mpsv->Entries[i].PersonalVehicleFlags.Set(0);
						mpsv->Entries[i].PersonalVehicleFlags.Set(11);
						count++;
					}
				}

				if (count > 0)
					Notifications::Show("Fix All Vehicles", std::format("{} vehicles fixed.", count), NotificationType::Success);
				else
					Notifications::Show("Fix All Vehicles", "No vehicles to fix.");
			}
		});
	}
}