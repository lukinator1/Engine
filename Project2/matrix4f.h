#pragma once
#include "vector3.h"
class matrix4f
{
private:
public:
	matrix4f();
	~matrix4f();
	float m[4][4];
	void makeIdentity() {
		for (int i = 0; i < 4; i++) {
			for (int u = 0; u < 4; u++) {
				m[0][0] = 1;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
				m[1][0] = 0;	 m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
				m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
				m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
			}
		}
	}
	void makeTranslation(vector3 translationvector) {
		for (int i = 0; i < 4; i++) {
			for (int u = 0; u < 4; u++) {
				m[0][0] = 1;	 m[0][1] = 0;	m[0][2] = 0;	m[0][3] = translationvector.x;
				m[1][0] = 0;	 m[1][1] = 1;	m[1][2] = 0;	m[1][3] = translationvector.y;
				m[2][0] = 0;	 m[2][1] = 0;	m[2][2] = 1;	m[2][3] = translationvector.z;
				m[3][0] = 0;	 m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
			}
		}
	}
	void operator*(matrix4f rhs) {
		matrix4f tempmatrix;
		for (int i = 0; i < 4; i++) {
			for (int u = 0; u < 4; u++) {
				tempmatrix.setElement(i, u, m[i][0] * rhs.getElement(0, u) +
											m[i][1] * rhs.getElement(1, u) +
											m[i][2] * rhs.getElement(2, u) +
											m[i][3] * rhs.getElement(3, u));
			}
		}
	}
	float getElement(int x, int y) {
		return m[x][y];
	}
	matrix4f &operator=(matrix4f &rhs) {
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
	/*matrix4f &operator[](int index){  //figure out later
		return m[index];
	}*/
};

