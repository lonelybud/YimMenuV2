
// #include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/backend/Tunables.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/Stats.hpp"
// #include "game/gta/Vehicle.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
// #include "types/blip/BlipSprite.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/MPScriptData.hpp"
#include "types/script/globals/GPBD_Flow.hpp"
#include "types/script/globals/g_SavedMPGlobals.hpp"
#include "types/script/globals/DailyObjectivesState.hpp"
#include "types/script/globals/WeeklyChallenge.hpp"
// #include "types/script/globals/GSBD_RandomEvents.hpp"
#include "types/script/globals/FreemodeGeneral.hpp"
//#include "types/script/globals/FreemodeDelivery.hpp"
#include "types/script/locals/StandardTimeTrialData.hpp"
#include "types/script/locals/RCBanditoTimeTrialData.hpp"
// #include "types/script/locals/BikeTimeTrialData.hpp"
#include "core/componentStates/BoolState.hpp"
#include "core/componentStates/CallCode.hpp"

namespace YimMenu::Features
{
	static void CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables collectable, int index)
	{
		SCRIPT_EVENT_COLLECT_COLLECTABLE data;
		data.CollectableType = collectable;
		data.CollectableIndex = index;
		data.SetCollected = TRUE;
		data.DisplayNotification = TRUE;
		data.Send();
	}

	static joaat_t GetNextExoticExportsVehicleHash()
	{
		constexpr ScriptGlobal order(1946095);
		for (int i = 1; i <= 10; i++)
		{
			auto offset = *order.At(i).As<int*>();
			if (!GPBD_Flow::Get()->Entries[Self::GetPlayer().GetId()].TunerCBVDeliveredFlags.IsSet(offset))
			{
				auto hash = *ScriptGlobal(1946084 + (offset + 1)).As<joaat_t*>();
				return hash;
			}
		}
		return 0;
	}

	class CompleteAllChallenges : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!Pointers.IsSessionStarted)
				return;

			for (int i = 0; i < 3; i++)
			{
				DailyObjectivesState::Get()->Objective[i] = g_SavedMPGlobals::Get()->Entries[0].GeneralSaved.DOObjectives[i].Objective;
			}
			DailyObjectivesState::Get()->Completed = TRUE;
			WeeklyChallenge::Get()->Entries[0].CurrentObjective = WeeklyChallenge::Get()->Entries[0].ObjectiveCountOverride;
		}
	};

	class CollectHiddenCache : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30297 + hiddenCacheIndex))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::HiddenCaches, hiddenCacheIndex);
			}
			else
			{
				Notifications::Show("Hidden Caches", "This Hidden Cache has already been collected.", NotificationType::Error);
			}
		}

	public:
		// 0 - 9
		int hiddenCacheIndex = 0;
	};

	class CollectTreasureChest : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(30307 + treasureChestIndex))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::TresureChests, treasureChestIndex);
			}
			else
			{
				Notifications::Show("Treasure Chests", "This Treasure Chest has already been collected.", NotificationType::Error);
			}
		}

	public:
		// 0 - 1
		int treasureChestIndex = 0;
	};

	class EnableTreasureChestInLS : public BoolState
	{
		using BoolState::BoolState;

		ScriptPatch m_EnableTreasureChestInLSPatch{};

		virtual void OnEnable() override
		{
			if (!m_EnableTreasureChestInLSPatch)
			{
				m_EnableTreasureChestInLSPatch = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("EnableTreasureChestInLSPatch", "1F 56 ? ? 38 00 47 ? ? 73"), {0x72});
			}
			m_EnableTreasureChestInLSPatch->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_EnableTreasureChestInLSPatch)
			{
				m_EnableTreasureChestInLSPatch->Disable();
			}
		}
	};

	class CollectShipwrecked : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(31734))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Shipwrecked, 0);
			}
			else
			{
				Notifications::Show("Shipwreck", "Shipwreck has already been collected.", NotificationType::Error);
			}
		}
	};

	class CollectBuriedStash : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(25522 + buriedStashIndex))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::BuriedStash, buriedStashIndex);
			}
			else
			{
				Notifications::Show("Buried Stashes", "This Buried Stash has already been collected.", NotificationType::Error);
			}
		}

	public:
		// 0 - 1
		int buriedStashIndex = 0;
	};

	class EnableBuriedStashInLS : public BoolState
	{
		using BoolState::BoolState;

		ScriptPatch m_EnableBuriedStashInLSPatch{};

		virtual void OnEnable() override
		{
			if (!m_EnableBuriedStashInLSPatch)
			{
				m_EnableBuriedStashInLSPatch = ScriptPatches::AddPatch("freemode"_J, ScriptPointer("EnableBuriedStashInLSPatch", "71 39 02 38 02 06 56 ? ? 2C"), {0x72});
			}
			m_EnableBuriedStashInLSPatch->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_EnableBuriedStashInLSPatch)
			{
				m_EnableBuriedStashInLSPatch->Disable();
			}
		}
	};

	class CompleteSkydive : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static Tunable checkpointReward{"SKYDIVING_CHALLENGE_CASH_REWARD_ALL_CHECKPOINTS_COLLECTED"_J};
			static Tunable parTimeReward{"SKYDIVING_CHALLENGE_CASH_REWARD_PAR_TIME"_J};
			static Tunable landingReward{"SKYDIVING_CHALLENGE_CASH_REWARD_ACCURATE_LANDING"_J};

			int index = skydiveIndex;
			int location = Stats::GetInt("MPX_DAILYCOLLECT_SKYDIVES" + std::to_string(index));
			bool checkpoints = Stats::GetPackedInt(34837 + (index * 4)) == location;
			bool partime = Stats::GetPackedInt(34838 + (index * 4)) == location;
			bool landing = Stats::GetPackedInt(34839 + (index * 4)) == location;

			*ScriptGlobal(1975726).As<int*>() = 1;
			*ScriptGlobal(1975726).At(1).As<int*>() = 1;
			*ScriptGlobal(1975726).At(3).As<int*>() = 5;
			*ScriptGlobal(1975726).At(4).As<int*>() = location + 1;
			*ScriptGlobal(1975726).At(8).At(1).As<int*>() = checkpointReward.Get<int>() / (1 + (checkpoints * 9));
			*ScriptGlobal(1975726).At(8).At(2).As<int*>() = parTimeReward.Get<int>() / (1 + (partime * 9));
			*ScriptGlobal(1975726).At(8).At(3).As<int*>() = landingReward.Get<int>() / (1 + (landing * 9));

			SET_SKYDIVE_COMPLETED data;
			data.SkydiveIndex = index;
			data.SkydiveLocation = location;
			data.AllCheckpointsHit = TRUE;
			data.ParTimeBeaten = TRUE;
			data.AccurateLanding = TRUE;
			data.Send();

			ScriptGlobal(1979681).At(4).As<SCR_BITSET<uint64_t>*>()->Clear(3);
		}

	public:
		// 0 - 9
		int skydiveIndex = 0;
	};

	class BeatTimeTrial : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			std::string stat = "";
			switch (timeTrialIndex)
			{
			case 0: stat = "MPPLY_TIMETRIAL_COMPLETED_WEEK"; break;
			case 1: stat = "MPPLY_RCTTCOMPLETEDWEEK"; break;
			case 2: stat = "MPPLY_BTTCOMPLETED"; break;
			}

			if (stat.empty() || Stats::GetInt(stat) != -1)
			{
				Notifications::Show("Time Trials", "This Time Trial has already been beaten.", NotificationType::Error);
				return;
			}

			rage::scrThread* thread = nullptr;
			if (timeTrialIndex == 2)
			{
				if (Scripts::IsScriptActive("fm_content_bicycle_time_trial"_J))
					return;

				MP_SCRIPT_DATA garbage{};
				thread = Scripts::FindScriptThreadByID(Scripts::StartScript("fm_content_bicycle_time_trial"_J, eStackSizes::MULTIPLAYER_FREEMODE, &garbage, SCR_SIZEOF(garbage)));
			}
			else
			{
				thread = Scripts::FindScriptThread("freemode"_J);
			}

			if (!thread)
				return;

			if (timeTrialIndex == 0)
			{
				if (auto ttData = StandardTimeTrialData::Get(thread))
				{
					ttData->Timer1.Time = *Pointers.NetworkTime;
					static ScriptFunction beatStandardTimeTrial("freemode"_J, ScriptPointer("BeatStandardTimeTrial", "2D 01 19 00 00 38"));
					beatStandardTimeTrial.Call<void>(ttData);
				}
			}
			else if (timeTrialIndex == 1)
			{
				if (auto rcttData = RCBanditoTimeTrialData::Get(thread))
				{
					rcttData->Timer1.Time = *Pointers.NetworkTime;
					static ScriptFunction beatRCTimeTrial("freemode"_J, ScriptPointer("BeatRCTimeTrial", "2D 01 17 00 00 38 00 40"));
					beatRCTimeTrial.Call<void>(rcttData);
				}
			}
			else if (timeTrialIndex == 2)
			{
				thread->m_Context.m_State = rage::scrThread::State::PAUSED;

				*ScriptLocal(thread, 3088).At(131).At(1).As<int*>() = FreemodeGeneral::Get()->DailyReset.Seed % 14; // if we don't init this, the par time duration function will return 0 and the COMPLETED stat will be set to 0, which is bad
				*ScriptLocal(thread, 144).At(4).As<int*>() = 0;
				static ScriptFunction onBTTEnd("fm_content_bicycle_time_trial"_J,
				    ScriptPointer("OnBTTEnd", "64 ? ? ? 5D ? ? ? 75 77").Add(1).Rip());
				onBTTEnd.Call<void>();

				thread->m_Context.m_State = rage::scrThread::State::KILLED;
			}
		}
	
	public:
		// 0 - 2
		int timeTrialIndex = 0;
	};

	class DeliverNextExoticExportsVehicle : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (GPBD_Flow::Get()->Entries[Self::GetPlayer().GetId()].TunerCBVDeliveredFlags.Value == 1023)
			{
				Notifications::Show("Exotic Exports", "You have already delivered all the vehicles.", NotificationType::Error);
				return;
			}

			/*if (!FreemodeDelivery::Get()->DeliveryCooldown1.HasTimePassed(30000))
			{
				Notifications::Show("Exotic Exports", "You have just delivered a vehicle, wait a moment.", NotificationType::Error);
				return;
			}*/

			auto hash = GetNextExoticExportsVehicleHash();
			static ScriptFunction onFreemodeDeliveryEnd("freemode"_J, ScriptPointer("OnFreemodeDeliveryEnd", "2D 0C 2A 00 00"));
			onFreemodeDeliveryEnd.Call<void>(0, Self::GetPlayer().GetId(), 0, 0, 0, 0, 0, 0, 0, 0, hash, 273);
			//FreemodeDelivery::Get()->DeliveryCooldown1.Reset();
		}
	};

	class CollectDeadDrop : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(36628))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::DeadDrop, 0);
			}
			else
			{
				Notifications::Show("G's Cache", "G's Cache has already been collected.", NotificationType::Error);
			}
		}
	};

	class EnterStashHouseSafeCode : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (auto thread = Scripts::FindScriptThread("fm_content_stash_house"_J))
			{
				for (int i = 0; i < 3; i++)
				{
					int combination = *ScriptLocal(thread, 144).At(22).At(i, 2).At(1).As<int*>();
					*ScriptLocal(thread, 144).At(22).At(i, 2).As<float*>() = combination;
				}
			}
		}
	};

	class SprayLSTag : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(42252 + lsTagIndex))
			{
				CollectCollectable(SCRIPT_EVENT_COLLECT_COLLECTABLE::eCollectables::Tagging, lsTagIndex);
			}
			else
			{
				Notifications::Show("LS Tags", "This LS Tag has already been sprayed.", NotificationType::Error);
			}
		}

	public:
		// 0 - 4
		int lsTagIndex = 0;
	};

	static constexpr auto wildlifePhotographyAnimalHashes = std::to_array({"A_C_Boar"_J,
	    "A_C_Cat_01"_J,
	    "A_C_Cow"_J,
	    "A_C_Coyote"_J,
	    "A_C_Deer"_J,
	    "A_C_Husky"_J,
	    "A_C_MtLion"_J,
	    "A_C_Pig"_J,
	    "A_C_Poodle"_J,
	    "A_C_Pug"_J,
	    "A_C_Rabbit_01"_J,
	    "A_C_Retriever"_J,
	    "A_C_Rottweiler"_J,
	    "A_C_shepherd"_J,
	    "A_C_Westy"_J,
	    "A_C_Chickenhawk"_J,
	    "A_C_Cormorant"_J,
	    "A_C_Crow"_J,
	    "A_C_Hen"_J,
	    "A_C_Seagull"_J});

	class PhotographAnimal : public CallCode
	{
		using CallCode::CallCode;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			if (!Stats::GetPackedBool(42059 + animalIndex))
			{
				int index = Stats::GetPackedInt(28091 + animalIndex);
				if (index < 0 || index >= wildlifePhotographyAnimalHashes.size())
					return;

				ScriptGlobal(2708777).At(544).As<SCR_BITSET<uint64_t>*>()->Set(6);
				*ScriptGlobal(2708777).At(547).As<joaat_t*>() = wildlifePhotographyAnimalHashes[index];
				*ScriptGlobal(2708777).At(548).As<int*>() = *Pointers.GameTimer - 1; // bypass 2 sec delay
			}
			else
			{
				Notifications::Show("Shoot Animals Photography", "This animal has already been photographed.", NotificationType::Error);
			}
		}

	public:
		// 0 - 2
		int animalIndex = 0;
	};

	inline EnableTreasureChestInLS _EnableTreasureChestInLS{"enabletreasurechestinls", "Enable Treasure Chests in LS", "Enables Treasure Chests in Los Santos, so you don't have to go to Cayo Perico."};
	inline EnableBuriedStashInLS _EnableBuriedStashInLS{"enableburiedstashinls", "Enable Buried Stashes in LS", "Enables Buried Stashes in Los Santos, so you don't have to go to Cayo Perico."};

	inline CompleteAllChallenges _CompleteAllChallenges{"completeallchallenges", "Complete All Challenges", "Completes all the Daily Objectives and the Weekly Challenge."};
	inline CollectHiddenCache _CollectHiddenCache{"collecthiddencache", "Collect Hidden Cache", "Collects the selected Hidden Cache."};
	inline CollectTreasureChest _CollectTreasureChest{"collecttreasurechest", "Collect Treasure Chest", "Collects the selected Treasure Chest."};
	inline CollectShipwrecked _CollectShipwrecked{"collectshipwrecked", "Collect Shipwreck", "Collects Shipwreck."};
	inline CollectBuriedStash _CollectBuriedStash{"collectburiedstash", "Collect Buried Stash", "Collects the selected Buried Stash."};
	inline CompleteSkydive _CompleteSkydive{"completeskydive", "Complete Skydive", "Completes the selected Skydive."};
	inline BeatTimeTrial _BeatTimeTrial{"beattimetrial", "Beat Time Trial", "Completes the selected Time Trial."};
	inline DeliverNextExoticExportsVehicle _DeliverNextExoticExportsVehicle{"delivernextexoticexportsvehicle", "Deliver Next Exotic Exports Vehicle", "Directly delivers the next Exotic Exports vehicle."};
	inline CollectDeadDrop _CollectDeadDrop{"collectdeaddrop", "Collect G's Cache", "Collects G's Cache."};
	inline EnterStashHouseSafeCode _EnterStashHouseSafeCode{"enterstashhousesafecode", "Enter Stash House Safe Code", "Enters the Stash House safe code."};
	inline SprayLSTag _SprayLSTag{"spraylstag", "Spray LS Tag", "Sprays the selected LS Tag."};
	inline PhotographAnimal _PhotographAnimal{"photographanimal", "Photograph Animal", "Photographs the selected animal."};
}