#include <stdlib.h>
#include "sampling.h"

int
sampling_no_collapse_amplitudes(
        qstate_t * state
        , double ** result)
{
    double * res = malloc(sizeof(double) * state->nqbits);
    if(!res)
    {
        return -1;
    }
    int i,j;
    for(i = 0; i < state->ndims; i++)
    {
        for(j = 0; j < state->nqbits; j++)
        {
            if(i & (1 << j))
            {
                res[j] += cabs(in_vector(state, i)) * cabs(in_vector(state, i));
            }
        }
    }
    *result = res;
    return 0;
}

int
sampling_no_collapse_bitstring_amplitude(
        qstate_t * state
        , uint64_t bitstring
        , double * result)
{
    if(bitstring >= state->ndims)
    {
        return -1;
    }

    *result = cabs(in_vector(state, bitstring)) * cabs(in_vector(state, bitstring));
    return 0;
}
