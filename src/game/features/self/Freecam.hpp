#include "core/componentStates/LoopState.hpp"
#include "core/util/Math.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/GUI.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"


namespace YimMenu::Features
{
	class Freecam : public LoopState
	{
		using LoopState::LoopState;

		float speed = 0.5f;
		float mult  = 0.f;

		int camEntity = 0;
		Vector3 position{};
		Vector3 rotation{};

		virtual void OnEnable()
		{
			camEntity = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
			position  = CAM::GET_GAMEPLAY_CAM_COORD();
			rotation  = CAM::GET_GAMEPLAY_CAM_ROT(2);

			CAM::SET_CAM_COORD(camEntity, position.x, position.y, position.z);
			CAM::SET_CAM_ROT(camEntity, rotation.x, rotation.y, rotation.z, 2);
			CAM::SET_CAM_ACTIVE(camEntity, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);
		}

		void UpdateFreecamPosition()
		{
			if (GUI::IsOpen())
				return;

			Vector3 vecChange = {0.f, 0.f, 0.f};

			// Left Shift
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
				vecChange.z += speed / 2;
			// Space
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				vecChange.z -= speed / 2;
			// Forward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				vecChange.y += speed;
			// Backward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				vecChange.y -= speed;
			// Left
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				vecChange.x -= speed;
			// Right
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				vecChange.x += speed;

			if (vecChange.x == 0.f && vecChange.y == 0.f && vecChange.z == 0.f)
				mult = 0.f;
			else if (mult < 10)
				mult += 0.15f;

			Vector3 rot = CAM::GET_CAM_ROT(camEntity, 2);
			float yaw   = Math::DegToRad(rot.z);

			position.x += (vecChange.x * cos(yaw) - vecChange.y * sin(yaw)) * mult;
			position.y += (vecChange.x * sin(yaw) + vecChange.y * cos(yaw)) * mult;
			position.z += vecChange.z * mult;

			CAM::SET_CAM_COORD(camEntity, position.x, position.y, position.z);
			STREAMING::SET_FOCUS_POS_AND_VEL(position.x, position.y, position.z, 0.0f, 0.0f, 0.0f);
		}

		virtual void OnTick() override
		{
			UpdateFreecamPosition();

			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			CAM::SET_CAM_ROT(camEntity, rotation.x, rotation.y, rotation.z, 2);

			TASK::CLEAR_PED_TASKS(Self::GetPed().GetHandle());
			TASK::CLEAR_PED_SECONDARY_TASK(Self::GetPed().GetHandle());
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(Self::GetPed().GetHandle());
			Self::GetPed().SetFrozen(true);
			Self::GetPed().SetVisible(false);

			if (!GUI::IsOpen())
			{
				static Hash controls[]{
				    (Hash)ControllerInputs::INPUT_JUMP,
				    (Hash)ControllerInputs::INPUT_SPRINT,
				    (Hash)ControllerInputs::INPUT_LOOK_UP_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_DOWN_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_LEFT_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_RIGHT_ONLY,
				};
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

				for (Hash c : controls)
				{
					PAD::ENABLE_CONTROL_ACTION(0, c, true);
				}
			}
		}

		virtual void OnDisable() override
		{
			CAM::SET_CAM_ACTIVE(camEntity, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
			CAM::DESTROY_CAM(camEntity, false);
			STREAMING::CLEAR_FOCUS();

			Self::GetPed().SetFrozen(false);
			Self::GetPed().SetVisible(true);

			camEntity = 0;
		}
	};

	inline Freecam _Freecam{"freecam", "Freecam", "Detaches your camera and allows you to go anywhere!"};
}