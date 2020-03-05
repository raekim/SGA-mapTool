#include "stdafx.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"


Player::Player()
{
	Clip* clip = new Clip;
	for (int i = 0; i < 2; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 2, 1, i);
		clip->AddFrame(sprite, 1 / 2.0f);
	}
	m_pAnimation->AddClip(PLAYER_STATE::Flying, clip);
}

Player::~Player()
{
	for (int i = 0; i < m_vecMissile.size(); i++)
		SAFE_DELETE(m_vecMissile[i]);
	m_vecMissile.clear();
}

void Player::Init()
{
	Unit::Init();

	m_fShootSpeed1 = 0.1f;	// �ʴ� �߻� �ӵ�
	m_fElapsedTime1 = 0.0f;	// �ð� ���� ��
	m_fShootSpeed2 = 0.2f;	// �ʴ� �߻� �ӵ�
	m_fElapsedTime2 = 0.0f;	// �ð� ���� ��
}

void Player::Keyboard()
{
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_vPosition.x -= m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		m_vPosition.x += m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	}

	if (g_pKeyManager->isStayKeyDown('W'))
	{
		m_vPosition.y += m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		m_vPosition.y -= m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
	}

	m_fElapsedTime1 += g_pTimeManager->GetDeltaTime();
	m_fElapsedTime2 += g_pTimeManager->GetDeltaTime();

	if (m_fShootSpeed1 < m_fElapsedTime1 && g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	{
		Missile* p = new Missile;

		D3DXVECTOR2 shootPos;
		shootPos.x = m_vPosition.x + cosf(m_vRotation.z) * 50.0f;
		shootPos.y = m_vPosition.y + sinf(m_vRotation.z) * 50.0f;

		p->Init(shootPos, m_vRotation);
		m_vecMissile.push_back(p);
		m_fElapsedTime1 = 0.0f;
	}

	static bool isLeft = true;

	if (m_fShootSpeed2 < m_fElapsedTime2 && g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	{
		float minDist = FLT_MAX;
		int minIndex = 0;
		for (int i = 0; i < m_vecEnemy->size(); i++)
		{
			D3DXVECTOR2 enemyPos = *(*m_vecEnemy)[i]->GetPosition();
			float dist = D3DXVec2Length(&(m_vPosition - enemyPos));

			if (dist < minDist)
			{
				minDist = dist;
				minIndex = i;
			}
		}

		Missile* p;
		D3DXVECTOR2* pTarget = NULL;
		if (m_vecEnemy->size() > 0)
			pTarget = (*m_vecEnemy)[minIndex]->GetPosition();

		D3DXVECTOR2 shootPos;

		//if (isLeft)
		//{
		//	shootPos.x = m_vPosition.x + cosf(m_vRotation.z + D3DX_PI * 0.5f) * 50.0f;
		//	shootPos.y = m_vPosition.y + sinf(m_vRotation.z + D3DX_PI * 0.5f) * 50.0f;
		//}
		//else
		//{
		//	shootPos.x = m_vPosition.x + cosf(m_vRotation.z - D3DX_PI * 0.5f) * 50.0f;
		//	shootPos.y = m_vPosition.y + sinf(m_vRotation.z - D3DX_PI * 0.5f) * 50.0f;
		//}
		//
		//isLeft = !isLeft;

		p = new Missile;
		shootPos.x = m_vPosition.x + cosf(m_vRotation.z + D3DX_PI * 0.5f) * 50.0f;
		shootPos.y = m_vPosition.y + sinf(m_vRotation.z + D3DX_PI * 0.5f) * 50.0f;
		p->Init(shootPos, m_vRotation, pTarget);
		m_vecMissile.push_back(p);

		p = new Missile;
		shootPos.x = m_vPosition.x + cosf(m_vRotation.z - D3DX_PI * 0.5f) * 50.0f;
		shootPos.y = m_vPosition.y + sinf(m_vRotation.z - D3DX_PI * 0.5f) * 50.0f;
		p->Init(shootPos, m_vRotation, pTarget);
		m_vecMissile.push_back(p);
		m_fElapsedTime2 = 0.0f;
	}
}

void Player::UpdateRotation()
{
	// ī�޶� �̵��� ���� ���콺 ������ ��밪 ���
	D3DXVECTOR2 fixedMouse(g_ptMouse.x + g_pCamera->GetPosition().x, g_ptMouse.y + g_pCamera->GetPosition().y);

	// �÷��̾��� ���� ���� ���콺 ��ġ�� ���� �ޱ� ���
	float targetAngle = GetAngleAsRadian(m_vPosition, fixedMouse);
	// ���� ���� 0�� �������� ����
	targetAngle -= m_vRotation.z;

	// ȸ���� ���
	float targetAmount = targetAngle;
	if (targetAmount > D3DX_PI)
		targetAmount = D3DX_PI * 2.0f - targetAmount;

	float rotAmount = m_fRotSpeed * g_pTimeManager->GetDeltaTime();

	// ȸ������ �������ӿ� ȸ���� �� �ִ� �纸�� ū ��쿡�� ȸ��
	if (fabs(targetAmount) > rotAmount)
	{
		// ��� �� ���� ���� 0���� ���� ��� ������� ���� ������ ��� ���ش�.
		if (targetAngle < 0.0f)
			targetAngle += D3DX_PI * 2.0f;
		
		m_vRotation.z += (targetAngle < D3DX_PI) ? rotAmount : -rotAmount;
		
		if (m_vRotation.z < 0.0f)
			m_vRotation.z += D3DX_PI * 2.0f;
		else if (m_vRotation.z > D3DX_PI * 2.0f)
			m_vRotation.z -= D3DX_PI * 2.0f;
	}
}

void Player::Update()
{
	Keyboard();
	UpdateRotation();

	Unit::Update();

	vector<Missile*>::iterator iter = m_vecMissile.begin();
	while (iter != m_vecMissile.end())
	{
		if ((*iter)->IsAlive() == false)
		{
			SAFE_DELETE(*iter);
			iter = m_vecMissile.erase(iter);
		}
		else
		{
			(*iter)->Update();
			iter++;
		}
	}
}

void Player::Render()
{
	Unit::Render();

	for (int i = 0; i < m_vecMissile.size(); i++)
		m_vecMissile[i]->Render();
}