#include "ParticleInfo.h"
#include "Material.h"
#include "ResourceManager.h"


ParticleInfo::ParticleInfo()
{
}


ParticleInfo::~ParticleInfo()
{
}

void ParticleInfo::Initialize(wstring _fp)
{
	HANDLE handle = CreateFile(_fp.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == handle)
	{
		ERR_MSG((L"Can't Load " + _fp + L" : Particle Data ").c_str());
		assert(0);
		return;
	}

	DWORD byte;
	ReadFile(handle, &m_info, sizeof(ParticleData), &byte, nullptr);

	DWORD burstCount;
	ReadFile(handle, &burstCount, sizeof(DWORD), &byte, nullptr);

	for (DWORD i = 0; i < burstCount; ++i)
	{
		ParticleData::Burst burst;
		ReadFile(handle, &burst, sizeof(ParticleData::Burst), &byte, nullptr);
		m_bursts.emplace_back(burst);
	}

	DWORD mtrlNameLength;
	ReadFile(handle, &mtrlNameLength, sizeof(DWORD), &byte, nullptr);
	TCHAR* nameBuffer = new TCHAR[mtrlNameLength + 1];
	for (DWORD i = 0; i < mtrlNameLength; ++i)
		ReadFile(handle, &nameBuffer[i], sizeof(wchar_t), &byte, nullptr);
	nameBuffer[mtrlNameLength] = '\0';

	m_material = ResourceManager::GetInstance()->GetResource<Material>(nameBuffer);

	SAFE_DELETE(nameBuffer);


	CloseHandle(handle);
}

void ParticleInfo::Release()
{
}


