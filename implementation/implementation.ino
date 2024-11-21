#define ACTUATORS_COUNT 4
#define ACTUATORS_CONTROL_PINS_COUNT 2

int COMMON_DELAY = 1500;
int HEALTH_CHECK_TIME = 1500;

int BATTERY_PUSH_TIME = 10500;
int MAX_ACTUATOR_WORK_TIME = 7000;
int VERY_BIG_ACTUATORS_WORK_TIME = 25000;

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

void actuator_stop(Actuators actuator) {
  digitalWrite(uno_dgt_pins[actuator][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator][IN2], LOW);
}

void all_actuators_stop() {
  actuator_stop(BATTERY_SWAPER_ACTUATOR_RIGHT);
  actuator_stop(BATTERY_SWAPER_ACTUATOR_LEFT);
  actuator_stop(DRONE_MOVER_ACTUATOR_LONG);
  actuator_stop(DRONE_MOVER_ACTUATOR_WIDTH);
}

void actuator_push(Actuators actuator) {
  digitalWrite(uno_dgt_pins[actuator][IN1], HIGH);
  digitalWrite(uno_dgt_pins[actuator][IN2], LOW);
}

void actuator_push_and_stop(Actuators actuator, int time) {
  actuator_push(actuator);
  delay(time);

  actuator_stop(actuator);
}

void actuator_pull(Actuators actuator) {
  digitalWrite(uno_dgt_pins[actuator][IN1], LOW);
  digitalWrite(uno_dgt_pins[actuator][IN2], HIGH);
}

void move_drone_to_station() {
  actuator_push_and_stop(DRONE_MOVER_ACTUATOR_LONG, MAX_ACTUATOR_WORK_TIME);
  actuator_push_and_stop(DRONE_MOVER_ACTUATOR_WIDTH, MAX_ACTUATOR_WORK_TIME);
}

void all_actuators_pull(int iteration) {
  actuator_pull(DRONE_MOVER_ACTUATOR_LONG);
  actuator_pull(DRONE_MOVER_ACTUATOR_WIDTH);
  if (iteration % 2 == 0) {
    actuator_pull(BATTERY_SWAPER_ACTUATOR_RIGHT);
  } else {
    actuator_pull(BATTERY_SWAPER_ACTUATOR_LEFT);
  }
}

void swap_battery(int iteration) {
  if (iteration % 2 == 0) {
    actuator_push_and_stop(BATTERY_SWAPER_ACTUATOR_RIGHT, BATTERY_PUSH_TIME);
  } else {
    actuator_push_and_stop(BATTERY_SWAPER_ACTUATOR_LEFT, BATTERY_PUSH_TIME);
  }
}

void loop() {
  healthcheck();

  for (int i;;) {
    delay(COMMON_DELAY);
    move_drone_to_station();
    delay(COMMON_DELAY);

    swap_battery(i);
    delay(COMMON_DELAY);

    all_actuators_pull(i);
    delay(VERY_BIG_ACTUATORS_WORK_TIME);
    all_actuators_stop();

    i = (i + 1) % 2;
  }
}

void healthcheck() {
  actuator_push(BATTERY_SWAPER_ACTUATOR_RIGHT);
  actuator_push(BATTERY_SWAPER_ACTUATOR_LEFT);
  actuator_push(DRONE_MOVER_ACTUATOR_LONG);
  actuator_push(DRONE_MOVER_ACTUATOR_WIDTH);
  delay(HEALTH_CHECK_TIME);
  all_actuators_stop();

  actuator_pull(BATTERY_SWAPER_ACTUATOR_RIGHT);
  actuator_pull(BATTERY_SWAPER_ACTUATOR_LEFT);
  actuator_pull(DRONE_MOVER_ACTUATOR_LONG);
  actuator_pull(DRONE_MOVER_ACTUATOR_WIDTH);
  delay(HEALTH_CHECK_TIME);
  all_actuators_stop();
}
