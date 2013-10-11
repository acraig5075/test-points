#include "TestPoints.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iomanip>

TestPoints::TestPoints()
: m_range1(-50.0), m_range2(50.0), m_error(1.0)
{
}

TestPoints::~TestPoints()
{
}

void TestPoints::SetRange(double range1, double range2)
{
	ValidateRange(range1, range2);
	m_range1 = range1;
	m_range2 = range2;
}

void TestPoints::SetError(double error)
{
	m_error = error;
}

void TestPoints::Generate(int count, int precision, std::ostream &os)
{
	os << count << std::endl;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < count; i++)
	{
		double x = RandomX();
		double y = Equation(x);
		y += RandomError();
		RotateXY(x, y);
		TranslateXY(x, y);

		os << std::setprecision(precision) << std::setiosflags(std::ios::fixed) << x << "," << y << std::endl;
	}
}

double TestPoints::RandomError() const
{
	double high = m_error * 0.5;
	double low = -high;
	return ((rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low);
}

double TestPoints::RandomX() const
{
	double high, low;
	GetXRange(low, high);

	return ((rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low);
}

void TestPoints::GetXRange(double &low, double &high) const
	{
	low = m_range1;
	high = m_range2;
	}

void TestPoints::ValidateRange(double &range1, double &range2) const
	{
	// base class does nothing. override for circle and ellipse
	}

void TestPoints::RotateXY(double &x, double &y) const
	{
	// base class does nothing. override for ellipse
	}

void TestPoints::TranslateXY(double &x, double &y) const
	{
	// base class does nothing. override for circle and ellipse
	}


/////////////////////// TestPointsLine ////////////////////////

TestPointsLine::TestPointsLine(double slope, double intercept)
: TestPoints(), m_slope(slope), m_intercept(intercept)
	{
	}

double TestPointsLine::Equation(double x) const
{
return (m_slope * x) + m_intercept;
}

/////////////////////// TestPointsCircle ////////////////////////

TestPointsCircle::TestPointsCircle(double centrex, double centrey, double radius)
: TestPoints(),
	m_centrex(centrex),
	m_centrey(centrey),
	m_radius(radius),
	m_radius2(radius * radius)
	{
	m_range1 = -m_radius;
	m_range2 = m_radius;
	}

double TestPointsCircle::Equation(double x) const
	{
	int sign = (RandomError() < 0 ? -1 : 1);
	return (sign * sqrt(m_radius2 - (x * x)));
	}

void TestPointsCircle::TranslateXY(double &x, double &y) const
	{
	x += m_centrex;
	y += m_centrey;
	}

void TestPointsCircle::ValidateRange(double &range1, double &range2) const
	{
	range1 = std::max<double>(range1, -m_radius);
	range2 = std::min<double>(range2, m_radius);
	}

/////////////////////// TestPointsEllipse ////////////////////////

TestPointsEllipse::TestPointsEllipse(double centrex, double centrey, double a, double b, double rotation)
: TestPoints(),
	m_centrex(centrex),
	m_centrey(centrey),
	m_a(a),
	m_b(b),
	m_rotation(rotation),
	m_a2(a * a),
	m_b2(b * b),
	m_sinr(sin(rotation)),
	m_cosr(cos(rotation))
	{
	m_range1 = -m_a;
	m_range2 = m_a;
	}

double TestPointsEllipse::Equation(double x) const
	{
	int sign = (RandomError() < 0 ? -1 : 1);
	return (sign * sqrt(m_b2 * (1.0 - (x * x) / m_a2)));
	}

void TestPointsEllipse::TranslateXY(double &x, double &y) const
	{
	x += m_centrex;
	y += m_centrey;
	}

void TestPointsEllipse::RotateXY(double &x, double &y) const
	{
	double xx = (x * m_cosr) - (y * m_sinr);
	double yy = (x * m_sinr) + (y * m_cosr);
	x = xx;
	y = yy;
	}

void TestPointsEllipse::ValidateRange(double &range1, double &range2) const
	{
	range1 = std::max<double>(range1, -m_a);
	range2 = std::min<double>(range2, m_a);
	}

/////////////////////// TestPointsFactory ////////////////////////

TestPointsFactory::TestPointsFactory()
	{
	}

TestPoints *TestPointsFactory::Create(int type)
	{
	if (0 == type) // line takes 2 parameters from command-line
		{
		double slope = 0.0;
		double intercept = 0.0;
		std::cin >> slope;
		std::cin >> intercept;
		return new TestPointsLine(slope, intercept);
		}
	else if (1 == type) // circle takes 3 parameters from command-line
		{
		double centrex = 0.0;
		double centrey = 0.0;
		double radius = 0.0;
		std::cin >> centrex;
		std::cin >> centrey;
		std::cin >> radius;
		return new TestPointsCircle(centrex, centrey, radius);
		}
	else if (2 == type) // ellipse takes 5 parameters from command-line
		{
		double centrex = 0.0;
		double centrey = 0.0;
		double a = 0.0;
		double b = 0.0;
		double rotation = 0.0;
		std::cin >> centrex;
		std::cin >> centrey;
		std::cin >> a;
		std::cin >> b;
		std::cin >> rotation;
		return new TestPointsEllipse(centrex, centrey, a, b, rotation);
		}
	else
		return NULL;
	}
