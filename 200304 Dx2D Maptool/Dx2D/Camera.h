#pragma once
#include "SingletonBase.h"

#define g_pCamera Camera::GetInstance()

class Camera : public SingletonBase<Camera>
{
#define MOVESPEED 500

private:
	ID3D11Buffer*		m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	ViewProjectionDesc	m_stViewProjMatrix;

	D3DXVECTOR2*		m_pTarget;

	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vFocus;
	D3DXVECTOR2			m_vMapSize;

	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vUp;

public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void SetTarget(D3DXVECTOR2* p) { m_pTarget = p; }
	void SetFocus(D3DXVECTOR2 v) { m_vFocus = v; }
	void SetFocus(float x, float y) { SetFocus(D3DXVECTOR2(x, y)); }
	void SetMapSize(float x, float y) { m_vMapSize.x = x; m_vMapSize.y = y; }

	ID3D11Buffer *const *GetViewProjBuffer() { return &m_pViewProjBuffer; }
	D3DXVECTOR2& GetPosition() { return m_vPosition; }
	D3DXVECTOR2 GetMapSize() { return m_vMapSize; }
};