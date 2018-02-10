#pragma once
struct Vector2 {
	float x;
	float y;

	Vector2();

	Vector2(float _x, float _y);

	Vector2 operator + (Vector2 v);
	Vector2 operator - (Vector2 v);
	Vector2 operator * (Vector2 v);
	Vector2 operator / (Vector2 v);

	Vector2 operator * (float f);

	static float cross(Vector2 v1, Vector2 v2);
	static float dot(Vector2 v1, Vector2 v2);
	static Vector2 nornalize(Vector2 v);
};