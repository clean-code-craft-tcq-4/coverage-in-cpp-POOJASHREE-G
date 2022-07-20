#include "Typewise-alert.hpp"
#include <iostream>

static const char *BreachType_str[] = { "NORMAL", "TOO_LOW", "TOO_HIGH"};
const char* recepient = "a.b@c.com";
static bool IsAlertSent2cntrlr = false;
static bool IsAlertSent2mail = false;


bool IsAlertSenttoCntrlr()
{
  return IsAlertSent2cntrlr;
}

bool IsAlertSenttoEmail()
{
  return IsAlertSent2mail;
}

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
  IsAlertSent2cntrlr = true;
}


void sendToEmail(BreachType breachType) {

  if(breachType != NORMAL) {

    printf("To: %s\n", recepient);
    printf("Hi, the temperature is %s\n", BreachType_str[breachType]);
    IsAlertSent2mail = true;

  }
  else{
    IsAlertSent2mail = false;
  }
}