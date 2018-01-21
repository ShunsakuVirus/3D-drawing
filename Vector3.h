#pragma once
struct Matrix4x4;
struct Vector3 {
	float x;
	float y;
	float z;

	Vector3();

	Vector3(float _x, float _y, float _z);

	Vector3 operator + (Vector3 v);
	Vector3 operator - (Vector3 v);
	Vector3 operator * (Vector3 v);
	Vector3 operator * (Matrix4x4 m);

	static Vector3 Cross(Vector3 v1, Vector3 v2);
	static float Dot(Vector3 v1, Vector3 v2);
	static Vector3 normalize(Vector3 v);
};
