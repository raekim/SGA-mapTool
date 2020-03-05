#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	// �� ��Ʈ���� ����
	m_vEye = D3DXVECTOR3(0, 0, -1);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);
	// ���̴����� ��Ʈ������ ��� ���� ������ �ٲ��ֱ� ������ Ʈ������� ���־�� �Ѵ�.

	// �������� ��Ʈ���� ����
	D3DXMatrixOrthoOffCenterLH(&m_stViewProjMatrix.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&m_stViewProjMatrix.Projection, &m_stViewProjMatrix.Projection);

	// ���� ����
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// ���ۿ� ���� ������
	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = &m_stViewProjMatrix;

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pViewProjBuffer);
}


Camera::~Camera()
{
	SAFE_RELEASE(m_pViewProjBuffer);
}

void Camera::Init()
{
	m_vFocus = D3DXVECTOR2(HALFSIZEX, HALFSIZEY);
	m_vPosition = D3DXVECTOR2(0, 0);

	m_vMapSize.x = WINSIZEX;
	m_vMapSize.y = WINSIZEY;

	m_pTarget = NULL;
}

void Camera::Update()
{
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		m_vPosition.x -= MOVESPEED * g_pTimeManager->GetDeltaTime();
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		m_vPosition.x += MOVESPEED * g_pTimeManager->GetDeltaTime();

	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
		m_vPosition.y -= MOVESPEED * g_pTimeManager->GetDeltaTime();
	else if (g_pKeyManager->isStayKeyDown(VK_UP))
		m_vPosition.y += MOVESPEED * g_pTimeManager->GetDeltaTime();

	if (m_pTarget)
	{
		m_vPosition = *m_pTarget - m_vFocus;
	}

	if (m_vPosition.x <= 0)
		m_vPosition.x = 0;
	else if (m_vPosition.x > m_vMapSize.x - WINSIZEX)
		m_vPosition.x = m_vMapSize.x - WINSIZEX;

	if (m_vPosition.y <= 0)
		m_vPosition.y = 0;
	else if (m_vPosition.y > m_vMapSize.y - WINSIZEY)
		m_vPosition.y = m_vMapSize.y - WINSIZEY;

	// �� ��Ʈ���� ����
	m_vEye = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, -1);
	m_vLookAt = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);

	DeviceContext->UpdateSubresource(m_pViewProjBuffer, 0, 0, &m_stViewProjMatrix, 0, 0);
}
