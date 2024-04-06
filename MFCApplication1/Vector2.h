#pragma once
#define DIM 3
class Vector2
{
	double v[DIM];
public:
	Vector2();
	Vector2(double x, double y);
	Vector2(double row[DIM]);
	double* getCoordinates();
	Vector2 operator - (const Vector2& vec);
	Vector2 operator + (const Vector2& vec);
	Vector2 operator * (const double scalar);
	double getMagnitude();
	POINT toPoint();
	friend class Matrix2;
};

class Matrix2 {
public:
	double m[DIM][DIM];
	Matrix2();
	Matrix2(const Matrix2& mat);
	Matrix2(Vector2 rows[DIM]);
	void setTrans(double x, double y);
	void setRotate(double deg);
	void setScale(double factor);
	Vector2 operator * (const Vector2& vec);
	void transpose();
	Matrix2 operator * (const Matrix2& mat);
};