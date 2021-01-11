#include <inttypes.h>
#include <stdlib.h>
#include <complex.h>

#include "qstate.h"

qstate_t * 
qstate_new(size_t nqbits)
{
    qstate_t * state = malloc(sizeof(qstate_t));
    if(!state)
    {
        return NULL;
    }

    state->nqbits = nqbits;
    state->ndims = 1 << nqbits;
    state->current_vector = 0;

#ifdef SIMPLE_QSTATE
    state->vector[0] = calloc(sizeof(complex double), state->ndims);
    if(!state->vector[0])
    {
        free(state);
        return NULL;
    }

    state->vector[1] = calloc(sizeof(complex double), state->ndims);
    if(!state->vector[1])
    {
        free(state->vector[0]);
        free(state);
        return NULL;
    }
    state->vector[0][0] = 1;
#endif
#ifdef CHUNKED_QSTATE
    state->vector = calloc(sizeof(complex double), 2 * state->ndims);
    if(!state->vector)
    {
        free(state);
        return NULL;
    }
    state->chunk_size = CHUNK_SIZE;
    state->vector[0] = 1;
#endif


    return state;
}


void
qstate_dealloc(qstate_t * state)
{
#ifdef SIMPLE_QSTATE
    free(state->vector[0]);
    free(state->vector[1]);
#endif
#ifdef CHUNKED_QSTATE
    free(state->vector);
#endif
    free(state);
}

void
qstate_switch_vectors(qstate_t * state)
{
    state->current_vector = (state->current_vector + 1) & 1;
}
