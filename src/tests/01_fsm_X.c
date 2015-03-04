/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       01_fsm_X.c
 *
 *  Description: TODO
 *
 *
 ***************************************************************************************/

/* Standard Headers */
#ifdef FSM_X_DEBUG
#include <stdio.h>
#endif

/* Implementation Headers */
#include "fsm_X.h"


/* Decalre custom setup func  */
void my_task_config (X_actions *actions);

/* Declare custom functions the FSM input/output */
void my_input_func (int *input);
void my_status_func (int status);
void my_signals (void);

/* Declare custom state actions */
void myStart (void);
void myState0 (void);
void myState1 (void);
void myState2 (void);
void myError (void);



/* Main application */
int main (int argc, char **argv)
{
    int fsm_counter = 0;

    /* Define FSM interface objects */
    X_fsm fsm;
    X_event event;
    X_actions tasks;

    /* generator input and status variables */
    int my_input = 0;
    int status = 0;

    /* Configure FSM state action functions */
    my_task_config(&tasks);

    /* FSM Cunstruction and initialization */
    fsmCreate(&fsm, &tasks);

    /* Display possible signals */
    my_signals();


    /* Main loop */
    for (;;)
    {
        #ifdef FSM_X_DEBUG
        printf("\r\n[X]: FSM Loop iteration = %d\r\n", fsm_counter++);
        #endif

        /* Example application input */
        my_input_func(&my_input);

        /* Run the FSM implementation */
        fsmGenerateEvent(&event, &my_input);
        fsmRunMachine(&fsm, &event, &status);

        /* Example status handling */
        my_status_func(status);
    }

    return 0;
}


/* Define custom action config */
void my_task_config (X_actions *actions)
{
    actions->Start = myStart;
    actions->State0 = myState0;
    actions->State1 = myState1;
    actions->State2 = myState2;
    actions->Error = myError;
}


/* Define custom input funtion */
void my_input_func (int *my_input)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: Input Function\r\n");
    #endif

    char rx_buff;

    /* Get input from event */
    printf("[X]: Input <- :");
    rx_buff = getc(stdin);
    getc(stdin);

    /* Process event data */
    if ( (rx_buff > 0x39) || (rx_buff < 0x30) )
    {
        *my_input = 0;
    }
    else
    {
        *my_input = (int)(rx_buff - 0x30);
    }
}


/* Define custom status handling */
void my_status_func (int status)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: Status = %d\r\n\r\n", status);
    #endif
}


void my_signals (void)
{
    printf("[X]: Possible signals are:\r\n");
    printf("    RESET_SIG = %d\r\n", RESET_SIG);
    printf("    START_SIG = %d\r\n", START_SIG);
    printf("    ENABLE_OP_SIG = %d\r\n", ENABLE_OP_SIG);
    printf("    DISABLE_OP_SIG = %d\r\n", DISABLE_OP_SIG);
    printf("    ERROR_SIG = %d\r\n", ERROR_SIG);
    printf("    ERROR_ACK_SIG = %d\r\n", ERROR_ACK_SIG);
    printf("\r\n");
};


/* Define custom state actions */

void myStart (void)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: Start Action\r\n");
    #endif
}

void myState0 (void)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: State-0 Action\r\n");
    #endif
}

void myState1 (void)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: State-1 Action\r\n");
    #endif
}

void myState2 (void)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: State-2 Action\r\n");
    #endif
}

void myError (void)
{
    #ifdef FSM_X_DEBUG
    printf("[X]: Error Action\r\n");
    #endif
}


/* EOF */
