#pragma once
#include "interfaces.hpp"
#include <vector>

enum class MOD
{
	XRMPE,
	OMP,
	SoProject,
	StalkerNET
};

enum TargetType
{
	Alive = 29,
	Static = 13
};

struct CActorMPNET : CActorMP
{
	CActorMPNET()
	{
		Base = 0x6ECC04;
		Name = 0x30C;
		Money = 0x2EC;

		Condition.Base = 0x9D8;
		Condition.HP = 0x4;
		Condition.Stamina = 0x114;

		Inventory.Base = 0;
		Inventory.ActorInventory.Base = 0x2E4;
		Inventory.ActorInventory.Weight = 0x5C;

		//!using something in the weapon class doesn't need past Actor BASE
		//!just paste the weapon base.
		Weapon.Base = 0x6F0C74;
		Weapon.CurrentWeapon = 0x14;
	}
};

struct CHUDManagerNET : CHUDManager
{
	CHUDManagerNET()
	{
		Base = 0x992D4;

		Crosshair.Base = 0x4C;
		Crosshair.DelayInfo = 0x4;
		Crosshair.Target.Base = 0x8;
		Crosshair.Target.Type = 0x14;

		set_module("xrEngine.exe");
	}
};

class Offsets
{
private:
	using pair_offsets_vector_baseoffset = std::pair<std::vector<DWORD>, IOffsetBase*>;

	class CActor
	{
	private:
		struct CCrosshair
		{
			pair_offsets_vector_baseoffset DelayInfo, TargetIsAlive, TargetType, TargetExists;
		};

		struct CWeapon
		{
			pair_offsets_vector_baseoffset IsInHands;
		};

	public:

		CWeapon Weapon;
		CCrosshair Crosshair;
		pair_offsets_vector_baseoffset HP, Stamina, Money, Weight, Name;
	};

public:

	Offsets(MOD _Platform)
	{
		switch (_Platform)
		{
		case MOD::StalkerNET:
			_Actor = &_ActorNET;
			_HudManager = &_HudManagerNET;
			break;

		case MOD::OMP:
			break;

		case MOD::SoProject:
			break;
		}

		_initOffsets();
	}

	CActor Actor;
private:

	void _initOffsets() noexcept
	{
		Actor.Stamina = { { _Actor->Base, _Actor->Condition.Base, _Actor->Condition.Stamina }, _Actor };
		Actor.HP = { { _Actor->Base, _Actor->Condition.Base, _Actor->Condition.HP }, _Actor };
		Actor.Name = { {_Actor->Base, _Actor->Name}, _Actor };
		Actor.Money = { {_Actor->Base, _Actor->Money}, _Actor };

		Actor.Weight = { {_Actor->Base, _Actor->Inventory.Base,
			_Actor->Inventory.ActorInventory.Base, _Actor->Inventory.ActorInventory.Weight}, _Actor };

		Actor.Crosshair.TargetExists = { {_HudManager->Base, _HudManager->Crosshair.Base,
			_HudManager->Crosshair.Target.Base, _HudManager->Crosshair.Target.Base}, _HudManager };

		Actor.Crosshair.TargetType = { {_HudManager->Base, _HudManager->Crosshair.Base,
			_HudManager->Crosshair.Target.Base, _HudManager->Crosshair.Target.Type}, _HudManager };

		Actor.Crosshair.DelayInfo = { {_HudManager->Base, _HudManager->Crosshair.Base, 
			_HudManager->Crosshair.DelayInfo},_HudManager };

		Actor.Weapon.IsInHands = { {_Actor->Weapon.Base, _Actor->Weapon.CurrentWeapon}, _Actor };
	}

	CActorMP* _Actor;
	CActorMPNET _ActorNET;

	CHUDManager* _HudManager;
	CHUDManagerNET _HudManagerNET;
};


/*/////////////////////soProject/////////////////////////
* #define oStamina 0x54
  #define oMoney 0x2EC
//"xrGame.dll" + 000E7584 + 98 + 4 + 40 + 100 + 124 + 1C + 4
//// ������ ������� � ����� �� �������� ������
//58 + 14 + 40 + 100 + 124 + 1C + 4
//58 + 4 + 30 + 100 + 124 + 1C + 4
//
/*
#define oX 0x18
#define oY 0x1C
#define oZ 0x20
//

//"xrCDB.dll" + 0001A5DC + 100 + 18C + 1F4 + C + 20 + 1C + 4
//"xrCDB.dll" + 0001A5E0 + 20 + 18C + 1F4 + C + 20 + 1C + 4
//oActor + 0x108 money
//"xrCDB.dll" + 0001A5E0 + 20 + 40 + 8 + E4 + 1C + 4
//"xrGame.dll" + 0064E2C0 + 2EC //money
// X bytes F3 0F 11 46 D4
// Y bytes F3 0F 11 46 D8
// Z bytes F3 0F 11 46 DC
#define oX 0x18
#define oY 0x20
#define oZ 0x1C
#define oResX 0x912F8
#define oResY 0x912FC

//Crosshair
#define oCrosshair 0x00092D3C
#define oCrossExist 0x8
#define oCrossLong 0xC
#define oCrossSkelet 0x10
#define oCrossShowInfoDelay 0x4

/////////////////////////
#define oPlayerState 0x38
#define Friendly 2147548928
#define Neutral 2164260736
#define Enemy 2164195328
#define CrosshairTargetEmpty 2164260863

//CrossSkelet
#define lEye 16
#define rEye 17
#define Head 15
#define Neck 13
#define NeckStom 14
#define Stomach 33 | 12 | 2 | 11 | 20
#define RHand 21 | 27 | 22
#define LHand 36 | 35 | 36
#define RLeg 10 | 9 | 8 | 7
#define LLeg 3 | 4 | 5 | 6
*/