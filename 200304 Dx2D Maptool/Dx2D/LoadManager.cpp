#include "stdafx.h"
#include "LoadManager.h"


void LoadManager::Init()
{
	g_pTextureManager->AddTexture(L"ProgressBack", L"progressBarBack.png");
	g_pTextureManager->AddTexture(L"ProgressFront", L"progressBarFront.png");
}

void LoadManager::Update()
{
	if (m_vecResourceList.size() == m_nNumLoaded) // �ε� �Ϸ�
	{
		g_pSceneManager->Change(m_eNextScene);
		return;
	}

	switch (m_vecResourceList[m_nNumLoaded]->eType)
	{
		case RESOURCE_TYPE::Image:
		{
			tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[m_nNumLoaded];
			g_pTextureManager->AddTexture(info->sKey, info->sFile);
		}
		break;
		case RESOURCE_TYPE::Sound:
		{
			tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[m_nNumLoaded];
			g_pSoundManager->AddSound(info->sKey, info->sFile, info->isBgm, info->isLoop);
		}
		break;
	}

	m_nNumLoaded++;
}

void LoadManager::ReleaseAll()
{
	ReleasePrevResources();
}

void LoadManager::ChangeScene(SCENE_KIND eNext)
{
	g_pSceneManager->Change(SCENE_KIND::Loading);

	m_eNextScene = eNext;
	ReleasePrevResources();
	MakeAResourcesList();
}

void LoadManager::ReleasePrevResources()
{
	for (int i = 0; i < m_vecResourceList.size(); i++)
	{
		switch (m_vecResourceList[i]->eType)
		{
			case RESOURCE_TYPE::Image:
			{
				tagTextureInfo* info = (tagTextureInfo*)m_vecResourceList[i];
				g_pTextureManager->Release(info->sKey);
				SAFE_DELETE(info);
			}
			break;
			case RESOURCE_TYPE::Sound:
			{
				tagSoundInfo* info = (tagSoundInfo*)m_vecResourceList[i];
				g_pSoundManager->ReleaseSound(info->sKey);
				SAFE_DELETE(info);
			}
			break;
		}
	}
	m_vecResourceList.clear();
}

void LoadManager::MakeAResourcesList()
{
	m_nNumLoaded = 0;

	switch (m_eNextScene)
	{
	case SCENE_KIND::Title:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TitleBack", L"ChloeBennet.bmp"));
		break;
	case SCENE_KIND::Play:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Background", L"BackGround.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Player", L"Shooting/����2_�Ʊ���ü.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"Missile", L"Shooting/����_spreadź.png"));
		break;
	case SCENE_KIND::MapTool:
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"TileSet1", L"Tilesets/Dungeon_A2.png"));
		m_vecResourceList.push_back(new tagTextureInfo(RESOURCE_TYPE::Image, L"SelectUI", L"System/Window.png"));
		break;
	}
}