#pragma once
struct Matrix4x4;
struct Vector3;
struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4();

	Vector4(float _x, float _y, float _z, float _w);

	Vector4 operator + (Vector4 v);
	Vector4 operator - (Vector4 v);
	Vector4 operator * (Matrix4x4 m);

	static Vector3 screenTransformation(Vector4 v, int width, int height);
};
