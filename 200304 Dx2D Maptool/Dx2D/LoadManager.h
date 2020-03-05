#pragma once
#include "SingletonBase.h"

#define g_pLoadManager LoadManager::GetInstance()

enum class RESOURCE_TYPE
{
	Image,
	Sound,
	End
};

struct tagResourceInfo
{
	RESOURCE_TYPE eType;
};

struct tagTextureInfo : tagResourceInfo
{
	wstring sKey;
	wstring sFile;

	tagTextureInfo(RESOURCE_TYPE type, wstring key, wstring file)
	{
		eType = type;
		sKey = key;
		sFile = file;
	}
};

struct tagSoundInfo : tagResourceInfo
{
	string sKey;
	string sFile;
	bool isBgm;
	bool isLoop;

	tagSoundInfo(RESOURCE_TYPE type, string key, string file, bool bgm, bool loop)
	{
		eType = type;
		sKey = key;
		sFile = file;
		isBgm = bgm;
		isLoop = loop;
	}
};

class LoadManager :	public SingletonBase<LoadManager>
{
private:
	vector<tagResourceInfo*>	m_vecResourceList;	// ������� ���ҽ� ���
	SCENE_KIND					m_eNextScene;		// ���� ��
	int							m_nNumLoaded;		// �ε� �Ϸ� �� ����

private:
	void ReleasePrevResources();	// ���� ������ ��� ���̴� ���ҽ� ����
	void MakeAResourcesList();		// ���� ������ ����� ����Ʈ ��� ����

public:
	void Init();						// �ε������� ����� ���ҽ� �ε�
	void Update();						// �ε� ����
	void ReleaseAll();					// ���ҽ� ����Ʈ ������ ������
	void ChangeScene(SCENE_KIND eNext);	// �� ���� ȣ�� �Լ�

	int GetNumLoaded() { return m_nNumLoaded; }
	int GetNumMax() { return m_vecResourceList.size(); }
};

