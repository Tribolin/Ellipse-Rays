#pragma once
#include "SFML/Graphics.hpp" 

struct Vec2 {
	double x;
	double y;
	operator sf::Vector2f() {
		return sf::Vector2f((float)x,(float)y);
	}
};
struct Quarternion {
	double r;
	double i;
	double j;
	double k;
	Quarternion operator *(Quarternion b) {
		return{
			((r * b.r) - (i * b.i) - (j * b.j) - (k * b.k)),
			((r * b.i) + (i * b.r) + (j * b.k) - (k * b.j)),
			((r * b.j) - (i * b.k) + (j * b.r) + (k * b.i)),
			((r * b.k) + (i * b.j) - (j * b.i) + (k * b.r))
		};
	}
};