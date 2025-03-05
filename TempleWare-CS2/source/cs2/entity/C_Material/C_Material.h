#pragma once
#include <cstdint>
#include "../../../templeware/utils/memory/memorycommon.h"
#include "../../../templeware/utils/math/vector/vector.h"
#include "../../../templeware/utils/schema/schema.h"
#include "../C_CSWeaponBase/C_CSWeaponBase.h"
#include <cstdint>

class CMaterial2
{
public:
	virtual const char* GetName() = 0;
	virtual const char* GetShareName() = 0;
};

struct MaterialKeyVar_t
{
	std::uint64_t uKey;
	const char* szName;

	MaterialKeyVar_t(std::uint64_t uKey, const char* szName) :
		uKey(uKey), szName(szName) { }

	MaterialKeyVar_t(const char* szName, bool bShouldFindKey = false) :
		szName(szName)
	{
		uKey = bShouldFindKey ? FindKey(szName) : 0x0;
	}

	std::uint64_t FindKey(const char* szName)
	{
		using fn = std::uint64_t(__fastcall*)(const char*, unsigned int, int);
		static auto find = reinterpret_cast<fn>(M::patternScan("particles", ("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 33 C0 8B DA")));
		return find(szName, 0x12, 0x31415926);
	}
};

class CObjectInfo
{
	MEM_PAD(0xB0);
	int nId;
};

class CSceneAnimatableObject {
public:
	CBaseHandle Owner() const {
		if (!this)
			return CBaseHandle();

		return *(CBaseHandle*)((std::uintptr_t)this + 0xB8);
	}
};  

struct Color {
	std::uint8_t r = 0U, g = 0U, b = 0U, a = 0U;
};

class CMeshData
{
public:

private:
	MEM_PAD(0x18); // 0x0
public:
	CSceneAnimatableObject* pSceneAnimatableObject; // 0x18
	CMaterial2* pMaterial; // 0x20
	CMaterial2* pMaterialCopy; // 0x20
private:
	MEM_PAD(0x10); // 0x28
public:
	CObjectInfo* pObjectInfo;
private:
	MEM_PAD(0x8);
public:
	Color color;
};

