#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Typewise-alert.hpp"

PASSIVE_COOLING passive_cooling;
HI_ACTIVE_COOLING hiactive_cooling;
MED_ACTIVE_COOLING medactive_cooling;


TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);

}

TEST_CASE( "Classify temperature breach for Passive cooling") {

  REQUIRE(classifyTemperatureBreach(passive_cooling, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(passive_cooling, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(passive_cooling, 35) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(passive_cooling, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(passive_cooling, 12) == NORMAL);

}