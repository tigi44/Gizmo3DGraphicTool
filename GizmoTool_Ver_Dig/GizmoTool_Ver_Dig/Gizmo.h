
#pragma once

class Gizmo
{
public:
	
	struct rotateInform{
		GLfloat angle;
		vector3f axis;
		//vector3f center;
		//vector3f translate_rotate;
		vector3f rotate_Axis;
	};
	
	rotateInform current_Rotate;
	vector<rotateInform> stack_Rotate;
	
	vector3f testVec;
	vector3f testVec1;
	vector3f testVec2;

	BOOL hit_ObjectGizmo_X;
	BOOL hit_ObjectGizmo_Y;
	BOOL hit_ObjectGizmo_Z;
	BOOL hit_ObjectGizmo_CENTER;
	BOOL hit_ObjectGizmo_XY;
	BOOL hit_ObjectGizmo_YZ;
	BOOL hit_ObjectGizmo_ZX;


	BOOL key_check_W;
	BOOL key_check_R;
	BOOL key_check_E;

	//GLuint *gizmoSelectBuf;
	GLint pick_Hit_Count;
	GLint selectedObject_ID;

	//vector3f objectCenter;
	vector3f center;
	vector3f translate;
	vector3f rotate; // 각 축 별 각도
	vector3f scale;
	vector3f scale_axis_R;

	vector3f translate_INIT;
	vector3f rotate_INIT; // 각 축 별 각도
	vector3f scale_INIT;

	vector3f x_axis;
	vector3f y_axis;
	vector3f z_axis;



	BOOL lbtnDown_X;
	BOOL lbtnDown_Y;
	BOOL lbtnDown_Z;
	BOOL lbtnDown_CENTER;
	BOOL lbtnDown_XY;
	BOOL lbtnDown_YZ;
	BOOL lbtnDown_ZX;

	BOOL check_selected;

	GLfloat rotateGab;
	GLint count_Gizmo;
	//vector3f dragGizmo_Center;
	
	CPoint beforePt;
	CPoint rotatePt;
	vector3f spherePoint;
	vector3f current_spherePoint;

	Camera current_Camera;

	vector3f beforePt3f;
public:
	Gizmo(void);
	~Gizmo(void);

	void DrawGizmo();
	void DrawGizmo_ViewMode();
	void DrawGizmo_Axis();
	void gizmo_Picking(CPoint cp,   Camera *camera);

	BOOL getHitGizmo();

	void setCheck_Selected(BOOL selected);

	void setHit_X(BOOL hit);
	void setHit_Y(BOOL hit);
	void setHit_Z(BOOL hit);
	void setHit_CENTER(BOOL hit);
	void setHit_XY(BOOL hit);
	void setHit_YZ(BOOL hit);
	void setHit_ZX(BOOL hit);

	BOOL getHit_X();
	BOOL getHit_Y();
	BOOL getHit_Z();
	BOOL getHit_CENTER();
	BOOL getHit_XY();
	BOOL getHit_YZ();
	BOOL getHit_ZX();

	BOOL gizmo_Mouse_Evnet(MSG *pMsg, Camera *camera);

	void gizmo_Translate(GLfloat gab, vector3f axis);
	void gizmo_Rotate(GLfloat angle, vector3f axis);
	void gizmo_Scale(GLfloat size, vector3f axis);

	void keyEvent_W();
	void keyEvent_E();
	void keyEvent_R();
	void keyEvent_C();



	//void rotate_Axis_xyz(); 
	void rotate_Axis_xyz_2(GLfloat angle, vector3f axis);

	void setRotate(GLfloat angle, vector3f axis);
	void setCenter(vector3f gizmo_center);

	void setAxis(vector3f xAxis, vector3f xYxis,vector3f xZxis);
	vector3f setTranslate_afterRotate(GLfloat selected_Size, vector3f Gizmo_center); //센터 기즈모에서 실행
};

