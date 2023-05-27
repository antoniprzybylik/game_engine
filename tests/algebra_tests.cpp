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

		v -= d;

		CHECK(float_cmp(v.get_x(), 3.1));
		CHECK(float_cmp(v.get_y(), 7.81));

		v *= 3;

		CHECK(float_cmp(v.get_x(), 9.3));
		CHECK(float_cmp(v.get_y(), 23.43));
	}
}

TEST_CASE("point")
{
	SECTION("Default constructor")
	{
		Point p;

		CHECK(!p.is_dir());
		CHECK(float_cmp(p.get_x(), 0.0));
		CHECK(float_cmp(p.get_y(), 0.0));
	}

	SECTION("X, Y constructor")
	{
		Point p(3.1, 7.81);

		CHECK(!p.is_dir());
		CHECK(float_cmp(p.get_x(), 3.1));
		CHECK(float_cmp(p.get_y(), 7.81));
	}
}

TEST_CASE("rect")
{
	SECTION("Set dimensions 1")
	{
		Rect r(1.12, 3.8, 2.22, 3.889);

		CHECK(float_cmp(r.get_pos_x(), 1.12));
		CHECK(float_cmp(r.get_pos_y(), 3.8));
		CHECK(float_cmp(r.get_dim_x(), 2.22));
		CHECK(float_cmp(r.get_dim_y(), 3.889));
	}

	SECTION("Set dimensions 2")
	{
		Rect r(Point(1.12, 3.8),
		       Vector(2.22, 3.889));

		CHECK(float_cmp(r.get_pos_x(), 1.12));
		CHECK(float_cmp(r.get_pos_y(), 3.8));
		CHECK(float_cmp(r.get_dim_x(), 2.22));
		CHECK(float_cmp(r.get_dim_y(), 3.889));
	}
}
