#include "stdafx.h"
#include "PlayScene.h"


void PlayScene::Init()
{
	// 클래스 생성
	m_pMap = new Map;
	m_pPlayer = new Player;
	m_pPlayer->Init();
	m_pPlayer->SetEnemyVector(&m_vecEnemy);

	m_pPlayer->SetPosition(m_pMap->GetWidth() * 0.5f, m_pMap->GetHeight() * 0.5f);
	g_pCamera->SetTarget(m_pPlayer->GetPosition());

	m_fResponeTime = 1.0f;
	m_fElapsedTime = 0.0f;
}

void PlayScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);

	if (m_pPlayer)
		m_pPlayer->Update();

	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedTime > m_fResponeTime)
	{
		Enemy* p = new Enemy;
		p->SetPlayer(m_pPlayer);
		p->Init();
		m_vecEnemy.push_back(p);
		m_fElapsedTime = 0.0f;
	}

	m_iterEnemy = m_vecEnemy.begin();
	while (m_iterEnemy != m_vecEnemy.end())
	{
		if ((*m_iterEnemy)->IsAlive())
		{
			(*m_iterEnemy)->Update();
			m_iterEnemy++;
		}
		else
			m_iterEnemy = m_vecEnemy.erase(m_iterEnemy);
	}

	g_pCamera->Update();
}

void PlayScene::Render()
{
	if (m_pMap)
		m_pMap->Render();

	if (m_pPlayer)
		m_pPlayer->Render();

	for (int i = 0; i < m_vecEnemy.size(); i++)
	{
		m_vecEnemy[i]->Render();
	}
}

void PlayScene::Release()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);

	for (int i = 0; i < m_vecEnemy.size(); i++)
		SAFE_DELETE(m_vecEnemy[i]);
	m_vecEnemy.clear();
}
