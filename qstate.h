#ifndef qstate_h_included_
#define qstate_h_included_

#include <inttypes.h>
#include <stdlib.h>
#include <complex.h>

#define in_vector(state) (state->vector[state->current_vector])
#define out_vector(state) (state->vector[state->current_vector ^ 1])

#define qstate_has_qbit(state, qbit) (qbit < state->nqbits)

typedef struct {
    size_t nqbits;
    size_t ndims;

    int current_vector;

    double complex * vector[2];
} qstate_t;

qstate_t * 
qstate_new(size_t nqbits);

void
qstate_dealloc(qstate_t * state);

void
qstate_switch_vectors(qstate_t * state);

#endif
