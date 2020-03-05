#pragma once
#include "Unit.h"

class Missile;
class Enemy;

enum class PLAYER_STATE
{
	READY = -1,
	Flying,
	MAX
};

class Player : public Unit<PLAYER_STATE>
{
private:
	vector<Missile*>	m_vecMissile;
	float				m_fShootSpeed1;
	float				m_fElapsedTime1;

	float				m_fShootSpeed2;
	float				m_fElapsedTime2;

	vector<Enemy*>*		m_vecEnemy;

private:
	void Keyboard();
	void UpdateRotation();

public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Render() override;

	void SetEnemyVector(vector<Enemy*>* p) { m_vecEnemy = p; }
};

