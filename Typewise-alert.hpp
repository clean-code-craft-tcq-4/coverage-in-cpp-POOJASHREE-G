#ifndef TYPEWISE_ALERT_HPP
#define TYPEWISE_ALERT_HPP

class PASSIVE_COOLING
{
  public:
  const int Lower_Limit = 0;
  const int Upper_Limit = 35;
};

class HI_ACTIVE_COOLING
{
  public:
  const int Lower_Limit = 0;
  const int Upper_Limit = 45;
};

class MED_ACTIVE_COOLING
{
  public:
  const int Lower_Limit = 0;
  const int Upper_Limit = 40;
};


typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;


typedef enum {
  SENT,
  NOT_SENT
} AlertStatus;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_UNKNOWN
} AlertTarget;


template <class CoolingType>
struct BatteryCharacter {
  CoolingType coolingType;
  char brand[48];
};

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

template <class CoolingType>
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {

  return inferBreach(temperatureInC, coolingType.Lower_Limit, coolingType.Upper_Limit);

}

template <typename CoolingType>
AlertStatus checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter<CoolingType> batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      return SENT;
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      return SENT;
      break;
    default:
      return NOT_SENT;
      break;
  }
}

#endif