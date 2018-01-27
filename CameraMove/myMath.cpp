#include "myMath.h"
namespace myMath {
	float degToRad(float deg) {
		return deg * 3.14159265358979f / 180.0f;
	}
	float radToDeg(float rad) {
		return rad * 180.0f / 3.14159265358979f;
	}
}