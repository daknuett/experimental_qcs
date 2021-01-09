#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <time.h>

#include "sampling.h"
#include "qop.h"
#include "qstate.h"
#include "unitaries.h"

#define NUM_DOF 12

int
U_interaction(qstate_t * state, int i, int j, double phi);

int
U_field(qstate_t * state, int i, double phi);

int
U_transfer_step(qstate_t * state, double dt, double g);



int main(int argc, char ** argv)
{
    qstate_t * state;

    if(argc != 2)
    {
        fprintf(stderr, "FATAL: expected 1 argument, got %d\n", argc - 1);
        return -1;
    }

    size_t nqbits;
    if(sscanf(argv[1], "%zd", &nqbits) != 1)
    {
        fprintf(stderr, "FATAL: failed to read argument 1 (nqbits: size_t)\n");
        return -1;
    }

    int i;
    const double g = 3;
    const double dt = 1e-3;
    const size_t T = 1000;
    clock_t start, stop;

    state = qstate_new(nqbits);
    start = clock();
    for(i = 0; i < T; i++)
    {
        int result = U_transfer_step(state, dt, g);
        if(result != 0)
        {
            fprintf(stderr, "ERROR: U_transfer_step returned nonzero %d\n", result);
            return -2;
        }
    }
    stop = clock();

    qstate_dealloc(state);

    printf("%ld\n", stop - start);

    return 0;
}

int
U_interaction(qstate_t * state, int i, int j,  double phi)
{
    qop_SAFE_APPLY(qop_CX(state, i, j));
    qop_SAFE_APPLY(unitary_RZ(state, i, phi));
    qop_SAFE_APPLY(qop_CX(state, i, j));

    return 0;
}

int
U_field(qstate_t * state, int i, double phi)
{
    qop_SAFE_APPLY(qop_H(state, i));
    qop_SAFE_APPLY(unitary_RZ(state, i, phi));
    qop_SAFE_APPLY(qop_H(state, i));

    return 0;
}

int
U_transfer_step(qstate_t * state, double dt, double g)
{
    int i;
    for(i = 0; i < state->nqbits - 1; i++)
    {
        qop_SAFE_APPLY(U_interaction(state, i, i+1, dt));
    }
    for(i = 0; i < state->nqbits; i++)
    {
        qop_SAFE_APPLY(U_field(state, i, dt*g));
    }
    return 0;
}
