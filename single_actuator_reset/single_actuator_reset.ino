#define ACTUATORS_COUNT 4
#define ACTUATORS_CONTROL_PINS_COUNT 2

int COMMON_DELAY = 1500;
int ACTUATOR_RESET_TIME = 50000;

enum Actuators {
  BATTERY_SWAPER_ACTUATOR_RIGHT,
  BATTERY_SWAPER_ACTUATOR_LEFT,
  DRONE_MOVER_ACTUATOR_LONG,
  DRONE_MOVER_ACTUATOR_WIDTH
};

enum Driver_direction_control_pin {
  IN1,
  IN2,
};

int uno_dgt_pins[ACTUATORS_COUNT][ACTUATORS_CONTROL_PINS_COUNT]{
  { 13, 12 },
  { 11, 10 },
  { 7, 6 },
  { 5, 4 },
};

void initilization() {
  for (int i; i < ACTUATORS_COUNT; i++) {
    for (int j; j < ACTUATORS_CONTROL_PINS_COUNT; j++) {
      pinMode(uno_dgt_pins[i][j], OUTPUT);
    }
  }
}

void setup() {
  initilization();
}

void actuator_stop(Actuators actuator) {
  digitalWrite(uno_dgt_pins[actuator][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator][IN2], LOW);
}

void actuator_pull(Actuators actuator, int time) {
  digitalWrite(uno_dgt_pins[actuator][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator][IN2], HIGH);
  delay(time);

  actuator_stop(actuator);
}

void loop() {
  actuator_pull(BATTERY_SWAPER_ACTUATOR_LEFT, ACTUATOR_RESET_TIME);
}
