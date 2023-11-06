#include <iostream>
#include <cstdlib>
/*
The program will take the argurment when called from the CLI, turn it into number
and convert it into object lengths that are familiar to American (or so I have heard)
*/
enum length // in mm
{
	km = 1000000, // 1km
	m = 1000,	  // 1m
	cm = 10,	  // 1cm
};

std::string length_str(int val)
{
	switch (val)
	{
	case length::km:
		return " American football field end to end"; // https://measuringly.com/how-long-is-1-km/, 11 of them
	case length::m:
		return " M16A4"; // https://en.wikipedia.org/wiki/M16_rifle, M16A4 is 1000mm
	case length::cm:
		return " standard 1/4 US staple"; // https://dimensionofstuff.com/9-things-that-are-about-1-centimeter-cm-long/
	default:
		return "bugged"; // eh
	}
}

int convert(long long int input)
{
	unsigned long int km = 0, m = 0, cm = 0;
	// because the input are in cm
	unsigned long long int number = input * 10;
	if (number <= 0)
	{
		return 0;
	}

	// turn it into km, m and cm. could be better but I don't know better.
	// I tried to devide it but it's bugged and I'm sleepy
	while (number > 0)
	{
		if (number >= length::km)
		{
			km++;
			number -= length::km;
		}
		if (number >= length::m)
		{
			m++;
			number -= length::m;
		}
		if (number >= length::cm)
		{
			cm++;
			number -= length::cm;
		}
	}
	// print the result
	std::cout << input << " cm is about ";
	if (km > 0)
	{
		std::cout << km * 11 << length_str(length::km);
		if (m > 0)
			std::cout << ", ";
	}
	if (m > 0)
	{
		std::cout << m << length_str(length::m);
		if (cm > 0)
			std::cout << " and ";
	}
	if (cm > 0)
	{
		std::cout << cm << length_str(length::cm);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		// multiple arguments in one call
		for (int i = 1; i < argc; i++)
		{
			convert(strtoull(argv[i], nullptr, 0));
			std::cout << "\n";
		}
	}
	else if (argc < 2)
	{
		// one argument, input required
		std::cout << "Input the number (in cm): ";
		long long int number;
		std::cin >> number;
		convert(number);
	}
	else
		convert(atoll(argv[1]));
	return 0;
}