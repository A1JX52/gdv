#pragma once
#define DIM 4

namespace consts {
	static const int axisX = 0, axisY = 1, axisZ = 2;
}

class Vector3
{
	double v[DIM];
public:
	Vector3();
	Vector3(double x, double y, double z);
	POINT toPoint();
	Vector3 operator * (const double& scalar);
	double* getCoordinates();
	Vector3 operator + (const Vector3& vec);
	friend class Matrix3;
};

class Matrix3 {
	double m[DIM][DIM];
public:
	Matrix3();
	void setTrans(double x, double y, double z);
	void setRotate(double deg, int opt);
	void setPersp(double dist);
	Vector3 operator * (const Vector3& vec);
};