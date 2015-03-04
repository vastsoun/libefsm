/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_X_fpm.h
 *
 *  Description: TODO
 *
 *
 ***************************************************************************************/


/* Implementation Dependencies */
#include <stdint.h>


/* IO FSM control and status data definitions */
#define STATUS_TYPE     int
#define SIGNAL_TYPE     int
#define INPUT_TYPE      int


/* FSM execution macros */
#define fsm_run(m_, e_)             (*(m_)->mState)((m_), (e_))
#define fsm_transition(m_, s_)      ((m_)->mState = (fsm_state)(s_))



/* FSM base type definitions */
typedef struct X_fsm X_fsm;
typedef struct X_event X_event;
typedef struct X_actions X_actions;
typedef enum X_signal X_signal;

/* FSM implementation type definitions */
typedef SIGNAL_TYPE event_signal;
typedef void (* fsm_state)(X_fsm *, X_event const *);
typedef void (* state_action)(void);



/** 
 * Definition of event signals
 */
enum  X_signal
{
    RESET_SIG,          //< System Reset: From NMT Master - Reset Node or Reset App.
    START_SIG,          //< System Start: From NMT Master - Node Operational
    ENABLE_OP_SIG,      //< "Enable Operation" command received.
    DISABLE_OP_SIG,     //< "Disable Operation" command received.
    ERROR_SIG,          //< A fault or "Fault Reset" has just occurred.
    ERROR_ACK_SIG       //< Fault reaction has completed.
};


/**
 *  Definition of state actions
 */
struct X_actions
{
    state_action Start;
    state_action State0;
    state_action State1;
    state_action State2;
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
    STATUS_TYPE mStatus;
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

void fsmRunMachine (X_fsm *machine, X_event const *event, STATUS_TYPE *status);


/* Event generation functions */

void fsmGenerateEvent (X_event *event, INPUT_TYPE *input);


/* State functions declarations */

void fsmStart(X_fsm *machine, X_event const *event);

void fsmState0(X_fsm *machine, X_event const *event);

void fsmState1(X_fsm *machine, X_event const *event);

void fsmState2(X_fsm *machine, X_event const *event);

void fsmError(X_fsm *machine, X_event const *event);


/* EOF */
