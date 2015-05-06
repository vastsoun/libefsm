/** *************************************************************************************
 *  Author:         Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:           fsm_template.h
 *
 *  Description:    TODO
 *
 *
 ***************************************************************************************/



#ifndef _FSM_TEMPLATE_H_
#define _FSM_TEMPLATE_H_



/* Core libefsm header */
#include "fsm_base.h"



/**
 *  The FSM state status
 */
#define FSM_STATUS_INIT             0
#define FSM_STATUS_START            1
#define FSM_STATUS_STATE_0          2 // SET THIS
#define FSM_STATUS_ERROR            3 // SET THIS


/**
 * Definition of event signals
 */
typedef enum
{
    RESET_SIG,          //< "System Reset" command received.
    START_SIG,          // SET THIS
    ERROR_SIG,          //< Error occurance.
    ERROR_OK_SIG        // SET THIS

} fsm_signal; // SET THIS




/**
 *  The standard FSM state-function
 */

void fsm_start(efsm *machine, fsm_event const *event);

void fsm_error(efsm *machine, fsm_event const *event);



/**
 *  User-specific state-functions
 */

void fsm_state_0(efsm *machine, fsm_event const *event); // SET THIS



#endif /* _FSM_TEMPLATE_H_ */



/* EOF */
