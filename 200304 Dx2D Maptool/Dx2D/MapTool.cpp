#include "stdafx.h"
#include "MapTool.h"


void MapTool::Init()
{
	//for (int i = 0; i < NUM_TILE_V; i++)
	for (int i = NUM_TILE_V - 1; i >= 0; i--)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			Sprite* pSprite = new Sprite(L"TileSet1", NUM_TILE_U, NUM_TILE_V, i * NUM_TILE_U + j);
			m_vecTerrain.push_back(pSprite);
		}
	}

	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			m_stTiles[i][j].eType = TEARRIN_TYPE::Walkable;
			m_stTiles[i][j].nImageIndex = 0;
		}
	}

	m_stSelected.eType = TEARRIN_TYPE::Walkable;
	m_stSelected.nImageIndex = 0;

	m_pRect = new Rect;
	m_pRect->SetBorder(true);
	m_pRect->SetDraw(false);

	m_pSelectUI = new Sprite(L"SelectUI", 8, 8, 39);
	m_pSelectUI->SetConstantScale(UI_FONT_SIZE, UI_FONT_SIZE);

	// 이전에 저장한 맵 파일 불러오기
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		auto mapIdx = g_pFileManager->LoadStringData(L"MapInfo", L"맵 정보", to_wstring(i) + L"Y" + L"Idx");
		auto mapType = g_pFileManager->LoadStringData(L"MapInfo", L"맵 정보", to_wstring(i) + L"Y" + L"Type");
		int idxIdx = 0, typeIdx = 0;
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			int n = 0;			
			while (idxIdx < mapIdx.size() && mapIdx[idxIdx++] != ' ')
			{
				n *= 10;
				n += mapIdx[idxIdx - 1] - '0';
			}
			m_stTiles[i][j].nImageIndex = n;

			n = 0;
			while (typeIdx < mapType.size() && mapType[typeIdx++] != ' ')
			{
				n *= 10;
				n += mapType[typeIdx - 1] - '0';
			}
			m_stTiles[i][j].eType = (TEARRIN_TYPE)n;
		}
	}
}

void MapTool::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		// 현재 드로우 영역의 맵 파일에 저장하기
		for (int i = 0; i < NUM_TILE_Y; i++)
		{
			string mapIdx;
			string mapType;
			for (int j = 0; j < NUM_TILE_X; j++)
			{
				mapIdx += to_string(m_stTiles[i][j].nImageIndex) + " ";
				mapType += to_string((int)m_stTiles[i][j].eType) + " ";
			}
			g_pFileManager->AddSaveString(L"맵 정보", to_wstring(i) + L"Y" + L"Idx", mapIdx);
			g_pFileManager->AddSaveString(L"맵 정보", to_wstring(i) + L"Y" + L"Type", mapType);
		}
		g_pFileManager->IniSave(L"MapInfo");

		// 타이틀 화면으로 나가기
		g_pLoadManager->ChangeScene(SCENE_KIND::Title);
	}

	// 팔레트 영역
	if (g_ptMouse.x > 0 && g_ptMouse.x < TOOL_AREA_X)
	{
		if (g_ptMouse.y < TOOL_AREA_Y)
		{
			int x = g_ptMouse.x / PALETTE_TILE_SIZE;
			int y = g_ptMouse.y / PALETTE_TILE_SIZE;

			if (m_pRect)
			{
				m_pRect->SetSize(PALETTE_TILE_SIZE, PALETTE_TILE_SIZE);
				m_pRect->SetLBPosition(x * PALETTE_TILE_SIZE, y * PALETTE_TILE_SIZE);
				m_pRect->Update();
			}

			if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
			{
				m_stSelected.nImageIndex = y * NUM_TILE_U + x;
			}
		}
		else
		{
			int x = g_ptMouse.x / UI_FONT_SIZE;
			int y = g_ptMouse.y / UI_FONT_SIZE;

			if (m_pRect)
			{
				m_pRect->SetSize(UI_FONT_SIZE, UI_FONT_SIZE);
				m_pRect->SetLBPosition(x * UI_FONT_SIZE, y * UI_FONT_SIZE + 10);
				m_pRect->Update();
			}

			if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
			{
				if (x == 1)
				{
					int typeIndex = ((int)m_stSelected.eType - 1) % (int)TEARRIN_TYPE::Max;
					if (typeIndex < 0)
						typeIndex = (int)TEARRIN_TYPE::Max - 1;
					m_stSelected.eType = (TEARRIN_TYPE)typeIndex;
				}
				else if (x == TOOL_AREA_X / UI_FONT_SIZE - 1)
				{
					int typeIndex = ((int)m_stSelected.eType + 1) % (int)TEARRIN_TYPE::Max;
					m_stSelected.eType = (TEARRIN_TYPE)typeIndex;
				}
			}
		}
	}
	else // 작업 영역
	{
		int x = (g_ptMouse.x - TOOL_AREA_X) / TILE_SIZE;
		int y = g_ptMouse.y / TILE_SIZE;

		if (m_pRect)
		{
			m_pRect->SetSize(TILE_SIZE, TILE_SIZE);
			m_pRect->SetLBPosition(x * TILE_SIZE + TOOL_AREA_X, y * TILE_SIZE);
			m_pRect->Update();
		}

		if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		{
			m_stTiles[y][x].nImageIndex = m_stSelected.nImageIndex;
		}
	}
}

void MapTool::Render()
{
	// 에디터 영역
	for (int i = 0; i < NUM_TILE_V; i++)
	{
		for (int j = 0; j < NUM_TILE_U; j++)
		{
			m_vecTerrain[i * NUM_TILE_U + j]->SetConstantScale(PALETTE_TILE_SIZE, PALETTE_TILE_SIZE);
			m_vecTerrain[i * NUM_TILE_U + j]->SetLBPosition(j * PALETTE_TILE_SIZE, i * PALETTE_TILE_SIZE);
			m_vecTerrain[i * NUM_TILE_U + j]->UpdateNRender();
		}
	}

	m_pSelectUI->SetRotation(0, 0, -D3DX_PI * 0.5f);
	m_pSelectUI->SetLBPosition(UI_FONT_SIZE, TOOL_AREA_Y + 10);
	m_pSelectUI->UpdateNRender();

	m_pSelectUI->SetRotation(0, 0, D3DX_PI * 0.5f);
	m_pSelectUI->SetLBPosition(TOOL_AREA_X - UI_FONT_SIZE * 1.75f, TOOL_AREA_Y + 10);
	m_pSelectUI->UpdateNRender();

	switch (m_stSelected.eType)
	{
	case TEARRIN_TYPE::Walkable:
		g_pTextManager->AlphabetRender("Walkable", UI_FONT_SIZE * 2, TOOL_AREA_Y + 10, UI_FONT_SIZE);
		break;
	case TEARRIN_TYPE::Rough:
		g_pTextManager->AlphabetRender("Rough", UI_FONT_SIZE * 2, TOOL_AREA_Y + 10, UI_FONT_SIZE);
		break;
	case TEARRIN_TYPE::Slippery:
		g_pTextManager->AlphabetRender("Slippery", UI_FONT_SIZE * 2, TOOL_AREA_Y + 10, UI_FONT_SIZE);
		break;
	case TEARRIN_TYPE::Unwalkable:
		g_pTextManager->AlphabetRender("Unwalkable", UI_FONT_SIZE * 2, TOOL_AREA_Y + 10, UI_FONT_SIZE);
		break;
	};

	// 드로잉 영역
	for (int i = 0; i < NUM_TILE_Y; i++)
	{
		for (int j = 0; j < NUM_TILE_X; j++)
		{
			int tileIndex = m_stTiles[i][j].nImageIndex;

			m_vecTerrain[tileIndex]->SetConstantScale(TILE_SIZE, TILE_SIZE);
			m_vecTerrain[tileIndex]->SetLBPosition(j * TILE_SIZE + TOOL_AREA_X, i * TILE_SIZE);
			m_vecTerrain[tileIndex]->UpdateNRender();
		}
	}

	if (m_pRect)
		m_pRect->Render();
}

void MapTool::Release()
{
	SAFE_DELETE(m_pSelectUI);
	SAFE_DELETE(m_pRect);

	for (int i = 0; i < m_vecTerrain.size(); i++)
		SAFE_DELETE(m_vecTerrain[i]);
	m_vecTerrain.clear();
}
