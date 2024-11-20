#define ACTUATORS_COUNT 4
#define ACTUATORS_CONTROL_PINS_COUNT 2

int COMMON_DELAY = 1500;
int ACTUATOR_FULL_PUSH_TIME = 50000;

enum Actuator
{
  BATTERY_SWAPER_ACTUATOR_RIGHT,
  BATTERY_SWAPER_ACTUATOR_LEFT
};

enum Driver_direction_control_pin
{
  IN1,
  IN2,
};

int uno_dgt_pins[ACTUATORS_COUNT][ACTUATORS_CONTROL_PINS_COUNT]{
    {13, 12},
    {11, 10},
    {7, 6},
    {5, 4},
};

void initilization()
{
  for (int i = 0; i < ACTUATORS_COUNT; i++)
  {
    for (int j = 0; j < ACTUATORS_CONTROL_PINS_COUNT; j++)
    {
      pinMode(uno_dgt_pins[i][j], OUTPUT);
    }
  }
}

void setup()
{
  initilization();
}

void actuator_full_push(Actuator actuator)
{
  digitalWrite(uno_dgt_pins[actuator][IN1], HIGH);
  digitalWrite(uno_dgt_pins[actuator][IN2], LOW);

  delay(ACTUATOR_FULL_PUSH_TIME);
}

void loop()
{
  actuator_full_push(BATTERY_SWAPER_ACTUATOR_LEFT);
}
