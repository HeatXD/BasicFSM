/**
MIT License

Copyright (c) 2020 HeatXD

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/ 
#ifndef BASIC_FSM_H
#define BASIC_FSM_H
/** DECLARATION */
typedef struct basic_fsm_s {
  void( * current_state)(struct basic_fsm_s * );
  /** the context of a state machine is a user-provided pointer which can be used to store information about the finite state machine instance. */
  void * ctx;
}
basic_fsm_t;

typedef void( * basic_fsm_func)(basic_fsm_t * );
/** assigns memory for a new fsm. */
basic_fsm_t * basic_fsm_create(void);
/** releases memory used by a fsm. */
void basic_fsm_delete(basic_fsm_t * fsm);
/** returns the current_state of the fsm.*/
basic_fsm_func basic_fsm_get_current_state(const basic_fsm_t * fsm);
/** sets the current state of the fsm. */
void basic_fsm_set_current_state(basic_fsm_t * fsm, basic_fsm_func state);
/** computes a single step (transition) of the fsm. */
void basic_fsm_run(basic_fsm_t * fsm);
/** returns 1 if the fsm is in a valid state, 0 otherwise. */
int basic_fsm_state_is_valid(const basic_fsm_t * fsm);
/** exits the fsm (put it into invalid state so subsequent calls to basic_fsm_run() will do nothing.) */
void basic_fsm_exit(basic_fsm_t * fsm);
/** sets the user context value */
void basic_fsm_set_ctx(basic_fsm_t * fsm, void * ctx);
/** gets the user context value */
void * basic_fsm_get_ctx(const basic_fsm_t * fsm);

#ifdef BASIC_FSM_IMPL_H

#include <stdlib.h>

basic_fsm_t * basic_fsm_create(void) {
  basic_fsm_t * fsm = NULL;
  fsm = (basic_fsm_t * ) calloc(1, sizeof(basic_fsm_t));
  return fsm;
}

void basic_fsm_delete(basic_fsm_t * fsm) {
  free(fsm);
}

void basic_fsm_set_current_state(basic_fsm_t * fsm, basic_fsm_func state) {
  fsm -> current_state = state;
}

basic_fsm_func basic_fsm_get_current_state(const basic_fsm_t * fsm) {
  return fsm -> current_state;
}

void basic_fsm_run(basic_fsm_t * fsm) {
  basic_fsm_func current_state;
  if (basic_fsm_state_is_valid(fsm)) {
    current_state = basic_fsm_get_current_state(fsm);
    current_state(fsm);
  }
}

int basic_fsm_state_is_valid(const basic_fsm_t * fsm) {
  basic_fsm_func current_state;
  current_state = basic_fsm_get_current_state(fsm);
  return current_state != NULL;
}

void basic_fsm_exit(basic_fsm_t * fsm) {
  basic_fsm_set_current_state(fsm, NULL);
}

void basic_fsm_set_ctx(basic_fsm_t * fsm, void * ctx) {
  fsm -> ctx = ctx;
}

void * basic_fsm_get_ctx(const basic_fsm_t * fsm) {
  return fsm -> ctx;
}

#endif /** BASIC_FSM_IMPL_H */

#endif /** BASIC_FSM_H */