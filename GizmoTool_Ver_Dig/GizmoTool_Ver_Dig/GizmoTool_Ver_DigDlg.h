
// GizmoTool_Ver_DigDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "afxcmn.h"


// CGizmoTool_Ver_DigDlg 대화 상자
class CGizmoTool_Ver_DigDlg : public CDialogEx
{
// 생성입니다.
public:
	CGizmoTool_Ver_DigDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GIZMOTOOL_VER_DIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	
public :
	Camera *main_camera;
	Camera *top_camera;
	Camera *side_camera;
	Camera *current_Camera;
	Camera *default_Camera;

	struct basic_Plane_Point{
		GLint top;
		GLint left;
		GLint width;
		GLint height;
	}basic_Plane_Point;

	struct undo_redo{
		vector<GLint> un_selectedObject_INDEX_Array;
		//GLint un_selectedObject_INDEX;
		GLenum un_gl_ObjectType;
		GLint un_objectID;
		Gizmo un_centerOfObjects_Gizmo;
		BOOL un_check_Draw_centerGizmo;
		vector<ObjectInform> un_object_Array;
	};
	vector<undo_redo> undo_editEvent;
	vector<undo_redo> redo_editEvent;

	void save_EditEvent();
	void load_EditEvent();
	void reload_EditEvent();
	void load_Last_EditEvent();
	void play_animate(GLint frame);


	GLdouble projection[16]; GLdouble modelView[16]; GLint viewPort[4];
	GLdouble projection1[16]; GLdouble modelView1[16]; GLint viewPort1[4];
	GLdouble projection2[16]; GLdouble modelView2[16]; GLint viewPort2[4];

	//CPoint currentView_topleft;


	void ReSizeGLScene(GLsizei width, GLsizei heght, GLenum viewNumber);
	void InitGL();
	void basic_Plane(Camera *view_Camera);
	void drag_Box();
	void DrawScene();
	//void object_Picking(CPoint cp,  Camera *camera);

	//GLint selectedObject_INDEX;
	vector<GLint> selectedObject_INDEX_Array;
	GLenum gl_ObjectType;
	GLint objectID;

	vector<ObjectInform> object_Array;
	//Gizmo *std_Gizmo;
	Gizmo std_Gizmo;
	Gizmo centerOfObjects_Gizmo;
	Gizmo temp;
	//ObjectInform exnewcube;

	void play_SideView();
	void play_TopView();
	void play_MainView();
	void play_Main_Gizmo();
	void play_Top_Gizmo();
	void play_Side_Gizmo();

	GLint count_Frame;
	vector<ObjectInform> startIndex_object_Array;
	vector<ObjectInform> endIndex_object_Array;

	BOOL check_Play_Animate;
	BOOL check_Draw_centerGizmo;
	BOOL check_CenterGizmo_Transform;
	BOOL check_Object_Transform;
	BOOL check_MouseView;
	BOOL bound_Line;
	BOOL bound_horizontal_Line;
	BOOL check_bound_Line;
	BOOL check_bound_horizontal_Line;
	CRect vertical_Line;
	CRect horizontal_Line;
	BOOL light_OnOff;
	BOOL check_MainFocus;
	BOOL check_TopFocus;
	BOOL check_SideFocus;


	void setObjectInformEdit(int selectedID);
	void clearObjectInformEdit();

	vector3f inf_plane;
	vector3f mouse_point3f;
	CPoint m_ptStart, m_ptEnd;
	BOOL check_DrawRectangle;
	BOOL check_Key_Q;
	BOOL check_Key_Z;
	BOOL check_Key_X;
	BOOL check_Key_P;
	GLfloat *buffer_for_blk_main;
	GLfloat *buffer_for_blk_top;
	GLfloat *buffer_for_blk_side;

public:
	HGLRC m_hRC[3];
	CDC *m_hDC[3];
	CRect sizeRect[3];

	HGLRC m_hRC_GIZMO[3];
	CDC *m_hDC_GIZMO[3];
	CRect sizeRect_GIZMO[3];

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

	
	afx_msg void OnTimer(UINT_PTR nIDEvent);



	afx_msg void OnClose();	

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKey_F();
	HACCEL hAccelTable;
//	afx_msg void OnKey_UP();
	afx_msg void OnKey_Down();
	afx_msg void OnKey_Up();
	afx_msg void OnKey_Right();
	afx_msg void OnKey_Left();
	afx_msg void OnKey_X();
	afx_msg void OnKey_Z();
	afx_msg void OnKey_Q();
	afx_msg void OnKey_O();
	afx_msg void OnKey_W();
	afx_msg void OnKey_E();
	afx_msg void OnKey_R();
	afx_msg void OnKey_Alt();
	afx_msg void OnKey_Enter();
	afx_msg void OnKey_Delete();
	afx_msg void OnKey_Space();
	afx_msg void OnKey_P();
	afx_msg void OnKey_C();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	CEdit edit_Pos_X;
	CEdit edit_Pos_Y;
	CEdit edit_Pos_Z;
	CEdit edit_Rot_X;
	CEdit edit_Rot_Y;
	CEdit edit_Rot_Z;
	CEdit edit_Scl_X;
	CEdit edit_Scl_Y;
	CEdit edit_Scl_Z;
	CEdit edit_ID;
	afx_msg void OnBnClickedBtnCube();
	CBitmapButton btn_Add_CUBE;
	CBitmapButton btn_Add_SPHERE;

	afx_msg void OnEnKillfocusPosX();
	afx_msg void OnEnKillfocusPosY();
	afx_msg void OnEnKillfocusPosZ();
	afx_msg void OnEnKillfocusRotX();
	afx_msg void OnEnKillfocusRotY();
	afx_msg void OnEnKillfocusRotZ();
	afx_msg void OnEnKillfocusSclX();
	afx_msg void OnEnKillfocusSclY();
	afx_msg void OnEnKillfocusSclZ();
	afx_msg void OnKey_CtrlZ();
	afx_msg void OnKey_CtrlY();

	CListBox listBox_Object;

	afx_msg void OnEnKillfocusId();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnSphere();
	
	
	afx_msg void OnLbnDblclkList2();
	afx_msg void OnLbnKillfocusList2();
	afx_msg void OnBnClickedBtnLight();
	afx_msg void OnLbnSelchangeList2();

	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedPlay();
	CEdit edit_Frame;
	CSliderCtrl slider_AniamteFrame;
	CEdit edit_Current_Frame;
	CButton btn_Undo;
	CButton btn_Redo;
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnRedo();
	CButton btn_Play;

	CStatic picture_Ctrl_TOPVIEW;
	CStatic picture_Ctrl_SIDEVIEW;
	CStatic picture_Ctrl_MAINVIEW;


	CEdit edit_Pos_Mouse;
};
