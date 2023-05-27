#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "engine.h"

TEST_CASE("engine")
{
	Engine e([](void){}, 0);

	CHECK_THROWS(e.exec());
}
