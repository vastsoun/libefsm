/** *************************************************************************************
 *  Author:     Vassilios Tsounis, vastsoun@gmail.com
 *
 *  File:       fsm_fp_method.c
 *
 *  Description: This is an implementation of an FSM using the function-pointer method.
 *
 *
 ***************************************************************************************/


#include "fsm.h"

/**
 * Struct definitions definitions
 */
struct Keyboard
{
    Fsm super_; /* extend the Fsm class */
    /* ... other attributes of Keyboard */
};


/**
 * Type definitions
 */
typedef struct Keyboard Keyboard;





void KeyboardCtor(Keyboard *me);
void Keyboard_initial(Keyboard *me, Event const *e);
void Keyboard_default(Keyboard *me, Event const *e);
void Keyboard_shifted(Keyboard *me, Event const *e);

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

void KeyboardCtor(Keyboard *me)
{
FsmCtor_(&me->super_, &Keyboard_initial);
}

void Keyboard_initial(Keyboard *me, Event const *e)
{
/* ... initialization of Keyboard attributes */
printf("Keyboard initialized");
FsmTran_((Fsm *)me, &Keyboard_default);
}

void Keyboard_default(Keyboard *me, Event const *e)
{
switch (e->sig)
{
   case SHIFT_DEPRESSED_SIG:
      printf("default::SHIFT_DEPRESSED");
      FsmTran_((Fsm *)me, &Keyboard_shifted);
      break;
   case ANY_KEY_SIG:
      printf("key %c", (char)tolower(((KeyboardEvt *)e)->code));
      break;
}
}

void Keyboard_shifted(Keyboard *me, Event const *e)
{
switch (e->sig)
{
   case SHIFT_RELEASED_SIG:
      printf("shifted::SHIFT_RELEASED");
      FsmTran_((Fsm *)me, &Keyboard_default);
      break;
   case ANY_KEY_SIG:
      printf("key %c", (char)toupper(((KeyboardEvt *)e)->code));
      break;
}
}












/* EOF */

