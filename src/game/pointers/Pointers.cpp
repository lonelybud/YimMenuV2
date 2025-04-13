#include "Pointers.hpp"

#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "core/util/Joaat.hpp"
#include "types/rage/atArray.hpp"

namespace YimMenu
{
	// on some cracked game builds
	static bool IsSocialClubNeverGoingToLoad()
	{
		return Pointers.ScriptThreads && Pointers.ScriptThreads->size() != 0;
	}

	bool Pointers::Init()
	{
		const auto gta5 = ModuleMgr.Get("GTA5_Enhanced.exe"_J);
		if (!gta5)
		{
			LOG(FATAL) << "Could not find GTA5_Enhanced.exe, is this GTA 5 Enhanced?";
			return false;
		}

		auto scanner = PatternScanner(gta5);

		constexpr auto swapchainPtrn = Pattern<"72 C7 EB 02 31 C0 8B 0D">("IDXGISwapChain");
		scanner.Add(swapchainPtrn, [this](PointerCalculator ptr) {
			CommandQueue = ptr.Add(0x1A).Add(3).Rip().As<ID3D12CommandQueue**>();
			SwapChain = ptr.Add(0x21).Add(3).Rip().As<IDXGISwapChain1**>();
		});

		constexpr auto wndProcPtrn = Pattern<"3D 85 00 00 00 0F 87 2D 02 00 00">("WndProc");
		scanner.Add(wndProcPtrn, [this](PointerCalculator ptr) {
			WndProc = ptr.Sub(0x4F).As<PVOID>();
		});

		constexpr auto hWndPtrn = Pattern<"E8 ? ? ? ? 84 C0 74 25 48 8B 0D">("HWND");
		scanner.Add(hWndPtrn, [this](PointerCalculator ptr) {
			Hwnd = ptr.Add(9).Add(3).Rip().As<HWND*>();
		});

		constexpr auto screenResPtrn = Pattern<"75 39 0F 57 C0 F3 0F 2A 05">("ScreenRes");
		scanner.Add(screenResPtrn, [this](PointerCalculator ptr) {
			ScreenResX = ptr.Add(0x5).Add(4).Rip().As<std::uint32_t*>();
			ScreenResY = ptr.Add(0x1E).Add(4).Rip().As<std::uint32_t*>();
		});

		constexpr auto versionPtrn = Pattern<"4C 8D 0D ? ? ? ? 48 8D 5C 24 ? 48 89 D9 48 89 FA">("Version");
		scanner.Add(versionPtrn, [this](PointerCalculator ptr) {
			GameVersion   = ptr.Add(3).Rip().As<const char*>();
			OnlineVersion = ptr.Add(0x47).Add(3).Rip().As<const char*>();
		});

		constexpr auto scriptThreadsPtrn = Pattern<"48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97">("ScriptThreads");
		scanner.Add(scriptThreadsPtrn, [this](PointerCalculator ptr) {
			ScriptThreads = ptr.Add(3).Rip().As<rage::atArray<rage::scrThread*>*>();
		});

		constexpr auto populateNativesPtrn = Pattern<"EB 2A 0F 1F 40 00 48 8B 54 17 10">("InitNativeTables");
		scanner.Add(populateNativesPtrn, [this](PointerCalculator ptr) {
			InitNativeTables = ptr.Sub(0x2A).As<PVOID>();
		});

		constexpr auto runScriptThreadsPtrn = Pattern<"BE 40 5D C6 00">("RunScriptThreads");
		scanner.Add(runScriptThreadsPtrn, [this](PointerCalculator ptr) {
			RunScriptThreads = ptr.Sub(0xA).As<PVOID>();
		});

		constexpr auto handlesAndPtrsPtrn = Pattern<"0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE 41">("HandlesAndPtrs");
		scanner.Add(handlesAndPtrsPtrn, [this](PointerCalculator ptr) {
			HandleToPtr = ptr.Add(0x21).Add(1).Rip().As<Functions::HandleToPtr>();
			PtrToHandle = ptr.Sub(0xB).Add(1).Rip().As<Functions::PtrToHandle>();
		});

		constexpr auto pedFactoryPtrn = Pattern<"C7 40 30 03 00 00 00 48 8B 0D">("PedFactory");
		scanner.Add(pedFactoryPtrn, [this](PointerCalculator ptr) {
			PedFactory = ptr.Add(7).Add(3).Rip().As<CPedFactory**>();
		});

		constexpr auto getNetPlayerFromPidPtrn = Pattern<"83 FB 20 74 2A 89 D9">("GetNetPlayerFromPID");
		scanner.Add(getNetPlayerFromPidPtrn, [this](PointerCalculator ptr) {
			GetNetPlayerFromPid = ptr.Add(8).Rip().As<Functions::GetNetPlayerFromPid>();
		});

		constexpr auto isSessionStarted = Pattern<"0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A">("IsSessionStarted");
		scanner.Add(isSessionStarted, [this](PointerCalculator addr) {
			IsSessionStarted = addr.Add(3).Rip().As<bool*>();
		});

		constexpr auto assignPhysicalIndexPtrn = Pattern<"41 8D 47 01 3C 20 0F 87 68 01 00 00">("AssignPhysicalIndex");
		scanner.Add(assignPhysicalIndexPtrn, [this](PointerCalculator ptr) {
			AssignPhysicalIndex = ptr.Sub(0x13).As<PVOID>();
		});

		constexpr auto networkPlayerManagerShutdownPtrn = Pattern<"84 C0 0F 84 88 00 00 00 4C 89 F9 E8">("NetworkPlayerMgrShutdown");
		scanner.Add(networkPlayerManagerShutdownPtrn, [this](PointerCalculator ptr) {
			NetworkPlayerMgrShutdown = ptr.Sub(0x1B).As<PVOID>();
		});

		constexpr auto scriptGlobalsPtrn = Pattern<"48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8">("ScriptGlobals");
		scanner.Add(scriptGlobalsPtrn, [this](PointerCalculator ptr) {
			ScriptGlobals = ptr.Add(7).Add(3).Rip().As<std::int64_t**>();
		});

		constexpr auto scriptProgramsPtrn = Pattern<"48 C7 84 C8 D8 00 00 00 00 00 00 00">("ScriptPrograms");
		scanner.Add(scriptProgramsPtrn, [this](PointerCalculator ptr) {
			ScriptPrograms = ptr.Add(0x13).Add(3).Rip().Add(0xD8).As<rage::scrProgram**>();
		});

		constexpr auto networkObjectMgrPtrn = Pattern<"41 83 7E FA 02 40 0F 9C C5 C1 E5 02">("NetworkObjectMgr&GetSyncTreeForType");
		scanner.Add(networkObjectMgrPtrn, [this](PointerCalculator ptr) {
			NetworkObjectMgr = ptr.Add(0xC).Add(3).Rip().As<CNetworkObjectMgr**>();
			GetSyncTreeForType = ptr.Add(0x13).Add(1).Rip().As<Functions::GetSyncTreeForType>();
		});

		constexpr auto writeNodeDataPtrn = Pattern<"48 8B 89 A8 00 00 00 48 8B 01 48 8B 40 10 48 FF E0">("WriteNodeData");
		scanner.Add(writeNodeDataPtrn, [this](PointerCalculator ptr) {
			WriteNodeData = ptr.As<PVOID>();
		});

		constexpr auto shouldUseNodeCachePtrn = Pattern<"83 FA 20 74 1D 48 89 CE">("ShouldUseNodeCache");
		scanner.Add(shouldUseNodeCachePtrn, [this](PointerCalculator ptr) {
			ShouldUseNodeCache = ptr.Sub(5).As<PVOID>();
		});

		constexpr auto isNodeInScopePtrn = Pattern<"41 83 F9 02 74 22 48 8B 06">("IsNodeInScope");
		scanner.Add(isNodeInScopePtrn, [this](PointerCalculator ptr) {
			IsNodeInScope = ptr.Sub(0x26).As<PVOID>();
		});

		constexpr auto writeSyncTreePtrn = Pattern<"4D 89 CD 45 89 C6 41 89 D7 48 89 CF 8B 05 ? ? ? ? 65 48 8B 0C 25 58 00 00 00">("WriteSyncTree");
		scanner.Add(writeSyncTreePtrn, [this](PointerCalculator ptr) {
			WriteSyncTree = ptr.Sub(0x10).As<PVOID>();
		});

		constexpr auto networkPlayerMgrPtrn = Pattern<"75 0E 48 8B 05 ? ? ? ? 48 8B 88 F0 00 00 00">("NetworkPlayerMgr");
		scanner.Add(networkPlayerMgrPtrn, [this](PointerCalculator ptr) {
			NetworkPlayerMgr = ptr.Add(2).Add(3).Rip().As<CNetworkPlayerMgr**>();
		});

		constexpr auto queuePacketPtrn = Pattern<"45 89 F1 E8 ? ? ? ? 84 C0 74 25">("QueuePacket");
		scanner.Add(queuePacketPtrn, [this](PointerCalculator ptr) {
			QueuePacket = ptr.Add(3).Add(1).Rip().As<Functions::QueuePacket>();
		});

		constexpr auto getNetObjectByIdPtrn = Pattern<"0F B7 4E 60 E8">("GetNetObjectById");
		scanner.Add(getNetObjectByIdPtrn, [this](PointerCalculator ptr) {
			GetNetObjectById = ptr.Add(4).Add(1).Rip().As<Functions::GetNetObjectById>();
		});

		constexpr auto requestControlPtrn = Pattern<"74 0A 48 89 F9 E8 ? ? ? ? 31 F6 89 F0 48 83 C4 20">("RequestControl");
		scanner.Add(requestControlPtrn, [this](PointerCalculator ptr) {
			RequestControl = ptr.Add(5).Add(1).Rip().As<Functions::RequestControl>();
		});

		constexpr auto spectatePatchPtrn = Pattern<"74 26 66 83 FF 0D 77 20 0F B7 C7">("SpectatePatch");
		scanner.Add(spectatePatchPtrn, [this](PointerCalculator ptr) {
			SpectatePatch = BytePatches::Add(ptr.As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto modelSpawnBypassPtrn = Pattern<"E8 ? ? ? ? 48 8B 78 48">("ModelSpawnBypass");
		scanner.Add(modelSpawnBypassPtrn, [this](PointerCalculator ptr) {
			ModelSpawnBypass = BytePatches::Add(ptr.Add(1).Rip().Add(0x2B).As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto receiveNetMessagePtrn = Pattern<"48 81 C1 00 03 00 00 4C 89 E2">("ReceiveNetMessage");
		scanner.Add(receiveNetMessagePtrn, [this](PointerCalculator ptr) {
			ReceiveNetMessage = ptr.Add(0xD).Add(1).Rip().As<PVOID>();
		});

		constexpr auto netEventMgrPtrn = Pattern<"4C 8B 05 ? ? ? ? 44 0F B7 CA">("NetEventMgr");
		scanner.Add(netEventMgrPtrn, [this](PointerCalculator ptr) {
			NetEventMgr = ptr.Add(3).Rip().As<rage::netEventMgr**>();
		});

		constexpr auto sendEventAckPtrn = Pattern<"84 C0 75 ? 89 EE 49 8D AD">("SendEventAck");
		scanner.Add(sendEventAckPtrn, [this](PointerCalculator ptr) {
			EventAck = ptr.Sub(4).Rip().As<Functions::EventAck>();
			SendEventAck = ptr.Add(0x13).Add(1).Rip().As<Functions::SendEventAck>();
		});

		constexpr auto queueDependencyPtrn = Pattern<"0F 29 46 50 48 8D 05">("QueueDependency&SigScanMemory");
		scanner.Add(queueDependencyPtrn, [this](PointerCalculator ptr) {
			QueueDependency = ptr.Add(0x71).Add(1).Rip().As<PVOID>();
			SigScanMemory = ptr.Add(4).Add(3).Rip().As<PVOID>();
		});

		constexpr auto scriptVMPtrn = Pattern<"49 63 41 1C">("ScriptVM");
		scanner.Add(scriptVMPtrn, [this](PointerCalculator ptr) {
			ScriptVM = ptr.Sub(0x24).As<Functions::ScriptVM>();
		});

		constexpr auto prepareMetricForSendingPtrn = Pattern<"48 89 F9 FF 50 20 48 8D 15">("PrepareMetricForSending");
		scanner.Add(prepareMetricForSendingPtrn, [this](PointerCalculator ptr) {
			PrepareMetricForSending = ptr.Sub(0x26).As<PVOID>();
		});

		constexpr auto beDataPtrn = Pattern<"48 C7 05 ? ? ? ? 00 00 00 00 E8 ? ? ? ? 48 89 C1 E8 ? ? ? ? E8 ? ? ? ? BD 0A 00 00 00">("BEData");
		scanner.Add(beDataPtrn, [this](PointerCalculator ptr) {
			BERestartStatus = ptr.Add(3).Rip().Add(8).Add(4).As<int*>();
			NeedsBERestart  = ptr.Add(3).Rip().Add(8).Add(4).Add(8).As<bool*>();
			IsBEBanned = ptr.Add(3).Rip().Add(8).Add(4).Add(8).Add(4).As<bool*>();
		});

		constexpr auto battlEyeStatusUpdatePatchPtrn = Pattern<"80 B9 92 0A 00 00 01">("BattlEyeStatusUpdatePatch");
		scanner.Add(battlEyeStatusUpdatePatchPtrn, [this](PointerCalculator ptr) {
			BattlEyeStatusUpdatePatch = BytePatches::Add(ptr.Sub(0x26).As<std::uint8_t*>(), 0xC3);
		});

		constexpr auto getPackedStatDataPtrn = Pattern<"8D 81 37 FE FF FF">("GetPackedStatData");
		scanner.Add(getPackedStatDataPtrn, [this](PointerCalculator ptr) {
			GetPackedStatData = ptr.Sub(0xE).As<Functions::GetPackedStatData>();
		});

		constexpr auto pedPoolPtrn = Pattern<"80 79 4B 00 0F 84 F5 00 00 00 48 89 F1">("PedPool");
		scanner.Add(pedPoolPtrn, [this](PointerCalculator ptr) {
			PedPool = ptr.Add(0x18).Add(3).Rip().As<PoolEncryption*>();
		});

		constexpr auto vehiclePoolPtrn = Pattern<"48 83 78 18 0D">("VehiclePool");
		scanner.Add(vehiclePoolPtrn, [this](PointerCalculator ptr) {
			VehiclePool = ptr.Sub(0xA).Add(3).Rip().As<rage::fwVehiclePool***>();
		});

		constexpr auto objectPoolPtrn = Pattern<"48 8B 04 0A C3 0F B6 05">("ObjectPool");
		scanner.Add(objectPoolPtrn, [this](PointerCalculator ptr) {
			ObjectPool = ptr.Add(5).Add(3).Rip().As<PoolEncryption*>();
		});

		constexpr auto httpStartRequestPtrn = Pattern<"56 57 48 83 EC 28 48 89 CE 8B 81 ? ? ? ? FF C8 83 F8 04 0F 87">("HttpStartRequest");
		scanner.Add(httpStartRequestPtrn, [this](PointerCalculator ptr) {
			HttpStartRequest = ptr.As<PVOID>();
		});

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";
			return false;
		}

		return true;
	}

	bool Pointers::LateInit()
	{
		auto sc = ModuleMgr.Get("socialclub.dll"_J);
		while (!sc)
		{
			LOG(WARNING) << "Waiting for socialclub.dll";
			std::this_thread::sleep_for(1s);

			if (IsSocialClubNeverGoingToLoad())
			{
				return false;
			}

			ModuleMgr.LoadModules();
			sc = ModuleMgr.Get("socialclub.dll"_J);
		}

		auto scanner = PatternScanner(sc);

		constexpr auto numHandlesPatchPtrn = Pattern<"83 FD 20 0F 87 54 02 00 00">("NumHandlesPatch");
		scanner.Add(numHandlesPatchPtrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.Add(2).As<std::uint8_t*>(), 100)->Apply(); // change handle limit to 100
		});

		constexpr auto readAttributePatchPtrn = Pattern<"75 70 EB 23">("ReadAttributesPatch");
		scanner.Add(readAttributePatchPtrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.As<void*>(), std::vector<std::uint8_t>{0x90, 0x90})->Apply();
		});

		constexpr auto readAttributePatch2Ptrn = Pattern<"32 C0 EB ? C7 83">("ReadAttributesPatch2");
		scanner.Add(readAttributePatch2Ptrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.As<void*>(), std::vector<std::uint8_t>{0xB0, 0x01})->Apply(); 
		});

		if (!scanner.Scan())
		{
			LOG(WARNING) << "Some socialclub patterns could not be found";
			return false;
		}

		return true;
	}
}