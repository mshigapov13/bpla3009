#define ACTUATORS_COUNT 4
#define ACTUATORS_CONTROL_PINS_COUNT 2

int COMMON_DELAY = 1500;
int BATTERY_PUSH_TIME = 10500;
int DRONE_MOVE_TIME = 7000;

enum Actuators {
  BATTERY_SWAPER_ACTUATOR_RIGHT,
  BATTERY_SWAPER_ACTUATOR_LEFT,
  DRONE_MOVER_ACTUATOR_LONG,
  DRONE_MOVER_ACTUATOR_WIDTH
};

enum Driver_direction_control_pins {
  IN1,
  IN2
};

int uno_dgt_pins[ACTUATORS_COUNT][ACTUATORS_CONTROL_PINS_COUNT]{
  { 13, 12 },
  { 11, 10 },
  { 7, 6 },
  { 5, 4 }
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

// void actuator_work(Actuators actuator_number, int work_time) {
//   digitalWrite(uno_dgt_pins[actuator_number][IN1], HIGH);
//   digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
//   delay(BATTRY_PUSH_TIME);

//   delay(COMMON_DELAY);

//   digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
//   digitalWrite(uno_dgt_pins[actuator_number][IN2], HIGH);
//   delay(BATTRY_PUSH_TIME);

//   digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
//   digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
// }

void actuator_stop(Actuators actuator_number) {
  digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
}

void actuator_push(Actuators actuator_number, int time) {
  digitalWrite(uno_dgt_pins[actuator_number][IN1], HIGH);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], LOW);
  delay(time);

  actuator_stop(actuator_number);
}

void actuator_pull(Actuators actuator_number, int time) {
  digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], HIGH);
  delay(time);

  actuator_stop(actuator_number);
}

void move_drone_to_station() {
  actuator_push(DRONE_MOVER_ACTUATOR_LONG, DRONE_MOVE_TIME);

  actuator_push(DRONE_MOVER_ACTUATOR_WIDTH, DRONE_MOVE_TIME);
}

void reset_actuator(Actuators actuator_number, int time) {
  digitalWrite(uno_dgt_pins[actuator_number][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator_number][IN2], HIGH);
  delay(time);

  actuator_stop(actuator_number);
}

void all_actuators_reset(int iteration) {
  reset_actuator(DRONE_MOVER_ACTUATOR_LONG, DRONE_MOVE_TIME);
  reset_actuator(DRONE_MOVER_ACTUATOR_WIDTH, DRONE_MOVE_TIME);
  if (iteration % 2 == 0) {
    reset_actuator(BATTERY_SWAPER_ACTUATOR_RIGHT, BATTERY_PUSH_TIME);
  } else {
    reset_actuator(BATTERY_SWAPER_ACTUATOR_LEFT, BATTERY_PUSH_TIME);
  }
}

void swap_battery(int iteration) {
  if (iteration % 2 == 0) {
    actuator_push(BATTERY_SWAPER_ACTUATOR_RIGHT, BATTERY_PUSH_TIME);
  } else {
    actuator_push(BATTERY_SWAPER_ACTUATOR_LEFT, BATTERY_PUSH_TIME);
  }
}

void loop() {
  for (int i;;) {
    move_drone_to_station();
    delay(COMMON_DELAY);

    swap_battery(i);
    delay(COMMON_DELAY);

    all_actuators_reset(i);
    delay(COMMON_DELAY);

    i = (i + 1) % 2;
  }
}
