/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_fp_method.h
 *
 *  Description: This is an implementation of an FSM using the function-pointer method.
 *
 *
 ***************************************************************************************/

#ifndef FSM_FP_METHOD_H
#define FSM_FP_METHOD_H


/**
 * FSM class methods.
 */

#define fsm_create(me_, init_)      ((me_)->state__ = (fsm_state)(init_))
#define fsm_init(me_, e_)           (*(me_)->state__)((me_), (e_))
#define fsm_dispatch(me_, e_)       (*(me_)->state__)((me_), (e_))
#define fsm_transition(me_, targ_)  ((me_)->state__ = (fsm_state)(targ_))


/**
 * Foundation type definitions
 */

typedef short fsm_signal;
typedef void (*fsm_state)(fsm *, fsm_event const *);


/**
 * Event base class
 */

typedef struct
{
   fsm_signal sig; // the event trigger
} fsm_event;


/**
 * Finite State Machine base class
 */

typedef struct
{
   fsm_state state__; // the current state
} fsm;




#endif

/* EOF */
