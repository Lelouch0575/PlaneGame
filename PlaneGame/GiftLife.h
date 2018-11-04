#pragma once
#include "GameObject.h"
class CGiftLife :public CGameObject
{
public:
	CGiftLife(void);
	~CGiftLife(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + GIFTWP_HEIGHT, m_ptPos.y + GIFTWP_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
private:
	static const int GIFTWP_HEIGHT = 50;                    //�л��Ŀ��
	static CImageList m_Images;
	int    m_nMotion;//���� 1->���� 0->ֹͣ -1->����
					 //�ٶ�
	int m_V;

};