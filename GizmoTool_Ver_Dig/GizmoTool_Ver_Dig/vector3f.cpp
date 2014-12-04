#include "StdAfx.h"
#include "vector3f.h"



vector3f::vector3f(){
x = 0.f;
y = 0.f; 
z = 0.f;
}
vector3f::vector3f(GLfloat setX, GLfloat setY, GLfloat setZ)
{
	x = setX;
	y = setY;
	z = setZ;
}

vector3f vector3f::normalVector(vector3f a, vector3f b, vector3f c){

	vector3f v1 = a - b;
	vector3f v2 = c - b;

	v2 = v2.crossProduct(v1);

	//v2.normalize();

	x = v2.x;
	y = v2.y;
	z = v2.z;

	return v2;

}




vector3f vector3f::normalize(){
			GLfloat temp = sqrt(x*x + y*y + z*z);
		//if(temp < 1.f)
		//	return ;

		x /= temp;
		y /= temp;
		z /= temp;

		return vector3f(x,y,z);

	}

void vector3f::sum(vector3f b) {
	x += b.x;
	y += b.y;
	z +=  b.z;	
}



void vector3f::set(GLfloat setX, GLfloat setY, GLfloat setZ){
	x = setX;
	y = setY;
	z = setZ;
}
void vector3f::setV(vector3f setVec){
	x = setVec.x;
	y = setVec.y;
	z = setVec.z;
}

void vector3f::printVector(){
TRACE("%f, %f, %f\n", x, y, z);
}


GLfloat vector3f::innerProduct(vector3f vec){
	   // vector3f temp;
		return (x * vec.x) + (y * vec.y) + (z * vec.z);
	}

vector3f vector3f::crossProduct(vector3f vec){
		vector3f cross;                                   //회전 축을 계산
		cross.x = y * vec.z - z * vec.y;
		cross.y = z * vec.x - x * vec.z;
		cross.z = x * vec.y - y * vec.x;
		cross.normalize();
		return cross;
}



GLfloat vector3f::acosTheta(vector3f vec){
	return acos((x * vec.x) + (y * vec.y) + (z * vec.z));
}


GLfloat vector3f::vectorValue(){
	return  sqrt(x*x + y*y + z*z);
}

void vector3f::DrawVector(int i){

	glPushMatrix();
	if(i==0)
		glColor3f(1,0,0);
	else if(i==1)
		glColor3f(0,1,0);
	else
		glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(x,y,z);
	glEnd();
	glPopMatrix();
}