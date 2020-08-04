#include <inttypes.h>
#include <stdlib.h>
#include <complex.h>

typedef struct {
    size_t nqbits;
    size_t ndims;

    char current_vector;

    double complex * vector[2];
} qstate_t;

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

    return state;
}


void
qstate_dealloc(qstate_t * state)
{
    free(state->vector[0]);
    free(state->vector[1]);
    free(state);
}

void
qstate_switch_vectors(qstate_t * state)
{
    state->current_vector = (state->current_vector + 1) & 1;
}
