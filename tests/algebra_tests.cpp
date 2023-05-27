#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "algebra.h"

TEST_CASE("vector")
{
	SECTION("Default constructor")
	{
		Vector v;

		CHECK(v.is_dir());
		CHECK(v.get_x() == 0);
		CHECK(v.get_y() == 0);
	}

	SECTION("Default point")
	{
		Vector v(false);

		CHECK(!v.is_dir());
		CHECK(v.get_x() == 0);
		CHECK(v.get_y() == 0);
	}

	SECTION("X, Y constructor")
	{
		Vector v(3.1, 7.81);

		CHECK(v.is_dir());
		CHECK(v.get_x() == 3.1);
		CHECK(v.get_y() == 7.81);
	}

	SECTION("X, Y constructor (point)")
	{
		Vector v(3.1, 7.81, false);

		CHECK(!v.is_dir());
		CHECK(v.get_x() == 3.1);
		CHECK(v.get_y() == 7.81);
	}
}
