// PlaneGameView.cpp : CPlaneGameView ���ʵ��
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
#include "BOSS.h"
#include "BOSS2.h"
#include "BOSS3.h"
#include "Ball1.h"
#include "Ball2.h"
#include "GiftWeapon.h"
#include "Bomb1.h"
#include "Skill.h"
#include "GiftLife.h"
#include "GiftShield.h"
#include "GiftWM.h"
#include "Shield.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
		InitGame();

}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}


BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBOSS::LoadImage();
	CBOSS2::LoadImage();
	CBOSS3::LoadImage();
	CBall1::LoadImage();
	CBall2::LoadImage();
	CGiftWeapon::LoadImage();
	CBomb1::LoadImage();
	CSkill::LoadImage();
	CGiftLife::LoadImage();
	CGiftShield::LoadImage();
	CGiftWM::LoadImage();
	CShield::LoadImage();
	CWingman::LoadImage();
	
	//��������(ս��)w
	m_pMe = new CMyPlane;
	m_pShield = NULL;
	m_pWingmanLeft = NULL;
	m_pWingmanRight = NULL;

	//������Ϸ
	SetTimer(1,30,NULL);

	scrolls = 0;  //��ʼ�����ڹ�������
	mylife = 50;  //��ʼ���������
	Invincible = 0;  //�޵�ģʽĬ�Ϲ�
	shield = 0;  //����
	delay = 0;   //�����ӳ�
	score = 0;   //�÷�
	weaponlevel = 1;   //�����ȼ�
	energy = 0;   //����
	shieldtime = 0;
	SetStage(1);  //��ʼ�ؿ�Ϊ1
	ispause = 0;
	pausetrue = 1;
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));

	//����
	CBitmap bitmap;                           //λͼ�����

	if (selectbackground == 1)
		bitmap.LoadBitmap(IDB_BACKGROUND1);   //����Դ��װ����λͼ
	else if (selectbackground == 2)
		bitmap.LoadBitmap(IDB_BACKGROUND2);     
	else if (selectbackground == 3)
		bitmap.LoadBitmap(IDB_BACKGROUND3);
	else if (selectbackground == 4)
		bitmap.LoadBitmap(IDB_BACKGROUND4);
	else if (selectbackground == 5)
		bitmap.LoadBitmap(IDB_BACKGROUND5);


	//load DC
	CDC comdc;  //����CDC����
	comdc.CreateCompatibleDC(m_pMemDC);   //�����豸����
	comdc.SelectObject(&bitmap);      //ѡ��λͼ����
	
	//��������DC����Ϣ��������ǰDC
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	//m_pMemDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &comdc, 0, 0, SRCCOPY);

	m_pMemDC->BitBlt(0, 0, GAME_WIDTH, scrolls, &comdc, 0, GAME_HEIGHT-scrolls, SRCCOPY);
	m_pMemDC->BitBlt(0, scrolls, GAME_WIDTH, GAME_HEIGHT-scrolls, &comdc, 0, 0, SRCCOPY);

	if (scrolls <= GAME_HEIGHT)    //���Ʊ�������
		scrolls += 6;
	else
		scrolls = 0;


	// ����Ѫ��
	CString hp;
	hp.Format(_T("HP:"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 255, 255));
	pMemDC->TextOut(20, 30, hp);
	CBrush br;  // Ѫ��
	br.CreateSolidBrush(RGB(0, 255, 102));
	m_pMemDC->SelectObject(br);
	m_pMemDC->Rectangle(42, 30, 42 + 4 * mylife, 45);
	CBrush br1;
	br1.CreateSolidBrush(RGB(0, 0, 0));
	m_pMemDC->SelectObject(br1);
	m_pMemDC->Rectangle(42 + 4 * mylife, 30, 42 + 200, 45);


	// ����������
	CString ene;
	ene.Format(_T("SP:"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 255, 255));
	pMemDC->TextOut(20, 50, ene);
	CBrush brene;  
	brene.CreateSolidBrush(RGB(249, 200, 2));
	m_pMemDC->SelectObject(brene);
	m_pMemDC->Rectangle(42, 50, 42 + energy/3, 65);
	CBrush brene1;
	brene1.CreateSolidBrush(RGB(0, 0, 0));
	m_pMemDC->SelectObject(brene1);
	m_pMemDC->Rectangle(42 + energy/3, 50, 42 + 200, 65);

	if (energy < 600)
		energy++;



	CString tip;
	tip.Format(_T("Z��ʹ�ü��� X�������޵�ģʽ R������ P����ͣ"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 255, 255));
	pMemDC->TextOut(205, 5, tip);




	CString wudi;
	if (Invincible == 0)
		wudi.Format(_T("�޵�ģʽ�ѹر�"));
	else
		wudi.Format(_T("�޵�ģʽ�ѿ���"));
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 255, 255));
	pMemDC->TextOut(72, 75, wudi);


	CString sc;
	sc.Format(_T("�÷֣�%d"),score);
	pMemDC->SetBkMode(TRANSPARENT);
	pMemDC->SetTextAlign(TA_CENTER);
	pMemDC->SetTextColor(RGB(0, 255, 255));
	pMemDC->TextOut(45, 95, sc);

	sc.Format(_T("��ǰ�ؿ���%d"), stage);
	pMemDC->TextOut(57, 115, sc);




	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
	   m_pMe->Draw(m_pMemDC,FALSE);
	   if (shield == 1)
	   {
		   CPoint s_point = m_pMe->GetPoint();
		   s_point.x -= 10;
		   s_point.y -= 20;
		   m_pShield->SetPoint(s_point);
		   m_pShield->Draw(m_pMemDC, FALSE);
	   }
	   if (m_pWingmanLeft != NULL)
	   {
		   CPoint s_point = m_pMe->GetPoint();
		   m_pWingmanLeft->SetPoint(s_point.x-35,s_point.y+10);
		   m_pWingmanLeft->Draw(m_pMemDC, FALSE);
	   }
	   if (m_pWingmanRight != NULL)
	   {
		   CPoint s_point = m_pMe->GetPoint();
		   m_pWingmanRight->SetPoint(s_point.x + m_pMe->PLANE_WIDTH +5, s_point.y+10);
		   m_pWingmanRight->Draw(m_pMemDC, FALSE);
	   }

	}
	else
	{   //Game Over
		CString str=_T("Game Over!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(0,255,255));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 15, _T("��R����"));
		
	}
	
	//table

	//���� ��������ը���л����ӵ�    
	for(int i=0;i<15;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() % 5 + 10;    //��������Ƶ��

	//��������л�
	if (nCreator <= 0)
	{
		nCreator = rand() % 5 + 10;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;



	//��������л�boss
	static int ncreatorboss = 400;     /*rand() % 500 + 500; */
	if (ncreatorboss <= 0 && bossnum == 0)
	{
		ncreatorboss = 400;        /*rand() % 500 + 500;*/
		if (selectboss == 1)
			m_ObjList[enBOSS].AddTail(new CBOSS);
		else if (selectboss == 2)
			m_ObjList[enBOSS2].AddTail(new CBOSS2);
		else if (selectboss == 3)
			m_ObjList[enBOSS3].AddTail(new CBOSS3);
		bossnum++;
	}
	ncreatorboss--;

	//�������������������
	static int ncreatorgiftwp = rand() % 50 + 200;
	if (ncreatorgiftwp <= 0)
	{
		ncreatorgiftwp = rand() % 50 + 200;
		m_ObjList[enGiftwp].AddTail(new CGiftWeapon);
	}
	ncreatorgiftwp--;
	

	//�������Ѫ��
	static int ncreatorgiftlf = rand() % 50 + 200;
	if (ncreatorgiftlf <= 0)
	{
		ncreatorgiftlf = rand() % 50 + 200;
		m_ObjList[enGiftlf].AddTail(new CGiftLife);
	}
	ncreatorgiftlf--;
	

	//���������������
	static int ncreatorgiftsd = rand() % 50 + 200;
	if (ncreatorgiftsd <= 0)
	{
		ncreatorgiftsd = rand() % 50 + 200;
		m_ObjList[enGiftShield].AddTail(new CGiftShield);
	}
	ncreatorgiftsd--;
	
	//��������Ż�����
	static int ncreatorgiftwm = rand() % 50 + 200;
	if (ncreatorgiftwm <= 0)
	{
		ncreatorgiftwm = rand() % 50 + 200;
		m_ObjList[enGiftwm].AddTail(new CGiftWM);
	}
	ncreatorgiftwm--;
	



	if (GetKey('R') && m_pMe == NULL)
	{
		m_pMe = new CMyPlane;
		m_pWingmanLeft = NULL;
		m_pWingmanRight = NULL;
		mylife = 50;
		weaponlevel = 1;
		energy = 0;
	}

	if (m_pMe == NULL)
		return;

	//����ĸ���������ƶ�ս��
	for (int i = 0; i < 4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1);

		nMeMotion = GetKey(VK_DOWN);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1);

	}

	//����ս������
	if (GetKey(VK_SPACE) == 1)//�����˿ո��
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (weaponlevel == 1)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));          //���������ӵ���λ��
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 48, pt.y + 10));
			}
			else if (weaponlevel == 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 5, pt.y + 10, -1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y, 0));     //���������ӵ���λ��
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 53, pt.y + 10, 1));
			}
			else if (weaponlevel == 3)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x - 5, pt.y + 10, -2));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x, pt.y + 10, -1));

				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y, 0));     //���������ӵ���λ��
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 48, pt.y + 10));

				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 58, pt.y + 10, 1));
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 65, pt.y + 10, 2));
			}

		}

		//�Ż������ӵ�
		// �Ż������ӵ�

		if (m_pMe != NULL && m_pMe->Fired() && m_pWingmanLeft != NULL)
		{
			CPoint pt = m_pWingmanLeft->GetPoint();
			m_ObjList[enBomb1].AddTail(new CBomb1(pt.x + 8, pt.y, 0));

		}
		if (m_pMe != NULL && m_pMe->Fired() && m_pWingmanRight != NULL)
		{
			CPoint pt = m_pWingmanRight->GetPoint();
			m_ObjList[enBomb1].AddTail(new CBomb1(pt.x + 8, pt.y, 0));

		}
	

	}
	if (GetKey('X') && delay == 0)
	{
		if (Invincible == 0)
			Invincible = 1;
		else if (Invincible == 1)
			Invincible = 0;
		delay++;
	}
	if (GetKey('Z') && energy >= 300 && delay == 0)
	{
		energy -= 300;
		for (int i = 0; i < 8; i++)
		{
			m_ObjList[enSkill].AddTail(new CSkill(0 + 128 * i, GAME_HEIGHT + 100));
		}
		delay++;
	}

	/*�����ǵз������ӵ�*/

	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = FALSE;

		//�л���ս��ǰ��
		if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
			by = TRUE;
		//�л���ս������
		if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
			by = TRUE;

		if (by && ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 20, ePt.y + 10, pEnemy->GetMontion()));    //�л��ӵ�λ��
		}
	}


	//boss�����ӵ�
	//PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enBOSS].GetHeadPosition(); ePos != NULL;)
	{
		CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos);
		if (!pBOSS->Fired())
			continue;
		CPoint  ePt = pBOSS->GetPoint();

		m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 30, ePt.y + 260, 1));   //�л��ӵ�λ��
		m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 150, ePt.y + 280, 1));    
		m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 350, ePt.y + 280, 1));
		m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 450, ePt.y + 260, 1));
	}

	//boss2�����ӵ�
	for (POSITION ePos = m_ObjList[enBOSS2].GetHeadPosition(); ePos != NULL;)
	{
		CBOSS2* pBOSS2 = (CBOSS2*)m_ObjList[enBOSS2].GetNext(ePos);
		if (!pBOSS2->Fired())
			continue;
		CPoint  ePt = pBOSS2->GetPoint();

		m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 50, ePt.y + 260, -2));   //�л��ӵ�λ��
		m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 150, ePt.y + 280, -1));
		m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 250, ePt.y + 300, 0));
		m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 350, ePt.y + 280, 1));
		m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 450, ePt.y + 260, 2));
		//}
	}

	//boss3�����ӵ�
	for (POSITION ePos = m_ObjList[enBOSS3].GetHeadPosition(); ePos != NULL;)
	{
		CBOSS3* pBOSS3 = (CBOSS3*)m_ObjList[enBOSS3].GetNext(ePos);
		if (!pBOSS3->Fired())
			continue;
		CPoint  ePt = pBOSS3->GetPoint();
		int balltype = rand();
		if (balltype %2==0)
		{
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 30, ePt.y + 260, 1));
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 150, ePt.y + 280, 1)); 
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 350, ePt.y + 280, 1));
			m_ObjList[enBall1].AddTail(new CBall1(ePt.x + 450, ePt.y + 260, 1));
		}
		else
		{
			m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 50, ePt.y + 260, -2));   
			m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 150, ePt.y + 280, -1));
			m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 250, ePt.y + 300, 0));
			m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 350, ePt.y + 280, 1));
			m_ObjList[enBall2].AddTail(new CBall2(ePt.x + 450, ePt.y + 260, 2));
		}
		
	}



	/*����������յ��������ж�*/


	//�л��ӵ�ը��ս��
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);

			//ɾ���ӵ�
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			//ɾ��ս��
			if (Invincible == 0 && shield == 0)
				mylife -= 2;
			if (mylife <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}

		}
	}
	//�л��ӵ�ը���Ż���
	//POSITION bPos1 = NULL, bPos2 = NULL;
	//if (m_pWingmanLeft != NULL)
	//{
		//CRect wRect = m_pWingmanLeft->GetRect();
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (m_pWingmanLeft != NULL)
			{
				CRect wRect = m_pWingmanLeft->GetRect();
				if (tmpRect.IntersectRect(&bRect, wRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(wRect.left, wRect.top)
					);

					//ɾ���ӵ�
					m_ObjList[enBall].RemoveAt(bPos2);
					delete pBall;

					//ɾ��ս��
					if (Invincible == 0 && shield == 0)
						m_pWingmanLeft->life -= 2;
					if (m_pWingmanLeft->life <= 0)
					{
						delete m_pWingmanLeft;
						m_pWingmanLeft = NULL;
						break;
					}

				}
			}
			if (m_pWingmanRight != NULL)
			{
				CRect wRect = m_pWingmanRight->GetRect();
				if (tmpRect.IntersectRect(&bRect, wRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(wRect.left, wRect.top)
					);

					//ɾ���ӵ�
					m_ObjList[enBall].RemoveAt(bPos2);
					delete pBall;

					//ɾ��ս��
					if (Invincible == 0 && shield == 0)
						m_pWingmanRight->life -= 2;
					if (m_pWingmanRight->life <= 0)
					{
						delete m_pWingmanRight;
						m_pWingmanRight = NULL;
						break;
					}

				}
			}
			
		}	
	

	//boss�ӵ�1����ս��
    //	mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall1].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall1* pBall1 = (CBall1*)m_ObjList[enBall1].GetNext(bPos1);
		CRect bRect = pBall1->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);

			//ɾ���ӵ�
			m_ObjList[enBall1].RemoveAt(bPos2);
			delete pBall1;

			//ɾ��ս��
			if (Invincible == 0 && shield == 0)
				mylife -= 3;
			if (mylife <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}

		}
	}

	//boss�ӵ�1ը���Ż���
	//POSITION bPos1 = NULL, bPos2 = NULL;
		for (bPos1 = m_ObjList[enBall1].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall1* pBall1 = (CBall1*)m_ObjList[enBall1].GetNext(bPos1);
			CRect bRect = pBall1->GetRect();
			CRect tmpRect;
			if (m_pWingmanLeft != NULL)
			{
				CRect wRect = m_pWingmanLeft->GetRect();
				if (tmpRect.IntersectRect(&bRect, wRect))
				{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(wRect.left, wRect.top)
				);

				//ɾ���ӵ�
				m_ObjList[enBall1].RemoveAt(bPos2);
				delete pBall1;

				//ɾ��ս��
				if (Invincible == 0 && shield == 0)
					m_pWingmanLeft->life -= 6;
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}

				}
				
			}
			if (m_pWingmanRight != NULL)
			{
				CRect wRect = m_pWingmanRight->GetRect();
				if (tmpRect.IntersectRect(&bRect, wRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(wRect.left, wRect.top)
					);

					//ɾ���ӵ�
					m_ObjList[enBall1].RemoveAt(bPos2);
					delete pBall1;

					//ɾ��ս��
					if (Invincible == 0 && shield == 0)
						m_pWingmanRight->life -= 6;
					if (m_pWingmanRight->life <= 0)
					{
						delete m_pWingmanRight;
						m_pWingmanRight = NULL;
						break;
					}

				}

			}
			
		}
	
	


	//boss�ӵ�2����ս��
	//mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall2].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall2* pBall2 = (CBall2*)m_ObjList[enBall2].GetNext(bPos1);
		CRect bRect = pBall2->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//��ӱ�ըЧ��
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
			);

			//ɾ���ӵ�
			m_ObjList[enBall2].RemoveAt(bPos2);
			delete pBall2;

			//ɾ��ս��
			if (Invincible == 0 && shield == 0)
				mylife -= 3;
			if (mylife <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}

		}
	}
	//boss�ӵ�2ը���Ż���
	//POSITION bPos1 = NULL, bPos2 = NULL;

	for (bPos1 = m_ObjList[enBall2].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall2* pBall2 = (CBall2*)m_ObjList[enBall2].GetNext(bPos1);
		CRect bRect = pBall2->GetRect();
		CRect tmpRect;
		if (m_pWingmanLeft != NULL)
		{
			CRect wRect = m_pWingmanLeft->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(wRect.left, wRect.top)
				);

				//ɾ���ӵ�
				m_ObjList[enBall2].RemoveAt(bPos2);
				delete pBall2;

				//ɾ��ս��
				if (Invincible == 0 && shield == 0)
					m_pWingmanLeft->life -= 6;
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}

			}
		}
		if (m_pWingmanRight != NULL)
		{
			CRect wRect = m_pWingmanRight->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				//ɾ���ӵ�
				m_ObjList[enBall2].RemoveAt(bPos2);
				delete pBall2;

				//ɾ��ս��
				if (Invincible == 0 && shield == 0)
					m_pWingmanRight->life -= 6;
				if (m_pWingmanRight->life <= 0)
				{
					delete m_pWingmanRight;
					m_pWingmanRight = NULL;
					break;
				}

			}
		}
		
	}
	
	




	/*�����Ƿɻ������ײ*/

	//�л�����ս��
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy* pEnecol = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos1);
		CRect bRect = pEnecol->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			m_ObjList[enEnemy].RemoveAt(bPos2);
			delete pEnecol;
			m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

			if (Invincible == 0 && shield == 0)
				mylife -= 2;
			if (mylife <= 0)
			{
				delete m_pMe;
				m_pMe = NULL;
				break;
			}
		}
	}

	//�л������Ż�
	for (bPos1 = m_ObjList[enEnemy].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CEnemy* pEnecol = (CEnemy*)m_ObjList[enEnemy].GetNext(bPos1);
		CRect bRect = pEnecol->GetRect();
		CRect tmpRect;
		if (m_pWingmanLeft != NULL)
		{
			CRect wRect = m_pWingmanLeft->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enEnemy].RemoveAt(bPos2);
				delete pEnecol;
				m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

				if (Invincible == 0 && shield == 0)
					m_pWingmanLeft->life -= 2;
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}
			}
		}
		if (m_pWingmanRight != NULL)
		{
			CRect wRect = m_pWingmanRight->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enEnemy].RemoveAt(bPos2);
				delete pEnecol;
				m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

				if (Invincible == 0 && shield == 0)
					m_pWingmanRight->life -= 2;
				if (m_pWingmanRight->life <= 0)
				{
					delete m_pWingmanRight;
					m_pWingmanRight = NULL;
					break;
				}
			}
		}

		
	}


	//BOSS����ս��
	for (bPos1 = m_ObjList[enBOSS].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS* pboscol = (CBOSS*)m_ObjList[enBOSS].GetNext(bPos1);
		CRect bRect = pboscol->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{


			static int invtime = 0;  //��boss��ײ���ж��ݵ��޵�ʱ��
			if (invtime == 0)
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
				pboscol->bosslife -= 5;
				if (Invincible == 0 && shield == 0)
				{
					mylife -= 10;
				}
				if (mylife <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
				if (pboscol->bosslife <= 0)
				{
					m_ObjList[enBOSS].RemoveAt(bPos2);
					//bossnum = 0;
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
					delete pboscol;
					SetStage(++stage);
					ncreatorboss = 400;
					break;
				}
			}
			invtime++;
			if (invtime == 20)
				invtime = 0;
		}
	}
	//boss�����Ż�
	for (bPos1 = m_ObjList[enBOSS].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS* pboscol = (CBOSS*)m_ObjList[enBOSS].GetNext(bPos1);
		CRect bRect = pboscol->GetRect();
		CRect tmpRect;
		if (m_pWingmanLeft != NULL)
		{
			CRect wRect = m_pWingmanLeft->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanLeft->life -= 10;
				}
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}
				//if (pboscol->bosslife <= 0)
				//{
				//	m_ObjList[enBOSS].RemoveAt(bPos2);
				//	//bossnum = 0;
				//	m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
				//	delete pboscol;
				//	SetStage(++stage);
				//	ncreatorboss = 400;
				//	break;
				//}
			}
		}
		if (m_pWingmanRight != NULL)
		{
			CRect wRect = m_pWingmanRight->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanRight->life -= 10;
				}
				if (m_pWingmanRight->life <= 0)
				{
					delete m_pWingmanRight;
					m_pWingmanRight = NULL;
					break;
				}
				//if (pboscol->bosslife <= 0)
				//{
				//	m_ObjList[enBOSS].RemoveAt(bPos2);
				//	//bossnum = 0;
				//	m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
				//	delete pboscol;
				//	SetStage(++stage);
				//	ncreatorboss = 400;
				//	break;
				//}
			}
		}
		
	}


	//BOSS2����ս��
	for (bPos1 = m_ObjList[enBOSS2].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS2* pboscol2 = (CBOSS2*)m_ObjList[enBOSS2].GetNext(bPos1);
		CRect bRect = pboscol2->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			static int invtime = 0;  //��boss��ײ���ж��ݵ��޵�ʱ��
			if (invtime == 0)
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
				pboscol2->bosslife -= 5;
				if (Invincible == 0 && shield == 0)
				{
					mylife -= 10;
				}
				if (mylife <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
				if (pboscol2->bosslife <= 0)
				{
					m_ObjList[enBOSS2].RemoveAt(bPos2);
					//bossnum = 0;
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
					delete pboscol2;
					SetStage(++stage);
					ncreatorboss = 400;
					break;
				}
			}
			invtime++;
			if (invtime == 20)
				invtime = 0;
		}
	}
	//boss2�����Ż�
	for (bPos1 = m_ObjList[enBOSS2].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS2* pboscol = (CBOSS2*)m_ObjList[enBOSS2].GetNext(bPos1);
		CRect bRect = pboscol->GetRect();
		CRect tmpRect;
		if (m_pWingmanLeft != NULL)
		{
			CRect wRect = m_pWingmanLeft->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanLeft->life -= 10;
				}
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}
			}
		}
		if (m_pWingmanRight != NULL)
		{
			CRect wRect = m_pWingmanRight->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));
				
				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanRight->life -= 10;
				}
				if (m_pWingmanRight->life <= 0)
				{
					delete m_pWingmanRight;
					m_pWingmanRight = NULL;
					break;
				}
			}
		}

	}



	//BOSS3����ս��
	for (bPos1 = m_ObjList[enBOSS3].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS3* pboscol3 = (CBOSS3*)m_ObjList[enBOSS3].GetNext(bPos1);
		CRect bRect = pboscol3->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			static int invtime = 0;  //��boss��ײ���ж��ݵ��޵�ʱ��
			if (invtime == 0)
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
				pboscol3->bosslife -= 5;
				if (Invincible == 0 && shield == 0)
				{
					mylife -= 10;
				}
				if (mylife <= 0)
				{
					delete m_pMe;
					m_pMe = NULL;
					break;
				}
				if (pboscol3->bosslife <= 0)
				{
					m_ObjList[enBOSS3].RemoveAt(bPos2);
					//bossnum = 0;
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));
					delete pboscol3;
					SetStage(++stage);
					ncreatorboss = 400;
					break;
				}
			}
			invtime++;
			if (invtime == 20)
				invtime = 0;
		}
	}
	//boss3�����Ż�
	for (bPos1 = m_ObjList[enBOSS3].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBOSS3* pboscol = (CBOSS3*)m_ObjList[enBOSS3].GetNext(bPos1);
		CRect bRect = pboscol->GetRect();
		CRect tmpRect;
		if (m_pWingmanLeft != NULL)
		{
			CRect wRect = m_pWingmanLeft->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanLeft->life -= 10;
				}
				if (m_pWingmanLeft->life <= 0)
				{
					delete m_pWingmanLeft;
					m_pWingmanLeft = NULL;
					break;
				}
			}
		}
		if (m_pWingmanRight != NULL)
		{
			CRect wRect = m_pWingmanRight->GetRect();
			if (tmpRect.IntersectRect(&bRect, wRect))
			{
				m_ObjList[enExplosion].AddTail(new CExplosion(wRect.left, wRect.top));

				if (Invincible == 0 && shield == 0)
				{
					m_pWingmanRight->life -= 10;
				}
				if (m_pWingmanRight->life <= 0)
				{
					delete m_pWingmanRight;
					m_pWingmanRight = NULL;
					break;
				}
			}
		}

	}



		//��ҳԵ���������
		for (bPos1 = m_ObjList[enGiftwp].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CGiftWeapon* gfwp = (CGiftWeapon*)m_ObjList[enGiftwp].GetNext(bPos1);
			CRect bRect = gfwp->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				if (weaponlevel < 3)
					weaponlevel++;
				m_ObjList[enGiftwp].RemoveAt(bPos2);
				delete gfwp;


			}
		}

		//��ҳԵ�Ѫ��
		for (bPos1 = m_ObjList[enGiftlf].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CGiftLife* gflf = (CGiftLife*)m_ObjList[enGiftlf].GetNext(bPos1);
			CRect bRect = gflf->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				mylife += 20;
				if (mylife > 50)
					mylife = 50;

				m_ObjList[enGiftlf].RemoveAt(bPos2);
				delete gflf;
			}
		}

		//��ҳԵ�����
		for (bPos1 = m_ObjList[enGiftShield].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CGiftShield* gfsd = (CGiftShield*)m_ObjList[enGiftShield].GetNext(bPos1);
			CRect bRect = gfsd->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				m_ObjList[enGiftShield].RemoveAt(bPos2);
				delete gfsd;

				if (m_pShield == NULL)
					m_pShield = new CShield;
				shield = 1;
				shieldtime = 200;
			}
		}

		//��ҳԵ��Ż�����
		for (bPos1 = m_ObjList[enGiftwm].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CGiftWM* gfwm = (CGiftWM*)m_ObjList[enGiftwm].GetNext(bPos1);
			CRect bRect = gfwm->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				m_ObjList[enGiftwm].RemoveAt(bPos2);
				delete gfwm;

				if (m_pWingmanLeft == NULL)
				{
					m_pWingmanLeft = new CWingman();
				}
				else if (m_pWingmanRight == NULL)
				{
					m_pWingmanRight = new CWingman();
				}

				/*if (m_pShield == NULL)
					m_pShield = new CShield;
				shield = 1;*/
				//shieldtime = 200;
			}
		}




		/*�����ǵ����յ��������ж�*/



		//ս������ը���л�
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;

					//ɾ���л�


					m_ObjList[enEnemy].RemoveAt(ePos2);
					score++;
					delete pEnemy;


					break;

				}
			}
		}

		//�Ż�����ը���л�
		//POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb1* pBomb1 = (CBomb1*)m_ObjList[enBomb1].GetNext(mPos1);
			CRect bRect = pBomb1->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);
					//ɾ������
					m_ObjList[enBomb1].RemoveAt(mPos2);
					delete pBomb1;
					//ɾ���л�
					m_ObjList[enEnemy].RemoveAt(ePos2);
					score++;
					delete pEnemy;
					break;
				}
			}
		}



		mPos1 = NULL, mPos2 = NULL;

		//ս����������BOSS
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos1);
				CRect mRect = pBOSS->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS->bosslife -= 1;

					if (pBOSS->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS].RemoveAt(ePos2);
						score += 10;
						delete pBOSS;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}

		//ս����������BOSS2
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS2* pBOSS2 = (CBOSS2*)m_ObjList[enBOSS2].GetNext(ePos1);
				CRect mRect = pBOSS2->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS2->bosslife -= 1;

					if (pBOSS2->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS2].RemoveAt(ePos2);
						score += 10;
						delete pBOSS2;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}


		//ս����������BOSS3
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS3* pBOSS3 = (CBOSS3*)m_ObjList[enBOSS3].GetNext(ePos1);
				CRect mRect = pBOSS3->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS3->bosslife -= 1;

					if (pBOSS3->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS3].RemoveAt(ePos2);
						score += 10;
						delete pBOSS3;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}

		//�Ż���������BOSS
		for (mPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb1* pBomb1 = (CBomb1*)m_ObjList[enBomb1].GetNext(mPos1);
			CRect bRect = pBomb1->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos1);
				CRect mRect = pBOSS->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb1].RemoveAt(mPos2);
					delete pBomb1;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS->bosslife -= 1;

					if (pBOSS->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS].RemoveAt(ePos2);
						score += 10;
						delete pBOSS;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}

		//�Ż���������BOSS2
		for (mPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb1* pBomb1 = (CBomb1*)m_ObjList[enBomb1].GetNext(mPos1);
			CRect bRect = pBomb1->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS2* pBOSS2 = (CBOSS2*)m_ObjList[enBOSS2].GetNext(ePos1);
				CRect mRect = pBOSS2->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb1].RemoveAt(mPos2);
					delete pBomb1;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS2->bosslife -= 1;

					if (pBOSS2->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS2].RemoveAt(ePos2);
						score += 10;
						delete pBOSS2;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}


		//�Ż���������BOSS3
		for (mPos1 = m_ObjList[enBomb1].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb1* pBomb1 = (CBomb1*)m_ObjList[enBomb1].GetNext(mPos1);
			CRect bRect = pBomb1->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS3* pBOSS3 = (CBOSS3*)m_ObjList[enBOSS3].GetNext(ePos1);
				CRect mRect = pBOSS3->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//ɾ������
					m_ObjList[enBomb1].RemoveAt(mPos2);
					delete pBomb1;
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					pBOSS3->bosslife -= 1;

					if (pBOSS3->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS3].RemoveAt(ePos2);
						score += 10;
						delete pBOSS3;
						//bossnum = 0;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}

				}
			}
		}





		//��Ҽ��ܹ����л�
		for (mPos1 = m_ObjList[enSkill].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CSkill* pSkill = (CSkill*)m_ObjList[enSkill].GetNext(mPos1);
			CRect bRect = pSkill->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(
						new CExplosion(mRect.left, mRect.top)
					);

					//ɾ���л�
					m_ObjList[enEnemy].RemoveAt(ePos2);
					score++;
					delete pEnemy;
					break;
				}
			}
		}


		//��Ҽ��ܹ���boss
		for (mPos1 = m_ObjList[enSkill].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CSkill* pSkill = (CSkill*)m_ObjList[enSkill].GetNext(mPos1);
			CRect bRect = pSkill->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS* pBOSS = (CBOSS*)m_ObjList[enBOSS].GetNext(ePos1);
				CRect mRect = pBOSS->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{
					static int i = 0;
					if (i == 0)
						pBOSS->bosslife -= 1;
					i++;
					if (i >= 8)
						i = 0;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					if (pBOSS->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS].RemoveAt(ePos2);
						score += 10;
						delete pBOSS;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}
				}
			}
		}
		
		//��Ҽ��ܹ���boss2
		for (mPos1 = m_ObjList[enSkill].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CSkill* pSkill = (CSkill*)m_ObjList[enSkill].GetNext(mPos1);
			CRect bRect = pSkill->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS2* pBOSS2 = (CBOSS2*)m_ObjList[enBOSS2].GetNext(ePos1);
				CRect mRect = pBOSS2->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{

					static int i = 0;
					if (i == 0)
						pBOSS2->bosslife -= 1;
					i++;
					if (i >= 8)
						i = 0;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					if (pBOSS2->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS2].RemoveAt(ePos2);
						score += 10;
						delete pBOSS2;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}
				}
			}
		}
		
		
		//��Ҽ��ܹ���boss3
		for (mPos1 = m_ObjList[enSkill].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CSkill* pSkill = (CSkill*)m_ObjList[enSkill].GetNext(mPos1);
			CRect bRect = pSkill->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBOSS3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CBOSS3* pBOSS3 = (CBOSS3*)m_ObjList[enBOSS3].GetNext(ePos1);
				CRect mRect = pBOSS3->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{

					static int i = 0;
					if (i == 0)
						pBOSS3->bosslife -= 1;
					i++;
					if (i >= 8)
						i = 0;

					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(bRect.left, bRect.top));

					if (pBOSS3->bosslife <= 0)
					{
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
						//ɾ��boss
						m_ObjList[enBOSS3].RemoveAt(ePos2);
						score += 10;
						delete pBOSS3;
						SetStage(++stage);
						ncreatorboss = 400;
						break;
					}
				}
			}
		}



}


void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	if (GetKey('P') == 1)//������p��
	{
		if (ispause <= 0 && pausetrue == 1)
			pausetrue = 0;
		else
			if (ispause <= 0 && pausetrue == 0)
			{
				pausetrue = 1;
			}
		ispause = 3;
	}

	ispause--;

	if (pausetrue == 1)
	{
		//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
		UpdateFrame(m_pMemDC);

		if (delay != 0)
			delay++;
		if (delay > 10)
			delay = 0;

		if (shieldtime > 0)    //����ʱ��
			shieldtime--;
		if (shieldtime == 0)
			shield = 0;

		AI();
	}
	CView::OnTimer(nIDEvent);
}


void CPlaneGameView::SetStage(int s)  //���ùؿ�
{
	stage = s;
	bossnum = 0;
	if (stage <= 3)
	{
		selectbackground = stage;
		selectboss = stage;
	}
		
	else
	{
		selectbackground = rand() % 5 + 1;
		selectboss = rand() % 3 + 1;
	}
		
}