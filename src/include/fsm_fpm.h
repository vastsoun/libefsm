/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_fpm.h
 *
 *  Description: This is an FSM implementation using the Function-Pointer Method (FPM).
 *               It is based upon the implementation authored by Miro Samek, [1].
 *
 *
 * References:  [1] Miro Samek, "State Machines for Event-Driven Systems",
 *                  www.barrgroup/com/Embedded-Systems/How-To/, March 2009.
 *
 *
 ***************************************************************************************/

#ifndef FSM_FP_METHOD_H
#define FSM_FP_METHOD_H


/**
 * FSM class methods.
 */

#define fsm_create(m_, init_)       ((m_)->state__ = (fsm_state)(init_))
#define fsm_init(m_, e_)            (*(m_)->state__)((m_), (e_))
#define fsm_dispatch(m_, e_)        (*(m_)->state__)((m_), (e_))
#define fsm_transition(m_, s_)      ((m_)->state__ = (fsm_state)(s_))


/**
 * Foundation type definitions
 */

typedef int fsm_signal;
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

} fsm_base;




#endif

/* EOF */
