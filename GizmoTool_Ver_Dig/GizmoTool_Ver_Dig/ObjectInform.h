
#pragma once
class ObjectInform
{

public:	

		vector3f center;

		vector3f leftTopBack_pos;
		vector3f RightBottomFront_pos;
		GLfloat sphere_Size;

		GLfloat color[4];

		GLenum gl_Object;
		GLenum check_SelectedObject;

		vector3f x_axis;
		vector3f y_axis;
		vector3f z_axis;

		//Gizmo *gizmo;
		Gizmo gizmo;
		
		
		
		int object_ID;
		CString object_Type;


		CPoint m_ptStart;
		CPoint m_ptEnd;
		CPoint m_ptCenter;
		BOOL check_KeyDown;
		BOOL check_DragBox;
		BOOL check_ObjectDrag;
		BOOL check_MouseMove;
		BOOL check_DrawGizmo;

public:
	ObjectInform();
	ObjectInform(int id, CString type, vector3f ltb, vector3f rbf);
	~ObjectInform(void);

	void object_Picking(CPoint cp, Camera *camera);
	
	void Draw();
	void DrawCube();
	void DrawSphere();
	
	void setObjectMode(GLenum mode);
	void setCheckDrag(BOOL drag);

	void setColor(GLfloat *setColor);
	void setTranslate(GLfloat x, GLfloat y, GLfloat z);
	void setScale(GLfloat x, GLfloat y, GLfloat z);
	void setRotate(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

	vector3f getPosition();
	vector3f getRotate();
	vector3f getScale();

	
	BOOL object_Event(MSG* pMsg, Camera *camera);

	void keyEvent_W();
	void keyEvent_E();
	void keyEvent_R();
	void keyEvent_C();

	void keyEvent_Q();
	void keyEvent_Z();
	void keyEvent_X();
	
	BOOL getHitGizmo();

};

