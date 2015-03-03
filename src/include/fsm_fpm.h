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

#ifndef _FSM_FPM_H_
#define _FSM_FPM_H_


/**
 * FSM class methods implemented as pre-proc macros.
 */

#define fsm_create(m_, init_)       ((m_)->state__ = (fsm_state)(init_))
#define fsm_init(m_, e_)            (*(m_)->state__)((m_), (e_))
#define fsm_dispatch(m_, e_)        (*(m_)->state__)((m_), (e_))
#define fsm_transition(m_, s_)      ((m_)->state__ = (fsm_state)(s_))


/**
 * Foundation type definitions
 */

typedef int volatile fsm_signal;
typedef struct fsm_event fsm_event;
typedef struct fsm_base fsm_base;
typedef void (* volatile fsm_state)(fsm_base *, fsm_event const *);


/**
 * Event base class
 */

struct fsm_event
{
    fsm_signal sig; // the event trigger

};


/**
 * Finite State Machine base class
 */

struct fsm_base
{
   fsm_state state__; // the current state

};




#endif /* _FSM_FPM_H_ */


/* EOF */
