#include "pch.h"
#include "Vector2.h"
#include <algorithm>

Vector2::Vector2() {
	for (int i = 0; i < DIM; i++) {
		v[i] = 0;
	}
}

Vector2::Vector2(double x, double y) {
	v[0] = x;
	v[1] = y;
	v[2] = 1;
}

Vector2::Vector2(double row[DIM]) {
	v[0] = row[0];
	v[1] = row[1];
	v[2] = row[2];
}

double* Vector2::getCoordinates() {
	double temp[DIM];
	std::copy(std::begin(v), std::end(v), std::begin(temp));
	return v;
}

Vector2 Vector2::operator - (const Vector2& vec) {
	Vector2 temp;

	for (int i = 0; i < DIM; i++) {
		temp.v[i] = v[i] - vec.v[i];
	}
	return temp;
}

Vector2 Vector2::operator + (const Vector2& vec) {
	Vector2 temp;

	for (int i = 0; i < DIM; i++) {
		temp.v[i] = v[i] + vec.v[i];
	}
	return temp;
}

Vector2 Vector2::operator * (const double scalar) {
	Vector2 temp;

	for (int i = 0; i < DIM; i++) {
		temp.v[i] = v[i] * scalar;
	}
	return temp;
}

double Vector2::getMagnitude() {
	double temp = 0;

	for (int i = 0; i < DIM; i++) {
		temp += v[i] * v[i];
	}
	return sqrt(temp);
}

POINT Vector2::toPoint() {
	POINT p;
	p.x = v[0];
	p.y = v[1];
	return p;
}

Matrix2::Matrix2() {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

Matrix2::Matrix2(const Matrix2& mat) {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			m[i][j] = mat.m[i][j];
		}
	}
}

Matrix2::Matrix2(Vector2 rows[DIM]) {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			m[i][j] = rows[i].v[j];
		}
	}
}

void Matrix2::setTrans(double dx, double dy) {
	m[0][2] = dx;
	m[1][2] = dy;
}

void Matrix2::setRotate(double deg) {
	m[0][0] = cos(deg);
	m[0][1] = -sin(deg);
	m[1][0] = sin(deg);
	m[1][1] = cos(deg);
}

void Matrix2::setScale(double factor) {
	m[0][0] = factor;
	m[1][1] = factor;
}

Vector2 Matrix2::operator * (const Vector2& vec) {
	Vector2 temp;

	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			temp.v[i] += m[i][j] * vec.v[j];
		}
	}
	return temp;
}

void Matrix2::transpose() {
	for (int i = 0; i < DIM; i++) {
		for (int j = i + 1; j < DIM; j++) {
			double temp = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = temp;
		}
	}
}

Matrix2 Matrix2::operator * (const Matrix2& mat) {
	Matrix2 matCpy = Matrix2(mat);
	matCpy.transpose();

	Vector2 resRows[DIM] = {};

	for (int i = 0; i < DIM; i++) {
		resRows[i] = (*this * Vector2(matCpy.m[i]));
	}
	Matrix2 temp = Matrix2(resRows);
	temp.transpose();
	return temp;
}