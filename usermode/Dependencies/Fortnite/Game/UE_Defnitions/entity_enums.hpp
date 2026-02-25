#include "../../../Kernel/driver.hpp"
#include "../../../../Includes/Definitions/hex_definitions.hpp"

struct WeaponInformation
{
	int32_t ammo_count;
	int32_t max_ammo;

	BYTE tier;
	std::string weapon_name;
	std::string buildplan;

};
std::string LocalPlayerWeapon;


WeaponInformation WeaponInfo;

enum EBoneIndex : int {
	Head = 110,
	Neck = 67,
	Chest = 66,
	Pelvis = 2,
	LShoulder = 9,
	LElbow = 10,
	LHand = 11,
	RShoulder = 38,
	RElbow = 39,
	RHand = 40,
	LHip = 71,
	LKnee = 72,
	LFoot = 73,
	RHip = 78,
	RKnee = 79,
	RFoot = 82,
	root = 0
};

enum bones : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot = 86,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRPalm = 58,
	HumanNeck = 67,
	HumanHead = 110,
	HumanChest = 66
};

//offsets ud by KeplerOnTop


enum offset {
	LocationUnderReticle = 0x2A30,
	aactor = 0x48,
	root_component = 0x1B0,
	relative_location = 0x140,
	PrimaryPickupItemEntry = 0x3A8,
	last_sumbit = 0x2E0,
	last_render = 0x328,
	levels = 0x1F0,
	LocalPawn = 0x358,
	bone_array = 0x5F0,
	pname = 0xA08,
	SpawnSourceOverride = 0xBE8,
	WorldTimeSeconds = 0x198,
};
enum weaponoffsets {

	AmmoCount = 0x10A4,

	CurrentWeapon = 0x990,
	WeaponData = 0x5B8,
	Tier = 0xAA,
	ItemName = 0xB0,
};

template< typename t >
class TArray
{
public:

	TArray() : tData(), iCount(), iMaxCount() { }
	TArray(t* data, int count, int max_count) :
		tData(tData), iCount(iCount), iMaxCount(iMaxCount) { }

public:
	t* tData;
	int iCount;
	int iMaxCount;
	uintptr_t Array = 0;
	uint32_t Count = 0;
	uint32_t MaxCount = 0;

	auto Get(int idx) -> t
	{
		return device_().read< t >(reinterpret_cast<__int64>(this->tData) + (idx * sizeof(t)));
	}

	auto Size() -> std::uint32_t
	{
		return this->iCount;
	}

	bool isValid() const {
		return Array && Count <= MaxCount && MaxCount <= 1000000;
	}

	bool IsValid()
	{
		return this->iCount != 0;
	}
};


uintptr_t TargetedFortPawn( ) {

	auto& cache = GameCache::Cache::getInstance( );

	readaddy( uintptr_t, cache.get_pcontroller( ).value_or( 0 ), 0x1830);
}
