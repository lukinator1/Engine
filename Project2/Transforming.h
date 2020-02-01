#pragma once
#include "Engine.h"
class Transforming
{
public:
	vector3 translation;
	Transforming();
	~Transforming();
	vector3 getTranslation() {
		return translation;
	}
	matrix4f newTransformatiobMatrix() {
		matrix4f translationmatrix;
		translationmatrix.makeTranslation(translation);
		return translationmatrix;
	}
	vector3 setTranslation(vector3 newtranslation){
		translation = newtranslation;
		}
};

