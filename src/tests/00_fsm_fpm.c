/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       00_fsm_fpm.c
 *
 *  Description: This is test for the DSP-402 FSM implementation using function-pointer
 *               method.
 *
 *
 ***************************************************************************************/


#include <stdio.h>

#include "fsm_dsp402_fpm.h"


int main (void)
{
    printf("\r\nThis is a test/demo for using libefsm/fpm variant.\r\n\r\n");

    /* Declare FSM objects*/
    dsp402_fsm      fsm;
    dsp402_event    event;

    /* Construct and initialize the FSM */
    fsmCreate(&fsm);
    fsmInit(&fsm);

    /* FSM Primary Loop */
    for (;;)
    {
        printf("\r\nSignal<-");
        event.code = getc(stdin);
        getc(stdin);

        switch (event.code)
        {
            case 0x30:
                event.mEvent.sig = RESET_SIG;
                break;

            case 0x31:
                event.mEvent.sig = SHUTDOWN_SIG;
                break;

            case 0x32:
                event.mEvent.sig = SWITCH_ON_SIG;
                break;

            case 0x33:
                event.mEvent.sig = ENABLE_OP_SIG;
                break;

            case 0x34:
                event.mEvent.sig = DISABLE_OP_SIG;
                break;

            case 0x35:
                event.mEvent.sig = QUICKSTOP_EN_SIG;
                break;

            case 0x36:
                event.mEvent.sig = QUICKSTOP_END_SIG;
                break;

            case 0x37:
                event.mEvent.sig = DISABLE_HV_SIG;
                break;

            case 0x38:
                event.mEvent.sig = FAULT_SIG;
                break;

            case 0x39:
                event.mEvent.sig = FAULT_ACT_SIG;
                break;

            case 0x40:
                event.mEvent.sig =FAULT_RESET_SIG;
                break;

            default:
                event.mEvent.sig = FSM_IDLE_SIG;
                break;
        }

        fsmRun(&fsm, &event);
    }

    return 0;
}


/* EOF */
