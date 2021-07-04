#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tourist.hpp"
#include "city.hpp"

enum Errors
{
	FILE_NOT_FOUND,
	EMPTY_FILE,
	ZERO_YEARS
};

// 0 - normal mode
// 1 - test mode
#define MODE 1

void generate_city_and_tourists(const std::string &filename, City &city, std::vector<Tourist *> &tourists)
{
	std::ifstream f(filename);
	if (f.fail())
	{
		throw Errors::FILE_NOT_FOUND;
	}

	int n, k, j;
	f >> n;
	city.setStatus(n);
	f >> k;
	city.setNumberOfYears(k);

	if (f.eof()) //If the file is empty, the program stops here
		throw Errors::EMPTY_FILE;
	else if (k == 0)
		throw Errors::ZERO_YEARS;

#if MODE == 0
	std::cout << "Content of the file: \n"
						<< n << "\n"
						<< k << "\n";
#endif
	tourists.resize(k * 3);
	Tourist *t;
	for (int i = 0; i < city.getNumberOfYears(); i++)
	{
		f >> j;
		t = new Japanese(j);
		tourists.at(i * 3) = t;
		f >> k;
		t = new Modern(k);
		tourists.at(i * 3 + 1) = t;
		f >> n;
		t = new Others(n);
		tourists.at(i * 3 + 2) = t;
#if MODE == 0
		std::cout << j << " " << k << " " << n << "\n";
#endif
	}
}

void delete_all(City &city, std::vector<Tourist *> &tourists)
{
	city.destroy();
	for (int i = 0; i < tourists.size(); i++)
	{
		delete tourists.at(i);
	}
	tourists.resize(0);
}

void simulate_and_print(const std::string &filename, City &city, std::vector<Tourist *> &tourists)
{
	std::ofstream f;
	f.open("output files/" + filename);
#if MODE == 0
	std::cout << "Starting the simulation..\n";
#endif
	for (int i = 0; i < city.getNumberOfYears(); i++)
	{
		int k = 3 * i;
		tourists.at(k)->checkCity(&city);
		tourists.at(k + 1)->checkCity(&city);
		tourists.at(k + 2)->checkCity(&city);

		city.hosts(tourists.at(k));
		city.hosts(tourists.at(k + 1));
		city.hosts(tourists.at(k + 2));

		//Write to file
		f << "------------------------------------------------------------\n";
		f << "Year " << i + 1 << ":\n"
			<< "Japanese:\n"
			<< "planned: " << tourists.at(k)->getPlanned() << ", actual: " << tourists.at(k)->getComing() << "\n..............................\n"
			<< "Modern:\n"
			<< "planned: " << tourists.at(k + 1)->getPlanned() << ", actual: " << tourists.at(k + 1)->getComing() << "\n..............................\n"
			<< "Others:\n"
			<< "planned: " << tourists.at(k + 2)->getPlanned() << ", actual: " << tourists.at(k + 2)->getComing() << "\n..............................\n";
		f << "The annual income of the city: " << city.getIncome() << " million HUF\n"
			<< "Status of the city, before the repairs: " << city.getStatus() << " which is " << city.getStatusWord() << "\n";
		f << "------------------------------------------------------------\n";
		city.repair();
	}
	f << "After the last year, the status of the city: " << city.getStatus() << " which is " << city.getStatusWord() << "\n";

	f.close();
}

#if (MODE == 0)

int main(int argc, char const *argv[])
{
	std::string filename;
	std::cout << "The input files should be in the \"input files\" folder.\n";
	std::cout << "Enter the input file name, please: ";
	std::cin >> filename;

	std::vector<Tourist *> tourists;
	City *city = City::getInstance();
	try
	{
		generate_city_and_tourists("input files/" + filename, *city, tourists);

		simulate_and_print(filename, *city, tourists);
		delete_all(*city, tourists);
	}
	catch (Errors &e)
	{
		if (e == Errors::FILE_NOT_FOUND)
			std::cerr << "File could not be found.\n";
		else if (e == Errors::EMPTY_FILE)
			std::cerr << "The file was empty.\n";
		else if (e == Errors::ZERO_YEARS)
			std::cerr << "The number of years is zero.\n";
	}

	std::cout << "\nCompleted.\n";

	return 0;
}

#elif (MODE == 1)
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Error handling", "t00.txt,t01.txt")
{
	std::vector<Tourist *> tourists;
	City *city = City::getInstance();
	SECTION("Not existing")
	{
		REQUIRE_THROWS_AS(generate_city_and_tourists("nothing.txt", *city, tourists), Errors);
	}

	SECTION("Empty file", "t00.txt")
	{
		REQUIRE_THROWS_AS(generate_city_and_tourists("input files/t00.txt", *city, tourists), Errors);
	}

	SECTION("Zero years", "t01.txt")
	{
		REQUIRE_THROWS_AS(generate_city_and_tourists("input files/t01.txt", *city, tourists), Errors);
	}
	delete_all(*city, tourists);
}

TEST_CASE("Bigger file", "t02.txt")
{
	std::vector<Tourist *> tourists;
	City *city = City::getInstance();
	generate_city_and_tourists("input files/t02.txt", *city, tourists);

	CHECK(tourists.size() == 120);

	delete_all(*city, tourists);
}

TEST_CASE("Only one type of tourist", "t03-t05.txt")
{
	std::vector<Tourist *> tourists;
	City *city = City::getInstance();
	SECTION("Only Japanese", "t03.txt")
	{
		generate_city_and_tourists("input files/t03.txt", *city, tourists);
		for (int i = 0; i < (tourists.size() / 3); ++i)
		{
			int k = 3 * i;
			CHECK((tourists.at(k)->isJapanese() == true && tourists.at(k)->getPlanned() != 0));
			CHECK((tourists.at(k + 1)->isJapanese() == false && tourists.at(k + 1)->getPlanned() == 0));
			CHECK((tourists.at(k + 2)->isJapanese() == false && tourists.at(k + 2)->getPlanned() == 0));
		}
	}
	SECTION("Only Modern", "t04.txt")
	{
		generate_city_and_tourists("input files/t04.txt", *city, tourists);
		for (int i = 0; i < (tourists.size() / 3); ++i)
		{
			int k = 3 * i;
			CHECK((tourists.at(k)->isModern() == false && tourists.at(k)->getPlanned() == 0));
			CHECK((tourists.at(k + 1)->isModern() == true && tourists.at(k + 1)->getPlanned() != 0));
			CHECK((tourists.at(k + 2)->isModern() == false && tourists.at(k + 2)->getPlanned() == 0));
		}
	}
	SECTION("Only Others", "t05.txt")
	{
		generate_city_and_tourists("input files/t05.txt", *city, tourists);
		for (int i = 0; i < (tourists.size() / 3); ++i)
		{
			int k = 3 * i;
			CHECK((tourists.at(k)->isOthers() == false && tourists.at(k)->getPlanned() == 0));
			CHECK((tourists.at(k + 1)->isOthers() == false && tourists.at(k + 1)->getPlanned() == 0));
			CHECK((tourists.at(k + 2)->isOthers() == true && tourists.at(k + 2)->getPlanned() != 0));
		}
	}

	delete_all(*city, tourists);
}

TEST_CASE("Function tests", "t06.txt")
{
	std::vector<Tourist *> tourists;
	City *city = City::getInstance();
	generate_city_and_tourists("input files/t06.txt", *city, tourists);

	SECTION("Initial values")
	{
		CHECK(city->getIncome() == 0);
		CHECK(city->getStatus() == 100);
		CHECK(city->getStatusWord() == "good");

		CHECK(tourists.at(0)->getPlanned() == 10000);
		CHECK(tourists.at(1)->getPlanned() == 10000);
		CHECK(tourists.at(2)->getPlanned() == 10000);
	}

	tourists.at(0)->checkCity(city);
	tourists.at(1)->checkCity(city);
	tourists.at(2)->checkCity(city);

	SECTION("Tourists checked the city")
	{
		CHECK(tourists.at(0)->getComing() == 12000);
		CHECK(tourists.at(1)->getComing() == 13000);
		CHECK(tourists.at(2)->getComing() == 10000);

		//Amount of damage they will do:
		CHECK(tourists.at(0)->damage() == 0);
		CHECK(tourists.at(1)->damage() == 130);
		CHECK(tourists.at(2)->damage() == 200);
	}

	city->hosts(tourists.at(0));
	city->hosts(tourists.at(1));
	city->hosts(tourists.at(2));

	SECTION("City hosted the tourists")
	{
		CHECK(city->getStatus() == 1);
		CHECK(city->getIncome() == 3500);
	}

	city->repair();
	//The city was able to fully repair
	CHECK(city->getStatus() == 100);

	//Controlled test, city can't fully repair
	Tourist *t = new Japanese(11000);
	SECTION("Controlled test", "city can't fully repair")
	{
		city->setStatus(50);
		t->checkCity(city);
		city->hosts(t);
		CHECK(city->getIncome() == 1100);
		city->repair();
		CHECK(city->getIncome() == 0);
		CHECK(city->getStatus() == 55);
	}

	SECTION("Controlled test", "City always good")
	{
		city->setStatus(100);
		t->checkCity(city);
		city->hosts(t);
		CHECK(city->getStatus() == 100);
		city->repair();
		CHECK(city->getStatus() == 100);
		city->hosts(t);
		CHECK(city->getStatus() == 100);
		city->repair();
		CHECK(city->getStatus() == 100);
	}
	delete t;
	t = new Others(10000);
	SECTION("Controlled test", "City always poor")
	{
		city->setStatus(1);
		t->checkCity(city);
		city->hosts(t);
		CHECK(city->getStatus() == 1);
		city->repair();
		CHECK(city->getStatus() == 1);
		city->hosts(t);
		CHECK(city->getStatus() == 1);
		city->repair();
		CHECK(city->getStatus() == 1);
	}
	delete t;
	t = nullptr;
	delete_all(*city, tourists);
}

TEST_CASE("File output", "t02-t06.txt")
{
	std::ifstream f;

	std::vector<Tourist *> tourists;
	City *city = City::getInstance();

	generate_city_and_tourists("input files/t02.txt", *city, tourists);
	simulate_and_print("t02.txt", *city, tourists);
	f.open("output files/t02.txt");
	CHECK(f.good());
	f.close();

	generate_city_and_tourists("input files/t03.txt", *city, tourists);
	simulate_and_print("t03.txt", *city, tourists);
	f.open("output files/t03.txt");
	CHECK(f.good());
	f.close();

	generate_city_and_tourists("input files/t04.txt", *city, tourists);
	simulate_and_print("t04.txt", *city, tourists);
	f.open("output files/t04.txt");
	CHECK(f.good());
	f.close();

	generate_city_and_tourists("input files/t05.txt", *city, tourists);
	simulate_and_print("t05.txt", *city, tourists);
	f.open("output files/t05.txt");
	CHECK(f.good());
	f.close();

	generate_city_and_tourists("input files/t06.txt", *city, tourists);
	simulate_and_print("t06.txt", *city, tourists);
	f.open("output files/t06.txt");
	CHECK(f.good());
	f.close();

	delete_all(*city, tourists);
}

#endif