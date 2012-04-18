#include <boost/program_options.hpp>
#include <iostream>
#include "TestPoints.h"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("type,t", po::value<int>(), "type of equation (line=0, circle=1, ellipse=2)")
		("count,c", po::value<int>(), "number of points to generate")
		("error,e", po::value<double>(), "max. error to apply to y-value")
		("range1", po::value<double>(), "start limit of x-values")
		("range2", po::value<double>(), "stop limit of x-values")
		("decimals,d", po::value<int>(), "decimal places for output")
		("help,h", "produce this message")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (1 == argc || vm.count("help") || 0 == vm.count("type"))
	{
		std::cout << "Usage: test-points [options]" << std::endl;
		std::cout << desc << std::endl;
		return 1;
	}

	int type = 0;
	if (vm.count("type"))
		type = vm["type"].as<int>();

	int count = 10;
	if (vm.count("count"))
		count = vm["count"].as<int>();

	double error = 1.0;
	if (vm.count("error"))
		error = vm["error"].as<double>();

	double range1 = -50.0;
	if (vm.count("range1"))
		range1 = vm["range1"].as<double>();

	double range2 = 50.0;
	if (vm.count("range2"))
		range2 = vm["range2"].as<double>();

	int precision = 6;
	if (vm.count("decimals"))
		precision = vm["decimals"].as<int>();

	bool setRange = (vm.count("range1") + vm.count("range1")) > 0;
	bool setError = vm.count("error") > 0;

	// TODO: validate range1 and range2 input

	TestPoints *t = TestPointsFactory::Create(type);
	if (t)
		{
		if (setRange)
			t->SetRange(range1, range2);
		if (setError)
			t->SetError(error);

		t->Generate(count, precision);
		delete t;
		return 0;
		}

	return 1;
}
