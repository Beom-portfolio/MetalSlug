#pragma once

// º¸°£
template<typename T1, typename T2>
inline const T1 Lerp(const T2& start, const T2& end, float process)
{
	return T1((1.f - process) * start + process * end);
}

inline float ToRadian(const float& angle)
{
	return angle * PI / 180.f;
}

inline const POSITION AnglePos(const float& posX, const float& posY, const float& angle, const int& length)
{
	return POSITION{posX + (cosf(ToRadian(angle)) * (float)length),
					posY - (sinf(ToRadian(angle)) * (float)length)};
}
