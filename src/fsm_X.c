/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm.c
 *
 *  Description: This is an extendible and configurable Finit State Machine (FSM)
 *               implementation which is well suited for high-performance embedded
 *               systems. It has a small memory footprint and scales well with
 *               the addition of states. In fact this implementation is O(m), where m
 *               is the number of transitions any given state can have.
 *
 *
 ***************************************************************************************/


/* Standard Headers */
#ifdef FSM_DEBUG
#include <stdio.h>
#endif

/* Module Header */
#include "fsm_X.h"


/**
 * Member function definitions
 */

/* FSM handling functions */

void fsmCreate (X_fsm *machine, X_actions *actions)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: FSM Created\r\n");
    #endif

    /* Initialize the FSM */
    fsm_transition(machine, fsmStart);
    fsm_set_status(machine, FSM_STATUS_INIT);

    /* Set the user-specific state actions */
    fsm_action_cfg(machine, actions, Background);
    fsm_action_cfg(machine, actions, Start);
    fsm_action_cfg(machine, actions, State0);
    fsm_action_cfg(machine, actions, State1);
    fsm_action_cfg(machine, actions, State2);
    fsm_action_cfg(machine, actions, Error);
}

void fsmReset (X_fsm *machine)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: FSM Reset\r\n");
    #endif

    /* Reset the FSM */
    fsm_transition(machine, fsmStart);
    fsm_set_status(machine, FSM_STATUS_INIT);
}


void fsmRunMachine (X_fsm *machine, X_event const *event, X_status *status)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: FSM RunMachine\r\n");
    #endif

    /* Run a state machine cycle */
    fsm_run(machine, event);

    /* Execute background action */
    fsm_action(machine, Background);

    /* Update status */
    fsm_get_status(machine, *status);
}


/* Event generation functions */

void fsmGenerateEvent (X_event *event, X_input *input)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: Event generator input = %d\r\n", *input);
    #endif

    /* Configure the signal based on the input */
    fsm_set_signal(event, input);
}


/* State functions declarations */

void fsmStart(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = Start\r\n");
    #endif

    /* Status update */
    fsm_set_status(machine, FSM_STATUS_START);

    /* State actions */
    fsm_action(machine, Start);

    /* State transitions */
    fsm_transition(machine, fsmState0);
}

void fsmState0(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = State 0\r\n");
    #endif

    /* Status update */
    fsm_set_status(machine, FSM_STATUS_STATE0);

    /* State actions */
    fsm_action(machine, State0);

    /* State transitions */
    switch (event->mSignal)
    {
        case START_SIG:
            fsm_transition(machine, fsmState1);
            break;

        case ERROR_SIG:
            fsm_transition(machine, fsmError);
            fsm_run(machine, event);
            break;
    }
}

void fsmState1(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = State 1\r\n");
    #endif

    /* Status update */
    fsm_set_status(machine, FSM_STATUS_STATE1);

    /* State actions */
    fsm_action(machine, State1);

    /* State transitions */
    switch (event->mSignal)
    {
        case RESET_SIG:
            fsm_transition(machine, fsmStart);
            break;

        case STOP_SIG:
            fsm_transition(machine, fsmState0);
            break;

        case ENABLE_OP_SIG:
            fsm_transition(machine, fsmState2);
            break;

        case ERROR_SIG:
            fsm_transition(machine, fsmError);
            fsm_run(machine, event);
            break;
    }
}

void fsmState2(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = State 2\r\n");
    #endif

    /* Status update */
    fsm_set_status(machine, FSM_STATUS_STATE2);

    /* State actions */
    fsm_action(machine, State2);

    /* State transitions */
    switch (event->mSignal)
    {
        case DISABLE_OP_SIG:
            fsm_transition(machine, fsmState1);
            break;

        case ERROR_SIG:
            fsm_transition(machine, fsmError);
            fsm_run(machine, event);
            break;
    }
}


void fsmError(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = Error\r\n");
    #endif

    /* Status update */
    fsm_set_status(machine, FSM_STATUS_ERROR);

    /* State actions */
    fsm_action(machine, Error);

    /* State transitions */
    switch (event->mSignal)
    {
        case ERROR_OK_SIG:
            fsm_transition(machine, fsmState2);
            break;

        case ERROR_ACK_SIG:
            fsm_transition(machine, fsmState1);
            break;

        case ERROR_RESET_SIG:
            fsm_transition(machine, fsmState0);
            break;
    }
}


/* EOF */
