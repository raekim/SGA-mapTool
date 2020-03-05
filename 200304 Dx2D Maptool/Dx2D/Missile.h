#pragma once
class Missile
{
private:
	Sprite*			m_pSprite;
	D3DXVECTOR2		m_vPosition;
	D3DXVECTOR3		m_vRotation;

	float			m_fMoveSpeed;
	float			m_fRotSpeed;

	D3DXVECTOR2*	m_vTarget;
	bool			m_isAlive;

public:
	Missile();
	~Missile();

	void Init(D3DXVECTOR2 pos, D3DXVECTOR3 rot, D3DXVECTOR2* target = NULL);
	void Update();
	void Render();

	bool IsAlive() { return m_isAlive; }
};

