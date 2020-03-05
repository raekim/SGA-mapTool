#pragma once

template <typename T>
class Unit
{
protected:
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR3			m_vRotation;

	Animation<T>*		m_pAnimation;
	T					m_eState;

	float				m_fMoveSpeed;
	float				m_fRotSpeed;

	bool				m_isAlive;

public:
	Unit();
	~Unit();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetPosition(float x, float y) { m_vPosition.x = x; m_vPosition.y = y; }
	D3DXVECTOR2* GetPosition() { return &m_vPosition; }
	bool IsAlive() { return m_isAlive; }
};

template<typename T>
inline Unit<T>::Unit()
{
	m_pAnimation = new Animation<T>;
}

template<typename T>
inline Unit<T>::~Unit()
{
	SAFE_DELETE(m_pAnimation);
}

template<typename T>
inline void Unit<T>::Init()
{
	m_eState = T::Flying;
	m_pAnimation->Play(m_eState);
	m_pAnimation->SetScale(0.1f, 0.1f);
	m_vRotation = D3DXVECTOR3(0, 0, 0);
	
	m_fMoveSpeed = 300.0f;	// 초당 이동 속도
	m_fRotSpeed = D3DX_PI;	// 초당 회전 속도

	m_isAlive = true;
}

template<typename T>
inline void Unit<T>::Update()
{
	m_pAnimation->SetPosition(m_vPosition.x, m_vPosition.y);
	m_pAnimation->SetRotation(m_vRotation.x, m_vRotation.y, m_vRotation.z - D3DX_PI * 0.5f);
	m_pAnimation->Play(m_eState);
	m_pAnimation->Update();
}

template<typename T>
inline void Unit<T>::Render()
{
	if (m_pAnimation)
		m_pAnimation->Render();
}
