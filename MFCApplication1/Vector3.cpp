#include "pch.h"
#include "Vector3.h"
#include <algorithm>
using namespace consts;

Vector3::Vector3() {
	for (int i = 0; i < DIM; i++) {
		v[i] = 0;
	}
}

Vector3::Vector3(double x, double y, double z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = 1;
}

POINT Vector3::toPoint() {
	POINT p;
	p.x = v[0];
	p.y = v[1];
	return p;
}

Vector3 Vector3::operator * (const double& scalar) {
	Vector3 temp;

	for (int i = 0; i < DIM; i++) {
		temp.v[i] = v[i] * scalar;
	}
	return temp;
}

double* Vector3::getCoordinates() {
	double temp[DIM];
	std::copy(std::begin(v), std::end(v), std::begin(temp));
	return temp;
}

Vector3 Vector3::operator + (const Vector3& vec) {
	Vector3 temp;

	for (int i = 0; i < DIM; i++) {
		temp.v[i] = v[i] + vec.v[i];
	}
	return temp;
}

Matrix3::Matrix3() {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

void Matrix3::setTrans(double dx, double dy, double dz) {
	m[0][3] = dx;
	m[1][3] = dy;
	m[2][3] = dz;
}

void Matrix3::setRotate(double deg, int opt) {
	if (opt == axisX) {
		m[1][1] = cos(deg);
		m[2][1] = -sin(deg);
		m[1][2] = sin(deg);
		m[2][2] = cos(deg);
	}
	else if (opt == axisY) {
		m[0][0] = cos(deg);
		m[2][0] = -sin(deg);
		m[0][2] = sin(deg);
		m[2][2] = cos(deg);
	}
	else if (axisZ) {
		m[0][0] = cos(deg);
		m[0][1] = -sin(deg);
		m[1][0] = sin(deg);
		m[1][1] = cos(deg);
	}
}

void Matrix3::setPersp(double dist) {
	m[2][2] = 0;
	m[3][2] = 1 / dist;
}

Vector3 Matrix3::operator * (const Vector3& vec) {
	Vector3 temp;

	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			temp.v[i] += m[i][j] * vec.v[j];
		}
	}
	return temp;
}