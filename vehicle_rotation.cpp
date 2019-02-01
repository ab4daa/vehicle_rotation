#include "vehicle_rotation.h"

namespace MYGAME
{
	const float DEFAULT_ROTATION_SPEED = 1.0f;
	vehicle_rotation::vehicle_rotation(float pitch, float yaw, float roll)
		: _pitch_spd(DEFAULT_ROTATION_SPEED), _yaw_spd(DEFAULT_ROTATION_SPEED), _roll_spd(DEFAULT_ROTATION_SPEED)
	{
		_pitch = constrainAngle180(pitch);
		_yaw = constrainAngle180(yaw);
		_roll = constrainAngle180(roll);
	}

	vehicle_rotation::vehicle_rotation()
		: _pitch(0.0f), _yaw(0.0f), _roll(0.0f),
		_pitch_spd(DEFAULT_ROTATION_SPEED), _yaw_spd(DEFAULT_ROTATION_SPEED), _roll_spd(DEFAULT_ROTATION_SPEED)
	{}

	/*bound = [leftBound, rightBound)*/
	float vehicle_rotation::turnTowardBound(float start, float dest, float speed, float timeStep)
	{
		const float leftBound = -180.0f;
		const float rightBound = 180.0f;
		if (!inBound(start, leftBound, rightBound))
			start = constrainAngle180(start);

		if (!inBound(dest, leftBound, rightBound))
			dest = constrainAngle180(dest);

		if (start == dest)
			return start;

		float leftD, rightD;
		if (inBound(dest, leftBound, start))
		{
			leftD = start - dest;
			rightD = (rightBound - start) + (dest - leftBound);
		}
		else
		{
			leftD = (start - leftBound) + (rightBound - dest);
			rightD = dest - start;
		}

		if (leftD < rightD)
		{
			if (leftD > timeStep * speed)
				return start - timeStep * speed;
			else
				return dest;
		}
		else
		{
			if (rightD > timeStep * speed)
				return start + timeStep * speed;
			else
				return dest;
		}
	}

	void vehicle_rotation::turnToward(float timeStep, float pitch_, float yaw_, float roll_)
	{
		_pitch = turnTowardBound(_pitch, pitch_, _pitch_spd, timeStep);
		_yaw = turnTowardBound(_yaw, yaw_, _yaw_spd, timeStep);
		_roll = turnTowardBound(_roll, roll_, _roll_spd, timeStep);
	}

	void vehicle_rotation::set_speed(float pitch_speed, float yaw_speed, float roll_speed)
	{
		_pitch_spd = pitch_speed;
		_yaw_spd = yaw_speed;
		_roll_spd = roll_speed;
	}

	void vehicle_rotation::set_rotation(float pitch, float yaw, float roll)
	{
		_pitch = constrainAngle180(pitch);
		_yaw = constrainAngle180(yaw);
		_roll = constrainAngle180(roll);
	}

	void vehicle_rotation::get_rotation(float &pitch, float &yaw, float &roll)
	{
		pitch = _pitch;
		yaw = _yaw;
		roll = _roll;
	}
}		/*namespace MYGAME*/
