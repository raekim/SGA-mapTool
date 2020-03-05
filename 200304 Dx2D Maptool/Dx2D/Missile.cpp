#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
	: m_vTarget(NULL)
{
	m_pSprite = new Sprite(L"Missile", 6, 1, 5);
	m_pSprite->SetSize(0.2f, 0.2f);
}


Missile::~Missile()
{
	SAFE_DELETE(m_pSprite);
}

void Missile::Init(D3DXVECTOR2 pos, D3DXVECTOR3 rot, D3DXVECTOR2* target)
{
	m_vPosition = pos;
	m_vRotation = rot;

	m_fMoveSpeed = 1000.0f;
	m_fRotSpeed = D3DX_PI;

	m_vTarget = target;
	m_isAlive = true;
}

void Missile::Update()
{
	ImGui::InputFloat("M_MoveSpeed", &m_fMoveSpeed);
	ImGui::InputFloat("M_RotSpeed", &m_fRotSpeed);

	if (m_vTarget) // 지정 타겟이 있는 경우
	{
		//*m_vTarget = D3DXVECTOR2(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y);

		float targetAngle = GetAngleAsRadian(m_vPosition, *m_vTarget);
		targetAngle -= m_vRotation.z;

		float targetAmount = targetAngle;
		if (targetAmount > D3DX_PI)
			targetAmount = D3DX_PI * 2.0f - targetAmount;

		float rotAmount = m_fRotSpeed * g_pTimeManager->GetDeltaTime();
		m_fRotSpeed += 0.1f;

		// 회전량이 한프레임에 회전할 수 있는 양보다 큰 경우에만 회전
		if (fabs(targetAmount) > rotAmount)
		{
			// 계산 된 각도 값이 0보다 작은 경우 양수값의 각도 값으로 계산 해준다.
			if (targetAngle < 0.0f)
				targetAngle += D3DX_PI * 2.0f;

			m_vRotation.z += (targetAngle < D3DX_PI) ? rotAmount : -rotAmount;

			if (m_vRotation.z < 0.0f)
				m_vRotation.z += D3DX_PI * 2.0f;
			else if (m_vRotation.z > D3DX_PI * 2.0f)
				m_vRotation.z -= D3DX_PI * 2.0f;
		}

		if (D3DXVec2Length(&(*m_vTarget - m_vPosition)) < 10.0f)
			m_isAlive = false;
	}

	m_vPosition.x += cosf(m_vRotation.z) * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	m_vPosition.y += sinf(m_vRotation.z) * m_fMoveSpeed * g_pTimeManager->GetDeltaTime();

	if (m_pSprite)
	{
		m_pSprite->SetPosition(m_vPosition);
		m_pSprite->SetRotation(m_vRotation.x, m_vRotation.y, m_vRotation.z - D3DX_PI * 0.5f);
		m_pSprite->Update();
	}
}

void Missile::Render()
{
	if (m_pSprite)
		m_pSprite->Render();
}
