#include <math.h>
#include "qop.h"

int
qop_X(qstate_t * state, unsigned short int act)
{
    qop_STATE_CHECK(state, act);
    size_t i;
    for(i = 0; i < state->ndims; i++)
    {
        out_vector(state)[i] = in_vector(state)[i ^ (1UL << act)];
    }
    qstate_switch_vectors(state);
    return 0;
}

int
qop_H(qstate_t * state, unsigned short int act)
{
    qop_STATE_CHECK(state, act);
    size_t i;
    for(i = 0; i < state->ndims; i++)
    {
        if(!(i & (1UL << act)))
        {
            out_vector(state)[i] = (in_vector(state)[i] 
                                    + in_vector(state)[i ^ (1UL << act)]
                                    ) * M_SQRT1_2;
        }
        else
        {
            out_vector(state)[i] = ( in_vector(state)[i ^ (1UL << act)]
                                    - in_vector(state)[i] 
                                    ) * M_SQRT1_2;
        }

    }
    qstate_switch_vectors(state);
    return 0;
}

int
qop_R(qstate_t * state, unsigned short int act, double phi)
{
    qop_STATE_CHECK(state, act);
    size_t i;
    for(i = 0; i < state->ndims; i++)
    {
        
        if(i & (1UL << act))
        {
            out_vector(state)[i] = in_vector(state)[i] * cexp(I * phi);
        }
        else
        {
            out_vector(state)[i] = in_vector(state)[i];
        }
    }
    qstate_switch_vectors(state);
    return 0;
}

int
qop_CX(qstate_t * state, unsigned short int act, unsigned short int control)
{
    qop_STATE_CHECK(state, act);
    qop_STATE_CHECK(state, control);
    size_t i;
    for(i = 0; i < state->ndims; i++)
    {
        if(i & (1 << control))
        {
            out_vector(state)[i] = in_vector(state)[i ^ (1UL << act)];
        }
        else
        {
            out_vector(state)[i] = in_vector(state)[i];
        }

    }
    qstate_switch_vectors(state);
    return 0;
}
