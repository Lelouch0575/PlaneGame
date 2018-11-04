#include "stdafx.h"
#include "BOSS2.h"
#include "resource.h"

CImageList CBOSS2::m_Images;

CBOSS2::CBOSS2(void)
{

	m_ptPos.x = 230;

	m_nMotion = 1;
	m_ptPos.y = -BOSS_HEIGHT;
	
	//���ȷ���ٶ�
	m_V = rand() % 6 + 2;

	m_nWait = 0;

	bosslife = 300;
}

CBOSS2::~CBOSS2(void)
{
}
BOOL CBOSS2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS3, RGB(0, 0, 0), 500, 325, 1);
}
BOOL CBOSS2::Draw(CDC* pDC, BOOL bPause)
{
	//bossѪ��
	CString boshp;
	boshp.Format(_T("BOSS:"));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);
	pDC->SetTextColor(RGB(0, 255, 255));
	pDC->TextOut(720, 30, boshp);

	CBrush bosbr;
	bosbr.CreateSolidBrush(RGB(255, 0, 0));
	pDC->SelectObject(bosbr);
	pDC->Rectangle(750, 30, 750 + bosslife/3 *2, 45);

	CBrush bosbr1;
	bosbr1.CreateSolidBrush(RGB(0, 0, 0));
	pDC->SelectObject(bosbr1);
	pDC->Rectangle(750 + bosslife/3 *2, 30, 750 + 200, 45);


	m_nWait++;
	if (m_nWait>30)                 //�޸ķ�����ʱ
		m_nWait = 0;

	if (!bPause)
	{
		if (m_ptPos.y <= 20)
			m_ptPos.y = m_ptPos.y + m_V;
		else
		{
			//static const int direct = rand() % 2;
			if (m_ptPos.x <= 0)
				m_nMotion = 1;
			if (m_ptPos.x >= GAME_WIDTH - BOSS_WIDTH)
				m_nMotion = -1;

			m_ptPos.x += m_nMotion * m_V;
		}
	}

	if (m_ptPos.y > GAME_HEIGHT + BOSS_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOSS_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBOSS2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}