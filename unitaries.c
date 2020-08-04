#include "unitaries.h"


int
unitary_RZ(qstate_t * state
        , unsigned short int act
        , double phi)
{
    qop_SAFE_APPLY(qop_X(state, act));
    qop_SAFE_APPLY(qop_R(state, act, phi));
    qop_SAFE_APPLY(qop_X(state, act));
    qop_SAFE_APPLY(qop_R(state, act, -1 * phi));
    return 0;
}


int
unitary_RY(qstate_t * state
        , unsigned short int act
        , double phi)
{
    qop_SAFE_APPLY(qop_R(state, act, -1 * M_PI / 2));
    qop_SAFE_APPLY(unitary_RX(state, act, phi));
    qop_SAFE_APPLY(qop_R(state, act, M_PI / 2));
    return 0;
}


int
unitary_RX(qstate_t * state
        , unsigned short int act
        , double phi)
{
    qop_SAFE_APPLY(qop_H(state, act));
    qop_SAFE_APPLY(unitary_RZ(state, act, phi));
    qop_SAFE_APPLY(qop_H(state, act));
    return 0;
}

int
unitary_one_qbit(qstate_t * state
        , unsigned short int act
        , double phi0
        , double phi1
        , double phi2)
{
    double phim = (phi1 - phi2) / 2;
    double phip = (phi1 + phi2) / 2;

    qop_SAFE_APPLY(unitary_RZ(state, act, phim));
    qop_SAFE_APPLY(unitary_RY(state, act, phi0));
    qop_SAFE_APPLY(unitary_RZ(state, act, phip));
    return 0;
}

int
unitary_two_qbit(qstate_t * state
                , unsigned short int act1
                , unsigned short int act2
                , double * phis)
{
    qop_SAFE_APPLY(unitary_RX(state, act2, phis[0]));
    qop_SAFE_APPLY(qop_CX(state, act2, act1));
    qop_SAFE_APPLY(unitary_one_qbit(state, act1, phis[1], phis[2], phis[3]));
    qop_SAFE_APPLY(unitary_one_qbit(state, act2, phis[4], phis[5], phis[6]));
    qop_SAFE_APPLY(qop_CX(state, act2, act1));
    qop_SAFE_APPLY(unitary_RX(state, act1, phis[7]));
    qop_SAFE_APPLY(unitary_RZ(state, act2, phis[8]));
    qop_SAFE_APPLY(qop_CX(state, act2, act1));
    qop_SAFE_APPLY(unitary_one_qbit(state, act1, phis[9], phis[10], phis[11]));
    qop_SAFE_APPLY(unitary_one_qbit(state, act2, phis[12], phis[13], phis[14]));

    return 0; 
}

