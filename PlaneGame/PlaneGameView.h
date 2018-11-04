// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once

#include "Shield.h"     //����
#include "Wingman.h"    //�Ż�

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType { enEnemy, enBomb, enBomb1, enBall,enExplosion, enBOSS, enBOSS2, enBOSS3, enBall1, enBall2, enGiftwp, enGiftlf, enGiftwm, enGiftShield, enSkill};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

	// ����
public:
	CPlaneGameDoc * GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//�ڴ�DC
	CDC * m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000) ? 1 : 0;
	}

	CMyPlane*  m_pMe;
	CShield* m_pShield;
	CWingman* m_pWingmanLeft;  //���Ż�
	CWingman* m_pWingmanRight;  //���Ż�

	CObList    m_ObjList[15];

	void SetStage(int s);

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	int scrolls;  //��֡�仯��ʵ�ֱ�������
	int mylife;  //�������
	int Invincible;  //�޵�ģʽ����
	int shield;  //���ܿ���
	int delay;  //�����ӳ�
	int score;  //�÷֣�ͨ���÷��ж��Ƿ�����boss
	int selectbackground;  //ѡ�񱳾�
	int weaponlevel;  //�����ȼ�
	int energy;     //����
	int shieldtime;  //����ʱ��
	int stage;  //�ؿ���
	int bossnum; //boss���������һ��
	int selectboss;  //ѡ�����ɵ�boss
	int ispause;  //�Ƿ�����ͣ������
	int pausetrue;  //�Ƿ�������Ҫ��ͣ

};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
{
	return reinterpret_cast<CPlaneGameDoc*>(m_pDocument);
}
#endif




