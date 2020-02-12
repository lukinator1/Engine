#pragma once
#include "vector3.h"
#include <math.h>
class matrix4f
{
private:
public:
	matrix4f(); //todo: constructor
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
	void makeCamera(vector3 forward, vector3 up) { //don't make this referenced (maybe)
		vector3 t = forward.Normalize();

		vector3 u = up.Normalize();
		u = u.crossProduct(t);	//right vector
		vector3 right = t.crossProduct(u);
		
		m[0][0] = u.x;			m[0][1] = u.y;			m[0][2] = u.z;			m[0][3] = 0;
		m[1][0] = right.x;		m[1][1] = right.y;		m[1][2] = right.z;		m[1][3] = 0;
		m[2][0] = t.x;			m[2][1] = t.y;			m[2][2] = t.z;			m[2][3] = 0;
		m[3][0] = 0;			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1.0f;
	}
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

