#pragma once

#include <vector>
#include <cmath>
#include <iostream>
#include "Vec2.h"
#define PI 3.14159265


class Ellipse
{
public:
	Ellipse();
	~Ellipse();
	std::vector<Vec2> generateLine(float a,float b, float detail);
	std::vector<Vec2> Raycast(Vec2 Start,Vec2 Direktion);

private:
	float b;
	float a;
	float c;
	Vec2 nomalise(Vec2 ToNorm);
	double Dot(Vec2 Vector1, Vec2 Vector2);
	double GetY(double X, Vec2 Start, Vec2 Dir);
	void shootRay(Vec2& Start, Vec2& Direktion,std::vector<Vec2>& raypoints);
};

