#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <windows.h>
#include "types/script/scrNativeHandler.hpp"
#include "core/memory/BytePatches.hpp"

namespace rage
{
	template<typename T>
	class atArray;
	class scrThread;
	class scrProgram;
	class netSyncTree;
	class netObject;
	class netConnectionManager;
	class netArrayMgr;
	class netEventMgr;
	class netCatalog;
	class netCatalogBaseItem;
	class fwBasePool;
	class fwVehiclePool;
	class rlSessionInfo;
	class rlGamerHandle;
	class rlTaskStatus;
	class rlScTaskStatus;
	class rlSessionByGamerTaskResult;
	class rlQueryPresenceAttributesContext;
	class rlScGamerHandle;
	class rlQueryAccountsResult;
	class rlGetAvatarsContext;
	class rlGetAvatarsPlayerList;
}
class CPedFactory;
class CNetGamePlayer;
class CEntity;
class CNetworkObjectMgr;
class CNetworkPlayerMgr;
class PoolEncryption;
class CStatsMgr;
class CNetShopTransaction;
class CNetworkSession;

namespace YimMenu
{
	namespace Functions
	{
		using HandleToPtr = void* (*)(int handle);
		using PtrToHandle = int (*)(void* pointer);
		using GetNetPlayerFromPid = CNetGamePlayer* (*)(int id);
		using GetSyncTreeForType = rage::netSyncTree* (*)(void* netObjMgr, uint16_t type);
		using QueuePacket = void(*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, std::uint16_t* out_seq_id);
		using GetNetObjectById = rage::netObject* (*)(uint16_t id);
		using RequestControl = void(*)(rage::netObject* object);
		using EventAck = bool(*)(uintptr_t data, CNetGamePlayer* target_player, uint32_t event_index, uint32_t event_handled_bitset);
		using SendEventAck = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player);
		using ScriptVM = int (*)(uint64_t* stack, int64_t** scr_globals, rage::scrProgram* program, void* ctx);
		using GetPackedStatData = void(*)(int index, int* row, bool* is_bool, bool* unk);
	}

	struct PointerData
	{
		IDXGISwapChain1** SwapChain;
		ID3D12CommandQueue** CommandQueue;
		HWND* Hwnd;
		PVOID WndProc;
		std::uint32_t* ScreenResX;
		std::uint32_t* ScreenResY;
		const char* GameVersion;
		const char* OnlineVersion;
		rage::atArray<rage::scrThread*>* ScriptThreads;
		PVOID InitNativeTables;
		std::int64_t** ScriptGlobals;
		PVOID RunScriptThreads;
		Functions::HandleToPtr HandleToPtr;
		Functions::PtrToHandle PtrToHandle;
		CPedFactory** PedFactory;
		Functions::GetNetPlayerFromPid GetNetPlayerFromPid;
		bool* IsSessionStarted;
		PVOID AssignPhysicalIndex;
		PVOID NetworkPlayerMgrShutdown;
		rage::scrProgram** ScriptPrograms;
		Functions::GetSyncTreeForType GetSyncTreeForType;
		CNetworkObjectMgr** NetworkObjectMgr;
		PVOID WriteNodeData;
		PVOID ShouldUseNodeCache;
		PVOID IsNodeInScope;
		PVOID WriteSyncTree;
		CNetworkPlayerMgr** NetworkPlayerMgr;
		Functions::QueuePacket QueuePacket;
		Functions::GetNetObjectById GetNetObjectById;	
		Functions::RequestControl RequestControl;
		BytePatch ModelSpawnBypass;
		BytePatch SpectatePatch; // used to patch the code that prevents you from spawning network objects when spectating
		PVOID ReceiveNetMessage;
		rage::netEventMgr** NetEventMgr;
		Functions::EventAck EventAck;
		Functions::SendEventAck SendEventAck;
		PVOID QueueDependency;
		PVOID SigScanMemory;
		Functions::ScriptVM ScriptVM;
		PVOID PrepareMetricForSending;
		int* BERestartStatus;
		bool* NeedsBERestart;
		bool* IsBEBanned;
		BytePatch BattlEyeStatusUpdatePatch;
		Functions::GetPackedStatData GetPackedStatData;
		PoolEncryption* PedPool;
		PoolEncryption* ObjectPool;
		rage::fwVehiclePool*** VehiclePool;
		PVOID HttpStartRequest;
	};

	struct Pointers : PointerData
	{
		bool Init();
		bool LateInit();
	};

	inline YimMenu::Pointers Pointers;
}