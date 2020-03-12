#pragma once
#include "vector3.h"
#include <math.h>
class matrix4f
{
private:
public:
	matrix4f() {
		m[0][0] = 0;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
		m[1][0] = 0;	 m[1][1] = 0;	m[1][2] = 0;	m[1][3] = 0;
		m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 0;	m[2][3] = 0;
		m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 0;
	} 
	~matrix4f();
	float m[4][4];
	void makeIdentity() {
		m[0][0] = 1;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
		m[1][0] = 0;	 m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
		m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
		m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	}
	void makeTranslation(vector3 translationvector) {
		m[0][0] = 1;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = translationvector.x;
		m[1][0] = 0;	 m[1][1] = 1;	m[1][2] = 0;	m[1][3] = translationvector.y;
		m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 1;	m[2][3] = translationvector.z;
		m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	}
	void makeTranslation(float x, float y, float z) {
		m[0][0] = 1;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = x;
		m[1][0] = 0;	 m[1][1] = 1;	m[1][2] = 0;	m[1][3] = y;
		m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 1;	m[2][3] = z;
		m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	}
	void makeRotation(vector3 rotationvector) {
		matrix4f x;
		matrix4f y;
		matrix4f z;

		float xa = rotationvector.x * (3.14159265358979323f / 180.0f);
		float ya = rotationvector.y * (3.14159265358979323f / 180.0f);
		float za = rotationvector.z * (3.14159265358979323f / 180.0f);

		x.m[0][0] = 1;		 x.m[0][1] = 0;			x.m[0][2] = 0;			x.m[0][3] = 0;
		x.m[1][0] = 0;		 x.m[1][1] = cos(xa);	x.m[1][2] = -sin(xa);	x.m[1][3] = 0;
		x.m[2][0] = 0;		 x.m[2][1] = sin(xa);	x.m[2][2] = cos(xa);	x.m[2][3] = 0;
		x.m[3][0] = 0;		 x.m[3][1] = 0;			x.m[3][2] = 0;			x.m[3][3] = 1;

		y.m[0][0] = cos(ya);	 y.m[0][1] = 0;		y.m[0][2] = -sin(ya);	y.m[0][3] = 0;
		y.m[1][0] = 0;			 y.m[1][1] = 1;		y.m[1][2] = 0;			y.m[1][3] = 0;
		y.m[2][0] = sin(ya);	 y.m[2][1] = 0;		y.m[2][2] = cos(ya);	y.m[2][3] = 0;
		y.m[3][0] = 0;			 y.m[3][1] = 0;		y.m[3][2] = 0;			y.m[3][3] = 1;

		z.m[0][0] = cos(za);	 z.m[0][1] = -sin(za);	z.m[0][2] = 0;	z.m[0][3] = 0;
		z.m[1][0] = sin(za);	 z.m[1][1] = cos(za);	z.m[1][2] = 0;	z.m[1][3] = 0;
		z.m[2][0] = 0;			 z.m[2][1] = 0;			z.m[2][2] = 1;	z.m[2][3] = 0;
		z.m[3][0] = 0;			 z.m[3][1] = 0;			z.m[3][2] = 0;	z.m[3][3] = 1;

		*this = (z * (y * x));
	}
	void makeQuatRotation(Quaternion q) {
		/*(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));*/
		vector3 f(2.0f * (q.x * q.z - q.w * q.y), 2.0f * (q.y * q.z + q.w * q.x), 1.0f - 2.0f * (q.x * q.x + q.y * q.y));
		vector3 u(2.0f * (q.x * q.y + q.w * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z), 2.0f * (q.y * q.z - q.w * q.x));
		vector3 r(1.0f - 2.0f * (q.y * q.y + q.z * q.z), 2.0f * (q.x * q.y - q.w * q.z), 2.0f * (q.x * q.z + q.w * q.y));
		f = f.Normalize();
		u = u.Normalize();
		r = r.Normalize();

		m[0][0] = r.x;			m[0][1] = r.y;			m[0][2] = r.z;			m[0][3] = 0;
		m[1][0] = u.x;			m[1][1] = u.y;			m[1][2] = u.z;			m[1][3] = 0;
		m[2][0] = f.x;			m[2][1] = f.y;			m[2][2] = f.z;			m[2][3] = 0;
		m[3][0] = 0;			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1.0f;
	}
	void makeScaling(vector3 incvec) {
		m[0][0] = incvec.x;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
		m[1][0] = 0;	 m[1][1] = incvec.y;	m[1][2] = 0;	m[1][3] = 0;
		m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = incvec.z;	m[2][3] = 0;
		m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	}
	void makeProjection(float fov, float width, float height, float znear, float zfar){

		float tanhalffov = tan((fov/2) * (3.14159265358979323f / 180.0f));
		float viewrange = znear - zfar;

		m[0][0] = 1.0f/(tanhalffov * (width/height));	m[0][1] = 0;					m[0][2] = 0;								m[0][3] = 0;
		m[1][0] = 0;									m[1][1] = (1.0f/tanhalffov);	m[1][2] = 0;								m[1][3] = 0;
		m[2][0] = 0;									m[2][1] = 0;					m[2][2] = (-znear - zfar)/viewrange;		m[2][3] = (2.0f * zfar * znear) / viewrange;
		m[3][0] = 0;									m[3][1] = 0;					m[3][2] = 1;								m[3][3] = 0;
}
	void makeOrthographic(float left, float right, float bottom, float top, float near, float far) {
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;

		m[0][0] = 2.0f/width;	 m[0][1] = 0;			m[0][2] = 0;			m[0][3] = -(right + left) / width;
		m[1][0] = 0;			 m[1][1] = 2.0f/height;	m[1][2] = 0;			m[1][3] = -(top + bottom) / height;
		m[2][0] = 0;			 m[2][1] = 0;			m[2][2] = -2.0f/depth;	m[2][3] = -(far + near) / depth;
		m[3][0] = 0;			 m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1;
	}
	/*void makeCamera(Quaternion q) { 
		/*vector3 t = forward;	//normalize?
		vector3 u = up;
		u = u.crossProduct(t);	//right vector
		vector3 right = t.crossProduct(u);
		Quaternion newquat(t, u, r, 0);

		makeQuatRotation()

		vector3 f(2.0f * (q.x * q.z - q.w * q.y), 2.0f * (q.y * q.z + q.w * q.x), 1.0f - 2.0f * (q.x * q.x + q.y * q.y));
		vector3 u(2.0f * (q.x * q.y + q.w * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z), 2.0f * (q.y * q.z - q.w * q.x));
		vector3 r(1.0f - 2.0f * (q.y * q.y + q.z * q.z), 2.0f * (q.x * q.y - q.w * q.z), 2.0f * (q.x * q.z + q.w * q.y));
		
		m[0][0] = u.x;			m[0][1] = u.y;			m[0][2] = u.z;			m[0][3] = 0;
		m[1][0] = r.x;			m[1][1] = r.y;			m[1][2] = r.z;			m[1][3] = 0;
		m[2][0] = f.x;			m[2][1] = f.y;			m[2][2] = f.z;			m[2][3] = 0;
		m[3][0] = 0;			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1.0f;
	}*/
	matrix4f operator*(matrix4f rhs) {
		matrix4f tempmatrix;
		for (int i = 0; i < 4; i++) {
			for (int u = 0; u < 4; u++) {
				tempmatrix.setElement(i, u, m[i][0] * rhs.getElement(0, u) +
											m[i][1] * rhs.getElement(1, u) +
											m[i][2] * rhs.getElement(2, u) +
											m[i][3] * rhs.getElement(3, u));
			}
		}
		return tempmatrix;
	}
	float getElement(int x, int y) {
		return m[x][y];
	}
	matrix4f &operator=(const matrix4f &rhs) {
		for (int i = 0; i < 4; i++) {
			for (int u = 0; u < 4; u++) {
				m[i][u] = rhs.m[i][u];
			}
		}
		return *this;
	}
	void setElement(int x, int y, float newelement) {
		m[x][y] = newelement;
	}
	/*matrix4f &operator[](int x){  //figure out later
		return matrix4f(;
	}
	matrix4f &operator[](int x) {  //figure out later
		return matrix4f(;
	}*/
};

