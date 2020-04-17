#pragma once

// º¸°£
template<typename T1, typename T2>
inline const T1 Lerp(const T2& start, const T2& end, float process)
{
	if (process > 1.f) return end;
	else if (process < 0.f) return start;

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

inline const float GetDistance(const POSITION& a, const POSITION& b)
{
	float distX = abs(a.X - b.X);
	float distY = abs(a.Y - b.Y);

	return sqrtf(distX * distX + distY * distY);
}
