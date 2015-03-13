/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_X.c
 *
 *  Description: This is an extendible and configurable Finit State Machine (FSM)
 *               implementation which is well suited for high-performance embedded
 *               systems. It has a small memory footprint and scales well with
 *               the addition of states. In fact this implementation is O(m), where m
 *               is the number of transitions any given state can have.
 *
 *
 ***************************************************************************************/



/* Implementation Dependencies */
#include <stdint.h>


/* IO FSM control and status data definitions */
#define STATUS_TYPE                 uint16_t
#define SIGNAL_TYPE                 uint32_t
#define INPUT_TYPE                  uint32_t


/* FSM execution macros */
#define fsm_run(m_, e_)             (*(m_)->mState)((m_), (e_))
#define fsm_action(m_, a_)          (*(m_)->mActions.a_)()
#define fsm_transition(m_, s_)      ((m_)->mState = (fsm_state)(s_))
#define fsm_set_status(m_, s_)      ((m_)->mStatus = s_)
#define fsm_get_status(m_, s_)      (s_ = (m_)->mStatus)
#define fsm_set_signal(e_, i_)      ((e_)->mSignal = (event_signal)(*(i_)))
#define fsm_action_cfg(m_, as_, a_) ((m_)->mActions.a_ = (as_)->a_)

/* The FSM state status */
#define FSM_STATUS_INIT             0
#define FSM_STATUS_START            1
#define FSM_STATUS_CONFIG           2
#define FSM_STATUS_STANDBY          3
#define FSM_STATUS_MOTORON          4
#define FSM_STATUS_ERROR            5



/* FSM base type definitions */
typedef struct X_fsm X_fsm;
typedef struct X_event X_event;
typedef struct X_actions X_actions;
typedef STATUS_TYPE X_status;
typedef INPUT_TYPE X_input;

/* FSM implementation type definitions */
typedef SIGNAL_TYPE event_signal;
typedef void (* fsm_state)(X_fsm *, X_event const *);
typedef void (* state_action)(void);



/**
 * Definition of event signals
 */
typedef enum
{
    RESET_SIG,          //< "System Reset" command received.
    START_SIG,          //< NMT Master sends "Node Operational"
    STOP_SIG,           //< NMT Master sends "Node Pre-Operational"
    ENABLE_OP_SIG,      //< "Enable Operation" command received.
    DISABLE_OP_SIG,     //< "Disable Operation" command received.
    ERROR_SIG,          //< A fault or "Fault Reset" has just occurred.
    ERROR_OK_SIG,       //< Error has been handled and system can continue to run.
    ERROR_ACK_SIG,      //< Error has been handled but its safer to go to standby.
    ERROR_RESET_SIG     //< Error is handled but system must be reconfigured.

} X_signal;


/**
 *  Definition of state actions
 */
struct X_actions
{
    /* A background action executed at every state */
    state_action Background;

    /* State specific actions */
    state_action Start;
    state_action Configure;
    state_action Standby;
    state_action MotorOn;
    state_action Error;
};


/**
 *  Definition of FSM type
 */
struct X_fsm
{
    /* The FSM current state */
    fsm_state mState;

    /* list of state actions */
    X_actions mActions;

    /* Status Flag */
    X_status mStatus;
};


/**
 *  Event Definition
 */
struct X_event
{
    /* The event signal */
    event_signal mSignal;

    /* The signal source */
    int mSource;

    /* Error code is only set non-zero by the error state action, else it remains zero */
    int mErrorCode;
};



/* FSM handling functions */

void fsmCreate (X_fsm *machine, X_actions *actions);

void fsmReset (X_fsm *machine);

void fsmRunMachine (X_fsm *machine, X_event const *event, X_status *status);


/* Event generation functions */

void fsmGenerateEvent (X_event *event, X_input *input);


/* State functions declarations */

void fsmStart(X_fsm *machine, X_event const *event);

void fsmConfigure(X_fsm *machine, X_event const *event);

void fsmStandby(X_fsm *machine, X_event const *event);

void fsmMotorOn(X_fsm *machine, X_event const *event);

void fsmError(X_fsm *machine, X_event const *event);


/* EOF */
