#include "StdAfx.h"
#include "Gizmo.h"


#define GIZMO_NAME_X 101
#define GIZMO_NAME_Y 102
#define GIZMO_NAME_Z 103
#define GIZMO_NAME_CENTER 100
#define GIZMO_NAME_XY 104
#define GIZMO_NAME_YZ 105
#define GIZMO_NAME_ZX 106
#define TRANSLATE_SPEED 0.004
//#define TRANSLATE_SPEED_Y 0.05
#define ROTATE_SPEED 0.16
#define GIZMO_SCALE 20

#define PI 3.14159265358979323846

Gizmo::Gizmo(void)
{
	pick_Hit_Count = 0;
	selectedObject_ID = -1;

	key_check_W = TRUE;
	key_check_R = FALSE;
	key_check_E = FALSE;

	hit_ObjectGizmo_X = FALSE;
	hit_ObjectGizmo_Y = FALSE;
	hit_ObjectGizmo_Z = FALSE;
	hit_ObjectGizmo_CENTER = FALSE;
	hit_ObjectGizmo_XY = FALSE;
	hit_ObjectGizmo_YZ= FALSE;
	hit_ObjectGizmo_ZX= FALSE;
	
	check_selected = TRUE;
	
	center.set(0,0,0);
	translate.set(0,0,0);
	rotate.set(0,0,0);
	scale.set(1,1,1);
	scale_axis_R = scale;
	translate_INIT.set(0,0,0);
	rotate_INIT.set(0,0,0);
	scale_INIT.set(1,1,1);

	x_axis.set(1.0f,0.f,0.f);
	y_axis.set(0.f,1.f,0.f);
	z_axis.set(0.f,0.f,1.f);

	lbtnDown_X = FALSE;
	lbtnDown_Y = FALSE;
	lbtnDown_Z = FALSE;
	lbtnDown_CENTER = FALSE;
	lbtnDown_XY = FALSE;
	lbtnDown_YZ = FALSE;
	lbtnDown_ZX = FALSE;
	

	current_Rotate.angle = 0;
	current_Rotate.axis.set(0,0,0);
	current_Rotate.rotate_Axis.set(0,0,0);
	testVec.set(0,0,0);
	testVec1.set(0,0,0);
	testVec2.set(0,0,0);

	rotateGab = 0;
	count_Gizmo = 0;
}


Gizmo::~Gizmo(void)
{
}

void SolidCone(){
	GLfloat size = 0.1f;
	glBegin(GL_TRIANGLES);
		glVertex3f(0,size,0);
		glVertex3f(-size,0,0);
		glVertex3f(0,-size,0);

				glVertex3f(0,size,0);
		glVertex3f(0,-size,0);
		glVertex3f(size,0,0);

				glVertex3f(0,size,0);
		glVertex3f(-size,0,0);
		glVertex3f(0,0,size*2);

				glVertex3f(-size,0,0);
		glVertex3f(0,-size,0);
		glVertex3f(0,0,size*2);

				glVertex3f(0,-size,0);
		glVertex3f(size,0,0);
		glVertex3f(0,0,size*2);

				glVertex3f(size,0,0);
		glVertex3f(0,size,0);
		glVertex3f(0,0,size*2);
	glEnd();
}
void SolidCube(){
	GLfloat size = 0.1f;
	glBegin(GL_QUADS);
		glVertex3f(-size,size,-size);
		glVertex3f(-size,size,size);
		glVertex3f(size,size,size);
		glVertex3f(size,size,-size);

		glVertex3f(-size,size,-size);
		glVertex3f(-size,size,size);
		glVertex3f(size,size,size);
		glVertex3f(size,size,-size);

		glVertex3f(-size,size,-size);
		glVertex3f(-size,-size,-size);
		glVertex3f(-size,-size,size);
		glVertex3f(-size,size,size);

		glVertex3f(-size,size,size);
		glVertex3f(-size,-size,size);
		glVertex3f(size,-size,size);
		glVertex3f(size,size,size);

		glVertex3f(size,size,size);
		glVertex3f(size,-size,size);
		glVertex3f(size,-size,-size);
		glVertex3f(size,size,-size);

		glVertex3f(size,size,-size);
		glVertex3f(size,-size,-size);
		glVertex3f(-size,-size,-size);
		glVertex3f(-size,size,-size);

		glVertex3f(-size,-size,-size);
		glVertex3f(-size,-size,size);
		glVertex3f(size,-size,size);
		glVertex3f(size,-size,-size);
	glEnd();
}
void Gizmo::DrawGizmo(){
	//glInitNames();
	glDepthFunc(GL_ALWAYS);
	//glDepthFunc(GL_NOTEQUAL);

	//testVec.DrawVector(0);
	//testVec1.DrawVector(1);
	//testVec2.DrawVector(2);
	
	glPushMatrix();
	
	//glDisable(GL_DEPTH_TEST);
	

	/*      /// 기즈모 트랜스레이트와 센터 값 점으로 표시
			glPushMatrix();
			glPointSize(20.f);
			glBegin(GL_POINTS);
			glColor4f(0.f, 0.0f, 0.0f, 1.0f);

			glVertex3f(center.x, center.y, center.z);
			glEnd();
			glPointSize(1.f);
			glPopMatrix();

			glPushMatrix();
			glPointSize(10.f);
			glBegin(GL_POINTS);
			glColor4f(1.f, 0.0f, 1.0f, 1.0f);

			glVertex3f(translate.x, translate.y, translate.z);
			glEnd();
			glPointSize(1.f);
			glPopMatrix();
		*/
			
		glTranslatef(translate.x, translate.y, translate.z);

		//glTranslatef(-current_Rotate.rotate_Axis.x, -current_Rotate.rotate_Axis.y, -current_Rotate.rotate_Axis.z);
		glRotatef(current_Rotate.angle, current_Rotate.axis.x, current_Rotate.axis.y, current_Rotate.axis.z);
		//glTranslatef(current_Rotate.rotate_Axis.x, current_Rotate.rotate_Axis.y, current_Rotate.rotate_Axis.z);
		for ( int i = stack_Rotate.size()-1 ; i >= 0 ; i--){
			//glTranslatef(-stack_Rotate[i].rotate_Axis.x, -stack_Rotate[i].rotate_Axis.y, -stack_Rotate[i].rotate_Axis.z);
			glRotatef(stack_Rotate[i].angle, stack_Rotate[i].axis.x, stack_Rotate[i].axis.y, stack_Rotate[i].axis.z); 
			//glTranslatef(stack_Rotate[i].rotate_Axis.x, stack_Rotate[i].rotate_Axis.y, stack_Rotate[i].rotate_Axis.z);
		}
		
		//if(center.x != 0)
		//		glScalef((current_Camera.pos_eye - vector3f(0,0,0)).vectorValue()/GIZMO_SCALE, (current_Camera.pos_eye - vector3f(0,0,0)).vectorValue()/GIZMO_SCALE, (current_Camera.pos_eye - vector3f(0,0,0)).vectorValue()/GIZMO_SCALE);
		//else
			glScalef((current_Camera.pos_eye - translate).vectorValue()/GIZMO_SCALE, (current_Camera.pos_eye - translate).vectorValue()/GIZMO_SCALE, (current_Camera.pos_eye - translate).vectorValue()/GIZMO_SCALE);
		


	glLineWidth(6.f);
	/////////////////xxxxxxxxxxxxxxxxxxxxx
		glPushName(GIZMO_NAME_X);
		glPushMatrix();
		glPushMatrix();
			if(key_check_R)
					glScalef(scale_axis_R.x,1,1);
		glBegin(GL_LINES);
			if(hit_ObjectGizmo_X || lbtnDown_X)
			 	glColor4f(1.f, 1.0f, 0.0f, 1.0f);
			else
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			if(!key_check_E){
			glVertex3f(0, 0 ,0);
			glVertex3f(2, 0 ,0);
			}
		glEnd();
		glPopMatrix();
		if(key_check_W){
			glPushMatrix();
				glTranslatef(2, 0, 0);
				glRotatef(90.f, 0.f, 1.f, 0.f);
				glScalef(2, 2, 2);
				SolidCone();
			glPopMatrix();
		}
		else if(key_check_R){
			glPushMatrix();
				glTranslatef(2*scale_axis_R.x, 0, 0);
				glScalef(2, 2, 2);
				SolidCube();
			glPopMatrix();
		}
		else if(key_check_E){
			glPushMatrix();
				//glDepthFunc(GL_LESS);
				glPointSize(4.f);
				glTranslatef(0, 0, 0);
				glBegin(GL_POINTS);
				for (int i=0; i<360; i+=1){
					float degInRad=i;
					glVertex3f(0, cos(degInRad)*2,sin(degInRad)*2);//y축 회전
				}
				glEnd();
				glPointSize(1.f);

				//glDepthFunc(GL_ALWAYS);
			glPopMatrix();
		}

		glPopMatrix();
		glPopName();

		/////////////////yyyyyyyyyyyyyyyyyyyyyyyyyyy
		glPushName(GIZMO_NAME_Y);
		glPushMatrix();
		glPushMatrix();
			if(key_check_R)
					glScalef(1,scale_axis_R.y,1);
		glBegin(GL_LINES);
			if(hit_ObjectGizmo_Y || lbtnDown_Y)
				glColor4f(1.f, 1.0f, 0.0f, 1.0f);
			else
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			if(!key_check_E){
			glVertex3f(0, 0 ,0);
			glVertex3f(0, 2 ,0);
			}
		glEnd();
		glPopMatrix();
		if(key_check_W){
			glPushMatrix();
				glTranslatef(0, 2, 0);
				glRotatef(-90.f, 1.f, 0.f, 0.f);
				glScalef(2, 2, 2);
				SolidCone();
			glPopMatrix();
		}
		else if(key_check_R){
			glPushMatrix();
				glTranslatef(0, 2*scale_axis_R.y, 0);
				glScalef(2, 2, 2);
				SolidCube();
			glPopMatrix();
		}
		else if(key_check_E){
			glPushMatrix();
				glPointSize(4.f);
				glTranslatef(0, 0, 0);
				glBegin(GL_POINTS);
				for (int i=0; i<360; i+=1){
					float degInRad=i;
					glVertex3f(cos(degInRad)*2, 0,sin(degInRad)*2);//y축 회전
				}
				glEnd();
				glPointSize(1.f);
			glPopMatrix();
		}

		glPopMatrix();
		glPopName();

		/////////////////zzzzzzzzzzzzzzzzzzzzzzzzz
		glPushName(GIZMO_NAME_Z);
		glPushMatrix();
		glPushMatrix();
			if(key_check_R)
					glScalef(1,1,scale_axis_R.z);
		glBegin(GL_LINES);
			if(hit_ObjectGizmo_Z || lbtnDown_Z)
				glColor4f(1.f, 1.0f, 0.0f, 1.0f);
			else
				glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			if(!key_check_E){
			glVertex3f(0, 0 ,0);
			glVertex3f(0, 0 ,2);
			}
		glEnd();
		glPopMatrix();
		if(key_check_W){
			glPushMatrix();
				glTranslatef(0, 0,2);
				glRotatef(90.f, 0.f, 0.f, 1.f);
				glScalef(2, 2, 2);
				SolidCone();
			glPopMatrix();
		}
		else if(key_check_R){
			glPushMatrix();
				glTranslatef(0, 0, 2*scale_axis_R.z);
				glScalef(2, 2, 2);
				SolidCube();
			glPopMatrix();
		}
		else if(key_check_E){
			glPushMatrix();
				glPointSize(4.f);
				glTranslatef(0, 0, 0);
				glBegin(GL_POINTS);
				for (int i=0; i<360; i+=1){
					float degInRad=i;
					glVertex3f(cos(degInRad)*2, sin(degInRad)*2,0);//y축 회전
				}
				glEnd();
				glPointSize(1.f);
			glPopMatrix();
		}

		glPopMatrix();
		glPopName();


		if(key_check_R){
			glPushName(GIZMO_NAME_CENTER);
			glPushMatrix();
			
				glPushMatrix();
					if(hit_ObjectGizmo_CENTER || lbtnDown_CENTER)
						glColor4f(1.f, 1.0f, 0.0f, 1.0f);
					else
						glColor4f(0.8f, 0.8f, 0.8f, 1.0f);

					glScalef(3, 3, 3);
					SolidCube();
				glPopMatrix();
			
			glPopMatrix();
			glPopName();
		}
		else if(key_check_W){
			glPushName(GIZMO_NAME_XY);
			glPushMatrix();
			
				glPushMatrix();
					if(hit_ObjectGizmo_XY || lbtnDown_XY)
						glColor4f(1.f, 1.0f, 0.0f, 0.4f);
					else
						glColor4f(0.0f, 0.0f, 1.0f, 0.4f);

					glBegin(GL_QUADS);
						glVertex3f(0, 0, 0);
						glVertex3f(0.5, 0, 0);
						glVertex3f(0.5, 0.5, 0);
						glVertex3f(0, 0.5, 0);
					glEnd();
				glPopMatrix();
			
			glPopMatrix();
			glPopName();

			glPushName(GIZMO_NAME_YZ);
			glPushMatrix();
			
				glPushMatrix();
					if(hit_ObjectGizmo_YZ || lbtnDown_YZ)
						glColor4f(1.f, 1.0f, 0.0f, 0.4f);
					else
						glColor4f(1.0f, 0.0f, 0.0f, 0.4f);

					glBegin(GL_QUADS);
						glVertex3f(0, 0, 0);
						glVertex3f(0, 0.5, 0);
						glVertex3f(0, 0.5, 0.5);
						glVertex3f(0, 0, 0.5);
					glEnd();
				glPopMatrix();
			
			glPopMatrix();
			glPopName();

			glPushName(GIZMO_NAME_ZX);
			glPushMatrix();
			
				glPushMatrix();
					if(hit_ObjectGizmo_ZX || lbtnDown_ZX)
						glColor4f(1.f, 1.0f, 0.0f, 0.4f);
					else
						glColor4f(0.0f, 1.0f, 0.0f, 0.4f);

					glBegin(GL_QUADS);
						glVertex3f(0, 0, 0);
						glVertex3f(0, 0, 0.5);
						glVertex3f(0.5, 0, 0.5);
						glVertex3f(0.5, 0, 0);
					glEnd();
				glPopMatrix();
			
			glPopMatrix();
			glPopName();

		}
		//glEnable(GL_DEPTH_TEST);
		glPopMatrix();
	glLineWidth(1.f);
	//


	if((lbtnDown_X || lbtnDown_Y || lbtnDown_Z) && key_check_E){
		glPushMatrix();
		glLineWidth(8.f);
		
		GLfloat line_color[4];
		if(lbtnDown_X){
			line_color[0]=1; line_color[1]=0; line_color[2]=0; line_color[3]=0.4f;
			
			glBegin(GL_LINES);
			glColor4f(0, 0, 0, 1.f);
			vector3f stdVec = spherePoint - translate;
			glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			glVertex3f((x_axis.crossProduct(stdVec.normalize())+spherePoint).x,(x_axis.crossProduct(stdVec.normalize())+spherePoint).y,(x_axis.crossProduct(stdVec.normalize())+spherePoint).z);

			//glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			//glVertex3f(-(x_axis.crossProduct(stdVec.normalize())+spherePoint).x,-(x_axis.crossProduct(stdVec.normalize())+spherePoint).y,-(x_axis.crossProduct(stdVec.normalize())+spherePoint).z);
			glEnd();
		}
		else if(lbtnDown_Y){
			line_color[0]=0; line_color[1]=1; line_color[2]=0; line_color[3]=0.4f;
						glBegin(GL_LINES);
			glColor4f(0, 0, 0, 1.f);
			vector3f stdVec = spherePoint - translate;
			glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			glVertex3f((y_axis.crossProduct(stdVec.normalize())+spherePoint).x,(y_axis.crossProduct(stdVec.normalize())+spherePoint).y,(y_axis.crossProduct(stdVec.normalize())+spherePoint).z);

			//glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			//glVertex3f(-(y_axis.crossProduct(stdVec.normalize())+spherePoint).x,-(y_axis.crossProduct(stdVec.normalize())+spherePoint).y,-(y_axis.crossProduct(stdVec.normalize())+spherePoint).z);
			glEnd();
		}
		else if(lbtnDown_Z){
			line_color[0]=0; line_color[1]=0; line_color[2]=1; line_color[3]=0.4f;
						glBegin(GL_LINES);
			glColor4f(0, 0, 0, 1.f);
			vector3f stdVec = spherePoint - translate;
			glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			glVertex3f((z_axis.crossProduct(stdVec.normalize())+spherePoint).x,(z_axis.crossProduct(stdVec.normalize())+spherePoint).y,(z_axis.crossProduct(stdVec.normalize())+spherePoint).z);

			//glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			//glVertex3f(-(z_axis.crossProduct(stdVec.normalize())+spherePoint).x,-(z_axis.crossProduct(stdVec.normalize())+spherePoint).y,-(z_axis.crossProduct(stdVec.normalize())+spherePoint).z);
			glEnd();

		}
					glLineWidth(1.f);
			glPopMatrix();


			glPushMatrix();
			glLineWidth(6.f);

			glBegin(GL_LINES);
				glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
				glVertex3f(translate.x,translate.y,translate.z);
				glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			glEnd();

			if(current_Rotate.angle >= 0){
				for(int i = 0 ; i < current_Rotate.angle ; i++){
					glPushMatrix();
					glTranslatef(translate.x,translate.y,translate.z);
					glRotatef(i, current_Rotate.axis.x, current_Rotate.axis.y, current_Rotate.axis.z);
					glTranslatef(-translate.x,-translate.y,-translate.z);
					glBegin(GL_LINES);
					glColor4f(0.6, 0.6, 0.6, 0.1f);
					glVertex3f(translate.x,translate.y,translate.z);
					glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
					glEnd();
					glPopMatrix();
				}
			}
			else{
				for(int i = 0 ; i > current_Rotate.angle ; i--){
					glPushMatrix();
					glTranslatef(translate.x,translate.y,translate.z);
					glRotatef(i, current_Rotate.axis.x, current_Rotate.axis.y, current_Rotate.axis.z);
					glTranslatef(-translate.x,-translate.y,-translate.z);
					glBegin(GL_LINES);
					glColor4f(0.6, 0.6, 0.6, 0.1f);
					glVertex3f(translate.x,translate.y,translate.z);
					glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
					glEnd();
					glPopMatrix();
				}
			}

			glTranslatef(translate.x,translate.y,translate.z);
			glRotatef(current_Rotate.angle, current_Rotate.axis.x, current_Rotate.axis.y, current_Rotate.axis.z);
			glTranslatef(-translate.x,-translate.y,-translate.z);
			glBegin(GL_LINES);
				glColor4fv(line_color);
				glVertex3f(translate.x,translate.y,translate.z);
				glVertex3f(spherePoint.x, spherePoint.y, spherePoint.z);
			glEnd();

			glLineWidth(1.f);
			glPopMatrix();
	}
	glDepthFunc(GL_LEQUAL);
}

void Gizmo::DrawGizmo_Axis(){
	
	vector3f leftTopBack_pos;
		vector3f RightBottomFront_pos;
		leftTopBack_pos.set(-4,-4,-4);
		RightBottomFront_pos.set(4,4,4);

		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();

				glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

				glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , leftTopBack_pos.z);
		glEnd();

				glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
			glVertex3f(leftTopBack_pos.x, leftTopBack_pos.y , RightBottomFront_pos.z);
		glEnd();

				glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
		glEnd();
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , RightBottomFront_pos.z);
			glVertex3f(RightBottomFront_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
			glVertex3f(leftTopBack_pos.x, RightBottomFront_pos.y , leftTopBack_pos.z);
		glEnd();
		

}
void Gizmo::DrawGizmo_ViewMode(){
	//glInitNames();
	GLfloat size_Gizmo = 10;
	glPushMatrix();
		
	GLfloat color[4] = {0.6f, 0.6f, 0.6f, 1.0f};
	/////////////////xxxxxxxxxxxxxxxxxxxxx
		
	glLineWidth(4.f);
		glPushMatrix();
			glPushMatrix();
			glColor4f(1.f,0.f,0.f,1.0f);
			glScalef(2,0.5,0.5);
			glTranslatef(2,0,0);
			DrawGizmo_Axis();
			glPopMatrix();
		
			glPushMatrix();
			glColor4fv(color);
			glScalef(2,0.5,0.5);
			glTranslatef(-2,0,0);
			DrawGizmo_Axis();
			glPopMatrix();
		
		glPopMatrix();
		

		/////////////////yyyyyyyyyyyyyyyyyyyyyyyyyyy
	
		glPushMatrix();
			glPushMatrix();
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			glScalef(0.5,2,0.5);
			glTranslatef(0,2,0);
			DrawGizmo_Axis();
			glPopMatrix();
		
			glPushMatrix();
			glColor4fv(color);
			glScalef(0.5,2,0.5);
			glTranslatef(0,-2,0);
			DrawGizmo_Axis();
			glPopMatrix();
		
		glPopMatrix();

		/////////////////zzzzzzzzzzzzzzzzzzzzzzzzz
		
		glPushMatrix();
			glPushMatrix();
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glScalef(0.5,0.5,2);
			glTranslatef(0,0,2);
			DrawGizmo_Axis();
			glPopMatrix();
		
			glPushMatrix();
			glColor4fv(color);
			glScalef(0.5,0.5,2);
			glTranslatef(0,0,-2);
			DrawGizmo_Axis();
			glPopMatrix();
		
		glPopMatrix();
		

		glPushMatrix();
		if(!current_Camera.Get_cameraView_Perspective_Ortho())
			glColor4f(1.0f,1.0f,1.0f,1);
		else
			glColor4f(1.0f,1.0f,0.0f,1);
			DrawGizmo_Axis();
		glPopMatrix();
			
			
		glPopMatrix();
	
	glLineWidth(1.f);

}

void Gizmo::gizmo_Picking(CPoint cp,  Camera *camera){
	
		current_Camera = *camera;
		int hits_count = 0;
		int viewport[4]; //[2]->width, [3]->height
	
		GLuint gizmoSelectBuf[128];
		
		glSelectBuffer(128, gizmoSelectBuf);

		glRenderMode(GL_SELECT);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(cp.x ,camera->viewPort[3] - cp.y, 8, 8,camera->viewPort);
			camera->cameraView();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glEnable(GL_DEPTH_TEST);
		DrawGizmo();
		//glDisable(GL_DEPTH_TEST);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glFlush();
		pick_Hit_Count = glRenderMode(GL_RENDER); //총 선택된 hits 수
	
		glMatrixMode(GL_MODELVIEW);
	
		//	for(int i = 0; i <= pick_Hit_Count; i++){
				if(gizmoSelectBuf[3] == GIZMO_NAME_X && !lbtnDown_Y && !lbtnDown_Z && !lbtnDown_CENTER && !lbtnDown_XY && !lbtnDown_YZ && !lbtnDown_ZX){ //i*4 - 1
					this->setHit_X(TRUE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_Y && !lbtnDown_X && !lbtnDown_Z && !lbtnDown_CENTER && !lbtnDown_XY && !lbtnDown_YZ && !lbtnDown_ZX){
					this->setHit_X(FALSE);
					this->setHit_Y(TRUE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);	
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_Z && !lbtnDown_Y && !lbtnDown_X && !lbtnDown_CENTER && !lbtnDown_XY && !lbtnDown_YZ && !lbtnDown_ZX){
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(TRUE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_CENTER && !lbtnDown_Y && !lbtnDown_X && !lbtnDown_Z){
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(TRUE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);	
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_XY && !lbtnDown_YZ && !lbtnDown_ZX  && !lbtnDown_Y && !lbtnDown_X && !lbtnDown_Z){
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(TRUE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);		
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_YZ && !lbtnDown_XY && !lbtnDown_ZX && !lbtnDown_Y && !lbtnDown_X && !lbtnDown_Z){
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(TRUE);
					this->setHit_ZX(FALSE);		
				
					//break;
				}
				else if(gizmoSelectBuf[3] == GIZMO_NAME_ZX && !lbtnDown_YZ && !lbtnDown_XY && !lbtnDown_Y && !lbtnDown_X && !lbtnDown_Z){
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(TRUE);	
					
					//break;
				}
				else{
					this->setHit_X(FALSE);
					this->setHit_Y(FALSE);
					this->setHit_Z(FALSE);
					this->setHit_CENTER(FALSE);
					this->setHit_XY(FALSE);
					this->setHit_YZ(FALSE);
					this->setHit_ZX(FALSE);
				}
			//}	
		
}

BOOL Gizmo::getHitGizmo(){
	return (lbtnDown_X || lbtnDown_Y || lbtnDown_Z || lbtnDown_CENTER ||lbtnDown_XY || lbtnDown_YZ || lbtnDown_ZX) ;
}

	void Gizmo::setHit_X(BOOL hit){
		hit_ObjectGizmo_X = hit;
	}
	void Gizmo::setHit_Y(BOOL hit){
		hit_ObjectGizmo_Y = hit;
	}
	void Gizmo::setHit_Z(BOOL hit){
		hit_ObjectGizmo_Z = hit;
	}
	void Gizmo::setHit_CENTER(BOOL hit){
		hit_ObjectGizmo_CENTER = hit;
	}
	void Gizmo::setHit_XY(BOOL hit){
		hit_ObjectGizmo_XY = hit;
	}
	void Gizmo::setHit_YZ(BOOL hit){
		hit_ObjectGizmo_YZ = hit;
	}
	void Gizmo::setHit_ZX(BOOL hit){
		hit_ObjectGizmo_ZX = hit;
	}

	
	BOOL Gizmo::getHit_X(){
		return hit_ObjectGizmo_X;
	}
	BOOL Gizmo::getHit_Y(){
		return hit_ObjectGizmo_Y;
	}
	BOOL Gizmo::getHit_Z(){
		return hit_ObjectGizmo_Z;
	}
		BOOL Gizmo::getHit_CENTER(){
		return hit_ObjectGizmo_CENTER;
	}
	BOOL Gizmo::getHit_XY(){
		return hit_ObjectGizmo_XY;
	}
	BOOL Gizmo::getHit_YZ(){
		return hit_ObjectGizmo_YZ;
	}
	BOOL Gizmo::getHit_ZX(){
		return hit_ObjectGizmo_ZX;
	}

	BOOL Gizmo::gizmo_Mouse_Evnet(MSG *pMsg, Camera *camera){
		


		
		CPoint point(LOWORD(pMsg->lParam) - camera->client_Rect.left, HIWORD(pMsg->lParam) - camera->client_Rect.top);
		vector3f point3f = worldPlane(point,camera->projection, camera->modelView, camera->viewPort);

		if(pMsg->message == WM_LBUTTONDOWN){
			beforePt3f = point3f;
			beforePt.SetPoint(LOWORD(pMsg->lParam) - camera->client_Rect.left, HIWORD(pMsg->lParam) - camera->client_Rect.top);
			rotatePt.SetPoint(LOWORD(pMsg->lParam) - camera->client_Rect.left, HIWORD(pMsg->lParam) - camera->client_Rect.top);
			spherePoint = fromMouseToWorld(rotatePt, camera->projection, camera->modelView, camera->viewPort);
	
			if(hit_ObjectGizmo_X){
					lbtnDown_X = TRUE;
				}
				else if(hit_ObjectGizmo_Y){
					lbtnDown_Y = TRUE;
				}
				else if(hit_ObjectGizmo_Z){
					lbtnDown_Z = TRUE;
				}
				else if(hit_ObjectGizmo_CENTER){
					lbtnDown_CENTER = TRUE;
				}
				else if(hit_ObjectGizmo_XY){
					lbtnDown_XY = TRUE;
				}
				else if(hit_ObjectGizmo_YZ){
					lbtnDown_YZ = TRUE;
				}
				else if(hit_ObjectGizmo_ZX){
					lbtnDown_ZX = TRUE;
				}

		
		}
		else if(pMsg->message == WM_LBUTTONUP){
			if(key_check_E && (lbtnDown_X || lbtnDown_Y || lbtnDown_Z) && (current_Rotate.angle != 0))
				stack_Rotate.push_back(current_Rotate);

			lbtnDown_X = FALSE;
			lbtnDown_Y = FALSE;
			lbtnDown_Z = FALSE;
			lbtnDown_CENTER = FALSE;
			lbtnDown_XY = FALSE;
			lbtnDown_YZ = FALSE;
			lbtnDown_ZX = FALSE;

			if(current_Rotate.angle != 0){
					rotate_Axis_xyz_2( current_Rotate.angle, current_Rotate.axis);
			
			}
			rotateGab = 0;
			current_Rotate.angle = 0;
			current_Rotate.axis.set(0,0,0);
			current_Rotate.rotate_Axis.set(0,0,0);
			scale_axis_R.set(1,1,1);
		
		}
		else if(pMsg->message == WM_RBUTTONDOWN){
		
			
		}
		else if(pMsg->message == WM_RBUTTONUP){
		
			
		}
		else if(pMsg->message == WM_MOUSEWHEEL){
		
		}

		else if(pMsg->message == WM_MOUSEMOVE && check_selected){
				vector3f worldPoint = fromMouseToWorld(point, camera->projection, camera->modelView, camera->viewPort);
				vector3f worldPoint_before = fromMouseToWorld(beforePt, camera->projection, camera->modelView, camera->viewPort);
				//worldPoint.y = worldPoint_before.y = 0;
				vector3f worldVec = worldPoint - worldPoint_before;
				//worldVec.normalize(); //마우스가 움직인 크기 만큼 이동하기 위해 노멀벡터를 하면 크기가 1로 고정되기 때문


				this->gizmo_Picking(point, camera);


			///////////////TRANSLATE//////////////////////
				if(key_check_W){
					if(lbtnDown_X){
	
					    GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Xaxis = fromWorldToMouse(x_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Xaxis = world_Xaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Xaxis.x * win_vec.x) + (win_Xaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y)) /100;
					/*
						vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * x_axis.x) + (world_vec.y * x_axis.y) +  (world_vec.z * x_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab, x_axis);





						beforePt = point;
						beforePt3f = point3f;
						
					}
					else if(lbtnDown_Y){

						/*
						GLfloat gab =  beforePt.y - point.y ;
						if(y_axis.y < 0)
							 gab =  point.y - beforePt.y ;
	
						translate.x += (y_axis.x * (gab/TRANSLATE_SPEED_Y * TRANSLATE_SPEED));
						translate.y += (y_axis.y * (gab/TRANSLATE_SPEED_Y * TRANSLATE_SPEED));
						translate.z += (y_axis.z * (gab/TRANSLATE_SPEED_Y * TRANSLATE_SPEED));
						*/
						 GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Yaxis = fromWorldToMouse(y_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Yaxis = world_Yaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Yaxis.x * win_vec.x) + (win_Yaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
						vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * y_axis.x) + (world_vec.y * y_axis.y) +  (world_vec.z * y_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab, y_axis);
		
						beforePt = point;

						beforePt3f = point3f;
					}
					else if(lbtnDown_Z){


						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Zaxis = fromWorldToMouse(z_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Zaxis = world_Zaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Zaxis.x * win_vec.x) + (win_Zaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
						vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * z_axis.x) + (world_vec.y * z_axis.y) +  (world_vec.z * z_axis.z);
						gab *= world_vec.vectorValue();
						*/
						gizmo_Translate(gab, z_axis);

						beforePt = point;
						beforePt3f = point3f;
					}
					else if(lbtnDown_XY){
						  GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Xaxis = fromWorldToMouse(x_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Xaxis = world_Xaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Xaxis.x * win_vec.x) + (win_Xaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * x_axis.x) + (world_vec.y * x_axis.y) +  (world_vec.z * x_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab/2, x_axis);

						gab=0;
						world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Yaxis = fromWorldToMouse(y_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Yaxis = world_Yaxis - world_Center;
						win_vec = point - beforePt;
						gab = (GLfloat)(win_Yaxis.x * win_vec.x) + (win_Yaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												 world_vec = point3f - beforePt3f;
						gab = (world_vec.x * y_axis.x) + (world_vec.y * y_axis.y) +  (world_vec.z * y_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab/2, y_axis);

						beforePt = point;
						beforePt3f = point3f;
					}
					else if(lbtnDown_YZ){
						
						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Yaxis = fromWorldToMouse(y_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Yaxis = world_Yaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Yaxis.x * win_vec.x) + (win_Yaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * y_axis.x) + (world_vec.y * y_axis.y) +  (world_vec.z * y_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab/2, y_axis);

						gab=0;
						world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Zaxis = fromWorldToMouse(z_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Zaxis = world_Zaxis - world_Center;
						win_vec = point - beforePt;
						gab = (GLfloat)(win_Zaxis.x * win_vec.x) + (win_Zaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												world_vec = point3f - beforePt3f;
						gab = (world_vec.x * z_axis.x) + (world_vec.y * z_axis.y) +  (world_vec.z * z_axis.z);
						gab *= world_vec.vectorValue();
						*/
						gizmo_Translate(gab/2, z_axis);

						beforePt = point;
						beforePt3f = point3f;
					}
					else if(lbtnDown_ZX){
						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Zaxis = fromWorldToMouse(z_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Zaxis = world_Zaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Zaxis.x * win_vec.x) + (win_Zaxis.y * win_vec.y);
						
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												vector3f world_vec = point3f - beforePt3f;
						gab = (world_vec.x * z_axis.x) + (world_vec.y * z_axis.y) +  (world_vec.z * z_axis.z);
						gab *= world_vec.vectorValue();
						*/
						gizmo_Translate(gab/2, z_axis);

						gab=0;
						world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Xaxis = fromWorldToMouse(x_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Xaxis = world_Xaxis - world_Center;
						win_vec = point - beforePt;
						gab = (GLfloat)(win_Xaxis.x * win_vec.x) + (win_Xaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						/*
												world_vec = point3f - beforePt3f;
						gab = (world_vec.x * x_axis.x) + (world_vec.y * x_axis.y) +  (world_vec.z * x_axis.z);
						gab *= world_vec.vectorValue();
						*/
							gizmo_Translate(gab/2, x_axis);

						beforePt = point;
						beforePt3f = point3f;
					}

				}

			///////////////SCALE//////////////////////
				if(key_check_R){
					if(lbtnDown_X){

						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Xaxis = fromWorldToMouse(x_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Xaxis = world_Xaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Xaxis.x * win_vec.x) + (win_Xaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Scale(gab, vector3f(1,0,0));

						beforePt = point;

						
					}
					else if(lbtnDown_Y){
						/*
						GLfloat gab =  beforePt.y - point.y ;
						if(y_axis.y < 0)
							 gab =  point.y - beforePt.y ;
	
						scale.y += (gab/TRANSLATE_SPEED_Y * TRANSLATE_SPEED);
						*/

						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Yaxis = fromWorldToMouse(y_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Yaxis = world_Yaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Yaxis.x * win_vec.x) + (win_Yaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Scale(gab, vector3f(0,1,0));

						beforePt = point;


					}
					else if(lbtnDown_Z){

						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Zaxis = fromWorldToMouse(z_axis+translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Zaxis = world_Zaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Zaxis.x * win_vec.x) + (win_Zaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Scale(gab, vector3f(0,0,1));

						beforePt = point;
					}

					else if(lbtnDown_CENTER){

						GLfloat gab=0;
						CPoint world_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint world_Zaxis = fromWorldToMouse((x_axis + y_axis + z_axis + y_axis) + translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Zaxis = world_Zaxis - world_Center;
						CPoint win_vec = point - beforePt;
						gab = (GLfloat)(win_Zaxis.x * win_vec.x) + (win_Zaxis.y * win_vec.y);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Scale(gab, vector3f(1,1,1));

						beforePt = point;
					}

				}

			///////////////ROTATE//////////////////////
				if(key_check_E){
					// worldPoint - worldPoint_before;

					//spherePoint = fromMouseToWorld(rotatePt, camera->projection, camera->modelView, camera->viewPort);
					current_spherePoint = fromMouseToWorld(point, camera->projection, camera->modelView, camera->viewPort);

					vector3f stdVec = spherePoint - translate;
					
					//rotateGab = 0;
					if(lbtnDown_X){
						
						GLfloat gab = 0;
						GLfloat sum;
						CPoint win_axis = fromWorldToMouse(x_axis.crossProduct(stdVec.normalize()) + translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_vec = point - beforePt;
						win_axis -= win_Center; //윈도우 상에서의 원점으로 부터 벡터 계산


						//TRACE("%d, %d,       %d, %d\n", win_axis.x, win_axis.y, win_vec.x, win_vec.y);

						//testVec = stdVec;
						//testVec1 = x_axis;
						//testVec2 = x_axis.crossProduct(stdVec.normalize());

						gab = (GLfloat)(win_axis.x * win_vec.x) + (win_axis.y * win_vec.y);

						//rotateGab = gab;
						
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Rotate(gab, x_axis);

						beforePt = point;

					}
					else if(lbtnDown_Y){

						GLfloat gab = 0;
						GLfloat sum;
						CPoint win_axis = fromWorldToMouse(y_axis.crossProduct(stdVec.normalize()) + translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_vec = point - beforePt;
						win_axis -= win_Center;
						
						gab = (GLfloat)(win_axis.x * win_vec.x) + (win_axis.y * win_vec.y);
						
						//rotateGab = gab;
						
						//gab = y_axis.crossProduct(stdVec).innerProduct(worldVec);
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Rotate(gab, y_axis);

				

						beforePt = point;

					}
					else if(lbtnDown_Z){

						GLfloat gab = 0;
						GLfloat sum;
						CPoint win_axis = fromWorldToMouse(z_axis.crossProduct(stdVec.normalize()) + translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_Center = fromWorldToMouse(translate, camera->projection, camera->modelView, camera->viewPort);
						CPoint win_vec = point - beforePt;
						win_axis -= win_Center;
						
						gab = (GLfloat)(win_axis.x * win_vec.x) + (win_axis.y * win_vec.y);

						
						
						//rotateGab = gab;
						
						//gab *= sqrt((GLfloat)(win_vec.x * win_vec.x + win_vec.y * win_vec.y));
						gizmo_Rotate(gab, z_axis);

						beforePt = point;
					}

					//TRACE("%f, %f, %f\n", rotate.x, rotate.y, rotate.z);

					//rotate_Axis_xyz();
				}
		}
			return TRUE;
	}

	void Gizmo::gizmo_Translate(GLfloat gab, vector3f axis){

						translate.x += (axis.x * (gab * TRANSLATE_SPEED));
						translate.y += (axis.y * (gab * TRANSLATE_SPEED));
						translate.z += (axis.z * (gab * TRANSLATE_SPEED));
						
						center.x += (axis.x * (gab * TRANSLATE_SPEED));
						center.y += (axis.y * (gab * TRANSLATE_SPEED));
						center.z += (axis.z * (gab * TRANSLATE_SPEED));



						GLfloat limited = 100;
						if(translate.x > limited)
							translate.x = limited;
						else if(translate.x < -limited)
							translate.x = -limited;
						if(translate.y > limited)
							translate.y = limited;
						else if(translate.y < -limited)
							translate.y = -limited;
						if(translate.z > limited)
							translate.z = limited;
						else if(translate.z < -limited)
							translate.z = -limited;
							
						

	}
	void Gizmo::gizmo_Rotate(GLfloat angle, vector3f axis){
		GLfloat sum;
		sum = abs(axis.x) + abs(axis.y) + abs(axis.z);

		rotate.x += ((axis.x / sum) * (angle * ROTATE_SPEED));
		rotate.y += ((axis.y / sum) * (angle * ROTATE_SPEED));
		rotate.z += ((axis.z / sum) * (angle * ROTATE_SPEED));

	
		rotateGab += (angle * ROTATE_SPEED);
		
		//TRACE("%d ANGLE : %f\n",count_Gizmo, (angle * ROTATE_SPEED));
		current_Rotate.angle += (angle * ROTATE_SPEED);
		current_Rotate.axis = axis;
		current_Rotate.rotate_Axis = translate - center;


	}
	void Gizmo::gizmo_Scale(GLfloat size, vector3f axis){

		scale.x += axis.x * (size * TRANSLATE_SPEED);
		scale.y += axis.y * (size * TRANSLATE_SPEED);
		scale.z += axis.z * (size * TRANSLATE_SPEED);


		scale_axis_R.x += axis.x * (size * TRANSLATE_SPEED);
		scale_axis_R.y += axis.y * (size * TRANSLATE_SPEED);
		scale_axis_R.z += axis.z * (size * TRANSLATE_SPEED);
	}

	void Gizmo::keyEvent_W(){
			if(key_check_W)
				key_check_W = FALSE;
			else{
				key_check_W = TRUE;
				key_check_R = FALSE;
				key_check_E = FALSE;
			}
		}
	void Gizmo::keyEvent_E(){
		if(key_check_E)
				key_check_E = FALSE;
			else{
				key_check_E = TRUE;
				key_check_W = FALSE;
				key_check_R = FALSE;
			}
	}
	void Gizmo::keyEvent_R(){
		if(key_check_R)
				key_check_R = FALSE;
			else{
				key_check_R = TRUE;
				key_check_W = FALSE;
				key_check_E = FALSE;
			}
	}
	void Gizmo::keyEvent_C(){
		center.set(0,0,0);
		translate.set(0,0,0);
		rotate.set(0,0,0);
		scale.set(1,1,1);
		translate_INIT.set(0,0,0);
		rotate_INIT.set(0,0,0);
		scale_INIT.set(1,1,1);

		x_axis.set(1,0,0);
		y_axis.set(0,1,0);
		z_axis.set(0,0,1);

		for(int i = (stack_Rotate.size()-1) ; i >= 0  ; i--){
				stack_Rotate.erase(stack_Rotate.begin() + i);
		}
			
	}

	void Gizmo::rotate_Axis_xyz_2(GLfloat angle, vector3f axis){
		GLfloat r_x;
		GLfloat r_y;
		GLfloat r_z;
		GLfloat costheta;
		GLfloat sintheta;
		GLfloat r[3][3];
		//GLfloat angle;


		//current_Rotate.angle += angle;
		//current_Rotate.axis = axis;


		 r_x = axis.x;      //회전축
		r_y = axis.y;
		 r_z = axis.z;
		  //TRACE("ANGLE : %f\n", angle);
		angle = angle * (PI/180) ;
		 // TRACE("RADIAN : %f\n", angle);
		 // TRACE("RADIAN : %f , %f, %f, %f\n", angle,r_x,r_y,r_z);
		  costheta = cos(angle);
		  sintheta = sin(angle);
		 // TRACE("cos %f, %f\n", costheta, cos(angle));
		  //TRACE("sin %f, %f\n", sintheta, sin(angle));

		r[0][0]  = (((1 - costheta) * r_x * r_x) + costheta) ;
		r[0][1]  = (((1 - costheta) * r_x *r_y) - (sintheta * r_z)) ;
		r[0][2]  = (((1 - costheta) * r_x * r_z) + (sintheta * r_y)) ;

		r[1][0]  = (((1 - costheta) * r_x *r_y) + (sintheta * r_z)) ;
		r[1][1]  = (((1 - costheta) * r_y * r_y) + costheta) ;
		r[1][2]  = (((1 - costheta) * r_y * r_z) - (sintheta * r_x)) ;

		r[2][0]  = (((1 - costheta) * r_x * r_z) - (sintheta * r_y)) ;
		r[2][1]  = (((1 - costheta) * r_y * r_z) + (sintheta * r_x)) ;
		r[2][2]  = (((1 - costheta) * r_z * r_z) + costheta) ;
		

		GLfloat temp_x = r[0][0]*x_axis.x + r[0][1]*x_axis.y + r[0][2]*x_axis.z ;
		GLfloat temp_y = r[1][0]*x_axis.x + r[1][1]*x_axis.y + r[1][2]*x_axis.z ;
		GLfloat temp_z = r[2][0]*x_axis.x + r[2][1]*x_axis.y + r[2][2]*x_axis.z ;
		x_axis.x = temp_x;
		x_axis.y = temp_y;
		x_axis.z = temp_z;

		temp_x = r[0][0]*y_axis.x + r[0][1]*y_axis.y + r[0][2]*y_axis.z ;
		temp_y = r[1][0]*y_axis.x + r[1][1]*y_axis.y + r[1][2]*y_axis.z ;
		temp_z = r[2][0]*y_axis.x + r[2][1]*y_axis.y + r[2][2]*y_axis.z ;
		y_axis.x = temp_x;
		y_axis.y = temp_y;
		y_axis.z = temp_z;

		temp_x = r[0][0]*z_axis.x + r[0][1]*z_axis.y + r[0][2]*z_axis.z ;
		temp_y = r[1][0]*z_axis.x + r[1][1]*z_axis.y + r[1][2]*z_axis.z ;
		temp_z = r[2][0]*z_axis.x + r[2][1]*z_axis.y + r[2][2]*z_axis.z ;
		z_axis.x = temp_x;
		z_axis.y = temp_y;
		z_axis.z = temp_z;

		
		//z_axis.x *= 1.1;
		//z_axis.y *= 1.1;
		//z_axis.z *= 1.1;
		//y_axis.x *= 1.1;
		//y_axis.y *= 1.1;
		//y_axis.z *= 1.1;
		//x_axis.x *= 1.1;
		//x_axis.y *= 1.1;
		//x_axis.z *= 1.1;

	
		x_axis.normalize();
		y_axis.normalize();
		z_axis.normalize();

		
		//TRACE("x축%f, %f, %f, %f\n",rotate.x, x_axis.x, x_axis.y,x_axis.z);
		//TRACE("y축%f, %f, %f, %f\n",rotate.y, y_axis.x, y_axis.y,y_axis.z);
		//TRACE("z축%f, %f, %f, %f\n\n",rotate.z, z_axis.x, z_axis.y,z_axis.z);
	}
/*
	void Gizmo::rotate_Axis_xyz(){
		GLfloat r_x;
		GLfloat r_y;
		GLfloat r_z;
		GLfloat angle;
		GLfloat costheta;
		GLfloat sintheta;
		GLfloat r[3][3];
		vector3f tempX_1;
		vector3f tempX_2;
		vector3f tempY_1;
		vector3f tempY_2;
		vector3f tempZ_1;
		vector3f tempZ_2;

					///////////////zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz축회전
		// r_x = z_axis.x;      //회전축
		//r_y = z_axis.y;
		// r_z = z_axis.z;
		 r_x = 0.0f;      //회전축
		r_y = 0.f;
		 r_z = 1.f;

		  angle = rotate.z * (PI/180) ;  //회전 시킬 각도를 구함. radian값
		//angle = angle_z * 2;

		 costheta = (GLfloat)cos(angle);
		  sintheta = (GLfloat)sin(angle);


		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

		tempX_1.set(r[0][0], r[1][0], r[2][0]);
		
		//normalize(&tempX_1);
		//printVector(tempX_1);
		tempY_1.x = r[0][1] ;
		tempY_1.y = r[1][1] ;
		tempY_1.z = r[2][1] ;
		//normalize(&tempY_1);

	
		
			///////////////yyyyyyyyyyyyyyyyyyyyyyyyyyyy축회전
		 //r_x = y_axis.x;      //회전축
		 //r_y = y_axis.y;
		// r_z = y_axis.z;

		  r_x = 0.f;      //회전축
		 r_y = 1.f;
		 r_z = 0.f;

		//angle =  angle_y * 2  ;  //회전 시킬 각도를 구함. radian값
		 angle = rotate.y * (PI/180) ;

		costheta = (GLfloat)cos(angle);
		sintheta = (GLfloat)sin(angle);

	

		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;
	
		tempX_2.x = r[0][0]*tempX_1.x + r[0][1]*tempX_1.y + r[0][2]*tempX_1.z;
		tempX_2.y = r[1][0]*tempX_1.x + r[1][1]*tempX_1.y + r[1][2]*tempX_1.z ;
		tempX_2.z = r[2][0]*tempX_1.x + r[2][1]*tempX_1.y + r[2][2]*tempX_1.z ;
		//normalize(&tempX_2);

		tempZ_1.x = r[0][2] ;
		tempZ_1.y = r[1][2] ;
		tempZ_1.z = r[2][2] ;
		//normalize(&tempZ_1);

		///////////////xxxxxxxxxxxxxxxxxxxxxxx축회전
		//r_x = x_axis.x;      //회전축
		//r_y = x_axis.y;
		//r_z = x_axis.z;

		r_x = 1.f;      //회전축
		r_y = 0.f;
		r_z = 0.f;

		//angle =  angle_x *2 ;  //회전 시킬 각도를 구함. radian값
		 angle = rotate.x  * (PI/180) ;

		costheta = (GLfloat)cos(angle);
		sintheta = (GLfloat)sin(angle);

		

		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;


		tempY_2.x = r[0][0]*tempY_1.x + r[0][1]*tempY_1.y + r[0][2]*tempY_1.z ;
		tempY_2.y = r[1][0]*tempY_1.x + r[1][1]*tempY_1.y + r[1][2]*tempY_1.z ;
		tempY_2.z = r[2][0]*tempY_1.x + r[2][1]*tempY_1.y + r[2][2]*tempY_1.z ;
		//normalize(&tempY_2);
		tempZ_2.x = r[0][0]*tempZ_1.x + r[0][1]*tempZ_1.y + r[0][2]*tempZ_1.z ;
		tempZ_2.y = r[1][0]*tempZ_1.x + r[1][1]*tempZ_1.y + r[1][2]*tempZ_1.z ;
		tempZ_2.z = r[2][0]*tempZ_1.x + r[2][1]*tempZ_1.y + r[2][2]*tempZ_1.z ;
		//normalize(&tempZ_2);

		x_axis.x =tempX_2.x;
		x_axis.y =tempX_2.y;
		x_axis.z =tempX_2.z;
				y_axis.x = tempY_2.x;
		y_axis.y =  tempY_2.y;
		y_axis.z = tempY_2.z;
				z_axis.x = tempZ_2.x;
		z_axis.y = tempZ_2.y;
		z_axis.z =  tempZ_2.z;
		
		z_axis.x *= 1.1;
		z_axis.y *= 1.1;
		z_axis.z *= 1.1;
		y_axis.x *= 1.1;
		y_axis.y *= 1.1;
		y_axis.z *= 1.1;
		x_axis.x *= 1.1;
		x_axis.y *= 1.1;
		x_axis.z *= 1.1;

	
		x_axis.normalize();
		y_axis.normalize();
		z_axis.normalize();
		
		TRACE("x축%f, %f, %f, %f\n",rotate.x, x_axis.x, x_axis.y,x_axis.z);
		TRACE("y축%f, %f, %f, %f\n",rotate.y, y_axis.x, y_axis.y,y_axis.z);
		TRACE("z축%f, %f, %f, %f\n\n",rotate.z, z_axis.x, z_axis.y,z_axis.z);
		
}*/

void Gizmo::setRotate(GLfloat angle, vector3f axis){

		rotate_Axis_xyz_2((angle), axis);
	

	rotateInform temp;
	temp.angle = angle;
	temp.axis = axis;
	temp.rotate_Axis = translate - center;


	stack_Rotate.push_back(temp);

	current_Rotate.angle = 0;
	current_Rotate.axis.set(0,0,0);
	current_Rotate.rotate_Axis.set(0,0,0);
}

void Gizmo::setCenter(vector3f gizmo_center){
	center = gizmo_center;
	translate = gizmo_center;
}
vector3f Gizmo::setTranslate_afterRotate(GLfloat selected_Size, vector3f Gizmo_center){
		count_Gizmo++;
		
		GLfloat angle = 0;
		GLfloat r_x;
		GLfloat r_y;
		GLfloat r_z;
		GLfloat costheta;
		GLfloat sintheta;
		GLfloat r[3][3];
	

		
		r_x = current_Rotate.axis.x;      //회전축
		r_y = current_Rotate.axis.y;
		 r_z = current_Rotate.axis.z;

		//  TRACE("%d rotateGab : %f\n",count_Gizmo, rotateGab );
		

		angle = rotateGab * (PI/180) ;

		

		  costheta = cos(angle);
		  sintheta = sin(angle);


		r[0][0]  = (((1 - costheta) * r_x * r_x) + costheta) ;
		r[0][1]  = (((1 - costheta) * r_x *r_y) - (sintheta * r_z)) ;
		r[0][2]  = (((1 - costheta) * r_x * r_z) + (sintheta * r_y)) ;

		r[1][0]  = (((1 - costheta) * r_x *r_y) + (sintheta * r_z)) ;
		r[1][1]  = (((1 - costheta) * r_y * r_y) + costheta) ;
		r[1][2]  = (((1 - costheta) * r_y * r_z) - (sintheta * r_x)) ;

		r[2][0]  = (((1 - costheta) * r_x * r_z) - (sintheta * r_y)) ;
		r[2][1]  = (((1 - costheta) * r_y * r_z) + (sintheta * r_x)) ;
		r[2][2]  = (((1 - costheta) * r_z * r_z) + costheta) ;
		
		vector3f translate_center_vec = Gizmo_center - center;
		vector3f temp;
		temp.x = r[0][0]*translate_center_vec.x + r[0][1]*translate_center_vec.y + r[0][2]*translate_center_vec.z ;
		temp.y = r[1][0]*translate_center_vec.x + r[1][1]*translate_center_vec.y + r[1][2]*translate_center_vec.z ;
		temp.z = r[2][0]*translate_center_vec.x + r[2][1]*translate_center_vec.y + r[2][2]*translate_center_vec.z ;
		

		temp = temp + center;

		if(count_Gizmo == selected_Size){
			count_Gizmo = 0;
			rotateGab = 0;
		}
		return temp;

}//

void Gizmo::setAxis(vector3f xAxis, vector3f xYxis,vector3f xZxis){
	x_axis = xAxis;
	y_axis = xYxis;
	z_axis = xZxis;
}

void Gizmo::setCheck_Selected(BOOL selected){
	check_selected = selected;
}