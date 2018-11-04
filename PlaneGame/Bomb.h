#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	CBomb(int x, int y, int dr);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BOMB_WIDTH,m_ptPos.y+BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 50;   //�ӵ��߶�
	static const int BOMB_WIDTH = 20; 
	static CImageList m_Images;
	int direct;  //�ӵ�����0Ϊ��ǰ������ֵΪ����ֵΪ��
};
