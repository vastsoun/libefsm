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
#include "fsm_fp_method.h"


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

} fsm_dsp402;


/**
 * Extended Event class - CiA DSP-402 specifications.
 */
typedef struct
{
    /* base fsm class */
    fsm_event mFSM;

    /* extension attributes */
    uint16_t fsm_controlword;
    uint16_t fsm_statusword;

} fsm_dsp402;












typedef struct KeyboardEvt KeyboardEvt;
struct KeyboardEvt
{
Event super_; /* extend the Event class */
char code;
};

/* signals used by the Keyboard FSM */
enum
{
    SHIFT_DEPRESSED_SIG,
    SHIFT_RELEASED_SIG,
    ANY_KEY_SIG,
};


void KeyboardCtor(Keyboard *me);
void Keyboard_initial(Keyboard *me, Event const *e);
void Keyboard_default(Keyboard *me, Event const *e);
void Keyboard_shifted(Keyboard *me, Event const *e);













/* EOF */
