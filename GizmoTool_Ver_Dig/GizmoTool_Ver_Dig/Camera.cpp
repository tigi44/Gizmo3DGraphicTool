#include "StdAfx.h"
#include "Camera.h"

#define ZOOMINOUT_SPEED 1;
#define TRANSLATE_SPEED 0.05f;
#define ROTATE_ALGLE_SPEED 0.002f;

enum {chk_Perspective, chk_Ortho};
Camera::Camera()
{
		pos_eye.x = 20.f;
		pos_eye.y = 20.f;
		pos_eye.z = 20.f;

		pos_center.x = 0.f;
		pos_center.y = 0.f;
		pos_center.z = 0.f;

		pos_upvector.x = 0.f;
		pos_upvector.y = 1.f;
		pos_upvector.z = 0.f;

		reset_eye.x = pos_eye.x;
		reset_eye.y = pos_eye.y;
		reset_eye.z = pos_eye.z; 

		reset_center.x = pos_center.x;
		reset_center.y = pos_center.y;
		reset_center.z = pos_center.z;

		reset_upvector.x = pos_upvector.x;
		reset_upvector.y = pos_upvector.y;
		reset_upvector.z = pos_upvector.z;

		camera_Perspective.m_fovy = 60.f;
		camera_Perspective.m_aspect = 1.f;
		camera_Perspective.m_zNear = 0.1f;
		camera_Perspective.m_zFar = 1000.f;

	camera_Ortho.left = -40;
	camera_Ortho.right = 40;
	camera_Ortho.bottom = -40;
	camera_Ortho.top = 40;
	camera_Ortho.mfar = 1000;
	camera_Ortho.mnear = -1;

		count_posPicked = 0;
		
		client_Rect.SetRect(0,0,0,0);

		check_LMouse = FALSE;
		check_RMouse = FALSE;
		key_check_Q = FALSE;
		key_check_X = FALSE;
		key_check_Z = FALSE;

		check_Perspective_Ortho = chk_Perspective;

		name = "MAIN";
}

Camera::Camera(vector3f eye, vector3f center, vector3f upvector)
{
		pos_eye.x = eye.x;
		pos_eye.y = eye.y;
		pos_eye.z = eye.z;

		pos_center.x = center.x;
		pos_center.y = center.y;
		pos_center.z = center.z;

		pos_upvector.x = upvector.x;
		pos_upvector.y = upvector.y;
		pos_upvector.z = upvector.z;

		reset_eye.x = pos_eye.x;
		reset_eye.y = pos_eye.y;
		reset_eye.z = pos_eye.z; 

		reset_center.x = pos_center.x;
		reset_center.y = pos_center.y;
		reset_center.z = pos_center.z;

		reset_upvector.x = pos_upvector.x;
		reset_upvector.y = pos_upvector.y;
		reset_upvector.z = pos_upvector.z;

		camera_Perspective.m_fovy = 60.f;
		camera_Perspective.m_aspect = 1.f;
		camera_Perspective.m_zNear = 0.1f;
		camera_Perspective.m_zFar = 1000.f;

	camera_Ortho.left = -40;
	camera_Ortho.right = 40;
	camera_Ortho.bottom = -40;
	camera_Ortho.top = 40;
	camera_Ortho.mfar = 1000;
	camera_Ortho.mnear = -1;

		count_posPicked = 0;
			client_Rect.SetRect(0,0,0,0);

				check_LMouse = FALSE;
		check_RMouse = FALSE;
				key_check_Q = FALSE;
		key_check_X = FALSE;
		key_check_Z = FALSE;

		check_Perspective_Ortho = chk_Perspective;
}


Camera::~Camera(void)
{
}

	void Camera::set_Count_pickedPos(){
		count_posPicked++;
	}
	
	BOOL Camera::get_Count_pickedPos(){
		if(count_posPicked == 0)
			return FALSE;
		else
			return TRUE;
	}
	void Camera::clear_Count_pickedPos(){
		count_posPicked = 0;
		pos_PickedRotatation.x = 0.f;
		pos_PickedRotatation.y = 0.f;
		pos_PickedRotatation.z = 0.f;
	}

	vector3f Camera::getLookVector(){
		vector3f lookVec;
		lookVec.x = pos_center.x - pos_eye.x;
		lookVec.y = pos_center.y - pos_eye.y;
		lookVec.z = pos_center.z - pos_eye.z;
		lookVec.normalize();
		
		return lookVec;
	}



void Camera::setPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){
		camera_Perspective.m_fovy = fovy;
		camera_Perspective.m_aspect = aspect;
		camera_Perspective.m_zNear = zNear;
		camera_Perspective.m_zFar = zFar;

		//gluPerspective(camera_Perspective.m_fovy,camera_Perspective.m_aspect, camera_Perspective.m_zNear, camera_Perspective.m_zFar);

}

void Camera::perspective(){
	gluPerspective(camera_Perspective.m_fovy,camera_Perspective.m_aspect, camera_Perspective.m_zNear, camera_Perspective.m_zFar);
}

void Camera::setOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble mnear, GLdouble mfar){
	camera_Ortho.left = left;
	camera_Ortho.right = right;
	camera_Ortho.bottom = bottom;
	camera_Ortho.top = top;
	camera_Ortho.mfar = mfar;
	camera_Ortho.mnear = mnear;
	//glOrtho(camera_Ortho.left,camera_Ortho.right,camera_Ortho.bottom,camera_Ortho.top,camera_Ortho.mnear ,camera_Ortho.mfar);
}

void Camera::Ortho(){
		glOrtho(camera_Ortho.left,camera_Ortho.right,camera_Ortho.bottom,camera_Ortho.top,camera_Ortho.mnear ,camera_Ortho.mfar);
}

void Camera::Set_cameraView_Perspective_Ortho(BOOL type){
	check_Perspective_Ortho = type;
}

BOOL Camera::Get_cameraView_Perspective_Ortho(){
	return check_Perspective_Ortho;
}
	
void Camera::cameraView(){
	if(!check_Perspective_Ortho){
		gluPerspective(camera_Perspective.m_fovy,camera_Perspective.m_aspect, camera_Perspective.m_zNear, camera_Perspective.m_zFar);
	}
	else{
		glOrtho(camera_Ortho.left,camera_Ortho.right,camera_Ortho.bottom,camera_Ortho.top,camera_Ortho.mnear ,camera_Ortho.mfar);
	}
}



void Camera::setLookAt(){
	gluLookAt(pos_eye.x, pos_eye.y, pos_eye.z,
			pos_center.x, pos_center.y, pos_center.z,
			pos_upvector.x, pos_upvector.y, pos_upvector.z);
}


void Camera::setLastPoint(CPoint cp){
	last_Point = cp;
}

void Camera::setReset(){
		pos_center = reset_center;
		pos_eye = reset_eye;
		pos_upvector = reset_upvector;

}
void Camera::setEyeCenter(vector3f eye, vector3f center){
	pos_center = center;
	pos_eye = eye;
}

void Camera::setPos_PickedRotatation(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){
	
	vector3f pos = worldPlane(cp,projection,modelView,viewPort);
	//TRACE("%d,%d\n", cp.x, cp.y);

	pos_PickedRotatation.x = pos.x;
	pos_PickedRotatation.y = pos.y;
	pos_PickedRotatation.z = pos.z;
	
	/*
	vector3f z_1_vec = z_1(cp,projection, modelView, viewPort);
	vector3f z_0_vec = z_0(cp,projection, modelView, viewPort);
	
	GLfloat t = z_0_vec.y / (z_0_vec.y - z_1_vec.y);
	
	pos_PickedRotatation.x = z_0_vec.x + t*(z_1_vec.x - z_0_vec.x);
	pos_PickedRotatation.y = 0;
	pos_PickedRotatation.z = z_0_vec.z + t*(z_1_vec.z - z_0_vec.z);
	*/
	
}

void Camera::zoomIn(){

		vector3f zoomIn_Vec;

		zoomIn_Vec.x = pos_center.x - pos_eye.x;
		zoomIn_Vec.y = pos_center.y - pos_eye.y;
		zoomIn_Vec.z = pos_center.z - pos_eye.z;

		zoomIn_Vec.normalize();
		


		pos_eye.x  = pos_eye.x + zoomIn_Vec.x/ZOOMINOUT_SPEED;
		pos_eye.y  = pos_eye.y + zoomIn_Vec.y/ZOOMINOUT_SPEED;
		pos_eye.z  = pos_eye.z + zoomIn_Vec.z/ZOOMINOUT_SPEED;

		pos_center.x = pos_center.x + zoomIn_Vec.x/ZOOMINOUT_SPEED;
		pos_center.y = pos_center.y + zoomIn_Vec.y/ZOOMINOUT_SPEED;
		pos_center.z = pos_center.z + zoomIn_Vec.z/ZOOMINOUT_SPEED;

	}

void Camera::zoomOut(){

		vector3f zoomOut_Vec;

		zoomOut_Vec.x = pos_center.x - pos_eye.x;
		zoomOut_Vec.y = pos_center.y - pos_eye.y;
		zoomOut_Vec.z = pos_center.z - pos_eye.z;

		zoomOut_Vec.normalize();
		

		pos_eye.x  = pos_eye.x - zoomOut_Vec.x/ZOOMINOUT_SPEED;
		pos_eye.y  = pos_eye.y - zoomOut_Vec.y/ZOOMINOUT_SPEED;
		pos_eye.z  = pos_eye.z - zoomOut_Vec.z/ZOOMINOUT_SPEED;

		pos_center.x = pos_center.x - zoomOut_Vec.x/ZOOMINOUT_SPEED;
		pos_center.y = pos_center.y - zoomOut_Vec.y/ZOOMINOUT_SPEED;
		pos_center.z = pos_center.z - zoomOut_Vec.z/ZOOMINOUT_SPEED;

		
	}

void Camera::camera_DirectionKey(UINT nChar){
		vector3f look_vec;
		vector3f cross_result;

		//for(int i=0;i<3;i++)
		look_vec.x = pos_center.x - pos_eye.x;
		look_vec.y = pos_center.y - pos_eye.y;
		look_vec.z = pos_center.z - pos_eye.z;

		cross_result.x = pos_upvector.y * look_vec.z - pos_upvector.z * look_vec.y;
		cross_result.y = pos_upvector.z * look_vec.x - pos_upvector.x * look_vec.z;
		cross_result.z = pos_upvector.x * look_vec.y - pos_upvector.y * look_vec.x;
		cross_result.normalize();
		look_vec.normalize();


		if(nChar == VK_LEFT){	
			pos_eye.x  = pos_eye.x + cross_result.x/ZOOMINOUT_SPEED;
			pos_eye.y  = pos_eye.y + cross_result.y/ZOOMINOUT_SPEED;
			pos_eye.z  = pos_eye.z + cross_result.z/ZOOMINOUT_SPEED;

			pos_center.x = pos_center.x + cross_result.x/ZOOMINOUT_SPEED;
			pos_center.y = pos_center.y + cross_result.y/ZOOMINOUT_SPEED;
			pos_center.z = pos_center.z + cross_result.z/ZOOMINOUT_SPEED;			
		}
		else if(nChar == VK_RIGHT){
			pos_eye.x  = pos_eye.x - cross_result.x/ZOOMINOUT_SPEED;
			pos_eye.y  = pos_eye.y - cross_result.y/ZOOMINOUT_SPEED;
			pos_eye.z  = pos_eye.z - cross_result.z/ZOOMINOUT_SPEED;

			pos_center.x = pos_center.x - cross_result.x/ZOOMINOUT_SPEED;
			pos_center.y = pos_center.y - cross_result.y/ZOOMINOUT_SPEED;
			pos_center.z = pos_center.z - cross_result.z/ZOOMINOUT_SPEED;
		}

		else if(nChar == VK_UP){
			pos_eye.x  = pos_eye.x + look_vec.x/ZOOMINOUT_SPEED;
			//pos_eye.y  = pos_eye.y + pos_upvector.y/ZOOMINOUT_SPEED;
			pos_eye.z  = pos_eye.z + look_vec.z/ZOOMINOUT_SPEED;

			pos_center.x  = pos_center.x + look_vec.x/ZOOMINOUT_SPEED;
			//pos_center.y  = pos_center.y + pos_upvector.y/ZOOMINOUT_SPEED;
			pos_center.z  = pos_center.z + look_vec.z/ZOOMINOUT_SPEED;
		}
		else if(nChar == VK_DOWN){
			pos_eye.x  = pos_eye.x - look_vec.x/ZOOMINOUT_SPEED;
			//pos_eye.y  = pos_eye.y - pos_upvector.y/ZOOMINOUT_SPEED;
			pos_eye.z  = pos_eye.z - look_vec.z/ZOOMINOUT_SPEED;

			pos_center.x  = pos_center.x - look_vec.x/ZOOMINOUT_SPEED;
			//pos_center.y  = pos_center.y - pos_upvector.y/ZOOMINOUT_SPEED;
			pos_center.z  = pos_center.z - look_vec.z/ZOOMINOUT_SPEED;
		}

		//Invalidate(FALSE);
	}

	void Camera::camera_translate(CPoint cp){
		//(view_Center.x - cp.x) * ROTATE_ALGLE_SPEED;
		GLfloat dic_x = cp.x - last_Point.x;
		GLfloat dic_y = cp.y - last_Point.y;

		vector3f look_vec;
		vector3f cross_result;
		vector3f cross_result_cross;

		//for(int i=0;i<3;i++)
		look_vec.x = pos_center.x - pos_eye.x;
		look_vec.y = pos_center.y - pos_eye.y;
		look_vec.z = pos_center.z - pos_eye.z;

		cross_result.x = pos_upvector.y * look_vec.z - pos_upvector.z * look_vec.y;
		cross_result.y = pos_upvector.z * look_vec.x - pos_upvector.x * look_vec.z;
		cross_result.z = pos_upvector.x * look_vec.y - pos_upvector.y * look_vec.x;
		
		cross_result.normalize();

		if(dic_x < 0){	
			pos_eye.x  = pos_eye.x - (cross_result.x *  (-dic_x)) * TRANSLATE_SPEED ;
			pos_eye.y  = pos_eye.y - (cross_result.y *  (-dic_x))* TRANSLATE_SPEED;
			pos_eye.z  = pos_eye.z - (cross_result.z *  (-dic_x))* TRANSLATE_SPEED;

			pos_center.x = pos_center.x - (cross_result.x * (-dic_x))* TRANSLATE_SPEED;
			pos_center.y = pos_center.y - (cross_result.y * (-dic_x))* TRANSLATE_SPEED;
			pos_center.z = pos_center.z - (cross_result.z * (-dic_x))* TRANSLATE_SPEED;			
		}
		else if(dic_x > 0){
			pos_eye.x  = pos_eye.x + (cross_result.x * (dic_x))* TRANSLATE_SPEED;
			pos_eye.y  = pos_eye.y + (cross_result.y *  (dic_x))* TRANSLATE_SPEED;
			pos_eye.z  = pos_eye.z + (cross_result.z *  (dic_x))* TRANSLATE_SPEED;

			pos_center.x = pos_center.x + (cross_result.x * (dic_x))* TRANSLATE_SPEED;
			pos_center.y = pos_center.y + (cross_result.y *  (dic_x))* TRANSLATE_SPEED;
			pos_center.z = pos_center.z + (cross_result.z *  (dic_x))* TRANSLATE_SPEED;
		}

		cross_result_cross.x = cross_result.y * look_vec.z - cross_result.z * look_vec.y;
		cross_result_cross.y = cross_result.z * look_vec.x - cross_result.x * look_vec.z;
		cross_result_cross.z = cross_result.x * look_vec.y - cross_result.y * look_vec.x;

		cross_result_cross.normalize();

		if(dic_y < 0){	
			pos_eye.x  = pos_eye.x + (cross_result_cross.x *  (-dic_y)) * TRANSLATE_SPEED ;
			pos_eye.y  = pos_eye.y + (cross_result_cross.y *  (-dic_y))* TRANSLATE_SPEED;
			pos_eye.z  = pos_eye.z + (cross_result_cross.z *  (-dic_y))* TRANSLATE_SPEED;

			pos_center.x = pos_center.x + (cross_result_cross.x * (-dic_y))* TRANSLATE_SPEED;
			pos_center.y = pos_center.y + (cross_result_cross.y * (-dic_y))* TRANSLATE_SPEED;
			pos_center.z = pos_center.z + (cross_result_cross.z * (-dic_y))* TRANSLATE_SPEED;			
		}
		else if(dic_y > 0){
			pos_eye.x  = pos_eye.x - (cross_result_cross.x * (dic_y))* TRANSLATE_SPEED;
			pos_eye.y  = pos_eye.y - (cross_result_cross.y *  (dic_y))* TRANSLATE_SPEED;
			pos_eye.z  = pos_eye.z - (cross_result_cross.z *  (dic_y))* TRANSLATE_SPEED;

			pos_center.x = pos_center.x - (cross_result_cross.x * (dic_y))* TRANSLATE_SPEED;
			pos_center.y = pos_center.y - (cross_result_cross.y *  (dic_y))* TRANSLATE_SPEED;
			pos_center.z = pos_center.z - (cross_result_cross.z *  (dic_y))* TRANSLATE_SPEED;
		}


		last_Point = cp;
		//Invalidate(FALSE);
	}

	void Camera::camera_First_Rotate(CPoint cp){
		/////// yaw 회전 (좌 우)
		vector3f look_vec;
		vector3f look_vec_After;
		GLfloat angle;

		look_vec.x = pos_center.x - pos_eye.x;
		look_vec.y = pos_center.y - pos_eye.y;
		look_vec.z = pos_center.z - pos_eye.z;

		GLfloat r_x = pos_upvector.x;      //회전축
		GLfloat r_y = pos_upvector.y;
		GLfloat r_z = pos_upvector.z;

		angle=(last_Point.x - cp.x) * ROTATE_ALGLE_SPEED;  //회전 시킬 각도를 구함. radian값


		GLfloat costheta = (GLfloat)cos(angle);
		GLfloat sintheta = (GLfloat)sin(angle);

		GLfloat r[3][3];

		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

		look_vec_After.x = r[0][0]*look_vec.x + r[0][1]*look_vec.y + r[0][2]*look_vec.z;
		look_vec_After.y = r[1][0]*look_vec.x + r[1][1]*look_vec.y + r[1][2]*look_vec.z;
		look_vec_After.z = r[2][0]*look_vec.x + r[2][1]*look_vec.y + r[2][2]*look_vec.z;

		pos_center.x = pos_eye.x + look_vec_After.x;
		pos_center.y = pos_eye.y + look_vec_After.y;
		pos_center.z = pos_eye.z + look_vec_After.z;


		/////// pitch 회전 (위, 아래)
		look_vec.x = pos_center.x - pos_eye.x;
		look_vec.y = pos_center.y - pos_eye.y;
		look_vec.z = pos_center.z - pos_eye.z;


		vector3f cross;                                   //회전 축을 계산
		cross.x = pos_upvector.y * look_vec.z - pos_upvector.z * look_vec.y;
		cross.y = pos_upvector.z * look_vec.x - pos_upvector.x * look_vec.z;
		cross.z = pos_upvector.x * look_vec.y - pos_upvector.y * look_vec.x;
		cross.normalize();
		

		r_x = cross.x;
		r_y = cross.y;
		r_z = cross.z;

		angle = (cp.y - last_Point.y) *  ROTATE_ALGLE_SPEED;

		//pitch_Check = pitch_Check + angle;

		//if(angle > - 0.7 && angle < 0.7)                //pitch회전시 각도가 90도 이상 넘어가는것 방지 radian각도로 계산
		{
			costheta=(GLfloat)cos(angle);
			sintheta=(GLfloat)sin(angle);

			r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
			r[0][1]  = ((1 - costheta) * r_x * r_y - sintheta * r_z) ;
			r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

			r[1][0]  = ((1 - costheta) * r_x * r_y + sintheta * r_z) ;
			r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
			r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

			r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
			r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
			r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

			look_vec_After.x = r[0][0]*look_vec.x + r[0][1]*look_vec.y + r[0][2]*look_vec.z;
			look_vec_After.y = r[1][0]*look_vec.x + r[1][1]*look_vec.y + r[1][2]*look_vec.z;
			look_vec_After.z = r[2][0]*look_vec.x + r[2][1]*look_vec.y + r[2][2]*look_vec.z;

			pos_center.x = pos_eye.x + look_vec_After.x;
			pos_center.y = pos_eye.y + look_vec_After.y;
			pos_center.z = pos_eye.z + look_vec_After.z;

		}
		//else
		//pitch_Check = pitch_Check - angle;

		vector3f lookVec = getLookVector();
		GLfloat value = lookVec.innerProduct(vector3f(0,1,0));
		if((value <= 1 && value >= 0.9999) || (value >= -1 && value <= -0.9999)){
		//if(value == 1 || value == -1){
			//pos_upvector.x*=(-1.0f);
			pos_upvector.y*=(-1.0f);
			//pos_upvector.z*=(-1.0f);
			pos_upvector.printVector();
		}
			
		//TRACE("%f\n",value);

		last_Point = cp;
		//Invalidate(FALSE);
	}


	void Camera::camera_Center_Rotate(CPoint cp){
		/////// yaw 회전 (좌 우)
		vector3f look_vec;
		vector3f look_vec_After;
		GLfloat angle;

		look_vec.x = pos_eye.x - pos_center.x; //센터에서 카메라를 보고 있는 방향 벡터 lookat의 반대
		look_vec.y = pos_eye.y - pos_center.y;
		look_vec.z = pos_eye.z - pos_center.z;

		GLfloat r_x = pos_upvector.x;      //회전축
		GLfloat r_y = pos_upvector.y;
		GLfloat r_z = pos_upvector.z;

		angle=(last_Point.x - cp.x) * ROTATE_ALGLE_SPEED;  //회전 시킬 각도를 구함. radian값


		GLfloat costheta = (GLfloat)cos(angle);
		GLfloat sintheta = (GLfloat)sin(angle);

		GLfloat r[3][3];

		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

		look_vec_After.x = r[0][0]*look_vec.x + r[0][1]*look_vec.y + r[0][2]*look_vec.z;
		look_vec_After.y = r[1][0]*look_vec.x + r[1][1]*look_vec.y + r[1][2]*look_vec.z;
		look_vec_After.z = r[2][0]*look_vec.x + r[2][1]*look_vec.y + r[2][2]*look_vec.z;

		pos_eye.x = pos_center.x + look_vec_After.x;
		pos_eye.y = pos_center.y + look_vec_After.y;
		pos_eye.z = pos_center.z + look_vec_After.z;


		/////// pitch 회전 (위, 아래)
		look_vec.x = pos_eye.x - pos_center.x;
		look_vec.y = pos_eye.y - pos_center.y;
		look_vec.z = pos_eye.z - pos_center.z;


		vector3f cross;                                   //회전 축을 계산
		cross.x = pos_upvector.y * look_vec.z - pos_upvector.z * look_vec.y;
		cross.y = pos_upvector.z * look_vec.x - pos_upvector.x * look_vec.z;
		cross.z = pos_upvector.x * look_vec.y - pos_upvector.y * look_vec.x;
		cross.normalize();

		r_x = cross.x;
		r_y = cross.y;
		r_z = cross.z;

		angle = (last_Point.y - cp.y) *  ROTATE_ALGLE_SPEED;

		//pitch_Check = pitch_Check + angle;

		//if(angle > - 0.7 && angle < 0.7)                //pitch회전시 각도가 90도 이상 넘어가는것 방지 radian각도로 계산
		{
			costheta=(GLfloat)cos(angle);
			sintheta=(GLfloat)sin(angle);

			r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
			r[0][1]  = ((1 - costheta) * r_x * r_y - sintheta * r_z) ;
			r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

			r[1][0]  = ((1 - costheta) * r_x * r_y + sintheta * r_z) ;
			r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
			r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

			r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
			r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
			r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

			look_vec_After.x = r[0][0]*look_vec.x + r[0][1]*look_vec.y + r[0][2]*look_vec.z;
			look_vec_After.y = r[1][0]*look_vec.x + r[1][1]*look_vec.y + r[1][2]*look_vec.z;
			look_vec_After.z = r[2][0]*look_vec.x + r[2][1]*look_vec.y + r[2][2]*look_vec.z;

			pos_eye.x = pos_center.x + look_vec_After.x;
			pos_eye.y = pos_center.y + look_vec_After.y;
			pos_eye.z = pos_center.z + look_vec_After.z;

		}

		vector3f lookVec = getLookVector();
		GLfloat value = lookVec.innerProduct(vector3f(0,1,0));
		if((value <= 1 && value >= 0.9999) || (value >= -1 && value <= -0.9999)){
			pos_upvector.x*=(-1.0f);
			pos_upvector.y*=(-1.0f);
			pos_upvector.z*=(-1.0f);
			pos_upvector.printVector();
		}
			

		last_Point = cp;
		//Invalidate(FALSE);
	}


	void Camera::camera_Pick_Rotate(CPoint cp){
		/////// yaw 회전 (좌 우)
		vector3f look_vec_center;
		vector3f look_vec_eye;
		vector3f look_vec_After_center;
		vector3f look_vec_After_eye;
		vector3f look_vec;
		GLfloat angle;

		look_vec_center.x = pos_center.x - pos_PickedRotatation.x; //센터에서 카메라를 보고 있는 방향 벡터 lookat의 반대
		look_vec_center.y = pos_center.y - pos_PickedRotatation.y;
		look_vec_center.z = pos_center.z - pos_PickedRotatation.z;

		look_vec_eye.x = pos_eye.x - pos_PickedRotatation.x; //카메라 위치에서 center를 바라 보고 있는 벡터
		look_vec_eye.y = pos_eye.y - pos_PickedRotatation.y;
		look_vec_eye.z = pos_eye.z - pos_PickedRotatation.z;

		GLfloat r_x = pos_upvector.x;      //회전축
		GLfloat r_y = pos_upvector.y;
		GLfloat r_z = pos_upvector.z;

		angle=(last_Point.x - cp.x) * ROTATE_ALGLE_SPEED;  //회전 시킬 각도를 구함. radian값


		GLfloat costheta = (GLfloat)cos(angle);
		GLfloat sintheta = (GLfloat)sin(angle);

		GLfloat r[3][3];

		r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
		r[0][1]  = ((1 - costheta) * r_x *r_y - sintheta * r_z) ;
		r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

		r[1][0]  = ((1 - costheta) * r_x *r_y + sintheta * r_z) ;
		r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
		r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

		r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
		r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
		r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

		look_vec_After_center.x = r[0][0]*look_vec_center.x + r[0][1]*look_vec_center.y + r[0][2]*look_vec_center.z;
		look_vec_After_center.y = r[1][0]*look_vec_center.x + r[1][1]*look_vec_center.y + r[1][2]*look_vec_center.z;
		look_vec_After_center.z = r[2][0]*look_vec_center.x + r[2][1]*look_vec_center.y + r[2][2]*look_vec_center.z;

		look_vec_After_eye.x = r[0][0]*look_vec_eye.x + r[0][1]*look_vec_eye.y + r[0][2]*look_vec_eye.z;
		look_vec_After_eye.y = r[1][0]*look_vec_eye.x + r[1][1]*look_vec_eye.y + r[1][2]*look_vec_eye.z;
		look_vec_After_eye.z = r[2][0]*look_vec_eye.x + r[2][1]*look_vec_eye.y + r[2][2]*look_vec_eye.z;

		pos_eye.x = pos_PickedRotatation.x + look_vec_After_eye.x;
		pos_eye.y = pos_PickedRotatation.y + look_vec_After_eye.y;
		pos_eye.z = pos_PickedRotatation.z + look_vec_After_eye.z;

		pos_center.x = pos_PickedRotatation.x  + look_vec_After_center.x;
		pos_center.y = pos_PickedRotatation.y  + look_vec_After_center.y;
		pos_center.z = pos_PickedRotatation.z + look_vec_After_center.z;



		/////// pitch 회전 (위, 아래)
		look_vec.x = pos_eye.x - pos_center.x; //회전축 계산을 위해
		look_vec.y = pos_eye.y - pos_center.y;
		look_vec.z = pos_eye.z - pos_center.z;

		look_vec_center.x = pos_center.x - pos_PickedRotatation.x; //센터에서 카메라를 보고 있는 방향 벡터 lookat의 반대
		look_vec_center.y = pos_center.y - pos_PickedRotatation.y;
		look_vec_center.z = pos_center.z - pos_PickedRotatation.z;

		look_vec_eye.x = pos_eye.x - pos_PickedRotatation.x; //카메라 위치에서 center를 바라 보고 있는 벡터
		look_vec_eye.y = pos_eye.y - pos_PickedRotatation.y;
		look_vec_eye.z = pos_eye.z - pos_PickedRotatation.z;


		vector3f cross;                                   //회전 축을 계산
		cross.x = pos_upvector.y * look_vec.z - pos_upvector.z * look_vec.y;
		cross.y = pos_upvector.z * look_vec.x - pos_upvector.x * look_vec.z;
		cross.z = pos_upvector.x * look_vec.y - pos_upvector.y * look_vec.x;
		cross.normalize();

		r_x = cross.x;
		r_y = cross.y;
		r_z = cross.z;

		angle = (last_Point.y - cp.y) *  ROTATE_ALGLE_SPEED;

		//pitch_Check = pitch_Check + angle;

		//if(angle > - 0.7 && angle < 0.7)                //pitch회전시 각도가 90도 이상 넘어가는것 방지 radian각도로 계산
		{
			costheta=(GLfloat)cos(angle);
			sintheta=(GLfloat)sin(angle);

			r[0][0]  = ((1 - costheta) * r_x * r_x + costheta) ;
			r[0][1]  = ((1 - costheta) * r_x * r_y - sintheta * r_z) ;
			r[0][2]  = ((1 - costheta) * r_x * r_z + sintheta * r_y) ;

			r[1][0]  = ((1 - costheta) * r_x * r_y + sintheta * r_z) ;
			r[1][1]  = ((1 - costheta) * r_y * r_y + costheta) ;
			r[1][2]  = ((1 - costheta) * r_y * r_z - sintheta * r_x) ;

			r[2][0]  = ((1 - costheta) * r_x * r_z - sintheta * r_y) ;
			r[2][1]  = ((1 - costheta) * r_y * r_z + sintheta * r_x) ;
			r[2][2]  = ((1 - costheta) * r_z * r_z + costheta) ;

			look_vec_After_center.x = r[0][0]*look_vec_center.x + r[0][1]*look_vec_center.y + r[0][2]*look_vec_center.z;
			look_vec_After_center.y = r[1][0]*look_vec_center.x + r[1][1]*look_vec_center.y + r[1][2]*look_vec_center.z;
			look_vec_After_center.z = r[2][0]*look_vec_center.x + r[2][1]*look_vec_center.y + r[2][2]*look_vec_center.z;

			look_vec_After_eye.x = r[0][0]*look_vec_eye.x + r[0][1]*look_vec_eye.y + r[0][2]*look_vec_eye.z;
			look_vec_After_eye.y = r[1][0]*look_vec_eye.x + r[1][1]*look_vec_eye.y + r[1][2]*look_vec_eye.z;
			look_vec_After_eye.z = r[2][0]*look_vec_eye.x + r[2][1]*look_vec_eye.y + r[2][2]*look_vec_eye.z;

			pos_eye.x = pos_PickedRotatation.x + look_vec_After_eye.x;
			pos_eye.y = pos_PickedRotatation.y + look_vec_After_eye.y;
			pos_eye.z = pos_PickedRotatation.z + look_vec_After_eye.z;

			pos_center.x = pos_PickedRotatation.x  + look_vec_After_center.x;
			pos_center.y = pos_PickedRotatation.y  + look_vec_After_center.y;
			pos_center.z = pos_PickedRotatation.z + look_vec_After_center.z;
		}
		
		vector3f lookVec = getLookVector();
		GLfloat value = lookVec.innerProduct(vector3f(0,1,0));
		if((value <= 1 && value >= 0.9999) || (value >= -1 && value <= -0.9999)){
			pos_upvector.x*=(-1.0f);
			pos_upvector.y*=(-1.0f);
			pos_upvector.z*=(-1.0f);
			pos_upvector.printVector();
		}
			

		last_Point = cp;
		//Invalidate(FALSE);

	}



	void Camera::set_Client_Rect(CRect rect){
		client_Rect = rect;
	}

	BOOL Camera::camera_Mouse_Evnet(MSG *pMsg){
		CPoint point(LOWORD(pMsg->lParam)-client_Rect.left, HIWORD(pMsg->lParam)-client_Rect.top);

		
		if(pMsg->message == WM_LBUTTONDOWN){
			check_LMouse = TRUE;
		
			//TRACE("%d, %d\n",point.x,point.y );
			
			this->setLastPoint(point);
			
			if(key_check_Z && !this->get_Count_pickedPos()){
	
	
				this->setPos_PickedRotatation(point,projection,modelView,viewPort);
				this->set_Count_pickedPos();
			}
		
		}
		else if(pMsg->message == WM_LBUTTONUP){
			check_LMouse = FALSE;
		}
		else if(pMsg->message == WM_RBUTTONDOWN){
			check_RMouse = TRUE;
			this->setLastPoint(point);
		}
		else if(pMsg->message == WM_RBUTTONUP){
			check_RMouse = FALSE;
			
		}
		else if(pMsg->message == WM_MOUSEWHEEL){
			if((int)pMsg->wParam > 0)
				this->zoomIn();
			else 
				this->zoomOut();
		}

		else if(pMsg->message == WM_MOUSEMOVE){
			if(check_LMouse){
				if(key_check_X){
				this->camera_Center_Rotate(point);
				
				}
				else if(key_check_Z){
					this->camera_Pick_Rotate(point);
				
				}
				else if(key_check_Q){
					this->camera_translate(point);
				
				}
			}
			else if(check_RMouse){
				this->camera_First_Rotate(point);
			}
				
		}
		
		return TRUE;
	}

	BOOL Camera::camera_Key_Event(MSG *pMsg){
	
	if(pMsg->message == WM_KEYUP){
		switch(pMsg->wParam){

		case 'X':
			key_check_X = FALSE;
			//key_check_Q = FALSE;
			break;
		case 'Z': // ALT
			key_check_Z = FALSE;
			this->clear_Count_pickedPos();
			break;

		default:
			break;
		}

	}

	return TRUE;
	}

	void Camera::set_Projection_Modelview_viewport(GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){
		
		for(int i = 0; i< 16; i++){
			this->projection[i] = projection[i];
			this->modelView[i] = modelView[i];
		}
		for(int i=0; i<4; i++){
			this->viewPort[i] = viewPort[i];
		}
		
		
	}

	void Camera::camera_KeyReset(){

		check_LMouse = FALSE;
		check_RMouse = FALSE;
		key_check_Q = FALSE;
		key_check_X = FALSE;
		key_check_Z = FALSE;
	}


	void Camera::keyEvent_F(){	
				this->setReset();
	}

	void Camera::keyEvent_Up(){
		camera_DirectionKey(VK_UP);
	}
	void Camera::keyEvent_Down(){
		camera_DirectionKey(VK_DOWN);
	}
	void Camera::keyEvent_Left(){
		camera_DirectionKey(VK_LEFT);
	}
	void Camera::keyEvent_Right(){
		camera_DirectionKey(VK_RIGHT);
	}

	void Camera::keyEvent_X(){
		key_check_X = TRUE;
	}
	void Camera::keyEvent_Z(){
		key_check_Z = TRUE;
	}
	void Camera::keyEvent_Q(){
		if(key_check_Q){
				key_check_Q = FALSE;	
			}
			else {
				key_check_Q = TRUE;
			}
	}
	void Camera::keyEvent_O(){
		if(check_Perspective_Ortho)
				check_Perspective_Ortho = chk_Perspective;
			else
				check_Perspective_Ortho = chk_Ortho;
	}