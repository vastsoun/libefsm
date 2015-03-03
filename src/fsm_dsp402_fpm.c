/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_dsp402_fpm.c
 *
 *  Description: This is an implementation of an FSM using the function-pointer method.
 *
 *
 ***************************************************************************************/


/* Standard Headers */
#ifdef FSM_FPM_DEBUG
#include <stdio.h>
#endif

/* Module Header */
#include "fsm_dsp402_fpm.h"


/**
 * Member function definitions
 */


void fsmCreate(dsp402_fsm *m)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: DSP-402 FSM Created.\r\n");
    #endif

    fsm_create( &m->mFSM, &fsmStart );
}


void fsmInit(dsp402_fsm *m)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: DSP-402 FSM Initialized.\r\n");
    #endif

    fsm_init( &m->mFSM, 0 );
}


void fsmRun(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: DSP-402 FSM Running.\r\n");
    #endif

    fsm_dispatch( &m->mFSM, &e->mEvent );
}


void fsmStart(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: DSP-402 FSM Started.\r\n");
    #endif

    /* Initialization of FSM attributes */
    m->controlword = 0;
    m->statusword = 0;

    /* Proceed to first initial state */
    fsm_transition( &m->mFSM, &fsmNotReadyToSwitchOn );
}


void fsmNotReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'NotReadyToSwitchOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0;

    /* State Actions */
    // TODO

    fsm_transition( &m->mFSM, &fsmSwithcOnDisabled );
}


void fsmSwithcOnDisabled(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'SwithcOnDisabled'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0040;

    /* State Actions */
    switch (e->mEvent.sig)
    {
        case FSM_IDLE_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SHUTDOWN_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Shutdown'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmReadyToSwitchOn );
            break;

        default:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition( &m->mFSM, &fsmFaultReactionActive );
            break;
    }
}


void fsmReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'ReadyToSwitchOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0021;

    /* State Actions */
    switch (e->mEvent.sig)
    {
        case FSM_IDLE_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SWITCH_ON_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Switch On'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmSwitchedOn );
            break;

        default:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition( &m->mFSM, &fsmFaultReactionActive );
            break;
    }
}


void fsmSwitchedOn(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'SwitchedOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0043;

    /* State Actions */
    switch (e->mEvent.sig)
    {
        case FSM_IDLE_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SWITCH_ON_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmOperationEnable );
            break;

        default:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition( &m->mFSM, &fsmFaultReactionActive );
            break;
    }
}


void fsmOperationEnable(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'OperationEnable'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0047;

    /* State Actions */
    switch (e->mEvent.sig)
    {
        case FSM_IDLE_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case DISABLE_OP_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmSwitchedOn );
            break;

        case SHUTDOWN_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmReadyToSwitchOn );
            break;

        case QUICKSTOP_EN_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmQuickstopActive );
            break;

        default:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition( &m->mFSM, &fsmFaultReactionActive );
            break;
    }
}


void fsmQuickstopActive(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'QuickstopActive'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0007;

    /* State Actions */

    // TODO: Start reducing speed

    switch (e->mEvent.sig)
    {
        case FSM_IDLE_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        /*case ENABLE_OP_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            // TODO

            fsm_transition(&m->mFSM, &fsmOperationEnable);
            break;
        */

        case QUICKSTOP_END_SIG:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition( &m->mFSM, &fsmSwithcOnDisabled );
            break;

        default:

            #ifdef FSM_FPM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition( &m->mFSM, &fsmFaultReactionActive );
            break;
    }
}


void fsmFaultReactionActive(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'FaultReactionActive'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x000F;

    /* State Actions */
    // TODO

    fsm_transition( &m->mFSM, &fsmFault );
}


void fsmFault(dsp402_fsm *m, dsp402_event const *e)
{
    #ifdef FSM_FPM_DEBUG
    printf("[FSM]: State = 'Fault'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->statusword = 0x0008;

    /* State Actions */
    // TODO

    fsm_transition( &m->mFSM, &fsmSwithcOnDisabled );
}


/* EOF */

