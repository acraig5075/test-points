#pragma once

#include <iostream>
#include <vector>

class TestPoints
{
	public:
		TestPoints();
		virtual ~TestPoints();

		virtual bool operator == (const TestPoints &rhs) const { return false; };

		void SetRange(double range1, double range2);
		void SetError(double tolerance);
		void Generate(int count, int precision, std::ostream &os);
		void Generate(int count, int precision, std::vector<double> &points);
	protected:
		double RandomError() const;

		bool CompareCoordinateValue(double a, double b) const;
		bool CompareAngleValue(double a, double b) const;

		double m_range1;
		double m_range2;
		double m_error;
	private:
		double RandomX() const;
		void GetXRange(double &low, double &high) const;
		virtual double Equation(double x) const = 0;
		virtual void ValidateRange(double &range1, double &range2) const;
		virtual void RotateXY(double &x, double &y) const;
		virtual void TranslateXY(double &x, double &y) const;
};

/////////////////////// TestPointsLine ////////////////////////

class TestPointsLine : public TestPoints
	{
	public:
		TestPointsLine(double slope, double intercept);
	private:
		double Equation(double x) const;

		bool operator == (const TestPoints &rhs) const;

		double m_slope;
		double m_intercept;
	};

/////////////////////// TestPointsCircle ////////////////////////

class TestPointsCircle : public TestPoints
	{
	public:
		TestPointsCircle(double centrex, double centrey, double radius);
	private:
		double Equation(double x) const;
		void TranslateXY(double &x, double &y) const;
		void ValidateRange(double &range1, double &range2) const;

		bool operator == (const TestPoints &rhs) const;

		double m_centrex;
		double m_centrey;
		double m_radius;
		double m_radius2;
	};

/////////////////////// TestPointsEllipse ////////////////////////

class TestPointsEllipse : public TestPoints
	{
	public:
		TestPointsEllipse(double centrex, double centrey, double a, double b, double rotation);
	private:
		double Equation(double x) const;
		void RotateXY(double &x, double &y) const;
		void TranslateXY(double &x, double &y) const;
		void ValidateRange(double &range1, double &range2) const;

		bool operator == (const TestPoints &rhs) const;

		double m_centrex;
		double m_centrey;
		double m_a;
		double m_b;
		double m_rotation;
		double m_a2;
		double m_b2;
		double m_sinr;
		double m_cosr;
	};

/////////////////////// TestPointsFactory ////////////////////////

class TestPointsFactory
	{
	public:
		TestPointsFactory();
		static TestPoints *Create(int type, std::istream &is);
	};
