#pragma once
using DWORD = unsigned long;

struct IOffsetBase
{
	IOffsetBase() : _Module{}
	{}

	inline const char* get_module() const noexcept { return _Module; }
	inline void set_module(const char* module) noexcept { _Module = module; }

private:
	const char* _Module;
};

struct CActorMP : IOffsetBase
{
	CActorMP() : Base{}, Name{}, Money{} {}
	DWORD Base, Name, Money;

	struct CActorCondition
	{
		CActorCondition() : Base{}, HP{}, Stamina{} {}

		DWORD Base, HP, Stamina;
	};

	struct CActorCameraManager
	{
		CActorCameraManager() : Base{}, Fov{} {};

		DWORD Base, Fov, MatrixStart = 0xC8;
	};

	struct CInventory
	{
		CInventory() : Base{}, ActorInventory{} {}

		struct CActorInventory
		{
			CActorInventory() : Base{}, Weight{} {}

			DWORD Base, Weight;
		};

		DWORD Base;
		CActorInventory ActorInventory;
	};

	struct CWeapon
	{
		CWeapon() : Base{}, CurrentWeapon{}
		{}
		DWORD Base, CurrentWeapon;
	};

	struct CPosition : CActorCameraManager
	{
		DWORD x, y, z;
	};

	CPosition Position;
	CInventory Inventory;
	CActorCondition Condition;
	CWeapon Weapon;
	CActorCameraManager CameraManager;
};

struct CHUDManager : public IOffsetBase
{
	CHUDManager() : Base{}, Crosshair{}
	{}

	struct Crosshair
	{
		Crosshair() : Base{}, DelayInfo{}, Target{}
		{}

		struct Target
		{
			Target() : Base{}, Type{}
			{}

			DWORD Base, Type;
		};

		DWORD Base, DelayInfo;
		Target Target;
	};

	DWORD Base;
	Crosshair Crosshair;
};