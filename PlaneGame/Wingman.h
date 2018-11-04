#pragma once
#include "GameObject.h"

class CWingman :public CGameObject
{
public:
	CWingman(void);
	CWingman(int x,int y);
	~CWingman(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}
	void SetPoint(int x,int y);
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + WM_WIDTH, m_ptPos.y + WM_HEIGHT));
	}

	//�Ƿ���Կ����䵼��
	BOOL Fired();

public:
	static const int WM_WIDTH = 30;
	static const int WM_HEIGHT = 40;                      //ս���Ŀ��
	int life;  //�Ż�����
private:

	static CImageList m_Images;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
	
};
