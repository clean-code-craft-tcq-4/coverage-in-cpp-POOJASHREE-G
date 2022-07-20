#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Typewise-alert.hpp"

PASSIVE_COOLING passive_cooling;
HI_ACTIVE_COOLING hiactive_cooling;
MED_ACTIVE_COOLING medactive_cooling;
BatteryCharacter<PASSIVE_COOLING> batteryChar_passive;
BatteryCharacter<HI_ACTIVE_COOLING> batteryChar_hiactive;
BatteryCharacter<MED_ACTIVE_COOLING> batteryChar_medactive;

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

TEST_CASE( "Classify temperature breach for high active cooling") {

  REQUIRE(classifyTemperatureBreach(hiactive_cooling, -3) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(hiactive_cooling, 46) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(hiactive_cooling, 45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(hiactive_cooling, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(hiactive_cooling, 26) == NORMAL);

}

TEST_CASE( "Classify temperature breach for Medium active cooling") {

  REQUIRE(classifyTemperatureBreach(medactive_cooling, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(medactive_cooling, 45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(medactive_cooling, 40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(medactive_cooling, 0) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(medactive_cooling, 8) == NORMAL);

}

TEST_CASE( "Check and alert status to controller") {

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_passive, 12) == SENT );

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_hiactive, 26) == SENT );

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar_medactive, 8) == SENT );

}

TEST_CASE( "Check and alert status to email") {

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_passive, 12) == SENT );

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_hiactive, 26) == SENT );

  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar_medactive, 8) == SENT );
}

TEST_CASE( "Check and alert status to email Failure") {

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_passive, 12) == NOT_SENT );

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_hiactive, 26) == NOT_SENT );

  REQUIRE(checkAndAlert(TO_UNKNOWN, batteryChar_medactive, 8) == NOT_SENT );
}