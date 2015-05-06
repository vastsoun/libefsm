/** *************************************************************************************
 *  Author:         Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:           fsm_base.h
 *
 *  Description:    TODO
 *
 *
 ***************************************************************************************/



#ifndef _FSM_BASE_H_
#define _FSM_BASE_H_



#ifdef FSM_DEBUG
#include <stdio.h>
#endif

/* Implementation dependency on standard c-types */
#include <stdint.h>

/* User configuration header */
#include "fsm_config.h"



/* Default FSM fundamental data types */
#ifndef FSM_STATUS_TYPE
#define FSM_STATUS_TYPE             uint16_t
#endif

#ifndef FSM_INPUT_TYPE
#define FSM_INPUT_TYPE              uint32_t
#endif

/* The internal signaling in the FSM is defined by the input data-type */
#define FSM_SIGNAL_TYPE             FSM_INPUT_TYPE

/* Default state number is a single, non-starting state */
#ifndef FSM_STATE_NUM
#define FSM_STATE_NUM               1
#endif

/* Standard FSM status definition */
#ifndef FSM_STATUS_INIT
#define FSM_STATUS_INIT             0
#endif

/* FSM implementation macros */
#define FSM_RUN(M_, E_)             (*(M_)->m_state)((M_), (E_))
#define FSM_ACTION(M_, A_)          (*(M_)->m_actions.A_)()
#define FSM_TRANSITION(M_, S_)      ((M_)->m_state = (fsm_state)(S_))
#define FSM_SET_STATUS(M_, S_)      ((M_)->m_status = S_)
#define FSM_GET_STATUS(M_, S_)      (S_ = (M_)->m_status)
#define FSM_SET_SIGNAL(E_, I_)      ((E_)->m_signal = (fsm_event_signal)(*(I_)))
#define FSM_GET_SIGNAL(E_)          ((E_)->m_signal)
#define FSM_ACTION_CFG(M_, AS_, A_) ((M_)->m_actions.A_ = (AS_)->A_)



/* Declaration of FSM base data types */
typedef FSM_STATUS_TYPE     fsm_status;
typedef FSM_INPUT_TYPE      fsm_input;
typedef FSM_SIGNAL_TYPE     fsm_event_signal;

/* Declaration of FSM composite data types */
typedef struct efsm         efsm;
typedef struct fsm_event    fsm_event;
typedef struct fsm_actions  fsm_actions;

/* Declaration of FSM implementation type definitions */
typedef void (* fsm_state)(efsm *, fsm_event const *);
typedef void (* state_action)(void);



/* Definition of the FSM composite types */

struct fsm_actions
{
    /* A background action executed at every state */
    state_action background;

    /* All FSMs commence execution at the starting state */
    state_action start;

    /* The configurable states */
    state_action state_action[FSM_STATE_NUM];

    /* The FSM error state*/
    state_action error;
};

struct efsm
{
    /* Current state */
    fsm_state m_state;

    /* Current status */
    fsm_status m_status;

    /* State actions */
    fsm_actions m_actions;
};

struct fsm_event
{
    /* The event signal */
    fsm_event_signal m_signal;

    /* The source state which generated the singal */
    int m_source;

    /* Error code is only set non-zero by the error state action, else it remains zero */
    int m_error_code;
};



/* FSM handling functions */

void fsm_create (efsm *machine, fsm_actions *actions);

void fsm_reset (efsm *machine);

void fsm_run_machine (efsm *machine, fsm_event const *event, fsm_status *status);


/* Event generation functions */

void fsm_generate_event (fsm_event *event, fsm_input *input);



#endif /* _FSM_BASE_H_ */



/* EOF */
