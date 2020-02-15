#pragma once
	class vector2 {
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
		float x;
		float y;
	};

