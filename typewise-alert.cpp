#include "Typewise-alert.hpp"
#include <iostream>

static const char *BreachType_str[] = { "NORMAL", "TOO_LOW", "TOO_HIGH"};
const char* recepient = "a.b@c.com";

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value <= lowerLimit) {
    return TOO_LOW;
  }
  if(value >= upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}


void sendToEmail(BreachType breachType) {

  if(breachType != NORMAL) {

    printf("To: %s\n", recepient);
    printf("Hi, the temperature is %s\n", BreachType_str[breachType]);
    
    }

}