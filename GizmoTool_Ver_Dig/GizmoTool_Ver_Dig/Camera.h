#pragma once
class Camera
{
public:
	struct camera_Perspective{
		 GLdouble m_fovy; 
		 GLdouble m_aspect; 
		 GLdouble m_zNear;
		 GLdouble m_zFar;
	}camera_Perspective;

	struct camera_Ortho{
		 GLdouble left; 
		 GLdouble right; 
		 GLdouble bottom;
		 GLdouble top;
		  GLdouble mnear;
		   GLdouble mfar; 
	}camera_Ortho;

	vector3f reset_center;
	vector3f reset_eye;
	vector3f reset_upvector;

	vector3f pos_center;
	vector3f pos_eye;
	vector3f pos_upvector;

	CPoint last_Point;
	vector3f pos_PickedRotatation;
	GLint count_posPicked;

	CRect client_Rect;

	BOOL check_LMouse;
	BOOL check_RMouse;
		GLenum check_Perspective_Ortho;

	BOOL key_check_Q;
	BOOL key_check_X; //'X'
	BOOL key_check_Z;

	GLdouble projection[16]; GLdouble modelView[16]; GLint viewPort[4];

	CString name;


public:
	Camera();
	Camera(vector3f eye, vector3f center, vector3f upvector);
	~Camera(void);

	void setPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	void perspective();

	void setOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble mnear, GLdouble mfar);
	void Ortho();	

	void Set_cameraView_Perspective_Ortho(BOOL type);
	BOOL Get_cameraView_Perspective_Ortho();
	void cameraView();

	//glOrtho (-10.0, 10.0, -10.0*(GLfloat)height/(GLfloat)width,10.0*(GLfloat)height/(GLfloat)width,-100.0, 1000.0);

	void setLookAt();
	//void setOrthoLookAt();
	void setLastPoint(CPoint cp);
	void setReset();
	void setEyeCenter(vector3f eye, vector3f center);
	void setPos_PickedRotatation(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]);

	void set_Count_pickedPos();
	BOOL get_Count_pickedPos();
	void clear_Count_pickedPos();

	void set_Client_Rect(CRect rect);
	void set_Projection_Modelview_viewport(GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]);

	vector3f getLookVector();

	void zoomIn();
	void zoomOut();
	void camera_DirectionKey(UINT nChar);

	void camera_translate(CPoint cp);

	void camera_First_Rotate(CPoint cp);
	void camera_Center_Rotate(CPoint cp);
	void camera_Pick_Rotate(CPoint cp);

	BOOL camera_Mouse_Evnet(MSG *pMsg);
	BOOL camera_Key_Event(MSG *pMsg);

	void camera_KeyReset();

	void keyEvent_F();
	void keyEvent_X();
	void keyEvent_Z();
	void keyEvent_Q();
	void keyEvent_O();

	void keyEvent_Up();
	void keyEvent_Down();
	void keyEvent_Left();
	void keyEvent_Right();

};

