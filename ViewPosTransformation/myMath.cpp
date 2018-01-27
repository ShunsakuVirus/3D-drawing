#include "myMath.h"
namespace myMath {
	float degToRad(float deg) {
		return deg * 3.14159265358979 / 180;
	}
	float radToDeg(float rad) {
		return rad * 180 / 3.14159265358979;
	}
}