#include <stdio.h>
#include <math.h>
#include <complex.h>

#include "sampling.h"
#include "qop.h"
#include "qstate.h"
#include "unitaries.h"

#define NUM_DOF 12

int
U_encode(qstate_t * state, double x, double y);
int
U_interaction(qstate_t * state, double phi);

int main(int argc, char ** argv)
{
    qstate_t * state;

    int i, j;
    double result;
    double tmp;

    double phis[NUM_DOF];
    for(i = 0; i < NUM_DOF; i++)
    {
        if(scanf("%lf", &tmp) != 1)
        {
            fprintf(stderr, "failed to read phi#%d\n", i);
            return -1;
        }
        phis[i] = tmp;
    }

    // XXX: This is the result obtained in the paper.
    //double phis[12] = {5.29683196,  5.38560137,  3.29346721, -5.52313328, -4.40234988,
    //    1.95117847,  1.61250749,  4.63700674,  5.12551132,  0.63872836,
    //    1.05582973, -0.45121964, -2.93235769,  0.30883892,  2.13654636};

#ifdef VERBOSE
    for(i = 0; i < NUM_DOF; i++)
    {
        fprintf(stderr, "phi[%d] = %lf\n", i, phis[i]);
    }
#endif

    int px_per_var = 256;

    for(i = 0; i < px_per_var; i++)
    {
        double x = (2 * i * M_PI) / px_per_var;
        for(j = 0; j < px_per_var; j++)
        {
            double y = (2 * j * M_PI) / px_per_var;
            state = qstate_new(2);
            U_encode(state, x, y);
            unitary_two_qbit_semitrotter(state, 0, 1, 2, phis);

            sampling_no_collapse_bitstring_amplitude(state, 0b01, &result);
            sampling_no_collapse_bitstring_amplitude(state, 0b10, &tmp);
            result += tmp;

            if(j != px_per_var - 1)
            {
                printf("%f,\t", result);
            }
            else
            {
                printf("%f\n", result);
            }
            
            qstate_dealloc(state);
        }
    }

    return 0;
}

int
U_interaction(qstate_t * state, double phi)
{
    qop_SAFE_APPLY(qop_CX(state, 1, 0));
    qop_SAFE_APPLY(unitary_RZ(state, 1, phi));
    qop_SAFE_APPLY(qop_CX(state, 1, 0));

    return 0;
}


int
U_encode(qstate_t * state, double x, double y)
{
    qop_SAFE_APPLY(qop_H(state, 0));
    qop_SAFE_APPLY(qop_H(state, 1));
    qop_SAFE_APPLY(unitary_RZ(state, 0, x));
    qop_SAFE_APPLY(unitary_RZ(state, 1, y));
    qop_SAFE_APPLY(U_interaction(state, (x - M_PI) * (y - M_PI)));
    qop_SAFE_APPLY(qop_H(state, 0));
    qop_SAFE_APPLY(qop_H(state, 1));
    qop_SAFE_APPLY(unitary_RZ(state, 0, x));
    qop_SAFE_APPLY(unitary_RZ(state, 1, y));
    qop_SAFE_APPLY(U_interaction(state, (x - M_PI) * (y - M_PI)));

    return 0;
}
