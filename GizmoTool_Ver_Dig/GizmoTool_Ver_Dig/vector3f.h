//#include "StdAfx.h"
#pragma once
class vector3f
{
public:	
			GLfloat x;
			GLfloat y;
			GLfloat z;

			vector3f();
			vector3f(GLfloat setX, GLfloat setY, GLfloat setZ);
			
			void set(GLfloat setX, GLfloat setY, GLfloat setZ);
			void setV(vector3f setVec);
			void sum(vector3f b) ;

			vector3f operator + (vector3f &vec){
				return vector3f(x+vec.x, y+vec.y, z+vec.z);
			}
			vector3f operator - (vector3f &vec){
				return vector3f(x-vec.x, y-vec.y, z-vec.z);
			}
			vector3f operator = (vector3f &vec){
				return vector3f(x=vec.x, y=vec.y, z=vec.z);
			}
			vector3f operator += (vector3f &vec){
				return vector3f(x+=vec.x, y+=vec.y, z+=vec.z);
			}
			vector3f operator -= (vector3f &vec){
				return vector3f(x-=vec.x, y-=vec.y, z-=vec.z);
			}

			vector3f normalVector(vector3f a, vector3f b, vector3f c);

			vector3f normalize();

			void printVector();

			GLfloat innerProduct(vector3f vec);

			vector3f crossProduct(vector3f vec);

			GLfloat acosTheta(vector3f vec);

			GLfloat vectorValue();

			void DrawVector(int i);



friend vector3f worldPlane(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){


		vector3f wxyz;
		GLdouble wx_0,wy_0,wz_0;
		GLdouble wx_1,wy_1,wz_1;

		GLfloat zCursor,winX,winY;

		winX = (GLfloat)cp.x;
		winY = (GLfloat)viewPort[3]-(GLfloat)cp.y;
		//TRACE("%f, %f, %f\n",winX, winY, viewPort[3]);
		//glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); // 클릭한 곳의 윈도우 z-buffer값 계산
	
		gluUnProject(winX,winY,0,modelView,projection,viewPort,&wx_0,&wy_0,&wz_0);
		gluUnProject(winX,winY,1,modelView,projection,viewPort,&wx_1,&wy_1,&wz_1);



		GLfloat t = wy_0 / (wy_0 - wy_1);

		wxyz.x = (GLfloat)(wx_0 + t*(wx_1 - wx_0));
		wxyz.y = 0.f;
		wxyz.z = (GLfloat)(wz_0 + t*(wz_1 - wz_0));

		return wxyz;
	};


friend vector3f z_1(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){


		vector3f wxyz;
		GLdouble wx,wy,wz;

		GLfloat zCursor,winX,winY;

		winX = (GLfloat)cp.x;
		winY = (GLfloat)viewPort[3]-(GLfloat)cp.y;
		//TRACE("%f, %f, %f\n",winX, winY, viewPort[3]);
		glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); // 클릭한 곳의 윈도우 z-buffer값 계산
	
		
		if(gluUnProject(winX,winY,1,modelView,projection,viewPort,&wx,&wy,&wz)==GLU_FALSE){
			//TRACE("실패\n");
		}

			wxyz.x = (GLfloat)wx;
			wxyz.y = (GLfloat)wy;
			wxyz.z = (GLfloat)wz;

		return wxyz;
	};
friend vector3f z_0(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){



		vector3f wxyz;
		GLdouble wx,wy,wz;

		GLfloat zCursor,winX,winY;

		winX = (GLfloat)cp.x;
		winY = (GLfloat)viewPort[3]-(GLfloat)cp.y;
		//TRACE("%f, %f, %f\n",winX, winY, viewPort[3]);
		glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); // 클릭한 곳의 윈도우 z-buffer값 계산
	
		
		if(gluUnProject(winX,winY,0,modelView,projection,viewPort,&wx,&wy,&wz)==GLU_FALSE){
			//TRACE("실패\n");
		}

			wxyz.x = (GLfloat)wx;
			wxyz.y = (GLfloat)wy;
			wxyz.z = (GLfloat)wz;

		return wxyz;
	};


friend vector3f fromMouseToWorld(CPoint cp, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){
	/*
		for(int i = 0 ; i <16 ; i+=4){
			if(i==0)
				TRACE("ASD\n");

			TRACE("%f, %f, %f, %f\n", modelView[i], modelView[i+1], modelView[i+2], modelView[i+3]);
		}
		*/



		vector3f wxyz;
		GLdouble wx,wy,wz;

		GLfloat zCursor,winX,winY;

		winX = (GLfloat)cp.x;
		winY = (GLfloat)viewPort[3]-(GLfloat)cp.y;
		//TRACE("%f, %f, %f\n",winX, winY, viewPort[3]);
		glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); // 클릭한 곳의 윈도우 z-buffer값 계산
	
		
		if(gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&wx,&wy,&wz)==GLU_FALSE){
			//TRACE("실패\n");
		}

			wxyz.x = (GLfloat)wx;
			wxyz.y = (GLfloat)wy;
			wxyz.z = (GLfloat)wz;

		return wxyz;
	};

friend CPoint fromWorldToMouse(vector3f vec, GLdouble projection[16], GLdouble modelView[16], GLint viewPort[4]){


	CPoint xy;
	GLdouble wx,wy,wz;
	gluProject(vec.x, vec.y, vec.z, modelView, projection, viewPort,&wx,&wy,&wz);

		xy.x = wx;
		xy.y = viewPort[3]-wy;
		return xy;

	};



};





