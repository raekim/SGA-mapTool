#pragma once
#include "iGameNode.h"

#define TILE_SIZE 32
#define NUM_TILE_X 80
#define NUM_TILE_Y 45
#define NUM_TILE_U 16
#define NUM_TILE_V 12

#define TOOL_AREA_X 512	// ����â ���� & �ȷ�Ʈ�� ���� ������
#define PALETTE_TILE_SIZE (TOOL_AREA_X / NUM_TILE_U) // ����â�� �׷��� Ÿ���� ũ��
#define TOOL_AREA_Y (PALETTE_TILE_SIZE * NUM_TILE_V) // �ȷ�Ʈ�� ���� ������

#define UI_FONT_SIZE 48

enum class TEARRIN_TYPE { Walkable, Rough, Slippery, Unwalkable, Max };

struct tagTileInfo
{
	TEARRIN_TYPE	eType;
	int				nImageIndex;
};

class MapTool : public iGameNode
{
private:
	vector<Sprite*>		m_vecTerrain;		// ���� �̹���
	tagTileInfo			m_stTiles[NUM_TILE_Y][NUM_TILE_X];
	tagTileInfo			m_stSelected;

	Rect*				m_pRect;
	Sprite*				m_pSelectUI;

public:
	MapTool() {};
	~MapTool() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};