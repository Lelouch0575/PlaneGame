#include "stdafx.h"
#include "GiftWM.h"
#include "resource.h"

CImageList CGiftWM::m_Images;

CGiftWM::CGiftWM(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - GIFTWM_HEIGHT) + 1;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -GIFTWM_HEIGHT;
	
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	//m_nWait = 0;
}

CGiftWM::~CGiftWM(void)
{
}
BOOL CGiftWM::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_GIFTWM, RGB(0, 0, 0), 50, 50, 1);
}
BOOL CGiftWM::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + GIFTWM_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -GIFTWM_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}