#include "stdafx.h"
#include "Map.h"
#include "Player.h"


Map::Map()
{
	m_pBackground = new Sprite(L"Background");
	m_pBackground->SetSize(1, 1);
	m_pBackground->SetLBPosition(0, 0);
	m_pBackground->Update();

	g_pCamera->SetMapSize(m_pBackground->GetWidth(), m_pBackground->GetHeight());
}


Map::~Map()
{
	SAFE_DELETE(m_pBackground);
}

void Map::Render()
{
	m_pBackground->Render();
}