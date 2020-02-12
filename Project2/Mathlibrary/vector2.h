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
		float x;
		float y;
	};

