#pragma once
#include <math.h>
#include "../Logger.h"
#include "Quaternion.h"
	class vector2 : public Logger
	{
	public:
		vector2() {

		}
		vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}
		~vector2() {

		}
		void setVector(float x, float y){
			this->x = x;
			this->y = y;
		}
		float Magnitude() {
			return sqrt((x * x) + (y * y));
		}
		float dotProduct() {
			return (x * x) + (y * y);
		}
		vector2 Normalize() {
			float length = sqrt((x * x) + (y * y));
			/*x = x / length;
			y = y / length;
			z = z / length;
			return *this;*/
			if (length == 0) {
				engineLog(__FILE__, __LINE__, "A vector2 of length 0 was attempted to be normalized. This is an invalid operation and did not go through. ", 3, 3, true);
				return *this;
			}
			else return vector2(x / length, y / length);
		}
		vector2 Rotate(float angle, vector2 axis){
			float sinhalfangle = sinf((angle / 2.0f) * (3.14159265358979323f / 180.0f));
			float coshalfangle = cosf((angle / 2.0f) * (3.14159265358979323f / 180.0f));

			float qx = axis.x * sinhalfangle;		//convert matrix -> quaternion
			float qy = axis.y * sinhalfangle;
			float qw = coshalfangle;

			Quaternion rotation(qx, qy, 0, qw);
			Quaternion rotationconjugate = rotation.Conjugate();

			Quaternion newquat = (rotation.Multiply(x, y, 0)).Multiply(rotationconjugate);
			vector2 newvector(newquat.x, newquat.y);

			/*x = newquat.x;
			y = newquat.y;
			z = newquat.z;*/

			return newvector;
		}
		float crossProduct(vector2 other) {
			return (x * other.y) - (y * other.x);
		}
		vector2 Add(vector2 adder)
		{
			return vector2(x + adder.x, y + adder.y);
		}
		vector2 Add(float adder)
		{
			return vector2(x + adder, y + adder);
		}
		vector2 Multiply(vector2 multiplier)
		{
			return vector2(x * multiplier.x, y * multiplier.y);
		}
		vector2 Multiply(float multiplier)
		{
			return vector2(x * multiplier, y * multiplier);
		}
		vector2 Subtract(vector2 sub) {
			return vector2(x - sub.x, y - sub.y);
		}
		vector2 Subtract(float sub) {
			return vector2(x - sub, y - sub);
		}
		vector2 interpolateVector(vector2 destination, float interpfactor) {
			return destination.Subtract(*this).Multiply(interpfactor).Add(*this);
		}
		bool operator==(vector2 & rhs) {
			if (x == rhs.x && y == rhs.y) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator!=(vector2 & rhs)
		{
			if (x != rhs.x || y != rhs.y) {
				return true;
			}
			else {
				return false;
			}
		}
		vector2 operator*(vector2 & rhs)
		{
			return vector2(x * rhs.x, y * rhs.y);
		}
		vector2 operator+(vector2 & rhs)
		{
			return vector2(x + rhs.x, y + rhs.y);
		}
		vector2 operator+=(vector2 & rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		vector2 operator-(vector2 & rhs)
		{
			return vector2(x - rhs.x, y - rhs.y);
		}
		float x;
		float y;
	};

