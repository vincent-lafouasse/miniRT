#pragma once

#include "gtest/gtest.h"

extern "C" {
#include "math/t_vec3/t_vec3.h"
};

struct Vector {
	t_vec3 self;

	Vector(double x, double y, double z): self(vec3_new(x, y, z)) {}
	// vvv PS: this is a converting constructor
	Vector(t_vec3 vec): self(vec) {}
	
	t_vec3 get() const { return this->self; }

	Vector operator+(const Vector& v) const {
		return vec3_add(self, v.get());
	}

	Vector operator-(const Vector& v) const {
		return vec3_sub(self, v.get());
	}

	Vector operator-() const {
		return *this * -1.0;
	}

	Vector operator*(const double s) const {
		return vec3_mul(s, self);
	}

	Vector operator/(const double s) const {
		return vec3_div(self, s);
	}

	static Vector Origin(void) {
		return vec3_new(0.0, 0.0, 0.0);
	}

	static Vector E_X(void) {
		return vec3_new(1.0, 0.0, 0.0);
	}

	static Vector E_Y(void) {
		return vec3_new(0.0, 0.0, 1.0);
	}

	static Vector E_Z(void) {
		return vec3_new(0.0, 0.0, 1.0);
	}
};

