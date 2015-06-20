/** *************************************************************************************
 *  Author:         Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:           fsm_template.c
 *
 *  Description:    TODO
 *
 *
 ***************************************************************************************/



/* FSM implementation header */
#include "fsm_template.h"



/**
 *  The standard FSM states - existence is required, implementation is user-specific
 *
 */

void fsm_start (efsm *machine, fsm_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = Start\r\n");
    #endif

    /* Status update */
    FSM_SET_STATUS(machine, FSM_STATUS_START);

    /* State actions */
    FSM_ACTION(machine, start);

    /* State transitions */
    FSM_TRANSITION(machine, fsm_state_0); // SET THIS
}


void fsm_error(efsm *machine, fsm_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = Error\r\n");
    #endif

    /* Status update */
    FSM_SET_STATUS(machine, FSM_STATUS_ERROR);

    /* State transitions */
    switch (FSM_GET_SIGNAL(event))
    {
        case ERROR_OK_SIG:  // SET THIS
            FSM_TRANSITION(machine, fsm_state_0); // SET THIS
            break;

        /* State actions */
        default:
            FSM_ACTION(machine, error);

    }
}



/**
 *  User-specific state definitions
 *
 */

void fsm_state_0 (efsm *machine, fsm_event const *event)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: State = State 0\r\n"); // SET THIS
    #endif

    /* Status update */
    FSM_SET_STATUS(machine, FSM_STATUS_STATE_0); // SET THIS

    /* State transitions */
    switch (FSM_GET_SIGNAL(event))
    {
        case START_SIG:
            FSM_TRANSITION(machine, fsm_start); // SET THIS
            break;

        case ERROR_SIG:
            FSM_TRANSITION(machine, fsm_error); // SET THIS
            FSM_RUN(machine, event);
            break;

        /* State actions */
        default:
            FSM_ACTION(machine, state_action[0]); // SET THIS

    }
}


