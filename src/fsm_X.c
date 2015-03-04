/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_X.c
 *
 *  Description: TODO
 *
 *
 ***************************************************************************************/


/* Standard Headers */
#ifdef FSM_FPM_DEBUG
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
    #ifdef FSM_X_DEBUG
    printf("[FSM]: FSM Created\r\n");
    #endif

    /* Initialize the FSM */
    machine->mState = fsmStart;
    machine->mStatus = -1;

    /* Set the user-specific state actions */
    machine->mActions.Start = actions->Start;
    machine->mActions.State0 = actions->State0;
    machine->mActions.State1 = actions->State1;
    machine->mActions.State2 = actions->State2;
    machine->mActions.Error = actions->Error;
}

void fsmReset (X_fsm *machine)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: FSM Reset\r\n");
    #endif

    /* Reset the FSM */
    machine->mState = fsmStart;
    machine->mStatus = -1;
}


void fsmRunMachine (X_fsm *machine, X_event const *event, STATUS_TYPE *status)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: FSM RunMachine\r\n");
    #endif

    /* Run the state machine */
    (*machine->mState)(machine, event);

    /* Update status */
    *status = machine->mStatus;
}


/* Event generation functions */

void fsmGenerateEvent (X_event *event, INPUT_TYPE *input)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: Event generator input = %d\r\n", *input);
    #endif

    /* Configure the signal based on the input */
    event->mSignal = (event_signal)(*input);
}


/* State functions declarations */

void fsmStart(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: State = Start\r\n");
    #endif

    /* Status update */
    machine->mStatus = 0;

    /* State actions */
    (*machine->mActions.Start)();

    /* State transitions */
    machine->mState = fsmState0;
}

void fsmState0(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: State = State 0\r\n");
    #endif

    /* Status update */
    machine->mStatus = 1;

    /* State actions */
    (*machine->mActions.State0)();

    /* State transitions */
    machine->mState = fsmState1;
}

void fsmState1(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: State = State 1\r\n");
    #endif

    /* Status update */
    machine->mStatus = 2;

    /* State actions */
    (*machine->mActions.State1)();

    /* State transitions */
    switch (event->mSignal)
    {
        case RESET_SIG:
            machine->mState = fsmState0;
            break;

        case ENABLE_OP_SIG:
            machine->mState = fsmState2;
            break;

        case ERROR_SIG:
            (machine->mState = fsmError);
            (*machine->mState)(machine, event);
            break;
    }
}

void fsmState2(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: State = State 2\r\n");
    #endif

    /* Status update */
    machine->mStatus = 3;

    /* State actions */
    (*machine->mActions.State2)();

    /* State transitions */
    switch (event->mSignal)
    {
        case DISABLE_OP_SIG:
            machine->mState = fsmState1;
            break;

        case ERROR_SIG:
            (machine->mState = fsmError);
            (*machine->mState)(machine, event);
            break;
    }
}


void fsmError(X_fsm *machine, X_event const *event)
{
    #ifdef FSM_X_DEBUG
    printf("[FSM]: State = Error\r\n");
    #endif

    /* Status update */
    machine->mStatus = -2;

    /* State actions */
    (*machine->mActions.Error)();

    /* State transitions */
    switch (event->mSignal)
    {
        case ERROR_ACK_SIG:
            machine->mState = fsmState0;
            break;
    }
}


/* EOF */
