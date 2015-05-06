/** *************************************************************************************
 *  Author:         Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:           00_template.c
 *
 *  Description:    TODO
 *
 *
 ***************************************************************************************/



/* Implementation Headers */
#include "fsm_template.h"



/* Decalre custom setup func  */
void my_task_config (fsm_actions *actions);

/* Declare custom functions the FSM input/output */
void my_input_func (fsm_input *input);
void my_status_func (fsm_status status);
void my_signals (void);

/* Declare custom state actions */
void my_background (void);
void my_start (void);
void my_state_0 (void);
void my_error (void);



/**
 *  Main application
 *
 */

int main (int argc, char **argv)
{
    int fsm_counter = 0;

    /* Define FSM interface objects */
    efsm fsm;
    fsm_event event;
    fsm_actions tasks;

    /* generator input and status variables */
    fsm_input my_input = 0;
    fsm_status status = 0;

    /* Configure FSM state action functions */
    my_task_config(&tasks);

    /* FSM Cunstruction and initialization */
    fsm_create(&fsm, &tasks);

    /* Display possible signals */
    my_signals();


    /* Main loop */
    for (;;)
    {
        #ifdef FSM_DEBUG
        printf("\r\n[TEMPLATE]: FSM Loop iteration = %d\r\n", fsm_counter++);
        #endif

        /* Example application input */
        my_input_func(&my_input);

        /* Run the FSM implementation */
        fsm_generate_event(&event, &my_input);
        fsm_run_machine(&fsm, &event, &status);

        /* Example status handling */
        my_status_func(status);
    }

    return 0;
}


/**
 *  Define custom action config
 */

void my_task_config (fsm_actions *actions)
{
    actions->background = my_background;
    actions->start = my_start;
    actions->error = my_error;

    actions->state_action[0] = my_state_0;
}


/**
 *  Define custom input funtion
 */

void my_input_func (fsm_input *my_input)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: Input Function\r\n");
    #endif

    char rx_buff;

    /* Get input from event */
    printf("[TEMPLATE]: Input <- :");
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


/**
 *  Define custom status handling
 *
 */

void my_status_func (fsm_status status)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: Status = %d\r\n\r\n", status);
    #endif
}


void my_signals (void)
{
    printf("[TEMPLATE]: Possible signals are:\r\n");
    printf("    RESET_SIG = %d\r\n", RESET_SIG);
    printf("    START_SIG = %d\r\n", START_SIG);
    printf("    ERROR_SIG = %d\r\n", ERROR_SIG);
    printf("    ERROR_OK_SIG = %d\r\n", ERROR_OK_SIG);
    printf("\r\n");
};


/**
 *  Define custom state actions
 *
 */

void my_background (void)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: Background Action\r\n");
    #endif
}

void my_start (void)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: Start Action\r\n");
    #endif
}

void my_state_0 (void)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: State-0 Action\r\n");
    #endif
}

void my_error (void)
{
    #ifdef FSM_DEBUG
    printf("[TEMPLATE]: Error Action\r\n");
    #endif
}


/* EOF */
