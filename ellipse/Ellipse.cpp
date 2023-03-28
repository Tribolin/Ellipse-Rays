#include "Ellipse.h"

Ellipse::Ellipse()
{
	a = 0;
	b = 0;
}

Ellipse::~Ellipse()
{
}
std::vector<Vec2> Ellipse::generateLine(float a, float b, float detail)
{
	std::vector<Vec2> Output;
	Ellipse::a = a;
	Ellipse::b = b;
	for (float i = -a; i < a; i += detail)
	{
		float y = (b/ a) * sqrt((a * a) - (i * i));
		Output.push_back({i,y});
	}
	std::vector<Vec2> Copy = Output;
	for (auto& i : Copy)
	{
		i.x *= -1;
		i.y *= -1;
		Output.push_back(i);
	}
	
	return Output;
	
}
std::vector<Vec2> Ellipse::Raycast(Vec2 Start, Vec2 Direktion)
{
	std::vector<Vec2> Raypoints;
	Raypoints.push_back(Start);
	for (size_t i = 0; i < 80; i++)
	{
		shootRay(Start,Direktion,Raypoints);
		Raypoints.push_back(Start);/*
		Raypoints.push_back({Start.x + Direktion.x * 100,Start.y + Direktion.y * 100});*/
		
	}
	return Raypoints;
}
void Ellipse::shootRay(Vec2& Start, Vec2& Direktion, std::vector<Vec2>& Raypoints)
{
	Vec2 NormDir = nomalise(Direktion);
	if (NormDir.x == 0)
	{
		if (NormDir.y > 0)
		{
			Start = { Start.x, ((b / a) * sqrt((a * a) - (Start.x * Start.x))) };
			return;
		}
		else
		{
			Start = { Start.x,-1 * ((b / a) * sqrt((a * a) - (Start.x * Start.x))) };
			return;
		}
	}
	else
	{
		
		//Calculate parameters
		double m = (NormDir.y / NormDir.x) ;
		
		//Calculate y-Offset
		double tY = (-1 * Start.x) / NormDir.x;
		double yOffset = NormDir.y * tY + Start.y;
		double c = yOffset;


		//Calc next possible x Cords
		double A = ((b * b) + ((a * a) * (m * m)));
		double B = (2 * (a * a) * m * c);
		double C = (((a * a) * (c * c)) - ((a * a) * (b * b)));
		double Dis = ((B * B) - (4 * A * C));
		double root = sqrt(Dis);

		//std::cout <<std::endl <<"Dis:" << Dis << std::endl;

		double X = 0;
		double Y = 0;

		double X1 = (-1 * B + root) / (2 * A);
		double X2 = (-1 * B - root) / (2 * A);
		if (Direktion.x > 0)
		{
			if (X1 > X2)
			{
				Y = GetY(X1, Start, NormDir);
				X = X1;
			}
			else
			{
				Y = GetY(X2, Start, NormDir);
				X = X2;
			}
			


		}
		else
		{
			
			if (X1 < X2)
			{
				Y = GetY(X1, Start, NormDir) ;
				X = X1;
			}
			else
			{
				Y = GetY(X2, Start, NormDir);
				X = X2;
			}

		}


		
		//Tangente
		const float move = 40;
		double TangentX = X + move;
		double TangentY = -1 * (((X / (a * a)) * TangentX) - 1) * ((b * b) / Y);

		Vec2 Tangent{ move,TangentY - Y };
		Vec2 I{ 0,-1 };
		Vec2 J{ 1,0 };
		Vec2 Normal{ ((Tangent.x * I.x) + (Tangent.y * J.x)),((Tangent.x * I.y) + (Tangent.y * J.y)) };

	
		/*Raypoints.push_back({ X,Y });
		Raypoints.push_back({(float)X + Tangent.x, (float)Y + Tangent.y});
		Raypoints.push_back({ (float)X,(float)Y });
		Raypoints.push_back({ (float)X + Normal.x/2, (float)Y + Normal.y/2 });*/
		

		double det = Normal.y * Tangent.x - (Normal.x * Tangent.y);
		
		
		double t = ((Tangent.y * NormDir.x )+ (-1* Tangent.x * NormDir.y))/det;
		double s = (( - 1 * Normal.y * NormDir.x) + (Normal.x * NormDir.y)) / det;

		Direktion = {( - 1 * s * Tangent.x) + (t * Normal.x),(-1 * s * Tangent.y) + (t * Normal.y) };
		Start = { X,Y };
		return;
	}
}

Vec2 Ellipse::nomalise(Vec2 ToNorm)
{
	float length = sqrt(((ToNorm.x * ToNorm.x) +(ToNorm.y * ToNorm.y)));
	ToNorm.x /= length;
	ToNorm.y /= length;
	return ToNorm;
}
double Ellipse::GetY(double X,Vec2 Start,Vec2 Dir)
{
	double t = (X - Start.x) / Dir.x;
	return ((Dir.y * t) +Start.y);
}
double Ellipse::Dot(Vec2 Vector1, Vec2 Vector2)
{
	return Vector1.x * Vector2.x + Vector1.y * Vector2.y;
}
double Ellipse::GetVecAngle(Vec2 Vector1, Vec2 Vector2)
{
	double length1 = sqrt((Vector1.x * Vector1.x) + (Vector1.y * Vector1.y));
	double length2 = sqrt((Vector2.x * Vector2.x) + (Vector2.y * Vector2.y));
	
	return acos((Dot(Vector1,Vector2)/(length1 * length2)));
}