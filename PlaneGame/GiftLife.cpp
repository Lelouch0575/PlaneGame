#include "stdafx.h"
#include "GiftLife.h"
#include "resource.h"

CImageList CGiftLife::m_Images;

CGiftLife::CGiftLife(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - GIFTWP_HEIGHT) + 1;

	//���ȷ��ͼ������
	//m_nImgIndex = rand()%2;

	//����ͼ������ȷ������
	m_nMotion = 1;
	m_ptPos.y = -GIFTWP_HEIGHT;
	//if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	//{
	//	m_nMotion=0;
	//	m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	//}
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	//m_nWait = 0;
}

CGiftLife::~CGiftLife(void)
{
}
BOOL CGiftLife::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_LIFE, RGB(0, 0, 0), 50, 50, 1);
}
BOOL CGiftLife::Draw(CDC* pDC, BOOL bPause)
{
	//m_nWait++;
	//if (m_nWait>20)
	//	m_nWait = 0;

	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
	}

	if (m_ptPos.y > GAME_HEIGHT + GIFTWP_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -GIFTWP_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
