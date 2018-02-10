#pragma once
struct Matrix4x4;
struct Vector4;
struct Vector3 {
	float x;
	float y;
	float z;

	Vector3();

	Vector3(float _x, float _y, float _z);

	Vector3 operator + (Vector3 v);
	Vector3 operator - (Vector3 v);
	Vector3 operator * (Vector3 v);
	Vector3 operator / (Vector3 v);

	Vector3 operator * (float f);
	Vector3 operator / (float f);

	static Vector3 cross(Vector3 v1, Vector3 v2);
	static float dot(Vector3 v1, Vector3 v2);
	static Vector3 normalize(Vector3 v);
	Vector3 normalized();
};
