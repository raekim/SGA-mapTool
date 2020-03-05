#pragma once
#include "iGameNode.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"


class PlayScene : public iGameNode
{
private:
	Map*				m_pMap;
	Player*				m_pPlayer;
	D3DXVECTOR2*		m_vTarget;

	vector<Enemy*>				m_vecEnemy;
	vector<Enemy*>::iterator	m_iterEnemy;
	float						m_fResponeTime;
	float						m_fElapsedTime;

public:
	PlayScene() {};
	~PlayScene() {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

