/** *************************************************************************************
 *  Author:         Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:           fsm_base.c
 *
 *  Description:    TODO
 *
 *
 ***************************************************************************************/



#include "fsm_base.h"



/**
 * [fsm_start description]
 *
 * @param machine [description]
 * @param event   [description]
 *
 */
extern void fsm_start(efsm *machine, fsm_event const *event);



/**
 * [fsm_create  description]
 *
 * @param machine [description]
 * @param actions [description]
 *
 */
void fsm_create (efsm *machine, fsm_actions *actions)
{
    int i;

    #ifdef FSM_DEBUG
    printf("[FSM]: Creating the FSM structure.\r\n");
    #endif

    /* Initialize the FSM */
    FSM_TRANSITION(machine, fsm_start);
    FSM_SET_STATUS(machine, FSM_STATUS_INIT);

    /* Set the actions for the standard state */
    FSM_ACTION_CFG(machine, actions, background);
    FSM_ACTION_CFG(machine, actions, start);
    FSM_ACTION_CFG(machine, actions, error);

    /* Set the actions for the user-specific states */
    for (i = 0; i < FSM_STATE_NUM; ++i)
    {
        FSM_ACTION_CFG(machine, actions, state_action[i]);
    }

    return;
}


/**
 * [fsm_reset  description]
 *
 * @param machine [description]
 *
 */
void fsm_reset (efsm *machine)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: FSM Reset\r\n");
    #endif

    /* Reset the FSM */
    FSM_TRANSITION(machine, fsm_start);
    FSM_SET_STATUS(machine, FSM_STATUS_INIT);
}


/**
 * [fsm_run_machine  description]
 *
 * @param machine [description]
 * @param event   [description]
 * @param status  [description]
 *
 */
void fsm_run_machine (efsm *machine, fsm_event const *event, fsm_status *status)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: FSM RunMachine\r\n");
    #endif

    /* Run a state machine cycle */
    FSM_RUN(machine, event);

    /* Execute background action */
    FSM_ACTION(machine, background);

    /* Update status */
    FSM_GET_STATUS(machine, *status);
}


/**
 * Event generation function
 *
 * @param event [description]
 * @param input [description]
 *
 */
void fsm_generate_event (fsm_event *event, fsm_input *input)
{
    #ifdef FSM_DEBUG
    printf("[FSM]: Event generator input = %d\r\n", *input);
    #endif

    /* Configure the signal based on the input */
    FSM_SET_SIGNAL(event, input);
}



/* EOF */
