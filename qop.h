#ifndef qop_h_included_
#define qop_h_included_

#include "qstate.h"

#define qop_STATE_CHECK(state, qbit) if(!qstate_has_qbit(state, qbit)){return -1;}
#define qop_SAFE_APPLY(statement) {int result = statement; if(result != 0){return result;}}

int
qop_X(qstate_t * state, unsigned short int act);

int
qop_H(qstate_t * state, unsigned short int act);

int
qop_R(qstate_t * state, unsigned short int act, double phi);

int
qop_CX(qstate_t * state, unsigned short int act, unsigned short int control);

int
qop_CZ(qstate_t * state, unsigned short int act, unsigned short int control);
#endif
