
// GizmoTool_Ver_DigDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "GizmoTool_Ver_Dig.h"
#include "GizmoTool_Ver_DigDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BASIC_PLANE 50
#define MAINVIEW_LEFT 617
#define MAINVIEW_TOP 42

#define MARGIN_LEFT 30
#define MARGIN_TOP 30
#define MARGIN_VERTICAL 1
#define MARGIN_HORIZONTAL 1

#define SIDE
#define TOP
#define MAIN

GLfloat color_10px_Line[4] = {0.3f,0.8f,0.8f,0.4f};
GLfloat color_1px_Line[4] = {0.8f, 0.8f, 0.8f, 0.3f};
GLfloat color_Background[4] = {0.24f, 0.24f, 0.24f, 0.05f};

GLfloat color_View_Background[4] = {0.04f, 0.14f, 0.2f, 0.0f}; //0.24f, 0.24f, 0.24f, 0.0f

enum{mainView, topView, sideView};
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CGizmoTool_Ver_DigDlg 대화 상자




CGizmoTool_Ver_DigDlg::CGizmoTool_Ver_DigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGizmoTool_Ver_DigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGizmoTool_Ver_DigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN, picture_Ctrl_MAINVIEW);
	DDX_Control(pDX, IDC_POS_X, edit_Pos_X);
	DDX_Control(pDX, IDC_POS_Y, edit_Pos_Y);
	DDX_Control(pDX, IDC_POS_Z, edit_Pos_Z);
	DDX_Control(pDX, IDC_ROT_X, edit_Rot_X);
	DDX_Control(pDX, IDC_ROT_Y, edit_Rot_Y);
	DDX_Control(pDX, IDC_ROT_Z, edit_Rot_Z);
	DDX_Control(pDX, IDC_SCL_X, edit_Scl_X);
	DDX_Control(pDX, IDC_SCL_Y, edit_Scl_Y);
	DDX_Control(pDX, IDC_SCL_Z, edit_Scl_Z);
	DDX_Control(pDX, IDC_ID, edit_ID);
	DDX_Control(pDX, IDC_BTN_CUBE, btn_Add_CUBE);
	DDX_Control(pDX, IDC_LIST2, listBox_Object);
	DDX_Control(pDX, IDC_BTN_SPHERE, btn_Add_SPHERE);
	DDX_Control(pDX, IDC_FRAME, edit_Frame);
	DDX_Control(pDX, IDC_FRAME_SLIDER, slider_AniamteFrame);
	DDX_Control(pDX, IDC_CURRENT_FRAME, edit_Current_Frame);
	DDX_Control(pDX, IDC_BTN_UNDO, btn_Undo);
	DDX_Control(pDX, IDC_BTN_REDO, btn_Redo);
	DDX_Control(pDX, IDC_PLAY, btn_Play);
	DDX_Control(pDX, IDC_TOP, picture_Ctrl_TOPVIEW);
	DDX_Control(pDX, IDC_SIDE, picture_Ctrl_SIDEVIEW);
	DDX_Control(pDX, IDC_MOUSE_POS, edit_Pos_Mouse);
}

BEGIN_MESSAGE_MAP(CGizmoTool_Ver_DigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_F, &CGizmoTool_Ver_DigDlg::OnKey_F)
//	ON_COMMAND(IDC_UP, &CGizmoTool_Ver_DigDlg::OnKey_UP)
	ON_COMMAND(IDC_DOWN, &CGizmoTool_Ver_DigDlg::OnKey_Down)
	ON_COMMAND(IDC_UP, &CGizmoTool_Ver_DigDlg::OnKey_Up)
	ON_COMMAND(IDC_RIGHT, &CGizmoTool_Ver_DigDlg::OnKey_Right)
	ON_COMMAND(IDC_LEFT, &CGizmoTool_Ver_DigDlg::OnKey_Left)
	ON_COMMAND(IDC_X, &CGizmoTool_Ver_DigDlg::OnKey_X)
	ON_COMMAND(IDC_Z, &CGizmoTool_Ver_DigDlg::OnKey_Z)
	ON_COMMAND(IDC_Q, &CGizmoTool_Ver_DigDlg::OnKey_Q)
	ON_COMMAND(IDC_O, &CGizmoTool_Ver_DigDlg::OnKey_O)
	ON_COMMAND(IDC_W, &CGizmoTool_Ver_DigDlg::OnKey_W)
	ON_COMMAND(IDC_E, &CGizmoTool_Ver_DigDlg::OnKey_E)
	ON_COMMAND(IDC_R, &CGizmoTool_Ver_DigDlg::OnKey_R)
	ON_COMMAND(IDC_ALT, &CGizmoTool_Ver_DigDlg::OnKey_Alt)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_CUBE, &CGizmoTool_Ver_DigDlg::OnBnClickedBtnCube)
	ON_EN_KILLFOCUS(IDC_POS_X, &CGizmoTool_Ver_DigDlg::OnEnKillfocusPosX)
	ON_EN_KILLFOCUS(IDC_POS_Y, &CGizmoTool_Ver_DigDlg::OnEnKillfocusPosY)
	ON_EN_KILLFOCUS(IDC_POS_Z, &CGizmoTool_Ver_DigDlg::OnEnKillfocusPosZ)
	ON_EN_KILLFOCUS(IDC_ROT_X, &CGizmoTool_Ver_DigDlg::OnEnKillfocusRotX)
	ON_EN_KILLFOCUS(IDC_ROT_Y, &CGizmoTool_Ver_DigDlg::OnEnKillfocusRotY)
	ON_EN_KILLFOCUS(IDC_ROT_Z, &CGizmoTool_Ver_DigDlg::OnEnKillfocusRotZ)
	ON_EN_KILLFOCUS(IDC_SCL_X, &CGizmoTool_Ver_DigDlg::OnEnKillfocusSclX)
	ON_EN_KILLFOCUS(IDC_SCL_Y, &CGizmoTool_Ver_DigDlg::OnEnKillfocusSclY)
	ON_EN_KILLFOCUS(IDC_SCL_Z, &CGizmoTool_Ver_DigDlg::OnEnKillfocusSclZ)
	ON_COMMAND(ID_ENTER, &CGizmoTool_Ver_DigDlg::OnKey_Enter)
	ON_COMMAND(ID_DELETE, &CGizmoTool_Ver_DigDlg::OnKey_Delete)
	ON_COMMAND(IDC_C, &CGizmoTool_Ver_DigDlg::OnKey_C)
	ON_EN_KILLFOCUS(IDC_ID, &CGizmoTool_Ver_DigDlg::OnEnKillfocusId)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_SPHERE, &CGizmoTool_Ver_DigDlg::OnBnClickedBtnSphere)
	ON_COMMAND(ID_SPACE, &CGizmoTool_Ver_DigDlg::OnKey_Space)
	ON_LBN_DBLCLK(IDC_LIST2, &CGizmoTool_Ver_DigDlg::OnLbnDblclkList2)
	ON_LBN_KILLFOCUS(IDC_LIST2, &CGizmoTool_Ver_DigDlg::OnLbnKillfocusList2)
	ON_BN_CLICKED(IDC_BTN_LIGHT, &CGizmoTool_Ver_DigDlg::OnBnClickedBtnLight)
	ON_LBN_SELCHANGE(IDC_LIST2, &CGizmoTool_Ver_DigDlg::OnLbnSelchangeList2)
	ON_COMMAND(ID_CTRL_Z, &CGizmoTool_Ver_DigDlg::OnKey_CtrlZ)
	ON_COMMAND(ID_CTRL_Y, &CGizmoTool_Ver_DigDlg::OnKey_CtrlY)
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_PLAY, &CGizmoTool_Ver_DigDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_BTN_UNDO, &CGizmoTool_Ver_DigDlg::OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_REDO, &CGizmoTool_Ver_DigDlg::OnBnClickedBtnRedo)
	ON_COMMAND(IDC_P, &CGizmoTool_Ver_DigDlg::OnKey_P)
END_MESSAGE_MAP()


// CGizmoTool_Ver_DigDlg 메시지 처리기




BOOL CGizmoTool_Ver_DigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));



	
	main_camera = new Camera();
	//current_Camera = new Camera();
	current_Camera = main_camera;//
	
	top_camera = new Camera(vector3f(0,30,1),vector3f(0,0,0),vector3f(0,1,0));
	//top_camera->Set_cameraView_Perspective_Ortho(TRUE); //TOPVIEW는 ORTHO로 시작

	side_camera = new Camera(vector3f(0,4,30),vector3f(0,0,0),vector3f(0,1,0));
	

	//std_Gizmo = new Gizmo();

	default_Camera = new Camera();

		check_MouseView = FALSE;
		bound_Line = FALSE;bound_horizontal_Line = FALSE;
		check_bound_Line = FALSE;
		check_bound_horizontal_Line = FALSE;

		light_OnOff = TRUE;
		check_Object_Transform = FALSE;
		check_CenterGizmo_Transform = FALSE;
		check_Draw_centerGizmo = FALSE;
		check_DrawRectangle = FALSE;

		check_Play_Animate = FALSE;
		count_Frame = 0;
		edit_Frame.SetWindowTextW(_T("200"));

		check_Key_Q = FALSE;
		check_Key_Z = FALSE;
		check_Key_X = FALSE;
		check_Key_P = FALSE;

		check_MainFocus = TRUE;
		check_TopFocus = FALSE;
		check_SideFocus = FALSE;

		m_ptStart.SetPoint(0,0);
		m_ptEnd.SetPoint(0,0);

		basic_Plane_Point.top = -5;
		basic_Plane_Point.left = -5;
		basic_Plane_Point.width = 10;
		basic_Plane_Point.height = 10;

		//selectedObject_INDEX = -1;
		
		gl_ObjectType = GL_TRIANGLE_FAN; //GL_TRIANGLE_STRIP
	
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		//TRACE("%d, %d\n", width, height);

		buffer_for_blk_main = new GLfloat[70*70*4];
		buffer_for_blk_top = new GLfloat[70*70*4];
		buffer_for_blk_side = new GLfloat[70*70*4];
		
		GetDlgItem(IDC_MAIN)->GetWindowRect(&sizeRect[mainView]);
        ScreenToClient( &sizeRect[mainView] );
		main_camera->set_Client_Rect(sizeRect[mainView]);
		//TRACE("main %d, %d, %d, %d, %d, %d\n", sizeRect[0].left, sizeRect[0].top, sizeRect[0].right, sizeRect[0].bottom, sizeRect[0].Width(), sizeRect[0].Height());
	
		GetDlgItem(IDC_TOP)->GetWindowRect(&sizeRect[topView]);
        ScreenToClient( &sizeRect[topView] );
		top_camera->set_Client_Rect(sizeRect[topView]);
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect[1].left, sizeRect[1].top, sizeRect[1].right, sizeRect[1].bottom, sizeRect[1].Width(), sizeRect[1].Height());

		GetDlgItem(IDC_SIDE)->GetWindowRect(&sizeRect[sideView]);
        ScreenToClient( &sizeRect[sideView] );
        side_camera->set_Client_Rect(sizeRect[sideView]);
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect[2].left, sizeRect[2].top, sizeRect[2].right, sizeRect[2].bottom, sizeRect[2].Width(), sizeRect[2].Height());


		GetDlgItem(IDC_MAIN_GIZMO)->MoveWindow(sizeRect[mainView].left,sizeRect[mainView].top,70,70);
		GetDlgItem(IDC_MAIN_GIZMO)->GetWindowRect(&sizeRect_GIZMO[mainView]);
        ScreenToClient( &sizeRect_GIZMO[mainView] );	
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect_GIZMO[0].left, sizeRect_GIZMO[0].top, sizeRect_GIZMO[0].right, sizeRect_GIZMO[0].bottom, sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height());

		GetDlgItem(IDC_TOP_GIZMO)->MoveWindow(sizeRect[topView].left,sizeRect[topView].top,70,70);
		GetDlgItem(IDC_TOP_GIZMO)->GetWindowRect(&sizeRect_GIZMO[topView]);
        ScreenToClient( &sizeRect_GIZMO[topView] );		 
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect_GIZMO[0].left, sizeRect_GIZMO[0].top, sizeRect_GIZMO[0].right, sizeRect_GIZMO[0].bottom, sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height());
		
		GetDlgItem(IDC_SIDE_GIZMO)->MoveWindow(sizeRect[sideView].left,sizeRect[sideView].top,70,70);
		GetDlgItem(IDC_SIDE_GIZMO)->GetWindowRect(&sizeRect_GIZMO[sideView]);
        ScreenToClient( &sizeRect_GIZMO[sideView] );		 

		
		GetDlgItem(IDC_MAIN)->ModifyStyle(0,WS_DLGFRAME);
		GetDlgItem(IDC_TOP)->ModifyStyle(0,WS_BORDER);
		GetDlgItem(IDC_SIDE)->ModifyStyle(0,WS_BORDER);


		MoveWindow(0,0,width-200,height-100);
		
	InitGL();
	
	SetTimer(1,33,0);

	btn_Add_CUBE.LoadBitmaps(IDB_CUBE,IDB_CUBE_CLICKED, NULL, NULL);
	btn_Add_CUBE.SizeToContent();

	btn_Add_SPHERE.LoadBitmaps(IDB_SPHERE,IDB_SPHERE_CLICKED, NULL, NULL);
	btn_Add_SPHERE.SizeToContent();

		objectID = 0;

		save_EditEvent();

		inf_plane.set(0,0,0);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGizmoTool_Ver_DigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGizmoTool_Ver_DigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialogEx::OnPaint();
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGizmoTool_Ver_DigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----------------------------------------------------------------------------------


void CGizmoTool_Ver_DigDlg::InitGL(){

			int pixelformat;
			m_hDC[0] = new CClientDC(GetDlgItem(IDC_MAIN));
			m_hDC[1] = new CClientDC(GetDlgItem(IDC_TOP));
			m_hDC[2] = new CClientDC(GetDlgItem(IDC_SIDE));
			m_hDC_GIZMO[0] = new CClientDC(GetDlgItem(IDC_MAIN_GIZMO));
			m_hDC_GIZMO[1] = new CClientDC(GetDlgItem(IDC_TOP_GIZMO));
			m_hDC_GIZMO[2] = new CClientDC(GetDlgItem(IDC_SIDE_GIZMO));

		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR), // sizeof
			1,// default version
			PFD_DRAW_TO_WINDOW|
			PFD_SUPPORT_OPENGL|
			PFD_GENERIC_FORMAT|
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0,0,0,0,0,0, // color bits ignored
			8,
			0,
			8,
			0,0,0,0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
		};


		pixelformat = ChoosePixelFormat(m_hDC[0]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC[0]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC[0] = wglCreateContext(m_hDC[0]->GetSafeHdc());
		VERIFY(wglMakeCurrent(m_hDC[0]->GetSafeHdc(),m_hRC[0]));

		pixelformat = ChoosePixelFormat(m_hDC[1]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC[1]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC[1] = wglCreateContext(m_hDC[1]->GetSafeHdc());
		//VERIFY(wglMakeCurrent(m_hDC[1]->GetSafeHdc(),m_hRC[1]));

		pixelformat = ChoosePixelFormat(m_hDC[2]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC[2]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC[2] = wglCreateContext(m_hDC[2]->GetSafeHdc());
		//VERIFY(wglMakeCurrent(m_hDC[2]->GetSafeHdc(),m_hRC[2]));


		pixelformat = ChoosePixelFormat(m_hDC_GIZMO[0]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC_GIZMO[0]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC_GIZMO[0] = wglCreateContext(m_hDC_GIZMO[0]->GetSafeHdc());

		pixelformat = ChoosePixelFormat(m_hDC_GIZMO[1]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC_GIZMO[1]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC_GIZMO[1] = wglCreateContext(m_hDC_GIZMO[1]->GetSafeHdc());

		pixelformat = ChoosePixelFormat(m_hDC_GIZMO[2]->GetSafeHdc(), &pfd);
		VERIFY(SetPixelFormat(m_hDC_GIZMO[2]->GetSafeHdc(),pixelformat,&pfd));
		m_hRC_GIZMO[2] = wglCreateContext(m_hDC_GIZMO[2]->GetSafeHdc());


	
}

void CGizmoTool_Ver_DigDlg::ReSizeGLScene(GLsizei width, GLsizei height, GLenum viewNumber){
		if(height == 0)
			height = 1;
	//if(viewNumber == mainView)
		glViewport(0,0,width,height);

		GLfloat aspect;
		//if(height >= width)
			aspect = (GLfloat)width/(GLfloat)height;
		//else
		//	aspect =    (GLfloat)height/(GLfloat)width;

		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		if(viewNumber == mainView){
			main_camera->setOrtho(-sizeRect[mainView].Width()/64,sizeRect[mainView].Width()/64,-sizeRect[mainView].Height()/64,sizeRect[mainView].Height()/64,0.1,1000);
			main_camera->setPerspective(60.f, aspect, 0.1f, 1000.f);
			main_camera->cameraView();
			
		}
		else if(viewNumber == topView){
			
			top_camera->setOrtho(-sizeRect[topView].Width()/32,sizeRect[topView].Width()/32,-sizeRect[topView].Height()/32,sizeRect[topView].Height()/32,0.1,1000);
			top_camera->setPerspective(60.f, aspect, 0.1f, 1000.f);
			top_camera->cameraView();
			
		}
		else if(viewNumber == sideView){
			
			side_camera->setOrtho(-sizeRect[sideView].Width()/32,sizeRect[sideView].Width()/32,-sizeRect[sideView].Height()/32,sizeRect[sideView].Height()/32,0.1,1000);
			side_camera->setPerspective(60.f, aspect, 0.1f, 1000.f);
			side_camera->cameraView();
		}
		


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

void CGizmoTool_Ver_DigDlg::basic_Plane(Camera *view_Camera){ 

		GLfloat center_View_x = 0.f;
		GLfloat center_View_z = 0.f;
		int gab = 1;
		int plane_Max;
		GLfloat camera_height;

		vector3f lookVec = view_Camera->getLookVector();

		GLfloat temp = - view_Camera->pos_eye.y / lookVec.y;

		center_View_x = view_Camera->pos_eye.x + temp * lookVec.x;
		center_View_z = view_Camera->pos_eye.z + temp * lookVec.z;

		if(center_View_z < view_Camera->pos_eye.z - BASIC_PLANE/5)
			center_View_z = view_Camera->pos_eye.z - BASIC_PLANE/5;
		else if(center_View_z > view_Camera->pos_eye.z + BASIC_PLANE/5)
			center_View_z = view_Camera->pos_eye.z + BASIC_PLANE/5;
		if(center_View_x < view_Camera->pos_eye.x - BASIC_PLANE/5)
			center_View_x = view_Camera->pos_eye.x - BASIC_PLANE/5;
		else if(center_View_x > view_Camera->pos_eye.x + BASIC_PLANE/5)
			center_View_x = view_Camera->pos_eye.x + BASIC_PLANE/5;
		/*
		if(center_View_z < -BASIC_PLANE/5)
			center_View_z = -BASIC_PLANE/5;
		else if(center_View_z > BASIC_PLANE/5)
			center_View_z = BASIC_PLANE/5;
		if(center_View_x < -BASIC_PLANE/5)
			center_View_x = -BASIC_PLANE/5;
		else if(center_View_x > BASIC_PLANE/5)
			center_View_x = BASIC_PLANE/5;
			*/

		camera_height = sqrt(view_Camera->pos_eye.y * view_Camera->pos_eye.y);
		plane_Max = camera_height/10 + 1;
		//TRACE("%f , %d\n", sqrt(pos_eye.y * pos_eye.y), plane_Max);

		basic_Plane_Point.top = center_View_z - BASIC_PLANE*plane_Max/2 ;
		basic_Plane_Point.height = center_View_z + BASIC_PLANE*plane_Max/2 ;

		basic_Plane_Point.width = center_View_x + BASIC_PLANE*plane_Max/2;
		basic_Plane_Point.left = center_View_x - BASIC_PLANE*plane_Max/2;

		glColor4fv(color_1px_Line);
		glBegin(GL_LINES);
		for(int j = basic_Plane_Point.top ; j <= basic_Plane_Point.height ; j += gab ){
			if( j%10 == 0)
				glColor4fv(color_10px_Line);
		
			glVertex3f(basic_Plane_Point.left, 0.001f , j);
			glVertex3f(basic_Plane_Point.width , 0.001f , j);
			glColor4fv(color_1px_Line);
		}
		for(int i = basic_Plane_Point.left ; i <= basic_Plane_Point.width ; i += gab){
			if( i%10 == 0)
				glColor4fv(color_10px_Line);
			glVertex3f(i, 0.001f , basic_Plane_Point.top);
			glVertex3f(i , 0.001f , basic_Plane_Point.height);
			glColor4fv(color_1px_Line);
		}
		glEnd();


		if(check_Key_Z || check_DrawRectangle){
			glColor4fv(color_Background);
			glBegin(GL_QUADS);
			glVertex3f(basic_Plane_Point.left, 0.f , basic_Plane_Point.top);
			glVertex3f( basic_Plane_Point.left , 0.f ,basic_Plane_Point.height);
			glVertex3f(basic_Plane_Point.width, 0.f ,basic_Plane_Point.height);
			glVertex3f(basic_Plane_Point.width, 0.f , basic_Plane_Point.top);
			glEnd();
		}

	}

void CGizmoTool_Ver_DigDlg::drag_Box(){

		 glPushMatrix();
		vector3f start = fromMouseToWorld(m_ptStart, current_Camera->projection, current_Camera->modelView, current_Camera->viewPort); 
		vector3f end = fromMouseToWorld(m_ptEnd, current_Camera->projection, current_Camera->modelView, current_Camera->viewPort); 
		vector3f start_end =  fromMouseToWorld(CPoint(m_ptStart.x , m_ptEnd.y), current_Camera->projection, current_Camera->modelView, current_Camera->viewPort); 
		vector3f end_start =  fromMouseToWorld(CPoint(m_ptEnd.x , m_ptStart.y), current_Camera->projection, current_Camera->modelView, current_Camera->viewPort); 

		 glDisable(GL_DEPTH_TEST);
		 glColor4f(0.2f,0.4f,0.6f,0.4f);
			glBegin(GL_QUADS);
				glVertex3f(start.x, start.y, start.z);
				glVertex3f(start_end.x, start_end.y, start_end.z);
				glVertex3f(end.x, end.y, end.z);
				glVertex3f(end_start.x, end_start.y, end_start.z);
			glEnd();
		glEnable(GL_DEPTH_TEST);
		 glPopMatrix();
		
}

void CGizmoTool_Ver_DigDlg::DrawScene(){

	if(light_OnOff){
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat lightPos[] = { 0.0f, 20.0f, 0.0f, 1.0f };
		//GLfloat lightDir[] = { 0.0f, 0.0f, 0.0f, 0.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		 glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		 glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		 // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
	}




		//basic_Plane(current_Camera);
		//glPushMatrix();
		if(selectedObject_INDEX_Array.size() > 1){
			//clearObjectInformEdit();
			vector3f centerOfObj(0,0,0);
			centerOfObjects_Gizmo.current_Camera = *current_Camera;
			if(!check_Draw_centerGizmo){
				for(int i = 0; i < selectedObject_INDEX_Array.size() ; i++){
					object_Array[selectedObject_INDEX_Array[i]].check_DrawGizmo = FALSE;
					object_Array[selectedObject_INDEX_Array[i]].gizmo.translate_INIT = object_Array[selectedObject_INDEX_Array[i]].gizmo.translate;
					object_Array[selectedObject_INDEX_Array[i]].gizmo.scale_INIT = object_Array[selectedObject_INDEX_Array[i]].gizmo.scale;
					object_Array[selectedObject_INDEX_Array[i]].gizmo.rotate_INIT = object_Array[selectedObject_INDEX_Array[i]].gizmo.rotate;
					centerOfObj = centerOfObj + object_Array[selectedObject_INDEX_Array[i]].center;
				}	
				centerOfObjects_Gizmo.center = vector3f(centerOfObj.x/selectedObject_INDEX_Array.size(), centerOfObj.y/selectedObject_INDEX_Array.size(), centerOfObj.z/selectedObject_INDEX_Array.size());
				centerOfObjects_Gizmo.translate_INIT = vector3f(centerOfObj.x/selectedObject_INDEX_Array.size(), centerOfObj.y/selectedObject_INDEX_Array.size(), centerOfObj.z/selectedObject_INDEX_Array.size());
				centerOfObjects_Gizmo.translate = centerOfObjects_Gizmo.translate_INIT ;
				//temp = centerOfObjects_Gizmo;
			}
				/*
				if(centerOfObjects_Gizmo.key_check_R){
					temp.stack_Rotate.assign(centerOfObjects_Gizmo.stack_Rotate.begin(), centerOfObjects_Gizmo.stack_Rotate.end());
					for(int i = 0 ; i < centerOfObjects_Gizmo.stack_Rotate.size() ; i++){
						temp.stack_Rotate[i].angle = centerOfObjects_Gizmo.stack_Rotate[i].angle;
						temp.stack_Rotate[i].axis = centerOfObjects_Gizmo.stack_Rotate[i].axis;
					}
					centerOfObjects_Gizmo.stack_Rotate = object_Array[selectedObject_INDEX_Array[0]].gizmo.stack_Rotate;
				}
				else{
					if(temp.stack_Rotate.size() != 0){
						TRACE("ASD\n");
						centerOfObjects_Gizmo.stack_Rotate.clear();
						centerOfObjects_Gizmo.stack_Rotate.assign(temp.stack_Rotate.begin(), temp.stack_Rotate.end());
						for(int i = 0 ; i < temp.stack_Rotate.size() ; i++){
							centerOfObjects_Gizmo.stack_Rotate[i].angle = temp.stack_Rotate[i].angle;
							centerOfObjects_Gizmo.stack_Rotate[i].axis = temp.stack_Rotate[i].axis;
						}
					}
					temp.stack_Rotate.clear();
				}
			*/

			for(int i = 0; i < selectedObject_INDEX_Array.size() ; i++){
				object_Array[selectedObject_INDEX_Array[i]].gizmo.scale = object_Array[selectedObject_INDEX_Array[i]].gizmo.scale_INIT + (centerOfObjects_Gizmo.scale - vector3f(1,1,1));
			
				object_Array[selectedObject_INDEX_Array[i]].gizmo.key_check_E = centerOfObjects_Gizmo.key_check_E;
				object_Array[selectedObject_INDEX_Array[i]].gizmo.lbtnDown_X = centerOfObjects_Gizmo.lbtnDown_X; 
				object_Array[selectedObject_INDEX_Array[i]].gizmo.lbtnDown_Y = centerOfObjects_Gizmo.lbtnDown_Y; 
				object_Array[selectedObject_INDEX_Array[i]].gizmo.lbtnDown_Z = centerOfObjects_Gizmo.lbtnDown_Z; 
				object_Array[selectedObject_INDEX_Array[i]].gizmo.current_Rotate.angle = centerOfObjects_Gizmo.current_Rotate.angle;
				object_Array[selectedObject_INDEX_Array[i]].gizmo.current_Rotate.axis = centerOfObjects_Gizmo.current_Rotate.axis;

				if(centerOfObjects_Gizmo.key_check_E && ( centerOfObjects_Gizmo.lbtnDown_X ||  centerOfObjects_Gizmo.lbtnDown_Y||  centerOfObjects_Gizmo.lbtnDown_Z) ){
					object_Array[selectedObject_INDEX_Array[i]].gizmo.setCenter(centerOfObjects_Gizmo.setTranslate_afterRotate(selectedObject_INDEX_Array.size(), object_Array[selectedObject_INDEX_Array[i]].gizmo.center));				
					object_Array[selectedObject_INDEX_Array[i]].gizmo.translate_INIT = object_Array[selectedObject_INDEX_Array[i]].gizmo.translate;
					centerOfObjects_Gizmo.translate_INIT = centerOfObjects_Gizmo.translate;
				}
				else{
				}
				object_Array[selectedObject_INDEX_Array[i]].gizmo.setCenter(object_Array[selectedObject_INDEX_Array[i]].gizmo.translate_INIT + (centerOfObjects_Gizmo.translate -centerOfObjects_Gizmo.translate_INIT)) ;
				
			}	
			
			check_Draw_centerGizmo = TRUE;
		}
		else{
			Gizmo init_Gizmo;
			init_Gizmo.center.set(0,0,0);
			if(selectedObject_INDEX_Array.size()==1){
				init_Gizmo.center = object_Array[selectedObject_INDEX_Array[0]].center;
				//object_Array[selectedObject_INDEX_Array[0]].gizmo.setCenter(object_Array[selectedObject_INDEX_Array[0]].gizmo.translate);
			}
			centerOfObjects_Gizmo = init_Gizmo;			
			check_Draw_centerGizmo = FALSE;
			
		}
		//glPopMatrix();

		if(check_Play_Animate){
			CString str;
			GLfloat frame;
			edit_Frame.GetWindowTextW(str);
			frame = _ttof(str);

			slider_AniamteFrame.SetPos(count_Frame);
			str.Format(_T("%d"),count_Frame);
			edit_Current_Frame.SetWindowText(str);

			if(check_Play_Animate && count_Frame < frame){
				clearObjectInformEdit();
				play_animate((GLint) frame);
			}
			else if(check_Play_Animate && count_Frame == frame){
				load_Last_EditEvent();
				check_Play_Animate = FALSE;
				btn_Play.SetWindowTextW(_T("PLAY"));
				count_Frame = 0;
				slider_AniamteFrame.SetPos(count_Frame);
			}
		}
		else{
			if((undo_editEvent.size()) > 2)
				btn_Play.EnableWindow(TRUE);
			else
				btn_Play.EnableWindow(FALSE);
		}


		for(int i = 0; i < object_Array.size(); i++){
		
			glPushMatrix();
				object_Array[i].Draw();
			glPopMatrix();
	
		}
		for(int i = 0; i < object_Array.size(); i++){
		
			glPushMatrix();
			if(object_Array[i].check_SelectedObject && object_Array[i].check_DrawGizmo)
				object_Array[i].gizmo.DrawGizmo();
			glPopMatrix();
	
		}

		if(selectedObject_INDEX_Array.size() > 1){
			centerOfObjects_Gizmo.DrawGizmo();
		}

		//-----------------------------------------------
		if(undo_editEvent.size() > 1){
			btn_Undo.EnableWindow(TRUE);
		}
		else
			btn_Undo.EnableWindow(FALSE);

		if(redo_editEvent.size() > 0){
			btn_Redo.EnableWindow(TRUE);
		}
		else
			btn_Redo.EnableWindow(FALSE);


		if(check_Key_P){
			if(mouse_point3f.y < 0){
				glPushMatrix();
				glPointSize(10.f);
				glBegin(GL_POINTS);
				glVertex3f(inf_plane.x, inf_plane.y, inf_plane.z);
				glEnd();
				glPointSize(1.f);
				glPopMatrix();
				CString str;
				str.Format(_T("%f,  %f,  %f"), inf_plane.x, inf_plane.y, inf_plane.z);
				edit_Pos_Mouse.SetWindowTextW(str);
			}
			else
			{
				glPushMatrix();
				glPointSize(10.f);
				glBegin(GL_POINTS);
				glVertex3f(mouse_point3f.x, mouse_point3f.y, mouse_point3f.z);
				glEnd();
				glPointSize(1.f);
				glPopMatrix();
				CString str;
				str.Format(_T("%f,  %f,  %f"), mouse_point3f.x, mouse_point3f.y, mouse_point3f.z);
				edit_Pos_Mouse.SetWindowTextW(str);
			}
		}
		else{
			edit_Pos_Mouse.SetWindowTextW(_T(""));
		}
}

void CGizmoTool_Ver_DigDlg::OnSize(UINT nType, int cx, int cy)
{
	//CDialogEx::OnSize(nType, cx, cy);

	CRect Window_Rect;
	GetWindowRect(&Window_Rect);
	//TRACE("win %d, %d, %d, %d, %d, %d\n", Window_Rect.left, Window_Rect.top, Window_Rect.right, Window_Rect.bottom, Window_Rect.Width(), Window_Rect.Height());
	

		GLint move_Distancs = 0;
		CRect boundInform_Rect;
		GetDlgItem(IDC_BOUND_INFORM)->GetWindowRect(&boundInform_Rect);
        ScreenToClient( &boundInform_Rect );	
		move_Distancs = boundInform_Rect.left;

		GetDlgItem(IDC_BOUND_INFORM)->MoveWindow(Window_Rect.Width() - boundInform_Rect.Width() - 30,boundInform_Rect.top,boundInform_Rect.Width(), Window_Rect.Height()-boundInform_Rect.top- MARGIN_VERTICAL*3);

		GetDlgItem(IDC_BOUND_INFORM)->GetWindowRect(&boundInform_Rect);
        ScreenToClient( &boundInform_Rect );	
		move_Distancs -= boundInform_Rect.left;


		CRect rect_mouse;
		GetDlgItem(IDC_MOUSE_POS)->GetWindowRect(&rect_mouse);
		ScreenToClient( &rect_mouse );
		GetDlgItem(IDC_MOUSE_POS)->MoveWindow(boundInform_Rect.left, Window_Rect.Height() - rect_mouse.Height() - 30, rect_mouse.Width(), rect_mouse.Height());
	
		//TRACE("%d\n", move_Distancs);

		for(int i = IDC_ID ; i <= IDC_LIST2 ; i++){
			CRect rect;
			GetDlgItem(i)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(i)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height());
			GetDlgItem(i)->Invalidate(0);
		}
		for(int i = IDC_BTN_LIGHT ; i <= IDC_STATIC_14 ; i++){
			if(i == IDC_BOUND_INFORM)
				continue;

			CRect rect;
			GetDlgItem(i)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(i)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(i)->Invalidate(0);
		}
		//GetDlgItem(IDC_BOUND_INFORM)->Invalidate(1);
		
		{
			CRect rect;
			GetDlgItem(IDC_PLAY)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(IDC_PLAY)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(IDC_PLAY)->Invalidate(0);
			//CRect rect;
			GetDlgItem(IDC_FRAME)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(IDC_FRAME)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(IDC_FRAME)->Invalidate(0);
			//CRect rect;
			GetDlgItem(IDC_FRAME_SLIDER)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(IDC_FRAME_SLIDER)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(IDC_FRAME_SLIDER)->Invalidate(0);

			GetDlgItem(IDC_BTN_UNDO)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(IDC_BTN_UNDO)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(IDC_BTN_UNDO)->Invalidate(0);

			GetDlgItem(IDC_BTN_REDO)->GetWindowRect(&rect);
			ScreenToClient( &rect );
			GetDlgItem(IDC_BTN_REDO)->MoveWindow(rect.left - move_Distancs, rect.top, rect.Width(), rect.Height()); 
			GetDlgItem(IDC_BTN_REDO)->Invalidate(0);

		}

	GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&vertical_Line);
    ScreenToClient( &vertical_Line );

	GetDlgItem(IDC_BOUND_LINE)->MoveWindow(vertical_Line.left, vertical_Line.top, vertical_Line.Width() , Window_Rect.Height() - vertical_Line.top - 60 );


	GetDlgItem(IDC_HOR_LINE)->GetWindowRect(&horizontal_Line);
    ScreenToClient( &horizontal_Line );
	
	GetDlgItem(IDC_HOR_LINE)->MoveWindow(horizontal_Line.left, horizontal_Line.top, vertical_Line.left - horizontal_Line.left, horizontal_Line.Height());


	GetDlgItem(IDC_MAIN)->MoveWindow(vertical_Line.left + MARGIN_VERTICAL,  sizeRect[mainView].top, boundInform_Rect.left - (vertical_Line.left + MARGIN_VERTICAL*2) , Window_Rect.Height() - sizeRect[mainView].top - 60 );
	//GetDlgItem(IDC_MAIN2)->MoveWindow(vertical_Line.left + MARGIN_VERTICAL-1,  sizeRect[mainView].top-1, boundInform_Rect.left - (vertical_Line.left + MARGIN_VERTICAL*2) +2, Window_Rect.Height() - sizeRect[mainView].top - 60 +2);
		GetDlgItem(IDC_MAIN)->GetWindowRect(&sizeRect[mainView]);
	
        ScreenToClient( &sizeRect[mainView] );
		main_camera->set_Client_Rect(sizeRect[mainView]);
		//TRACE("main %d, %d, %d, %d, %d, %d\n", sizeRect[0].left, sizeRect[0].top, sizeRect[0].right, sizeRect[0].bottom, sizeRect[0].Width(), sizeRect[0].Height());
	

	GetDlgItem(IDC_TOP)->MoveWindow(sizeRect[topView].left,  sizeRect[topView].top, (vertical_Line.left - MARGIN_VERTICAL) - sizeRect[topView].left,  (horizontal_Line.top - MARGIN_HORIZONTAL)  - sizeRect[topView].top );
	//GetDlgItem(IDC_TOP2)->MoveWindow(sizeRect[topView].left-1,  sizeRect[topView].top-1, (vertical_Line.left - MARGIN_VERTICAL) - sizeRect[topView].left +2,  (horizontal_Line.top - MARGIN_HORIZONTAL)  - sizeRect[topView].top+2 );
		
		GetDlgItem(IDC_TOP)->GetWindowRect(&sizeRect[topView]);
        ScreenToClient( &sizeRect[topView] );
		top_camera->set_Client_Rect(sizeRect[topView]);
		//TRACE("top %d, %d, %d, %d, %d, %d\n", sizeRect[1].left, sizeRect[1].top, sizeRect[1].right, sizeRect[1].bottom, sizeRect[1].Width(), sizeRect[1].Height());

	GetDlgItem(IDC_SIDE)->MoveWindow(sizeRect[sideView].left,   (horizontal_Line.top + MARGIN_HORIZONTAL), (vertical_Line.left - MARGIN_VERTICAL) - sizeRect[sideView].left, Window_Rect.Height() -  (horizontal_Line.top + MARGIN_HORIZONTAL) - 60);
	//GetDlgItem(IDC_SIDE2)->MoveWindow(sizeRect[sideView].left-1,   (horizontal_Line.top + MARGIN_HORIZONTAL)-1, (vertical_Line.left - MARGIN_VERTICAL) - sizeRect[sideView].left+2, Window_Rect.Height() -  (horizontal_Line.top + MARGIN_HORIZONTAL) - 60+2);

		GetDlgItem(IDC_SIDE)->GetWindowRect(&sizeRect[sideView]);
        ScreenToClient( &sizeRect[sideView] );
        side_camera->set_Client_Rect(sizeRect[sideView]);
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect[2].left, sizeRect[2].top, sizeRect[2].right, sizeRect[2].bottom, sizeRect[2].Width(), sizeRect[2].Height());


		
		

		GetDlgItem(IDC_MAIN_GIZMO)->MoveWindow(sizeRect[mainView].right - 70-3,sizeRect[mainView].top+3,70,70);
		GetDlgItem(IDC_MAIN_GIZMO)->GetWindowRect(&sizeRect_GIZMO[mainView]);
        ScreenToClient( &sizeRect_GIZMO[mainView] );	
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect_GIZMO[0].left, sizeRect_GIZMO[0].top, sizeRect_GIZMO[0].right, sizeRect_GIZMO[0].bottom, sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height());

		GetDlgItem(IDC_TOP_GIZMO)->MoveWindow(sizeRect[topView].left+3,sizeRect[topView].top+3,70,70);
		GetDlgItem(IDC_TOP_GIZMO)->GetWindowRect(&sizeRect_GIZMO[topView]);
        ScreenToClient( &sizeRect_GIZMO[topView] );		 
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect_GIZMO[0].left, sizeRect_GIZMO[0].top, sizeRect_GIZMO[0].right, sizeRect_GIZMO[0].bottom, sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height());
		
		GetDlgItem(IDC_SIDE_GIZMO)->MoveWindow(sizeRect[sideView].left+3,sizeRect[sideView].bottom - 70-3,70,70);
		GetDlgItem(IDC_SIDE_GIZMO)->GetWindowRect(&sizeRect_GIZMO[sideView]);
        ScreenToClient( &sizeRect_GIZMO[sideView] );		 
		//TRACE("%d, %d, %d, %d, %d, %d\n", sizeRect_GIZMO[0].left, sizeRect_GIZMO[0].top, sizeRect_GIZMO[0].right, sizeRect_GIZMO[0].bottom, sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height());


	


		
		
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

int CGizmoTool_Ver_DigDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	ModifyStyle(0,WS_MAXIMIZEBOX);
    ModifyStyle(0,WS_MINIMIZEBOX);
    ModifyStyle(0,WS_THICKFRAME);

	
	return 0;
}

void CGizmoTool_Ver_DigDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
		wglDeleteContext(m_hRC[0]);
		::ReleaseDC(m_hWnd, m_hDC[0]->GetSafeHdc());
				wglDeleteContext(m_hRC[1]);
		::ReleaseDC(m_hWnd, m_hDC[1]->GetSafeHdc());
				wglDeleteContext(m_hRC[2]);
		::ReleaseDC(m_hWnd, m_hDC[2]->GetSafeHdc());

			delete m_hDC[2];
		delete m_hDC[1];
		delete m_hDC[0];
		delete m_hDC_GIZMO[0];
		delete m_hDC_GIZMO[1];
		delete m_hDC_GIZMO[2];

	//delete std_Gizmo;
	delete side_camera;
	delete top_camera;
	//delete current_Camera;
	delete	main_camera;
	delete default_Camera;
	
	delete buffer_for_blk_main;
	delete buffer_for_blk_top;
	delete buffer_for_blk_side;


		KillTimer(1);


}

	void CGizmoTool_Ver_DigDlg::play_SideView(){
		#ifdef SIDE
		//--------//////SIDE VIEW-----------------------------------------------------------------------
		 //--------//////SIDE VIEW-----------------------------------------------------------------------
		 //--------//////SIDE VIEW-----------------------------------------------------------------------
		 //--------//////SIDE VIEW-----------------------------------------------------------------------
	  glPushMatrix();



		wglDeleteContext(m_hRC[sideView]);
		m_hRC[sideView] = wglCreateContext(m_hDC[sideView]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC[sideView]->GetSafeHdc(), m_hRC[sideView]);
		
		glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
			ReSizeGLScene(sizeRect[sideView].Width(),sizeRect[sideView].Height(),sideView);
				
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		side_camera->setLookAt();

		glGetDoublev(GL_PROJECTION_MATRIX,projection2);
		glGetDoublev(GL_MODELVIEW_MATRIX,modelView2);
		glGetIntegerv(GL_VIEWPORT,viewPort2);
	
		side_camera->set_Projection_Modelview_viewport(projection2, modelView2, viewPort2);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA
	

DrawScene();
 

  		if(current_Camera->get_Count_pickedPos()){
			glColor4f(0.9f, 0.2f, 0.6f, 1.0f);
			glPointSize(20.f);
			glBegin(GL_POINTS);
			glVertex3f(current_Camera->pos_PickedRotatation.x, current_Camera->pos_PickedRotatation.y , current_Camera->pos_PickedRotatation.z);
			glEnd();
		}
		
		basic_Plane(side_camera);
		
		if(check_DrawRectangle && current_Camera->name == "SIDE")
			drag_Box();

	
		glPopMatrix();
	glDrawPixels(70,70,GL_RGBA,GL_FLOAT,buffer_for_blk_side);
		SwapBuffers(m_hDC[sideView]->GetSafeHdc());
#endif
	}
	void CGizmoTool_Ver_DigDlg::play_TopView(){
		#ifdef TOP
			
		//--------//////TOP VIEW------------------------------------------------------------------------
			//--------//////TOP VIEW------------------------------------------------------------------------
//--------//////TOP VIEW------------------------------------------------------------------------
			//--------//////TOP VIEW------------------------------------------------------------------------
		glPushMatrix();
		
				wglDeleteContext(m_hRC[topView]);
		m_hRC[topView] = wglCreateContext(m_hDC[topView]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC[topView]->GetSafeHdc(), m_hRC[topView]);

		
		
		glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		
	

		

		ReSizeGLScene(sizeRect[topView].Width(),sizeRect[topView].Height(),topView);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		top_camera->setLookAt();

		
		
		glGetDoublev(GL_PROJECTION_MATRIX,projection1);
		glGetDoublev(GL_MODELVIEW_MATRIX,modelView1);
		glGetIntegerv(GL_VIEWPORT,viewPort1);
		top_camera->set_Projection_Modelview_viewport(projection1, modelView1, viewPort1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA

DrawScene();

  		if(current_Camera->get_Count_pickedPos()){
			glColor4f(0.9f, 0.2f, 0.6f, 1.0f);
			glPointSize(20.f);
			glBegin(GL_POINTS);
			glVertex3f(current_Camera->pos_PickedRotatation.x, current_Camera->pos_PickedRotatation.y , current_Camera->pos_PickedRotatation.z);
			glEnd();
			
		}

		basic_Plane(top_camera);

		if(check_DrawRectangle && current_Camera->name == "TOP")
			drag_Box();

 glPopMatrix();
 glDrawPixels(70,70,GL_RGBA,GL_FLOAT,buffer_for_blk_top);
		SwapBuffers(m_hDC[topView]->GetSafeHdc());
		
#endif	
	}
	void CGizmoTool_Ver_DigDlg::play_MainView(){
		#ifdef MAIN
		 
		//--------//////MAIN VIEW--------------------------------------------------------------------------.
		//--------//////MAIN VIEW--------------------------------------------------------------------------
		//--------//////MAIN VIEW--------------------------------------------------------------------------
		//--------//////MAIN VIEW--------------------------------------------------------------------------
		
		glPushMatrix();
		
	
		wglDeleteContext(m_hRC[mainView]);
		m_hRC[mainView] = wglCreateContext(m_hDC[mainView]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC[mainView]->GetSafeHdc(), m_hRC[mainView]);
					
		
		
		glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		ReSizeGLScene(sizeRect[mainView].Width(),sizeRect[mainView].Height(),mainView);

	

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		main_camera->setLookAt();

		glGetDoublev(GL_PROJECTION_MATRIX,projection);
		glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
		glGetIntegerv(GL_VIEWPORT,viewPort);
		main_camera->set_Projection_Modelview_viewport(projection, modelView, viewPort);

		

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA
		
DrawScene();

   		if(current_Camera->get_Count_pickedPos()){
			glColor4f(0.9f, 0.2f, 0.6f, 1.0f);
			glPointSize(20.f);
			glBegin(GL_POINTS);
			glVertex3f(current_Camera->pos_PickedRotatation.x, current_Camera->pos_PickedRotatation.y , current_Camera->pos_PickedRotatation.z);
			glEnd();
			
		}
		 basic_Plane(main_camera);
		if(check_DrawRectangle && current_Camera->name == "MAIN")
			drag_Box();

		glPopMatrix();
		//glCopyPixels(0,0,sizeRect[0].Width(),sizeRect[0].Height(),GL_RGBA);


		//glReadPixels(sizeRect[0].Width()-70, sizeRect[0].Height()-70,70, 70,GL_RGBA,GL_FLOAT,buffer_for_blk);	
		glDrawPixels(70,70,GL_RGBA,GL_FLOAT,buffer_for_blk_main);
		
		SwapBuffers(m_hDC[mainView]->GetSafeHdc());
	
		
#endif

	}

	void CGizmoTool_Ver_DigDlg::play_Main_Gizmo(){
		
		//glPushMatrix();
		wglDeleteContext(m_hRC_GIZMO[0]);
		m_hRC_GIZMO[0] = wglCreateContext(m_hDC_GIZMO[0]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC_GIZMO[0]->GetSafeHdc(), m_hRC_GIZMO[0]);
		m_hDC_GIZMO[0]->SetBkMode(TRANSPARENT);
		//m_hDC_GIZMO[0]->SetBkColor(1);
		
			//GetDlgItem(IDC_MAIN_GIZMO)->
		glClearColor(0.24,0.24,0.24,0);
		//glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		

		glViewport(0,0,sizeRect_GIZMO[0].Width(),sizeRect_GIZMO[0].Height());

		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
			if(!(main_camera->Get_cameraView_Perspective_Ortho()))
				gluPerspective(60.f,sizeRect_GIZMO[0].Width()/sizeRect_GIZMO[0].Height() , 0.1f, 1000.f);
			else
				glOrtho(-15,15,-15,15,0.1,1000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		main_camera->setLookAt();
		
		//glRasterPos2i(20,20);
		//glDrawPixels(70,70,GL_RGBA,GL_FLOAT,buffer_for_blk);
		//glCopyPixels(0,0,70,70,GL_RGBA);
		//glFlush();
		

		glPushMatrix();
		
		  glTranslatef(main_camera->pos_center.x, main_camera->pos_center.y, main_camera->pos_center.z);
			std_Gizmo.current_Camera = *main_camera;
			
			std_Gizmo.DrawGizmo_ViewMode();
		glPopMatrix();
	
		glPopMatrix();	
		
		glReadPixels(0, 0,70, 70,GL_RGBA,GL_FLOAT,buffer_for_blk_main);
		//m_hDC_GIZMO[0]->TransparentBlt( 0, 0,1920,1200, m_hDC_GIZMO[0], 0,0,1920, 1200, RGB(0,0,0));
		//m_hDC_GIZMO[0]->TransparentBlt( sizeRect_GIZMO[0].left,sizeRect_GIZMO[0].bottom,sizeRect_GIZMO[0].Width(),sizeRect_GIZMO[0].Height(), m_hDC[0], 0,0,sizeRect_GIZMO[0].Width(), sizeRect_GIZMO[0].Height(), RGB(255,255,255));
		
		//SwapBuffers(m_hDC_GIZMO[0]->GetSafeHdc());
}
	void CGizmoTool_Ver_DigDlg::play_Top_Gizmo(){
		glPushMatrix();
		wglDeleteContext(m_hRC_GIZMO[1]);
		m_hRC_GIZMO[1] = wglCreateContext(m_hDC_GIZMO[1]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC_GIZMO[1]->GetSafeHdc(), m_hRC_GIZMO[1]);
				
		
		glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		glViewport(0,0,sizeRect_GIZMO[1].Width(),sizeRect_GIZMO[1].Height());

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

			if(!(top_camera->Get_cameraView_Perspective_Ortho()))
				gluPerspective(60.f,sizeRect_GIZMO[1].Width()/sizeRect_GIZMO[1].Height() , 0.1f, 1000.f);
			else
				glOrtho(-15,15,-15,15,0.1,1000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		top_camera->setLookAt();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA
		
		glPushMatrix();
		  glTranslatef(top_camera->pos_center.x, top_camera->pos_center.y, top_camera->pos_center.z);
			std_Gizmo.current_Camera = *top_camera;
			std_Gizmo.DrawGizmo_ViewMode();
		glPopMatrix();
	
		glPopMatrix();	
		//SwapBuffers(m_hDC_GIZMO[1]->GetSafeHdc());
		glReadPixels(0, 0,70, 70,GL_RGBA,GL_FLOAT,buffer_for_blk_top);
	}
	void CGizmoTool_Ver_DigDlg::play_Side_Gizmo(){
		glPushMatrix();
		wglDeleteContext(m_hRC_GIZMO[2]);
		m_hRC_GIZMO[2] = wglCreateContext(m_hDC_GIZMO[2]->GetSafeHdc()) ;
		wglMakeCurrent(m_hDC_GIZMO[2]->GetSafeHdc(), m_hRC_GIZMO[2]);
			
		//glClearColor(0,0,0,0);
		glClearColor(color_View_Background[0], color_View_Background[1], color_View_Background[2], color_View_Background[3]);//0.7f, 0.8f, 0.85f, 1.0f
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		glViewport(0,0,sizeRect_GIZMO[2].Width(),sizeRect_GIZMO[2].Height());

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
			if(!(side_camera->Get_cameraView_Perspective_Ortho()))
				gluPerspective(60.f,sizeRect_GIZMO[2].Width()/sizeRect_GIZMO[2].Height() , 0.1f, 1000.f);
			else
				glOrtho(-15,15,-15,15,0.1,1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		side_camera->setLookAt();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //GL_ONE_MINUS_SRC_ALPHA
		
		glPushMatrix();
		  glTranslatef(side_camera->pos_center.x, side_camera->pos_center.y, side_camera->pos_center.z);
			 std_Gizmo.current_Camera = *side_camera;
			std_Gizmo.DrawGizmo_ViewMode();
		glPopMatrix();
	
		glPopMatrix();	
		//SwapBuffers(m_hDC_GIZMO[2]->GetSafeHdc());
		glReadPixels(0, 0,70, 70,GL_RGBA,GL_FLOAT,buffer_for_blk_side);
	}

void CGizmoTool_Ver_DigDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch(nIDEvent){
	case 1:
		{
			/*
			if(selectedObject_INDEX != -1)
				setObjectInformEdit(selectedObject_INDEX);
			else
				clearObjectInformEdit();
				*/

				if(current_Camera->key_check_Q )
					SetCursor(LoadCursor(NULL, IDC_SIZEALL));
				else if(bound_Line || check_bound_Line)
					SetCursor(LoadCursor(NULL, IDC_SIZEWE));
				else if(bound_horizontal_Line || check_bound_horizontal_Line)
					SetCursor(LoadCursor(NULL, IDC_SIZENS));
				else
					SetCursor(LoadCursor(NULL, IDC_ARROW));

	
			if( current_Camera->name == "MAIN" ){	
	
				play_Side_Gizmo();
				play_Top_Gizmo();
				play_Main_Gizmo();
				play_SideView();
				play_TopView();
				play_MainView();
	

			}
			else if( current_Camera->name == "TOP"){
				play_Main_Gizmo();
				play_Side_Gizmo();
				play_Top_Gizmo();
				play_MainView();
				play_SideView();
				play_TopView();
			}
			else if( current_Camera->name == "SIDE"){
				play_Top_Gizmo();
				play_Main_Gizmo();
				play_Side_Gizmo();
				play_TopView();
				play_MainView();
				play_SideView();
			}

		}
	}	

	CDialogEx::OnTimer(nIDEvent);
}

void CGizmoTool_Ver_DigDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	delete	main_camera;
	delete top_camera;
	delete side_camera;
	//delete std_Gizmo;
	delete default_Camera;
	//delete current_Camera;
		
		KillTimer(1);
		wglDeleteContext(m_hRC[0]);
		::ReleaseDC(m_hWnd, m_hDC[0]->GetSafeHdc());
				wglDeleteContext(m_hRC[1]);
		::ReleaseDC(m_hWnd, m_hDC[1]->GetSafeHdc());
				wglDeleteContext(m_hRC[2]);
		::ReleaseDC(m_hWnd, m_hDC[2]->GetSafeHdc());
		
			delete m_hDC[0];
		delete m_hDC[1];
		delete m_hDC[2];
				delete m_hDC_GIZMO[0];
		delete m_hDC_GIZMO[1];
		delete m_hDC_GIZMO[2];

			delete buffer_for_blk_main;
	delete buffer_for_blk_top;
	delete buffer_for_blk_side;

	CDialogEx::OnClose();
}

void CGizmoTool_Ver_DigDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//point.SetPoint((int)point.x - currentView_topleft.x, (int)point.y - currentView_topleft.y);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*
	vector3f z_1_vec = z_1(CPoint((int)point.x - sizeRect[ mainView ].left, (int)point.y - sizeRect[ mainView ].top),main_camera->projection, main_camera->modelView, main_camera->viewPort);
	vector3f z_0_vec = z_0(CPoint((int)point.x - sizeRect[ mainView ].left, (int)point.y - sizeRect[ mainView ].top),main_camera->projection, main_camera->modelView, main_camera->viewPort);
	
	GLfloat t = z_0_vec.y / (z_0_vec.y - z_1_vec.y);
	
	inf_plane.x = z_0_vec.x + t*(z_1_vec.x - z_0_vec.x);
	inf_plane.y = 0;
	inf_plane.z = z_0_vec.z + t*(z_1_vec.z - z_0_vec.z);
	*/
	CRect rect;
	GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
    ScreenToClient( &rect );
	if(rect.PtInRect(point)){
		check_bound_Line = TRUE;
	}
	else
		check_bound_Line = FALSE;

	GetDlgItem(IDC_HOR_LINE)->GetWindowRect(&rect);
    ScreenToClient( &rect );
	if(rect.PtInRect(point)){
		check_bound_horizontal_Line = TRUE;
	}
	else
		check_bound_horizontal_Line = FALSE;
	
	
	if(sizeRect[ mainView ].PtInRect(point) && check_MainFocus){
		inf_plane = worldPlane(CPoint((int)point.x - sizeRect[ mainView ].left, (int)point.y - sizeRect[ mainView ].top),main_camera->projection, main_camera->modelView, main_camera->viewPort);
		mouse_point3f = fromMouseToWorld(CPoint((int)point.x - sizeRect[ mainView ].left, (int)point.y - sizeRect[ mainView ].top),main_camera->projection, main_camera->modelView, main_camera->viewPort);

		//TRACE("%d, %d\n",point.x, point.y);
		//point.SetPoint((int)point.x - sizeRect[ mainView ].left, (int)point.y - sizeRect[ mainView ].top);
			current_Camera = main_camera;
			current_Camera->name = "MAIN";
			check_MouseView = TRUE;

			if(nFlags == MK_LBUTTON && check_DrawRectangle && !check_Key_Q && !check_Key_Z && !check_Key_X)
			{
				m_ptEnd.SetPoint((int)point.x - sizeRect[ mainView ].left , (int)point.y - sizeRect[ mainView ].top );
			}
	}
	else if(sizeRect[ topView ].PtInRect(point) && check_TopFocus){
		inf_plane = worldPlane(CPoint((int)point.x - sizeRect[ topView ].left, (int)point.y - sizeRect[ topView ].top),top_camera->projection, top_camera->modelView, top_camera->viewPort);
		mouse_point3f = fromMouseToWorld(CPoint((int)point.x - sizeRect[ topView ].left, (int)point.y - sizeRect[ topView ].top),top_camera->projection, top_camera->modelView, top_camera->viewPort);

		//point.SetPoint((int)point.x - sizeRect[ topView ].left, (int)point.y - sizeRect[ topView ].top);
				current_Camera = top_camera;
				current_Camera->name = "TOP";
				check_MouseView = TRUE;

			if(nFlags == MK_LBUTTON && check_DrawRectangle && !check_Key_Q && !check_Key_Z && !check_Key_X)
			{
				m_ptEnd.SetPoint((int)point.x - sizeRect[ topView ].left , (int)point.y - sizeRect[ topView ].top );
			}

	}
	else if(sizeRect[ sideView ].PtInRect(point) && check_SideFocus){
		inf_plane = worldPlane(CPoint((int)point.x - sizeRect[ sideView ].left, (int)point.y - sizeRect[ sideView ].top),side_camera->projection, side_camera->modelView, side_camera->viewPort);
		mouse_point3f = fromMouseToWorld(CPoint((int)point.x - sizeRect[ sideView ].left, (int)point.y - sizeRect[ sideView ].top),side_camera->projection, side_camera->modelView, side_camera->viewPort);

		//point.SetPoint((int)point.x - sizeRect[ sideView ].left, (int)point.y - sizeRect[ sideView ].top);
		//TRACE("ASDASD : %d, %d\n", point.x, point.y);
			current_Camera = side_camera;
			current_Camera->name = "SIDE";
			check_MouseView = TRUE;
			if(nFlags == MK_LBUTTON && check_DrawRectangle && !check_Key_Q && !check_Key_Z && !check_Key_X)
			{
				m_ptEnd.SetPoint((int)point.x - sizeRect[ sideView ].left , (int)point.y - sizeRect[ sideView ].top );
			}
		
	}
	else{
		//check_DrawRectangle = FALSE;
		current_Camera->camera_KeyReset();
		current_Camera = default_Camera;
		current_Camera->name = "MAIN";
			check_MouseView = FALSE;
	}
	

	if(bound_Line){
		
		CRect rect;
		GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );

		//if( (rect.left - MARGIN_VERTICAL) <= point.x &&  point.x <= (rect.left + MARGIN_VERTICAL) ){
			GetDlgItem(IDC_BOUND_LINE)->MoveWindow(point.x, rect.top, rect.Width(), rect.Height());
			//OnSize(0,0,0);
			
	//	}
		

	}

	if(bound_horizontal_Line){
		
		CRect rect;
		GetDlgItem(IDC_HOR_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
		//if( (rect.top - MARGIN_HORIZONTAL) <= point.y &&  point.y <= (rect.top + MARGIN_HORIZONTAL) ){
			GetDlgItem(IDC_HOR_LINE)->MoveWindow(rect.left, point.y, rect.Width(), rect.Height());
			//OnSize(0,0,0);
	//	}
	}
	
		


	CDialogEx::OnMouseMove(nFlags, point);
}

void CGizmoTool_Ver_DigDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(sizeRect[ mainView ].PtInRect(point) && !check_MainFocus){
		m_ptStart.SetPoint(0,0);
		m_ptEnd.SetPoint(0,0);
		check_MainFocus = TRUE;
		check_TopFocus = FALSE;
		check_SideFocus = FALSE;
		GetDlgItem(IDC_MAIN)->ModifyStyle(WS_BORDER,WS_DLGFRAME);
		GetDlgItem(IDC_TOP)->ModifyStyle(WS_DLGFRAME,WS_BORDER);
		GetDlgItem(IDC_SIDE)->ModifyStyle(WS_DLGFRAME,WS_BORDER);
		
		CRect rect;
		GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left-1, rect.top, rect.Width(), rect.Height());

		OnSize(0,0,0);
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left+1, rect.top, rect.Width(), rect.Height());
		OnSize(0,0,0);
	}
	else if(sizeRect[ topView ].PtInRect(point) && !check_TopFocus){
				m_ptStart.SetPoint(0,0);
		m_ptEnd.SetPoint(0,0);
		check_MainFocus = FALSE;
		check_TopFocus = TRUE;
		check_SideFocus = FALSE;

		GetDlgItem(IDC_MAIN)->ModifyStyle(WS_DLGFRAME,WS_BORDER);
		GetDlgItem(IDC_TOP)->ModifyStyle(WS_BORDER,WS_DLGFRAME);
		GetDlgItem(IDC_SIDE)->ModifyStyle(WS_DLGFRAME,WS_BORDER);

		CRect rect;
		GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left-1, rect.top, rect.Width(), rect.Height());

		OnSize(0,0,0);
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left+1, rect.top, rect.Width(), rect.Height());
		OnSize(0,0,0);
	}
	else if(sizeRect[ sideView ].PtInRect(point) && !check_SideFocus){
				m_ptStart.SetPoint(0,0);
		m_ptEnd.SetPoint(0,0);
		check_MainFocus = FALSE;
		check_TopFocus = FALSE;
		check_SideFocus = TRUE;

		GetDlgItem(IDC_MAIN)->ModifyStyle(WS_DLGFRAME,WS_BORDER);
		GetDlgItem(IDC_TOP)->ModifyStyle(WS_DLGFRAME,WS_BORDER);
		GetDlgItem(IDC_SIDE)->ModifyStyle(WS_BORDER,WS_DLGFRAME);

		CRect rect;
		GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left-1, rect.top, rect.Width(), rect.Height());

		OnSize(0,0,0);
		GetDlgItem(IDC_BOUND_LINE)->MoveWindow(rect.left+1, rect.top, rect.Width(), rect.Height());
		OnSize(0,0,0);
	}




	CRect rect;
	GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
	ScreenToClient( &rect );
	if(rect.PtInRect(point)){
		bound_Line = TRUE;
	}

	GetDlgItem(IDC_HOR_LINE)->GetWindowRect(&rect);
	ScreenToClient( &rect );
	if(rect.PtInRect(point)){
		bound_horizontal_Line = TRUE;
	}
	BOOL checkHitGizmo_Objects = FALSE;
	for(int i = selectedObject_INDEX_Array.size()-1 ; i >= 0 ; i--)
		checkHitGizmo_Objects = (object_Array[selectedObject_INDEX_Array[i]].getHitGizmo());



	if((selectedObject_INDEX_Array.size() == 0 || !checkHitGizmo_Objects) && !check_Draw_centerGizmo){
		check_DrawRectangle = TRUE;
		int i = 0;
		/*
		if(current_Camera->name == "MAIN")
			i = mainView;
		else if(current_Camera->name == "TOP")
			i = topView;
		else if(current_Camera->name == "SIDE")
			i = sideView;
*/
		if(check_MainFocus)
			i = mainView;
		else if(check_TopFocus)
			i = topView;
		else if(check_SideFocus)
			i = sideView;

		m_ptStart.SetPoint(point.x - sizeRect[i].left, point.y - sizeRect[i].top);
		m_ptEnd.SetPoint(point.x - sizeRect[i].left, point.y - sizeRect[i].top);
		//TRACE("start %d, %d \n", m_ptStart.x, m_ptStart.y);
		//TRACE("end %d, %d \n", m_ptEnd.x, m_ptEnd.y);
	}

	for(int i = 0 ; i < object_Array.size(); i++){
		object_Array[i].setCheckDrag(check_DrawRectangle);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CGizmoTool_Ver_DigDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(bound_Line){
		
		CRect rect;
		GetDlgItem(IDC_BOUND_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
			OnSize(0,0,0);

	}
	if(bound_horizontal_Line){
		
		CRect rect;
		GetDlgItem(IDC_HOR_LINE)->GetWindowRect(&rect);
		ScreenToClient( &rect );
			OnSize(0,0,0);
	}


	bound_Line = FALSE;
	bound_horizontal_Line = FALSE;

	check_DrawRectangle = FALSE;
	m_ptStart.SetPoint(0,0);
	m_ptEnd.SetPoint(0,0);

	CDialogEx::OnLButtonUp(nFlags, point);
}

BOOL CGizmoTool_Ver_DigDlg::PreTranslateMessage(MSG* pMsg)
{
	/*
	CPoint point(LOWORD(pMsg->lParam) , HIWORD(pMsg->lParam));
	if(sizeRect[ mainView ].PtInRect(point)){
		GetDlgItem(IDC_MAIN)->Invalidate(0);
	}
	else if(sizeRect[ topView ].PtInRect(point)){
		GetDlgItem(IDC_TOP)->Invalidate(0);
	}
	else if(sizeRect[ sideView ].PtInRect(point)){
		GetDlgItem(IDC_SIDE)->Invalidate(0);
	}*/

	if(pMsg->message == WM_KEYUP){
		check_Key_Z = FALSE;
		check_Key_X = FALSE;
	}

	if(check_MouseView){
		current_Camera->camera_Mouse_Evnet(pMsg);
		current_Camera->camera_Key_Event(pMsg);
		centerOfObjects_Gizmo.gizmo_Mouse_Evnet(pMsg, current_Camera);

		vector<GLint> selected_Index_array;

		for(int i = 0; i < object_Array.size(); i++){
			if(object_Array[i].object_Event(pMsg, current_Camera)){
				selected_Index_array.push_back(i);

			}
		}
		if(pMsg->message == WM_LBUTTONDOWN){
			if(check_Draw_centerGizmo && !centerOfObjects_Gizmo.getHitGizmo() && !check_Key_Q && !check_Key_Z && !check_Key_X){
				
				selectedObject_INDEX_Array.clear();
				check_Draw_centerGizmo = FALSE;
				save_EditEvent();
			}
		}
		if(pMsg->message == WM_LBUTTONUP){
			if(check_Draw_centerGizmo){
				for(int i = 0 ; i < selectedObject_INDEX_Array.size(); i++){
					object_Array[selectedObject_INDEX_Array[i]].check_SelectedObject = TRUE;
				}
				if(check_CenterGizmo_Transform){
					save_EditEvent();
				}
				check_CenterGizmo_Transform = FALSE;

			}
			else{
				if(selectedObject_INDEX_Array.size() != selected_Index_array.size()){
					selectedObject_INDEX_Array = selected_Index_array;
					save_EditEvent();
				}
				else{
					for(int i = 0 ; i < selectedObject_INDEX_Array.size() ; i++){
						if(selectedObject_INDEX_Array[i] != selected_Index_array[i]){
							selectedObject_INDEX_Array = selected_Index_array;
							save_EditEvent();
						}
					}
				}

				selectedObject_INDEX_Array = selected_Index_array;

				if(check_Object_Transform){
					if(selectedObject_INDEX_Array.size() ==1)
						setObjectInformEdit(selectedObject_INDEX_Array[0]);
					save_EditEvent();
					check_Object_Transform =FALSE;
				}

				if(selectedObject_INDEX_Array.size() != 0)
					setObjectInformEdit(selectedObject_INDEX_Array[0]);
				else
					clearObjectInformEdit();
			}
		}

		else if(pMsg->message == WM_MOUSEMOVE){
			if(check_Draw_centerGizmo){
				setObjectInformEdit(-1);
				for(int i = 0 ; i < selectedObject_INDEX_Array.size(); i++){
					object_Array[selectedObject_INDEX_Array[i]].check_SelectedObject = TRUE;
				}
				check_CenterGizmo_Transform = centerOfObjects_Gizmo.getHitGizmo();
			}
			else{
				if(selected_Index_array.size() != 0){
					check_Object_Transform = (object_Array[selected_Index_array[0]].getHitGizmo()) ;

					if(check_Object_Transform){
						if(selectedObject_INDEX_Array.size() != 0)
							setObjectInformEdit(selectedObject_INDEX_Array[0]);
						else
							clearObjectInformEdit();
					}
				}
			}
		}


	}




	
	if (hAccelTable != NULL)
     {
         if (TranslateAccelerator(m_hWnd, hAccelTable, pMsg))
            return TRUE;
     }
	


	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGizmoTool_Ver_DigDlg::setObjectInformEdit(int selectedIndex){
	int size = selectedObject_INDEX_Array.size();
	if(size <= 1){
		listBox_Object.SetCurSel(selectedIndex);
		CString str;


		vector3f position = object_Array[selectedIndex].getPosition();
		vector3f rotate = object_Array[selectedIndex].getRotate();
		vector3f scale = object_Array[selectedIndex].getScale();



		str.Format(_T("%d"),object_Array[selectedIndex].object_ID);

		if(selectedIndex == -1){
			position.set(0,0,0);
			rotate.set(0,0,0);
			scale.set(1,1,1);
			str.Format(_T("0"));
		}

		edit_ID.SetWindowTextW(str);

		str.Format(_T("%f"),position.x);		
		edit_Pos_X.SetWindowText(str);
		str.Format(_T("%f"),position.y);		
		edit_Pos_Y.SetWindowText(str);
		str.Format(_T("%f"),position.z);		
		edit_Pos_Z.SetWindowText(str);

		str.Format(_T("%f"),rotate.x);		
		edit_Rot_X.SetWindowText(str);
		str.Format(_T("%f"),rotate.y);		
		edit_Rot_Y.SetWindowText(str);
		str.Format(_T("%f"),rotate.z);		
		edit_Rot_Z.SetWindowText(str);

		str.Format(_T("%f"),scale.x);		
		edit_Scl_X.SetWindowText(str);
		str.Format(_T("%f"),scale.y);		
		edit_Scl_Y.SetWindowText(str);
		str.Format(_T("%f"),scale.z);		
		edit_Scl_Z.SetWindowText(str);

	}
	else if(size > 1){
		CString str;
		BOOL check_SameData[9] = {0,0,0,0,0,0,0,0,0};
		vector3f *position = new vector3f[size];
		vector3f *rotate = new vector3f[size];
		vector3f *scale = new vector3f[size];
		
		for(int i = 0 ; i < size ; i++){
			position[i] = object_Array[selectedObject_INDEX_Array[i]].getPosition();
			rotate[i] = object_Array[selectedObject_INDEX_Array[i]].getRotate();
			scale[i] = object_Array[selectedObject_INDEX_Array[i]].getScale();
		}

		str.Format(_T("-"));
		edit_ID.SetWindowTextW(str);

		for(int i = 1 ; i < size ; i++){
			if(position[i-1].x == position[i].x)
				check_SameData[0] = TRUE;
			else
				check_SameData[0] = FALSE;
			if(position[i-1].y == position[i].y)
				check_SameData[1] = TRUE;
			else
				check_SameData[1] = FALSE;
			if(position[i-1].z == position[i].z)
				check_SameData[2] = TRUE;
			else
				check_SameData[2] = FALSE;
//---------------------------------------------------------------
						if(rotate[i-1].x == rotate[i].x)
				check_SameData[3] = TRUE;
			else
				check_SameData[3] = FALSE;
			if(rotate[i-1].y == rotate[i].y)
				check_SameData[4] = TRUE;
			else
				check_SameData[4] = FALSE;
			if(rotate[i-1].z == rotate[i].z)
				check_SameData[5] = TRUE;
			else
				check_SameData[5] = FALSE;
//---------------------------------------------------------------
						if(scale[i-1].x == scale[i].x)
				check_SameData[6] = TRUE;
			else
				check_SameData[6] = FALSE;
			if(scale[i-1].y == scale[i].y)
				check_SameData[7] = TRUE;
			else
				check_SameData[7] = FALSE;
			if(scale[i-1].z == scale[i].z)
				check_SameData[8] = TRUE;
			else
				check_SameData[8] = FALSE;
		}

		if(check_SameData[0]){
			str.Format(_T("%f"),position[0].x);		
			edit_Pos_X.SetWindowText(str);
		}
		else{	
			edit_Pos_X.SetWindowText(_T("-"));
		}
		if(check_SameData[1]){
			str.Format(_T("%f"),position[0].y);		
			edit_Pos_Y.SetWindowText(str);
		}
		else
			edit_Pos_Y.SetWindowText(_T("-"));
		if(check_SameData[2]){
			str.Format(_T("%f"),position[0].z);		
			edit_Pos_Z.SetWindowText(str);
		}
		else
			edit_Pos_Z.SetWindowText(_T("-"));
//---------------------------------------------------------
				if(check_SameData[3]){
			str.Format(_T("%f"),rotate[0].x);		
			edit_Rot_X.SetWindowText(str);
		}
		else{	
			edit_Rot_X.SetWindowText(_T("-"));
		}
		if(check_SameData[4]){
			str.Format(_T("%f"),rotate[0].y);		
			edit_Rot_Y.SetWindowText(str);
		}
		else
			edit_Rot_Y.SetWindowText(_T("-"));
		if(check_SameData[5]){
			str.Format(_T("%f"),rotate[0].z);		
			edit_Rot_Z.SetWindowText(str);
		}
		else
			edit_Rot_Z.SetWindowText(_T("-"));
//---------------------------------------------------------
				if(check_SameData[6]){
			str.Format(_T("%f"),scale[0].x);		
			edit_Scl_X.SetWindowText(str);
		}
		else{	
			edit_Scl_X.SetWindowText(_T("-"));
		}
		if(check_SameData[7]){
			str.Format(_T("%f"),scale[0].y);		
			edit_Scl_Y.SetWindowText(str);
		}
		else
			edit_Scl_Y.SetWindowText(_T("-"));
		if(check_SameData[8]){
			str.Format(_T("%f"),scale[0].z);		
			edit_Scl_Z.SetWindowText(str);
		}
		else
			edit_Scl_Z.SetWindowText(_T("-"));
		
		listBox_Object.SetCurSel(-1);

		delete position;
		delete rotate;
		delete scale;

	}
}

void CGizmoTool_Ver_DigDlg::clearObjectInformEdit(){

		edit_ID.SetWindowTextW(_T(""));

		edit_Pos_X.SetWindowTextW(_T(""));edit_Pos_Y.SetWindowTextW(_T(""));edit_Pos_Z.SetWindowTextW(_T(""));

		edit_Rot_X.SetWindowTextW(_T(""));edit_Rot_Y.SetWindowTextW(_T(""));edit_Rot_Z.SetWindowTextW(_T(""));

		edit_Scl_X.SetWindowTextW(_T(""));edit_Scl_Y.SetWindowTextW(_T(""));edit_Scl_Z.SetWindowTextW(_T(""));

		listBox_Object.SetCurSel(-1);
	}

void CGizmoTool_Ver_DigDlg::OnKey_F()
{
	if(selectedObject_INDEX_Array.size() == 0)
		current_Camera->keyEvent_F();
	else if(selectedObject_INDEX_Array.size() == 1){
		current_Camera->setEyeCenter(object_Array[selectedObject_INDEX_Array[0]].center + vector3f(20,20,20), object_Array[selectedObject_INDEX_Array[0]].center);
	}
	else if(selectedObject_INDEX_Array.size() > 1){
		current_Camera->setEyeCenter(centerOfObjects_Gizmo.center + vector3f(20,20,20), 
			centerOfObjects_Gizmo.center);

	}

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGizmoTool_Ver_DigDlg::OnKey_Down()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Down();
}

void CGizmoTool_Ver_DigDlg::OnKey_Up()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Up();
}

void CGizmoTool_Ver_DigDlg::OnKey_Right()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Right();
}

void CGizmoTool_Ver_DigDlg::OnKey_Left()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Left();
}

void CGizmoTool_Ver_DigDlg::OnKey_X()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_X();

	for(int i = 0; i < object_Array.size(); i++){
		//if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_X();
	}

	check_Key_X = TRUE;
}

void CGizmoTool_Ver_DigDlg::OnKey_Z()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Z();
	for(int i = 0; i < object_Array.size(); i++){
		//if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_Z();
	}

	check_Key_Z = TRUE;
}

void CGizmoTool_Ver_DigDlg::OnKey_Q()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_Q();

	for(int i = 0; i < object_Array.size(); i++){
		//if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_Q();
	}

	if(check_Key_Q)
		check_Key_Q = FALSE;
	else 
		check_Key_Q = TRUE;
}

void CGizmoTool_Ver_DigDlg::OnKey_O()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	current_Camera->keyEvent_O();
}

void CGizmoTool_Ver_DigDlg::OnKey_W()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	for(int i = 0; i < object_Array.size(); i++){
		if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_W();
	}

	centerOfObjects_Gizmo.keyEvent_W();
}

void CGizmoTool_Ver_DigDlg::OnKey_E()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	for(int i = 0; i < object_Array.size(); i++){
		if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_E();
	}
	centerOfObjects_Gizmo.keyEvent_E();
}

void CGizmoTool_Ver_DigDlg::OnKey_R()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	for(int i = 0; i < object_Array.size(); i++){
		if(object_Array[i].check_SelectedObject)
			object_Array[i].keyEvent_R();
	}
	centerOfObjects_Gizmo.keyEvent_R();
}

void CGizmoTool_Ver_DigDlg::OnKey_C()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
		//if(selectedObject_INDEX != -1){
	if(selectedObject_INDEX_Array.size() != 0){
		for(int i = 0; i < selectedObject_INDEX_Array.size() ; i++)
			object_Array[selectedObject_INDEX_Array[i]].keyEvent_C();
		//object_Array[selectedObject_INDEX].setTranslate(0, 0, 0);
		//object_Array[selectedObject_INDEX].setRotate(0, 0, 0);
		//object_Array[selectedObject_INDEX].setScale(1, 1, 1);

			setObjectInformEdit(selectedObject_INDEX_Array[0]);
			//clearObjectInformEdit();
			centerOfObjects_Gizmo.keyEvent_C();
			save_EditEvent();
	}
}

void CGizmoTool_Ver_DigDlg::OnKey_P()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(check_Key_P)
		check_Key_P = FALSE;
	else
		check_Key_P = TRUE;
}

void CGizmoTool_Ver_DigDlg::OnKey_Alt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TRACE("ALT\n");
}

void CGizmoTool_Ver_DigDlg::OnKey_Enter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	BOOL check_Str[9] = {0,0,0,0,0,0,0,0,0};
	CString str;
	GLfloat pos_X;
	GLfloat pos_Y;
	GLfloat pos_Z;
	edit_Pos_X.GetWindowTextW(str);
	if(!str.Compare(_T("-")))
		check_Str[0] = FALSE;
	else
		check_Str[0] = TRUE;
	pos_X = _ttof(str);

	edit_Pos_Y.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[1] = FALSE;
	else
		check_Str[1] = TRUE;
	pos_Y = _ttof(str);

	edit_Pos_Z.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[2] = FALSE;
	else
		check_Str[2] = TRUE;
	pos_Z = _ttof(str);
	
	if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setTranslate(pos_X, pos_Y, pos_Z);
	
	
	
	GLfloat rot_X;
	GLfloat rot_Y;
	GLfloat rot_Z;
	edit_Rot_X.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[3] = FALSE;
	else
		check_Str[3] = TRUE;
	rot_X = _ttof(str);
	edit_Rot_Y.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[4] = FALSE;
	else
		check_Str[4] = TRUE;
	rot_Y = _ttof(str);
	edit_Rot_Z.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[5] = FALSE;
	else
		check_Str[5] = TRUE;
	rot_Z = _ttof(str);
	
	if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setRotate(rot_X, rot_Y, rot_Z);

	
	GLfloat scl_X;
	GLfloat scl_Y;
	GLfloat scl_Z;
	edit_Scl_X.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[6] = FALSE;
	else
		check_Str[6] = TRUE;
	scl_X = _ttof(str);
	edit_Scl_Y.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[7] = FALSE;
	else
		check_Str[7] = TRUE;
	scl_Y = _ttof(str);
	edit_Scl_Z.GetWindowTextW(str);
		if(!str.Compare(_T("-")))
		check_Str[8] = FALSE;
	else
		check_Str[8] = TRUE;
	scl_Z = _ttof(str);
	
	if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setScale(scl_X, scl_Y, scl_Z);

	if(selectedObject_INDEX_Array.size() > 1){
		//for(int i = 0 ; i < selectedObject_INDEX_Array.size() ; i++){

	
		
		vector3f centerOfObj(0,0,0);

		//object_Array[selectedObject_INDEX_Array[i]].setTranslate(pos_X, pos_Y, pos_Z);
		for(int i = 0 ; i < selectedObject_INDEX_Array.size() ; i++){
			if(!check_Str[0])
				pos_X = object_Array[selectedObject_INDEX_Array[i]].gizmo.translate.x;
			if(!check_Str[1])
				pos_Y = object_Array[selectedObject_INDEX_Array[i]].gizmo.translate.y;
			if(!check_Str[2])
				pos_Z = object_Array[selectedObject_INDEX_Array[i]].gizmo.translate.z;
			if(!check_Str[3])
				rot_X = object_Array[selectedObject_INDEX_Array[i]].gizmo.rotate.x;
			if(!check_Str[4])
				rot_Y =object_Array[selectedObject_INDEX_Array[i]].gizmo.rotate.y;
			if(!check_Str[5])
				rot_Z = object_Array[selectedObject_INDEX_Array[i]].gizmo.rotate.z;
			if(!check_Str[6])
				scl_X = object_Array[selectedObject_INDEX_Array[i]].gizmo.scale.x;
			if(!check_Str[7])
				scl_Y =  object_Array[selectedObject_INDEX_Array[i]].gizmo.scale.y;
			if(!check_Str[8])
				scl_Z = object_Array[selectedObject_INDEX_Array[i]].gizmo.scale.z;

			object_Array[selectedObject_INDEX_Array[i]].setTranslate(pos_X, pos_Y, pos_Z);
			object_Array[selectedObject_INDEX_Array[i]].gizmo.translate_INIT = vector3f( pos_X, pos_Y, pos_Z);

			object_Array[selectedObject_INDEX_Array[i]].setRotate(rot_X, rot_Y, rot_Z);
			
			object_Array[selectedObject_INDEX_Array[i]].gizmo.scale_INIT = vector3f(scl_X, scl_Y, scl_Z);
			object_Array[selectedObject_INDEX_Array[i]].setScale(scl_X, scl_Y, scl_Z);
			centerOfObj = centerOfObj + object_Array[selectedObject_INDEX_Array[i]].center;
		}
			centerOfObjects_Gizmo.center = vector3f(centerOfObj.x/selectedObject_INDEX_Array.size(), centerOfObj.y/selectedObject_INDEX_Array.size(), centerOfObj.z/selectedObject_INDEX_Array.size());
			centerOfObjects_Gizmo.translate_INIT = vector3f(centerOfObj.x/selectedObject_INDEX_Array.size(), centerOfObj.y/selectedObject_INDEX_Array.size(), centerOfObj.z/selectedObject_INDEX_Array.size());
			centerOfObjects_Gizmo.translate = centerOfObjects_Gizmo.translate_INIT ;
			centerOfObjects_Gizmo.center = centerOfObjects_Gizmo.translate;
			centerOfObjects_Gizmo.scale.set(1,1,1);
	}

		OnEnKillfocusId();

	save_EditEvent();
}

void CGizmoTool_Ver_DigDlg::OnKey_Delete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(selectedObject_INDEX_Array.size() != 0){
		for(int i = selectedObject_INDEX_Array.size() -1 ; i >= 0 ; i--){
		object_Array.erase(object_Array.begin() + selectedObject_INDEX_Array[i]);

		listBox_Object.DeleteString(selectedObject_INDEX_Array[i]);
		selectedObject_INDEX_Array.pop_back();
				
		}
		if(check_Draw_centerGizmo)
			check_Draw_centerGizmo=FALSE;

		save_EditEvent();
		
	}
	clearObjectInformEdit();
}

void CGizmoTool_Ver_DigDlg::OnKey_Space()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	//GL_LINE_LOOP GL_TRIANGLE_STRIP  GL_TRIANGLE_FAN

	if(gl_ObjectType == GL_TRIANGLE_FAN)
		gl_ObjectType = GL_LINE_LOOP;
	else if(gl_ObjectType == GL_LINE_LOOP)
		gl_ObjectType = GL_TRIANGLE_STRIP;
	else
		gl_ObjectType = GL_TRIANGLE_FAN;

	for(int i = 0; i < object_Array.size(); i++){
		object_Array[i].setObjectMode(gl_ObjectType);
	}
	save_EditEvent();
}

void CGizmoTool_Ver_DigDlg::OnKey_CtrlZ()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	load_EditEvent();
}

void CGizmoTool_Ver_DigDlg::OnKey_CtrlY()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
		reload_EditEvent();
}

void CGizmoTool_Ver_DigDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}

HBRUSH CGizmoTool_Ver_DigDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	UINT nID = pWnd->GetDlgCtrlID();

	switch(nCtlColor)
    {
    case CTLCOLOR_DLG:
        return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;
	case CTLCOLOR_STATIC:
		for(int i = 1033 ; i <= 1047 ; i++){
			if(nID == i){
				pDC->SetBkMode(TRANSPARENT);      // 배경투명
				pDC->SetTextColor(RGB(255, 255,255));  // 글자 색
			    pDC->SetBkColor(RGB(0, 128, 0));  // 배경 색
				 return (HBRUSH)GetStockObject(NULL_BRUSH);
			}
		}
		//if(nID == 1000){
			//TRACE("ASD\n");
			//CBrush brush(RGB(0, 0,0));
			//pDC->SelectObject(&brush); 
		//	return (HBRUSH)GetStockObject(NULL_BRUSH);
		//}
        break;
	case CTLCOLOR_MAX:
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;
	case CTLCOLOR_EDIT:
			//pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(200, 200,200));  // 글자 색
		 pDC->SetBkColor(RGB(61, 61,61));  // 배경 색
		 if(nID == IDC_FRAME){
			 pDC->SetTextColor(RGB(255, 255,255));
			 pDC->SetBkColor(RGB(1, 60,120));
		 }
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;
	case CTLCOLOR_LISTBOX:
			//pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(240, 40,120));  // 글자 색
		 pDC->SetBkColor(RGB(61, 61,61));  // 배경 색
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;
	case CTLCOLOR_MSGBOX:
			//pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(200, 200,200));  // 글자 색
		 pDC->SetBkColor(RGB(61, 61,61));  // 배경 색
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;
	case CTLCOLOR_BTN:
			pDC->SetBkMode(TRANSPARENT);
			//pDC->SetTextColor(RGB(200, 200,200));  // 글자 색
		 pDC->SetBkColor(RGB(61, 61,61));  // 배경 색
		return (HBRUSH)GetStockObject(DKGRAY_BRUSH);
        break;

    }    


	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CGizmoTool_Ver_DigDlg::OnBnClickedBtnCube()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ObjectInform newCube(objectID++, _T("CUBE"), vector3f(-2,2,-2), vector3f(2,-2,2));
	object_Array.push_back(newCube);

	CString str;
	str.Format(_T("CUBE         ID : %d"),objectID-1);
	listBox_Object.InsertString( object_Array.size()-1, str);

	

	for(int i = 0 ; i <selectedObject_INDEX_Array.size() ; i++){
		object_Array[selectedObject_INDEX_Array[i]].check_SelectedObject = FALSE;
	}

	selectedObject_INDEX_Array.clear();
	selectedObject_INDEX_Array.push_back(object_Array.size()-1);

	setObjectInformEdit(selectedObject_INDEX_Array[0]);
	save_EditEvent();
	//object_Array[selectedObject_INDEX_Array[0]].check_SelectedObject = TRUE;
}

void CGizmoTool_Ver_DigDlg::OnBnClickedBtnSphere()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ObjectInform newSphere(objectID++, _T("SPHERE"), vector3f(-2,2,-2), vector3f(2,-2,2));
	object_Array.push_back(newSphere);
	
	CString str;
	str.Format(_T("SPHERE     ID : %d"),objectID-1);
	listBox_Object.InsertString( object_Array.size()-1, str);

	

	for(int i = 0 ; i <selectedObject_INDEX_Array.size() ; i++){
		object_Array[selectedObject_INDEX_Array[i]].check_SelectedObject = FALSE;
	}

	selectedObject_INDEX_Array.clear();
	selectedObject_INDEX_Array.push_back(object_Array.size()-1);

	setObjectInformEdit(selectedObject_INDEX_Array[0]);
	save_EditEvent();
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusPosX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GLfloat pos_X;
	GLfloat pos_Y;
	GLfloat pos_Z;
	edit_Pos_X.GetWindowTextW(str);
	pos_X = _ttof(str);
	edit_Pos_Y.GetWindowTextW(str);
	pos_Y = _ttof(str);
	edit_Pos_Z.GetWindowTextW(str);
	pos_Z = _ttof(str);
	
	if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setTranslate(pos_X, pos_Y, pos_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusPosY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GLfloat pos_X;
	GLfloat pos_Y;
	GLfloat pos_Z;
	edit_Pos_X.GetWindowTextW(str);
	pos_X = _ttof(str);
	edit_Pos_Y.GetWindowTextW(str);
	pos_Y = _ttof(str);
	edit_Pos_Z.GetWindowTextW(str);
	pos_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setTranslate(pos_X, pos_Y, pos_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusPosZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GLfloat pos_X;
	GLfloat pos_Y;
	GLfloat pos_Z;
	edit_Pos_X.GetWindowTextW(str);
	pos_X = _ttof(str);
	edit_Pos_Y.GetWindowTextW(str);
	pos_Y = _ttof(str);
	edit_Pos_Z.GetWindowTextW(str);
	pos_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setTranslate(pos_X, pos_Y, pos_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusRotX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GLfloat rot_X;
	GLfloat rot_Y;
	GLfloat rot_Z;
	edit_Rot_X.GetWindowTextW(str);
	rot_X = _ttof(str);
	edit_Rot_Y.GetWindowTextW(str);
	rot_Y = _ttof(str);
	edit_Rot_Z.GetWindowTextW(str);
	rot_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setRotate(rot_X, rot_Y, rot_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusRotY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString str;
	GLfloat rot_X;
	GLfloat rot_Y;
	GLfloat rot_Z;
	edit_Rot_X.GetWindowTextW(str);
	rot_X = _ttof(str);
	edit_Rot_Y.GetWindowTextW(str);
	rot_Y = _ttof(str);
	edit_Rot_Z.GetWindowTextW(str);
	rot_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setRotate(rot_X, rot_Y, rot_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusRotZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString str;
	GLfloat rot_X;
	GLfloat rot_Y;
	GLfloat rot_Z;
	edit_Rot_X.GetWindowTextW(str);
	rot_X = _ttof(str);
	edit_Rot_Y.GetWindowTextW(str);
	rot_Y = _ttof(str);
	edit_Rot_Z.GetWindowTextW(str);
	rot_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setRotate(rot_X, rot_Y, rot_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusSclX()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GLfloat scl_X;
	GLfloat scl_Y;
	GLfloat scl_Z;
	edit_Scl_X.GetWindowTextW(str);
	scl_X = _ttof(str);
	edit_Scl_Y.GetWindowTextW(str);
	scl_Y = _ttof(str);
	edit_Scl_Z.GetWindowTextW(str);
	scl_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setScale(scl_X, scl_Y, scl_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusSclY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString str;
	GLfloat scl_X;
	GLfloat scl_Y;
	GLfloat scl_Z;
	edit_Scl_X.GetWindowTextW(str);
	scl_X = _ttof(str);
	edit_Scl_Y.GetWindowTextW(str);
	scl_Y = _ttof(str);
	edit_Scl_Z.GetWindowTextW(str);
	scl_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setScale(scl_X, scl_Y, scl_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusSclZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString str;
	GLfloat scl_X;
	GLfloat scl_Y;
	GLfloat scl_Z;
	edit_Scl_X.GetWindowTextW(str);
	scl_X = _ttof(str);
	edit_Scl_Y.GetWindowTextW(str);
	scl_Y = _ttof(str);
	edit_Scl_Z.GetWindowTextW(str);
	scl_Z = _ttof(str);
	
if(selectedObject_INDEX_Array.size() == 1)
		object_Array[selectedObject_INDEX_Array[0]].setScale(scl_X, scl_Y, scl_Z);
}

void CGizmoTool_Ver_DigDlg::OnEnKillfocusId()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	edit_ID.GetWindowTextW(str);
	if(!str.Compare(_T("-"))){ 
		//setObjectInformEdit(-1);
	}
	else{
		TRACE("ID NEW \n");
		GLint id = _ttof(str);

		selectedObject_INDEX_Array.clear();

		for(int i = 0; i < object_Array.size(); i++){

			object_Array[i].check_SelectedObject = FALSE;
			//selectedObject_INDEX = -1;
			//setObjectInformEdit(selectedObject_INDEX);

			if(object_Array[i].object_ID == id){
				object_Array[i].check_SelectedObject = TRUE;
				object_Array[i].check_DrawGizmo = TRUE;
				selectedObject_INDEX_Array.push_back(i);
				setObjectInformEdit(selectedObject_INDEX_Array[0]);

				//setObjectInformEdit(selectedObject_INDEX);
			}
		}
		if(selectedObject_INDEX_Array.size() == 0)
			clearObjectInformEdit();
	}
}

void CGizmoTool_Ver_DigDlg::OnLbnSelchangeList2()
{
	TRACE("%d\n",listBox_Object.GetCurSel());
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for(int i = 0; i < object_Array.size(); i++){
		object_Array[i].check_SelectedObject = FALSE;
	}
	//clearObjectInformEdit();
	if(listBox_Object.GetCurSel() >= 0){
		selectedObject_INDEX_Array.clear();
		object_Array[listBox_Object.GetCurSel()].check_SelectedObject = TRUE;
		object_Array[listBox_Object.GetCurSel()].check_DrawGizmo = TRUE;
		selectedObject_INDEX_Array.push_back(listBox_Object.GetCurSel());

		if(selectedObject_INDEX_Array.size() != 0){
				setObjectInformEdit(selectedObject_INDEX_Array[0]);
				save_EditEvent();
		}
	}
}

void CGizmoTool_Ver_DigDlg::OnLbnDblclkList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	

	current_Camera = main_camera;
	OnKey_F();
}

void CGizmoTool_Ver_DigDlg::OnLbnKillfocusList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//listBox_Object.SetCurSel(-1);
}

void CGizmoTool_Ver_DigDlg::OnBnClickedBtnLight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(light_OnOff)
		light_OnOff = FALSE;
	else
		light_OnOff = TRUE;
}

void CGizmoTool_Ver_DigDlg::save_EditEvent(){
		redo_editEvent.clear();
		undo_redo temp;
		temp.un_gl_ObjectType = gl_ObjectType;

	    temp.un_selectedObject_INDEX_Array = selectedObject_INDEX_Array;
		temp.un_centerOfObjects_Gizmo = centerOfObjects_Gizmo;
		temp.un_check_Draw_centerGizmo = check_Draw_centerGizmo;
		//temp.un_selectedObject_INDEX = -1;
		temp.un_objectID = objectID;
		for(int i=0 ; i < object_Array.size() ; i++){
			ObjectInform temp_Object(-1, 0, vector3f(0,0,0), vector3f(0,0,0));
			temp_Object = object_Array[i];
			temp.un_object_Array.push_back(temp_Object);
		}

		
		undo_editEvent.push_back(temp);
		TRACE("save event %d\n", undo_editEvent.size());	
}

void CGizmoTool_Ver_DigDlg::load_EditEvent(){
	if(undo_editEvent.size() == 1){
		TRACE("undo 0\n");

	}
	else{
		redo_editEvent.push_back(undo_editEvent.back());
		undo_editEvent.pop_back();
		TRACE("undo %d\n", undo_editEvent.size());
		//selectedObject_INDEX_Array[0] = editEvent[editEvent.size() - 1].un_selectedObject_INDEX;
		selectedObject_INDEX_Array.clear();
		selectedObject_INDEX_Array = undo_editEvent[undo_editEvent.size() - 1].un_selectedObject_INDEX_Array;
		centerOfObjects_Gizmo = undo_editEvent[undo_editEvent.size() - 1].un_centerOfObjects_Gizmo;
		check_Draw_centerGizmo = undo_editEvent[undo_editEvent.size() - 1].un_check_Draw_centerGizmo;
		gl_ObjectType = undo_editEvent[undo_editEvent.size() - 1].un_gl_ObjectType;
		objectID = undo_editEvent[undo_editEvent.size() - 1].un_objectID;
		//for(int i=0 ; i < editEvent[editEvent.size() - 1].un_object_Array.size() ; i++){
		//	object_Array[i] = editEvent[editEvent.size() - 1].un_object_Array[i]; 
	//	}
		object_Array = undo_editEvent[undo_editEvent.size() - 1].un_object_Array; 
		

		//TRACE("%f\n", editEvent[editEvent.size() - 1].un_object_Array[0].gizmo->translate.x);

		

		listBox_Object.ResetContent();

		CString str;
		for(int i = 0; i < object_Array.size() ; i++){
			if(object_Array[i].object_Type == _T("CUBE"))
				str.Format(_T("CUBE         ID : %d"),object_Array[i].object_ID);
			else
				str.Format(_T("SPHERE     ID : %d"),object_Array[i].object_ID);

			listBox_Object.InsertString( i, str);
		}

		
	}

		if(selectedObject_INDEX_Array.size() != 0)
				setObjectInformEdit(selectedObject_INDEX_Array[0]);
			else
				clearObjectInformEdit();

}

void CGizmoTool_Ver_DigDlg::reload_EditEvent(){
	if(redo_editEvent.size() == 0){
		TRACE("redo empty\n");
	}
	else{

		undo_editEvent.push_back(redo_editEvent.back());

		TRACE("redo %d\n", redo_editEvent.size());

		selectedObject_INDEX_Array.clear();
		selectedObject_INDEX_Array = redo_editEvent.back().un_selectedObject_INDEX_Array;
		centerOfObjects_Gizmo = redo_editEvent.back().un_centerOfObjects_Gizmo;
		check_Draw_centerGizmo = redo_editEvent.back().un_check_Draw_centerGizmo;
		gl_ObjectType = redo_editEvent.back().un_gl_ObjectType;
		objectID = redo_editEvent.back().un_objectID;

		object_Array = redo_editEvent.back().un_object_Array; 

		listBox_Object.ResetContent();

		CString str;
		for(int i = 0; i < object_Array.size() ; i++){
			if(object_Array[i].object_Type == _T("CUBE"))
				str.Format(_T("CUBE         ID : %d"),object_Array[i].object_ID);
			else
				str.Format(_T("SPHERE     ID : %d"),object_Array[i].object_ID);

			listBox_Object.InsertString( i, str);
		}

		
	

		if(selectedObject_INDEX_Array.size() != 0)
				setObjectInformEdit(selectedObject_INDEX_Array[0]);
			else
				clearObjectInformEdit();

		redo_editEvent.pop_back();
	}
}

void CGizmoTool_Ver_DigDlg::load_Last_EditEvent(){
	if(undo_editEvent.size() == 1){
		TRACE("undo 0\n");

	}
	else{
		TRACE("last undo %d\n", undo_editEvent.size());

		selectedObject_INDEX_Array.clear();
		selectedObject_INDEX_Array = undo_editEvent.back().un_selectedObject_INDEX_Array;
		centerOfObjects_Gizmo = undo_editEvent.back().un_centerOfObjects_Gizmo;
		check_Draw_centerGizmo = undo_editEvent.back().un_check_Draw_centerGizmo;
		gl_ObjectType = undo_editEvent.back().un_gl_ObjectType;
		objectID = undo_editEvent.back().un_objectID;
		object_Array = undo_editEvent.back().un_object_Array; 

		listBox_Object.ResetContent();

		CString str;
		for(int i = 0; i < object_Array.size() ; i++){
			if(object_Array[i].object_Type == _T("CUBE"))
				str.Format(_T("CUBE         ID : %d"),object_Array[i].object_ID);
			else
				str.Format(_T("SPHERE     ID : %d"),object_Array[i].object_ID);

			listBox_Object.InsertString( i, str);
		}

		
	}

		if(selectedObject_INDEX_Array.size() != 0)
				setObjectInformEdit(selectedObject_INDEX_Array[0]);
			else
				clearObjectInformEdit();

}

void CGizmoTool_Ver_DigDlg::play_animate(GLint frame){
	
	//GLint frame = 30;
	GLint start_Index = -1;
	GLint end_Index = -1;
	if(undo_editEvent.size() <= 2){
		check_Play_Animate = FALSE;
		return;
	}

	GLint framePerStack = frame/(undo_editEvent.size()-2);
	//TRACE("%d\n", framePerStack);
	if( count_Frame % framePerStack == 0){

		start_Index = count_Frame/framePerStack + 1;
		end_Index = start_Index + 1;

		if(end_Index == undo_editEvent.size()){
			start_Index -= 1;
			end_Index = 0;
			count_Frame = frame;
			
		}
		else{
			startIndex_object_Array = undo_editEvent[start_Index].un_object_Array;
			endIndex_object_Array = undo_editEvent[end_Index].un_object_Array;



			selectedObject_INDEX_Array.clear();
			//GLint un_selectedObject_INDEX;
			gl_ObjectType = GL_TRIANGLE_STRIP;
			//objectID;
			//centerOfObjects_Gizmo;
			check_Draw_centerGizmo = FALSE;
			object_Array = startIndex_object_Array;
			if(startIndex_object_Array.size() > endIndex_object_Array.size()){
				for(int i = startIndex_object_Array.size() - endIndex_object_Array.size() ; i > 0 ; i--)
					endIndex_object_Array.push_back(startIndex_object_Array[startIndex_object_Array.size()-i]);
			}
			for(int i = 0 ; i < object_Array.size() ; i++)
				object_Array[i].check_SelectedObject = FALSE;
		}
	}

	if(end_Index != 0){
		for(int i = 0 ; i < object_Array.size() ; i++){
			if(endIndex_object_Array[i].object_ID == startIndex_object_Array[i].object_ID){
				vector3f diff_Trans = endIndex_object_Array[i].center - startIndex_object_Array[i].center;
				vector3f diff_Scale = endIndex_object_Array[i].gizmo.scale - startIndex_object_Array[i].gizmo.scale;

				object_Array[i].setTranslate( object_Array[i].center.x + diff_Trans.x/framePerStack  ,  
					object_Array[i].center.y + diff_Trans.y/framePerStack,   
					object_Array[i].center.z + diff_Trans.z/framePerStack);

				object_Array[i].setScale( object_Array[i].gizmo.scale.x + diff_Scale.x/framePerStack  ,  
					object_Array[i].gizmo.scale.y + diff_Scale.y/framePerStack,   
					object_Array[i].gizmo.scale.z + diff_Scale.z/framePerStack);

				if(endIndex_object_Array[i].gizmo.stack_Rotate.size() != 0 && (endIndex_object_Array[i].gizmo.stack_Rotate.size() > object_Array[i].gizmo.stack_Rotate.size())){
					object_Array[i].gizmo.current_Rotate.axis = endIndex_object_Array[i].gizmo.stack_Rotate.back().axis;
					object_Array[i].gizmo.current_Rotate.rotate_Axis = endIndex_object_Array[i].gizmo.stack_Rotate.back().rotate_Axis;
					if(endIndex_object_Array[i].gizmo.key_check_E)
						object_Array[i].gizmo.current_Rotate.angle += endIndex_object_Array[i].gizmo.stack_Rotate.back().angle/framePerStack;
				}
			}
		}
		count_Frame++;
	}
}

void CGizmoTool_Ver_DigDlg::OnBnClickedPlay()
{
	if(!check_Play_Animate){
		check_Play_Animate = TRUE;
		btn_Play.SetWindowTextW(_T("STOP"));

		CString str;
		GLfloat frame;
		edit_Frame.GetWindowTextW(str);
		frame = _ttof(str);
		slider_AniamteFrame.SetRange(0, (GLint)frame);
		slider_AniamteFrame.SetTicFreq(10);
	}
	else{
		check_Play_Animate = FALSE;
		btn_Play.SetWindowTextW(_T("PLAY"));
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGizmoTool_Ver_DigDlg::OnBnClickedBtnUndo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnKey_CtrlZ();
}

void CGizmoTool_Ver_DigDlg::OnBnClickedBtnRedo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnKey_CtrlY();
}


