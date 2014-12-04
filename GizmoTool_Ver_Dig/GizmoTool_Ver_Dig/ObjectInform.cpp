#include "StdAfx.h"
#include "ObjectInform.h"

#define PI 3.14159265358979323846
GLfloat basic_color[4] = {0.9f, 0.1f, 0.4f, 1.0f};
 GLfloat selected_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
   GLfloat basic_Line_color[4] = {0.2f, 0.2f, 0.2f, 0.4f};
  GLfloat slected_Line_color[4] = {0.0f, 1.0f, 0.9f, 0.4f};

 ObjectInform::ObjectInform()
{
	center.x = 0;
	center.y = 0;
	center.z = 0;

	gl_Object =  GL_TRIANGLE_FAN;
	check_SelectedObject = TRUE;
	setColor(basic_color);

	check_MouseMove = FALSE;
	check_DragBox = FALSE;
	check_KeyDown = FALSE;
	check_DrawGizmo = TRUE;
	check_ObjectDrag = FALSE;
}
ObjectInform::ObjectInform(int id, CString type, vector3f ltb, vector3f rbf)
{
	
	center.x = (rbf.x + ltb.x)/2;
	center.y = (rbf.y + ltb.y)/2;
	center.z = (rbf.z + ltb.z)/2;

	sphere_Size = rbf.x - ltb.x;

	leftTopBack_pos.setV(ltb);


	RightBottomFront_pos.x = rbf.x;
	RightBottomFront_pos.y = rbf.y;
	RightBottomFront_pos.z = rbf.z;


	center.x = 0;
	center.y = 0;
	center.z = 0;

	
	gl_Object =  GL_TRIANGLE_FAN;
	check_SelectedObject = TRUE;
	setColor(basic_color);

		x_axis.x=1.f;
		x_axis.y=0.f;
		x_axis.z=0.f;

		y_axis.x=0.f;
		y_axis.y=1.f;
		y_axis.z=0.f;

		z_axis.x=0.f;
		z_axis.y=0.f;
		z_axis.z=1.f;
		object_ID = id;
		object_Type = type;

	//gizmo= new Gizmo;
	//m_ptStart.x = -1;
	check_MouseMove = FALSE;
	check_DragBox = FALSE;
	check_KeyDown = FALSE;
	check_DrawGizmo = TRUE;
	check_ObjectDrag = FALSE;
}


ObjectInform::~ObjectInform(void)
{
	//delete gizmo;
	//delete gizmo_Object;
	//delete selectBuf;
}


void ObjectInform::setTranslate(GLfloat x, GLfloat y, GLfloat z){
	/*
	if(x - gizmo.translate.x != 0)
		gizmo.gizmo_Translate( (x - gizmo.translate.x) / 0.004, vector3f(1,0,0));
	else if(y - gizmo.translate.y != 0)
		gizmo.gizmo_Translate( (y - gizmo.translate.y) / 0.004, vector3f(0,1,0));
	else if(z - gizmo.translate.z != 0)
		gizmo.gizmo_Translate( (z - gizmo.translate.z) / 0.004, vector3f(0,0,1));
		*/
	gizmo.translate = vector3f(x,y,z);
	gizmo.center = vector3f(x,y,z);
	center = gizmo.center;


}
void ObjectInform::setScale(GLfloat x, GLfloat y, GLfloat z){
		gizmo.scale.x = x;
		gizmo.scale.y = y;
		gizmo.scale.z = z;
}
void ObjectInform::setRotate(GLfloat angle_x, GLfloat angle_y, GLfloat angle_z){
		
		angle_x = angle_x - gizmo.rotate.x;
		angle_y -= gizmo.rotate.y;
		angle_z -= gizmo.rotate.z;
		//TRACE("ANGLE %f, %f, %f\n",angle_x, angle_y,  angle_z);

		if(angle_x != 0){
			gizmo.rotate.x += angle_x;
			gizmo.setRotate(angle_x, vector3f(1,0,0));
			//TRACE("XXX");
		}

		else if(angle_y != 0){
			gizmo.rotate.y += angle_y;
			gizmo.setRotate(angle_y, vector3f(0,1,0));
				//TRACE("YYY");
		}

		else if(angle_z != 0){
			gizmo.rotate.z += angle_z;
			gizmo.setRotate(angle_z, vector3f(0,0,1));
			//TRACE("ZZZ");
		}
}




void ObjectInform::object_Picking(CPoint cp,  Camera *camera){
		int hits_count = 0;
		//int viewport[4]; //[2]->width, [3]->height
		//delete selectBuf;
		GLuint selectBuf[128];
		
		glSelectBuffer(128, selectBuf);

		cp.SetPoint((int)cp.x - camera->client_Rect.left, (int)cp.y - camera->client_Rect.top);
		//TRACE("%d, %d\n",cp.x,cp.y );
		//glGetIntegerv(GL_VIEWPORT, viewport);
		//camera->setLookAt();
		glRenderMode(GL_SELECT);

		glMatrixMode(GL_PROJECTION);

		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(cp.x , camera->viewPort[3] - cp.y, 4, 4, camera->viewPort);
		
		camera->cameraView();

		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();

		Draw();
	

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glFlush();

		hits_count = glRenderMode(GL_RENDER); //ÃÑ ¼±ÅÃµÈ hits ¼ö
		//TRACE("hit : %d\n", hits_count);
		glMatrixMode(GL_MODELVIEW);
		//Invalidate(FALSE);

		//selectedObject_ID = selectBuf[3];
	
		if(selectBuf[0] == 1){
			//TRACE("%u, %u, %u, %u\n", selectBuf[0],selectBuf[1],selectBuf[2], selectBuf[3]);
		}
			if(selectBuf[0] == 1){
				check_SelectedObject = TRUE;
				check_DrawGizmo = TRUE;
			}
			else{
				check_SelectedObject = FALSE;
				check_DrawGizmo = TRUE;
				//check_DrawGizmo = FALSE;
			}
			
		
		
}

void ObjectInform::Draw(){

	gizmo.setCheck_Selected(check_SelectedObject);
	
			glPushMatrix();
			glPointSize(30.f);
			glBegin(GL_POINTS);
			glColor4f(1.f, 0.5f, 0.0f, 0.0f);

			//glVertex3f(center.x, center.y, center.z);
			glEnd();
			glPointSize(1.f);
			glPopMatrix();




	if(!object_Type.Compare(_T("CUBE"))){
			DrawCube();
		}
	else if(!object_Type.Compare(_T("SPHERE"))){
			DrawSphere();
		}

	//TRACE("GIZMO CENTER :");
	//gizmo.center.printVector();
}

void ObjectInform::DrawCube(){
	
	//TRACE("%f, %f, %f, %f\n", color[0],color[1],color[2],color[3]);
		
	glInitNames();
		
		//glTranslatef(translate.x, translate.y, translate.z);
		//glScalef(scale.x, scale.y, scale.z);
	
		GLenum type;
		GLfloat gap=0;


		if(check_SelectedObject){
				setColor(selected_color);	
				//gizmo->DrawGizmo();		
		}
			else{
				
				setColor(basic_color);
			}

		for(int i = 0; i < 2 ; i++){
			glPushName(object_ID);
			glPushMatrix();

		center = gizmo.center;
		

		glTranslatef(gizmo.translate.x, gizmo.translate.y, gizmo.translate.z);
		
		

		
		//glTranslatef(-gizmo.current_Rotate.rotate_Axis.x, -gizmo.current_Rotate.rotate_Axis.y, -gizmo.current_Rotate.rotate_Axis.z);
		glRotatef(gizmo.current_Rotate.angle, gizmo.current_Rotate.axis.x, gizmo.current_Rotate.axis.y, gizmo.current_Rotate.axis.z);
		//glTranslatef(gizmo.current_Rotate.rotate_Axis.x, gizmo.current_Rotate.rotate_Axis.y, gizmo.current_Rotate.rotate_Axis.z);

		for ( int i = gizmo.stack_Rotate.size()-1 ; i >= 0 ; i--){
		//	glTranslatef(-gizmo.stack_Rotate[i].rotate_Axis.x, -gizmo.stack_Rotate[i].rotate_Axis.y, -gizmo.stack_Rotate[i].rotate_Axis.z);
			glRotatef(gizmo.stack_Rotate[i].angle, gizmo.stack_Rotate[i].axis.x, gizmo.stack_Rotate[i].axis.y, gizmo.stack_Rotate[i].axis.z); 
		//	glTranslatef(gizmo.stack_Rotate[i].rotate_Axis.x, gizmo.stack_Rotate[i].rotate_Axis.y, gizmo.stack_Rotate[i].rotate_Axis.z);
		}

		

		glScalef(gizmo.scale.x, gizmo.scale.y, gizmo.scale.z);
		

		if(i==1 && gl_Object != GL_TRIANGLE_FAN && gl_Object != GL_LINE_LOOP && !check_SelectedObject){
			glColor4fv(basic_Line_color);
			type = GL_LINE_LOOP;
			gap = 0.05;
		}
		else{
			glColor4fv(color);
			type = gl_Object;
			if(type == GL_TRIANGLE_FAN)
				type = GL_TRIANGLE_STRIP;
		}
		if(i==1 && check_SelectedObject){
			glColor4fv(slected_Line_color);
			type = GL_LINE_LOOP;
		}
		glLineWidth(2.f);
		vector3f nomalVector;
		
		
		glBegin(type);
			nomalVector.normalVector(vector3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();
		
		glBegin(type);
		nomalVector.normalVector(vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

		glBegin(type);
		nomalVector.normalVector(vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		glBegin(type);
		nomalVector.normalVector(vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();

		glBegin(type);
		nomalVector.normalVector(vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		glBegin(type);
		nomalVector.normalVector(vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

				glBegin(type);
				nomalVector.normalVector(vector3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(type);
			nomalVector.normalVector(vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

				glBegin(type);
				nomalVector.normalVector(vector3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(type);
						nomalVector.normalVector(vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();

				glBegin(type);
				nomalVector.normalVector(vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z),
									vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(type);
		nomalVector.normalVector(vector3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z),
									vector3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z));
			glNormal3f(nomalVector.x, nomalVector.y, nomalVector.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		
		glPopMatrix();
		glPopName();

		}

		if(check_SelectedObject && check_DrawGizmo){
				//setColor(selected_color);
				//gizmo.DrawGizmo();	
				//centerGizmoOfObjects.DrawGizmo();
				
		}
		glLineWidth(1.f);
			

		
}

void ObjectInform::DrawSphere(){

	glInitNames();

	GLenum type;
	GLfloat gap=0;


	if(check_SelectedObject){
		setColor(selected_color);
		
		//gizmo->DrawGizmo();
	}
	else{
		
		setColor(basic_color);
	}

	for(int i = 0; i < 2 ; i++){
		glPushName(object_ID);
		glPushMatrix();

		glTranslatef(gizmo.translate.x, gizmo.translate.y, gizmo.translate.z);

		center = gizmo.center;

		

		//glTranslatef(-gizmo.current_Rotate.rotate_Axis.x, -gizmo.current_Rotate.rotate_Axis.y, -gizmo.current_Rotate.rotate_Axis.z);
		glRotatef(gizmo.current_Rotate.angle, gizmo.current_Rotate.axis.x, gizmo.current_Rotate.axis.y, gizmo.current_Rotate.axis.z);
		//glTranslatef(gizmo.current_Rotate.rotate_Axis.x, gizmo.current_Rotate.rotate_Axis.y, gizmo.current_Rotate.rotate_Axis.z);

		for ( int i = gizmo.stack_Rotate.size()-1 ; i >= 0 ; i--){
		//	glTranslatef(- gizmo.stack_Rotate[i].rotate_Axis.x, -gizmo.stack_Rotate[i].rotate_Axis.y, -gizmo.stack_Rotate[i].rotate_Axis.z);
			glRotatef(gizmo.stack_Rotate[i].angle, gizmo.stack_Rotate[i].axis.x, gizmo.stack_Rotate[i].axis.y, gizmo.stack_Rotate[i].axis.z); 
		//	glTranslatef(gizmo.stack_Rotate[i].rotate_Axis.x, gizmo.stack_Rotate[i].rotate_Axis.y, gizmo.stack_Rotate[i].rotate_Axis.z);
		}

		glScalef(gizmo.scale.x, gizmo.scale.y, gizmo.scale.z);


		if(i==1 && gl_Object != GL_TRIANGLE_FAN && gl_Object != GL_LINE_LOOP&& !check_SelectedObject){
			glColor4fv(basic_Line_color);
			type = GL_LINE_LOOP;
			gap = 0.05;
		}
		else{
			glColor4fv(color);
			type = gl_Object;
			if(type == GL_TRIANGLE_FAN)
				type = GL_TRIANGLE_STRIP;
		}
		if(i==1 && check_SelectedObject){
			glColor4fv(slected_Line_color);
			type = GL_LINE_LOOP;
		}

		GLfloat x,y,z, dleta = 0.1f;
		glLineWidth(2.f);
		
		glBegin(type);
	
		for(GLfloat phi = 0; phi < 3.2; phi += 0.1){
			for(GLfloat theta = 0; theta <= 6.3; theta += 0.1){
				x = sin(phi) * cos(theta);
				y = sin(phi) * sin(theta);
				z = cos(phi);
				glNormal3f(x,y,z);
				glVertex3f(sphere_Size*x,sphere_Size*y,sphere_Size*z);
				phi += 0.1;
				x = sin(phi) * cos(theta);
				y = sin(phi) * sin(theta);
				z = cos(phi);
				glNormal3f(x,y,z);
				glVertex3f(sphere_Size*x,sphere_Size*y,sphere_Size*z);
				phi -= 0.1;
			}
		}
		
		glEnd();
		

		glPopMatrix();
		glPopName();

	}
	glLineWidth(1.f);
			if(check_SelectedObject && check_DrawGizmo){
				//setColor(selected_color);
				//gizmo.DrawGizmo();		
		}

}

void ObjectInform::setObjectMode(GLenum mode){
	gl_Object = mode;
}

void ObjectInform::setColor(GLfloat *setColor){
	color[0] = setColor[0];
	color[1] = setColor[1];
	color[2] = setColor[2];
	color[3] = setColor[3];
}

	vector3f ObjectInform::getPosition(){
		return this->gizmo.translate;
	}
	vector3f ObjectInform::getRotate(){
		return this->gizmo.rotate;
	}
	vector3f ObjectInform::getScale(){
		return this->gizmo.scale;
	}

	BOOL ObjectInform::object_Event(MSG* pMsg, Camera *camera){


		CPoint point(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));

		if(pMsg->message == WM_KEYUP && pMsg->wParam != 'Q'){
			check_KeyDown = FALSE;
		}

		
		if(pMsg->message == WM_LBUTTONDOWN && !check_KeyDown){
			m_ptStart = point;
			m_ptEnd = point;
			m_ptCenter = fromWorldToMouse(center, camera->projection, camera->modelView, camera->viewPort);
			m_ptCenter += CPoint( camera->client_Rect.left, camera->client_Rect.top);
			if(!gizmo.getHitGizmo())
				check_DragBox = TRUE;

		}
		else if(pMsg->message == WM_MOUSEMOVE && !check_KeyDown && check_DragBox  ){//
			check_MouseMove = TRUE;

			m_ptEnd = point;

			CPoint mS;
			CPoint mE;
			if(m_ptStart.x < m_ptEnd.x){
				mS.x = m_ptStart.x;
				mE.x = m_ptEnd.x;
			}
			else{
				mS.x = m_ptEnd.x;
				mE.x = m_ptStart.x;
			}
			if(m_ptStart.y < m_ptEnd.y){
				mS.y = m_ptStart.y;
				mE.y = m_ptEnd.y;
			}
			else{
				mS.y = m_ptEnd.y;
				mE.y = m_ptStart.y;
			}
			
			
			if(m_ptCenter.x >= mS.x && m_ptCenter.x <= mE.x && m_ptCenter.y >= mS.y && m_ptCenter.y <= mE.y && check_ObjectDrag)
				check_SelectedObject = TRUE;
			else if(!gizmo.getHitGizmo()){
				check_SelectedObject = FALSE;
			}
			
		}
		else if(pMsg->message == WM_LBUTTONUP && !check_KeyDown){
			if(!check_MouseMove)
				this->object_Picking(point, camera);
			
			check_DragBox = FALSE;
			check_MouseMove = FALSE;

			
		}
		gizmo.gizmo_Mouse_Evnet(pMsg, camera);
		
		return check_SelectedObject;
}

		void ObjectInform::keyEvent_W(){
			gizmo.keyEvent_W();
			
		}
	void ObjectInform::keyEvent_E(){
		gizmo.keyEvent_E();
		
	}
	void ObjectInform::keyEvent_R(){
		gizmo.keyEvent_R();
		
	}
	void ObjectInform::keyEvent_C(){
		gizmo.keyEvent_C();
		center = gizmo.translate;
	}

	void ObjectInform::keyEvent_Q(){
		if(check_KeyDown)
			check_KeyDown = FALSE;
		else
			check_KeyDown = TRUE;
	}
	void ObjectInform::keyEvent_Z(){
		check_KeyDown = TRUE;
	}
	void ObjectInform::keyEvent_X(){
		check_KeyDown = TRUE;
	}


	BOOL ObjectInform::getHitGizmo(){
		return gizmo.getHitGizmo() ;
	}
	void ObjectInform::setCheckDrag(BOOL drag){
		check_ObjectDrag = drag;
	}