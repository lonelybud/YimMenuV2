#include "common.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/settings/Settings.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/hooking/Hooking.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/frontend/GUI.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2";
		FileMgr::Init(documents);

		LogHelper::Init("YimMenuV2", FileMgr::GetProjectFile("./cout.log"));

		g_HotkeySystem.RegisterCommands();
		Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr.LoadModules())
			goto unload;

		if (!Pointers.Init())
			goto unload;

		if (!Renderer::Init())
			goto unload;

		Hooking::Init();

		ScriptMgr::Init();
		LOG(INFO) << "ScriptMgr initialized";

		FiberPool::Init(5);
		LOG(INFO) << "FiberPool initialized";

		GUI::Init();

		while (g_Running)
		{
			Settings::Tick();
			std::this_thread::yield();
		}

		ScriptMgr::AddScript(std::make_unique<Script>(&Commands::RunScript));

		Notifications::Show("YimMenuV2", "Loaded succesfully", NotificationType::Success);

	unload:
		LOG(INFO) << "Unloading";
		ScriptMgr::Destroy();
		FiberPool::Destroy();
		Hooking::Destroy();
		Renderer::Destroy();
		LogHelper::Destroy();

		CloseHandle(g_MainThread);
		FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
	using namespace YimMenu;

	DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}