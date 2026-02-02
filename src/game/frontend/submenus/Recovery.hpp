#pragma once
#include "core/frontend/manager/Submenu.hpp"
#include "game/features/recovery/PlayAllMissionsSolo.hpp"
#include "game/features/recovery/Simple.hpp"
#include "game/features/recovery/UnlockEverything.hpp"
#include "game/features/recovery/UnlockGTAPlus.hpp"
#include "game/features/vehicle/SavePersonalVehicle.hpp"
#include "game/frontend/components/components.hpp"
#include "game/features/recovery/RpMultiplier.hpp"
#include "game/features/recovery/LSCCustomsBypass.hpp"
#include "Recovery/DailyActivitiesCategory.hpp"
#include "game/features/recovery/ClaimSafeEarnings.hpp"
#include "Recovery/RecoveryHeistCategory.hpp"

namespace YimMenu::Submenus
{
	class RecoveryGeneralCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			components::checkbox(YimMenu::Features::_UnlockGTAPlus);

			if (*Pointers.IsSessionStarted)
			{
				components::ver_space();
				components::checkbox(YimMenu::Features::_OverrideRPMultiplier);
				if (YimMenu::Features::_OverrideRPMultiplier.m_State)
				{
					ImGui::SameLine();
					ImGui::SetNextItemWidth(200);
					ImGui::SliderFloat("Value###rp_mult_val", &YimMenu::Features::_OverrideRPMultiplier._RpMultiplierInput, 1, 10);
				}

				components::ver_space();

				if (ImGui::Button("Remove Appearance Cooldown"))
					FiberPool::Push([] {
						Tunable("CHARACTER_APPEARANCE_COOLDOWN"_J).Set(0);
					});
				if (ImGui::Button("Allow Gender Change"))
					FiberPool::Push([] {
						Stats::SetInt("MPX_ALLOW_GENDER_CHANGE", 52);
					});
			}
		}
	};

	class RecoveryShoppingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (!*Pointers.IsSessionStarted)
			{
				ImGui::Text("Go online to see this view.");
				return;
			}

			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
				Features::SavePersonalVehicle::Save();

			components::ver_space();

			components::checkbox(YimMenu::Features::_LSCCustomsBypass);

			components::ver_space();

			ImGui::Text("Gun Van -");
			static int selected_slot = 0, selected_weap_slot = 0;
			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Slot##allowedGunVanSlots", Features::allowedGunVanSlots[selected_slot]))
			{
				for (int i = 0; i < Features::allowedGunVanSlots.size(); ++i)
					if (ImGui::Selectable(Features::allowedGunVanSlots[i], selected_slot == i))
						selected_slot = i;
				ImGui::EndCombo();
			}
			ImGui::SetNextItemWidth(300.f);
			if (ImGui::BeginCombo("Weapon##allowedGunVanWeapons", Features::allowedGunVanWeapons[selected_weap_slot]))
			{
				for (int i = 0; i < Features::allowedGunVanWeapons.size(); ++i)
					if (ImGui::Selectable(Features::allowedGunVanWeapons[i], selected_weap_slot == i))
						selected_weap_slot = i;
				ImGui::EndCombo();
			}
			if (ImGui::Button("Set Gun Van Weapon"))
				Features::SetGunvanWeapon(Features::allowedGunVanWeapons[selected_weap_slot], selected_slot + 1);
		}
	};

	class UnlockEverythingCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;

		void Draw()
		{
			if (!*Pointers.IsSessionStarted)
			{
				ImGui::Text("Go online to see this view.");
				return;
			}

			if (ImGui::Button("unlock_packed_bools_simple"))
				UnlockEverything::unlock_packed_bools_simple();

			if (ImGui::Button("unlock_paints"))
				UnlockEverything::unlock_paints();

			if (ImGui::Button("set_misc"))
				UnlockEverything::set_misc();

			if (ImGui::Button("unlock_stats"))
				UnlockEverything::StatUnlockMech.setStat();
			ImGui::SameLine();
			ImGui::Checkbox("Log locked stats in console", &UnlockEverything::StatUnlockMech.logging);
			ImGui::Text("Stats Done: %d/%llu", UnlockEverything::StatUnlockMech.statsUnlocked, UnlockEverything::allStats.size());

			components::ver_space();

			static int achievmentNo = 1;
			ImGui::SetNextItemWidth(200);
			ImGui::SliderInt("Achievment ID", &achievmentNo, 1, 77);
			if (ImGui::Button("Unlock#achievment"))
				UnlockEverything::unlock_achievement(achievmentNo);

			// if (ImGui::Button("set_int_bit"))
			// 	UnlockEverything::set_int_bit(int_bit_index);
			// ImGui::SameLine();
			// ImGui::Text("Done: %d/%llu", int_bit_index, UnlockEverything::_ints_bits.size());

			// if (ImGui::Button("set_ints_bit_range"))
			// 	UnlockEverything::set_ints_bit_range(ints_bit_range_index);
			// ImGui::SameLine();
			// ImGui::Text("Done: %d/%llu", ints_bit_range_index, UnlockEverything::_ints_bits_range.size());
		}
	};

	class RecoveryBusinessCategory : public SubmenuMenuCategory
	{
		using SubmenuMenuCategory::SubmenuMenuCategory;
		void Draw()
		{
			if (!*Pointers.IsSessionStarted)
			{
				ImGui::Text("Go online to see this view.");
				return;
			}

			ImGui::SetNextItemWidth(200.f);
			if (ImGui::BeginCombo("Business##earnings", Features::_ClaimSafeEarnings.selected_business.second))
			{
				for (auto& business : Features::businessNames)
					if (ImGui::Selectable(business.second, Features::_ClaimSafeEarnings.selected_business.first == business.first))
						Features::_ClaimSafeEarnings.selected_business = business;
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			components::button(YimMenu::Features::_ClaimSafeEarnings);

			ImGui::Text("Nightclub Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.NightclubData.SafeCashValue);
			ImGui::Text("Arcade Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.ArcadeData.SafeCashValue);
			ImGui::Text("Agency Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.FixerHQData.SafeCashValue);
			ImGui::Text("SalvageYard Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.SalvageYardData.TotalEarnings);
			ImGui::Text("BailShop Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.BailShopData.SafeCashValue);
			ImGui::Text("GarmentFactory Value: %d", GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.HackerDenData.SafeCashValue);
			ImGui::Text("HandsOnCarWash Value: %d", GPBD_FM_2::Get()->Entries[Self::GetPlayer().GetId()].SYVehSaleData.HOWCData.SafeCashValue);

			components::ver_space();

			if (ImGui::Button("Increase NightClub Popularity"))
				FiberPool::Push([] {
					Stats::SetInt("MPX_CLUB_POPULARITY", 1000);
				});
			if (ImGui::Button("Remove Money Fronts Businesses Heat"))
				FiberPool::Push([] {
					// https://www.unknowncheats.me/forum/grand-theft-auto-v/707419-lua-scripts-yimmenuv2-collection-thread-12.html#post4539651
					for (int i = 24924; i <= 24926; ++i)
						Stats::SetPackedInt(i, 0); // Money Fronts Businesses Heat Removed!
				});

			// components::ver_space();
			// // https://www.unknowncheats.me/forum/grand-theft-auto-v/578963-packed-stats-int-bool-collection-thread-47.html#post4549061
			// static int target = 1;
			// static constexpr const int targetsDeliveryBools[] = {51199, 51200, 5120};
			// static constexpr const int targetsSecureBools[] = {42274, 42275, 42276};
			// ImGui::SetNextItemWidth(150);
			// ImGui::InputInt("Bail Office Target", &target);
			// if (ImGui::Button("Deliver Target"))
			// 	FiberPool::Push([] {
			// 		Stats::SetPackedBool(targetsDeliveryBools[target - 1], true);
			// 	});
			// ImGui::SameLine();
			// if (ImGui::Button("Secure Target"))
			// 	FiberPool::Push([] {
			// 		Stats::SetPackedBool(targetsSecureBools[target - 1], true);
			// 	});
			// if (ImGui::Button("Deliver Most Wanted Target"))
			// 	FiberPool::Push([] {
			// 		Stats::SetPackedBool(51202, true);
			// 	});
			// ImGui::SameLine();
			// if (ImGui::Button("Secure Most Wanted Target"))
			// 	FiberPool::Push([] {
			// 		Stats::SetPackedBool(42251, true);
			// 	});
		}
	};

	class RecoverySubmenu : public Submenu
	{
	public:
		RecoverySubmenu() :
		    Submenu("Recovery")
		{
			auto general = std::make_shared<RecoveryGeneralCategory>("General");
			AddCategory(std::move(general));
			auto shopping = std::make_shared<RecoveryShoppingCategory>("Shopping");
			AddCategory(std::move(shopping));
			auto heist = std::make_shared<RecoveryHeistCategory>("Heist");
			AddCategory(std::move(heist));
			auto business = std::make_shared<RecoveryBusinessCategory>("Business");
			AddCategory(std::move(business));
			auto dailyActivities = std::make_shared<DailyActivitiesCategory>("DailyActivities");
			AddCategory(std::move(dailyActivities));
			auto unlockEverything = std::make_shared<UnlockEverythingCategory>("UnlockEverything");
			AddCategory(std::move(unlockEverything));
		}
	};
}