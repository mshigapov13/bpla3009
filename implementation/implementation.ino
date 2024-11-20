#define ACTUATORS_COUNT 4
#define ACTUATORS_CONTROL_PINS_COUNT 2

int COMMON_DELAY = 1500;
int BATTRY_PUSH_TIME = 10500;

enum Actuators { BATTERY_SWAPER_ACTUATOR_RIGHT,
                 BATTERY_SWAPER_ACTUATOR_LEFT };

enum Driver_direction_control_pins {
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
  for (int i = 0; i < ACTUATORS_COUNT; i++) {
    for (int j = 0; j < ACTUATORS_CONTROL_PINS_COUNT; j++) {
      pinMode(uno_dgt_pins[i][j], OUTPUT);
    }
  }
}

void setup() {
  initilization();
}

void battery_swap_move(int actuator_number) {
  digitalWrite(uno_dgt_pins[actuator_number][IN1], HIGH);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
  delay(BATTRY_PUSH_TIME);

  delay(COMMON_DELAY);

  digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], HIGH);
  delay(BATTRY_PUSH_TIME);

  digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
}

void loop() {
  battery_swap_move(BATTERY_SWAPER_ACTUATOR_RIGHT);
  delay(COMMON_DELAY);

  battery_swap_move(BATTERY_SWAPER_ACTUATOR_LEFT);
  delay(COMMON_DELAY);
}
