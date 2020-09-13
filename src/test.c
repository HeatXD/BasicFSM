#define BASIC_FSM_IMPL_H
#include <stdio.h>
#include "basicFSM.h"

// basic fsm example traffic light
void red_light(basic_fsm_t * fsm);
void orange_light(basic_fsm_t * fsm);
void green_light(basic_fsm_t * fsm);

int main(void) {
  basic_fsm_t * fsm;
  fsm = basic_fsm_create();
  basic_fsm_set_current_state(fsm, red_light);

  int timer = 0;

  while (basic_fsm_state_is_valid(fsm)) {
    basic_fsm_set_ctx(fsm, &timer);
    basic_fsm_run(fsm);
    timer++;

    if (timer > 1000) {
      basic_fsm_exit(fsm);
    }
  }
  basic_fsm_delete(fsm);
  return 0;
}

void red_light(basic_fsm_t * fsm) {
  int *ctx = basic_fsm_get_ctx(fsm);
  int t = *ctx;

  if (t % 50 == 0) {
    printf("RED\n");
  }

  if (t % 200 == 0) {
    printf("Switching to GREEN!\n");
    basic_fsm_set_current_state(fsm, green_light);
  }
}

void orange_light(basic_fsm_t * fsm) {
  int *ctx = basic_fsm_get_ctx(fsm);
  int t = *ctx;

  if (t % 50 == 0) {
    printf("ORANGE\n");
  }

  if (t % 200 == 0) {
    printf("Switching to RED!\n");
    basic_fsm_set_current_state(fsm, red_light);
  }
}

void green_light(basic_fsm_t * fsm) {
  int *ctx = basic_fsm_get_ctx(fsm);
  int t = *ctx;

  if (t % 50 == 0) {
    printf("GREEN\n");
  }

  if (t % 200 == 0) {
    printf("Switching to ORANGE!\n");
    basic_fsm_set_current_state(fsm, orange_light);
  }
}