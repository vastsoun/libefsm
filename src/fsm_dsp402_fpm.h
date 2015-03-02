/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_dsp402_fpm.h
 *
 *  Description: This is an implementation of an FSM using the function-pointer method.
 *
 *
 ***************************************************************************************/


/* Standard Headers */
#include <stdint.h>

/* Module Header */
#include "fsm_fpm.h"


/* Set to 1 for enabling debug output, else set to 0 */
#define FSM_DEBUG 1


/**
 * Extended FSM class - CiA DSP-402 specifications.
 */
typedef struct
{
    /* base fsm class */
    fsm_base mFSM;

    /* extension attributes */
    uint16_t fsm_controlword;
    uint16_t fsm_statusword;

} dsp402_fsm;


/**
 * Extended Event class - CiA DSP-402 specifications.
 */
typedef struct
{
    /* base event class */
    fsm_event mEvent;

    /* extension attributes */
    uint32_t event_src;
    uint32_t event_code;

} dsp402_event;



/* signals used by the DSP-402 FSM */
enum
{
    FSM_IDLE_SIG,       //< FSM is in idle state, i.e. no state transition event occurred.
    RESET_SIG,          //< System Reset: From NMT Master - Reset Node or Reset App.
    INIT_SYS_SIG,       //< Initialization or configuration load complete.
    SHUTDOWN_SIG,       //< "Shutdown" command received.
    SWITCH_ON_SIG,      //< "Switch On" command received.
    ENABLE_OP_SIG,      //< "Enable Operation" command received.
    DISABLE_OP_SIG,     //< "Disable Operation" command received.
    QUICKSTOP_EN_SIG,   //< "Quickstop" command received.
    QUICKSTOP_END_SIG,  //< "Quickstop" command complete.
    DISABLE_HV_SIG,     //< "Disable High Voltage" command received.
    FAULT_SIG,          //< A fault has just occurred.
    FAULT_ACT_SIG,      //< Fault reaction has completed.
    FAULT_RESET_SIG,    //< "Fault Reset" command received.
};


/**
 * FSM DSP-402 Class member functions.
 *
 *
 *
 */

/* Constructor and Initialization */

void fsmCreate(dsp402_fsm *m);

void fsmInit(dsp402_fsm *m, dsp402_event const *e);


/* State implementor functions */

void fsmNotReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e);

void fsmSwithcOnDisabled(dsp402_fsm *m, dsp402_event const *e);

void fsmReadyToSwitchOn(dsp402_fsm *m, dsp402_event const *e);

void fsmSwitchedOn(dsp402_fsm *m, dsp402_event const *e);

void fsmOperationEnable(dsp402_fsm *m, dsp402_event const *e);

void fsmQuickstopActive(dsp402_fsm *m, dsp402_event const *e);

void fsmFaultReactionActive(dsp402_fsm *m, dsp402_event const *e);

void fsmFault(dsp402_fsm *m, dsp402_event const *e);


/* EOF */
