#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "algebra.h"
#include "float_utils.h"

TEST_CASE("vector")
{
	SECTION("Default constructor")
	{
		Vector v;

		CHECK(v.is_dir());
		CHECK(float_cmp(v.get_x(), 0.0));
		CHECK(float_cmp(v.get_y(), 0.0));
	}

	SECTION("Default point")
	{
		Vector v(false);

		CHECK(!v.is_dir());
		CHECK(float_cmp(v.get_x(), 0.0));
		CHECK(float_cmp(v.get_y(), 0.0));
	}

	SECTION("X, Y constructor")
	{
		Vector v(3.1, 7.81);

		CHECK(v.is_dir());
		CHECK(float_cmp(v.get_x(), 3.1));
		CHECK(float_cmp(v.get_y(), 7.81));
	}

	SECTION("X, Y constructor (point)")
	{
		Vector v(3.1, 7.81, false);

		CHECK(!v.is_dir());
		CHECK(float_cmp(v.get_x(), 3.1));
		CHECK(float_cmp(v.get_y(), 7.81));
	}

	SECTION("Vector arithmetics")
	{
		Vector v(3.1, 7.81, false);
		Vector d(1.1, 8.3, true);

		v += d;

		CHECK(float_cmp(v.get_x(), 4.2));
		CHECK(float_cmp(v.get_y(), 16.11));
	}
}
