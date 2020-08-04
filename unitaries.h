#ifndef unitaries_h_included_
#define unitaries_h_included_
#include <math.h>
#include "qop.h"
#include "qstate.h"

int
unitary_RZ(qstate_t * state
        , unsigned short int act
        , double phi);

int
unitary_RY(qstate_t * state
        , unsigned short int act
        , double phi);

int
unitary_RX(qstate_t * state
        , unsigned short int act
        , double phi);

/*
 * \Qcircuit @C=1em @R=.7em {
 * & \qw & \gate{R_Z(\phi_{-})}  & \gate{R_Y(\phi_0)}
 * & \gate{R_Z(\phi_{+}))} & \qw \\
 * }
 *
 * */
int
unitary_one_qbit(qstate_t * state
        , unsigned short int act
        , double phi0
        , double phi1
        , double phi2);


/*
 * \Qcircuit @C=1em @R=.7em {
 * & \qw        & \ctrl{1} & \gate{U_3} & \ctrl{1} & \gate{R_X} & \ctrl{1} & \gate{U_1} & \qw \\
 * & \gate{R_X} & \gate{X} & \gate{U_4} & \gate{X} & \gate{R_Z} & \gate{X} & \gate{U_2}& \qw \\
 * }
 *
 * Where the U_i are ``unitary_one_qbit`` gates.
 * */
int
unitary_two_qbit(qstate_t * state
                , unsigned short int act1
                , unsigned short int act2
                , double * phis);


#endif
