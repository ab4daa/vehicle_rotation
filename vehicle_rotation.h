#pragma once
#ifndef __VEHICLE_ROTATION_H__
#define __VEHICLE_ROTATION_H__

#include <math.h>

namespace MYGAME
{
	class vehicle_rotation
	{
	public:
		vehicle_rotation(float pitch, float yaw, float roll);
		vehicle_rotation();
		~vehicle_rotation() {}
		void turnToward(float timeStep, float pitch_, float yaw_, float roll_);
		void set_speed(float pitch_speed, float yaw_speed, float roll_speed);
		void set_rotation(float pitch, float yaw, float roll);
		void get_rotation(float &pitch, float &yaw, float &roll);

	private:
		float _pitch;
		float _yaw;
		float _roll;
		float _pitch_spd;
		float _yaw_spd;
		float _roll_spd;

		inline float constrainAngle180(float x) {
			x = fmod(x + 180, 360);
			if (x < 0)
				x += 360;
			return x - 180;
		}
		/*bound = [leftBound, rightBound)*/
		inline bool inBound(float x, float leftBound, float rightBound) { return (x >= leftBound && x < rightBound); }
		float turnTowardBound(float start, float dest, float speed, float timeStep);
	};
}

#endif
