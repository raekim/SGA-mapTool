#include "stdafx.h"
#include "TitleScene.h"


void TitleScene::Init()
{
	m_pBackground = new Sprite(L"TitleBack");

	m_strTitle = "Any Key To Continue";
	m_fElapsedTime = 0.0f;
	m_isRender = true;
}

void TitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		g_pLoadManager->ChangeScene(SCENE_KIND::Play);
	else if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		g_pLoadManager->ChangeScene(SCENE_KIND::MapTool);

	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedTime >= 0.5f)
	{
		m_fElapsedTime = 0.0f;
		m_isRender = !m_isRender;
	}
}

void TitleScene::Render()
{
	if (m_pBackground)
		m_pBackground->Render();

	if (m_isRender)
		g_pTextManager->AlphabetRender(m_strTitle.c_str(), HALFSIZEX - 280, HALFSIZEY, 50);
}

void TitleScene::Release()
{
	g_pTextureManager->Release(L"TitleBack");
}
