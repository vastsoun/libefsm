/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_dsp402_fpm.c
 *
 *  Description: This is an implementation of an FSM using the function-pointer method.
 *
 *
 ***************************************************************************************/


/* Module Header */
#include "fsm_dsp402_fpm.h"


/**
 * Member function definitions
 */


void fsmCreate(dsp402_fsm *m)
{
    fsm_create(&m->mFSM, &fsmInit);
}


void fsmInit(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: DSP-402 FSM Initialized.\r\n");
    #endif

    /* Initialization of FSM attributes */
    m->fsm_controlword = 0;
    m->fsm_statusword = 0;

    /* Proceed to first initial state */
    fsm_transition((fsm_base *)m, &fsmNotReadyToSwitchOn);
}


void fsmNotReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'NotReadyToSwitchOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0;

    /* State Actions */
    // TODO

    fsm_transition((dsp402_fsm *)m, &fsmSwithcOnDisabled);
}


void fsmSwithcOnDisabled(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'SwithcOnDisabled'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0040;

    /* State Actions */
    switch (e->sig)
    {
        case FSM_IDLE_SIG:

            #if FSM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SHUTDOWN_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Shutdown'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmReadyToSwitchOn);
            break;

        default:

            #if FSM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmFaultReactionActive);
            break;
    }
}


void fsmReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'ReadyToSwitchOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0021;

    /* State Actions */
    switch (e->sig)
    {
        case FSM_IDLE_SIG:

            #if FSM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SWITCH_ON_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Switch On'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmSwitchedOn);
            break;

        default:

            #if FSM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmFaultReactionActive);
            break;
    }
}


void fsmSwitchedOn(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'SwitchedOn'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0043;

    /* State Actions */
    switch (e->sig)
    {
        case FSM_IDLE_SIG:

            #if FSM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case SWITCH_ON_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmOperationEnable);
            break;

        default:

            #if FSM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmFaultReactionActive);
            break;
    }
}


void fsmOperationEnable(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'OperationEnable'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0047;

    /* State Actions */
    switch (e->sig)
    {
        case FSM_IDLE_SIG:

            #if FSM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        case DISABLE_OP_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmSwitchedOn);
            break;

        case SHUTDOWN_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmReadyToSwitchOn);
            break;

        case QUICKSTOP_EN_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmQuickstopActive);
            break;

        default:

            #if FSM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmFaultReactionActive);
            break;
    }
}


void fsmQuickstopActive(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'QuickstopActive'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0007;

    /* State Actions */

    // TODO: Start reducing speed

    switch (e->sig)
    {
        case FSM_IDLE_SIG:

            #if FSM_DEBUG
            printf("[FSM]: FSM is Idle.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            break;

        /*case ENABLE_OP_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmOperationEnable);
            break;
        */

        case QUICKSTOP_END_SIG:

            #if FSM_DEBUG
            printf("[FSM]: Received 'Enable Operation'.\r\n");
            #endif

            /* Transition Actions */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmSwithcOnDisabled);
            break;

        default:

            #if FSM_DEBUG
            printf("[FSM]: error: unknown signal, proceeding to 'Fault Reaction Active'.\r\n");
            #endif

            /* Error has occurred */
            // TODO

            fsm_transition((dsp402_fsm *)m, &fsmFaultReactionActive);
            break;
    }
}


void fsmFaultReactionActive(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'FaultReactionActive'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x000F;

    /* State Actions */
    // TODO

    fsm_transition((dsp402_fsm *)m, &fsmFault);
}


void fsmFault(dsp402_fsm *m, dsp402_event const *e)
{
    #if FSM_DEBUG
    printf("[FSM]: State = 'Fault'.\r\n");
    #endif

    /* Set the fsm status flag */
    m->fsm_statusword = 0x0008;

    /* State Actions */
    // TODO

    fsm_transition((dsp402_fsm *)m, &fsmSwithcOnDisabled);
}


/* EOF */

