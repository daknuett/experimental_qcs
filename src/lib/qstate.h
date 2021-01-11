#ifndef qstate_h_included_
#define qstate_h_included_

#include <inttypes.h>
#include <stdlib.h>
#include <complex.h>

#ifdef SIMPLE_QSTATE
#define in_vector(state, i) (state->vector[state->current_vector][i])
#define out_vector(state, i) (state->vector[state->current_vector ^ 1][i])
#endif

#ifdef CHUNKED_QSTATE
#define in_vector(state, i) (state->vector[state->chunk_size*((i)/state->chunk_size) + (i) % state->chunk_size])
#define out_vector(state, i) (state->vector[state->chunk_size*((i)/state->chunk_size + state->current_vector) + (i) % state->chunk_size])

#endif

#define qstate_has_qbit(state, qbit) (qbit < state->nqbits)

#ifdef SIMPLE_QSTATE
typedef struct {
    size_t nqbits;
    size_t ndims;

    int current_vector;

    double complex * vector[2];
} qstate_t;
#endif
#ifdef CHUNKED_QSTATE
typedef struct {
    size_t nqbits;
    size_t ndims;
    size_t chunk_size;

    int current_vector;

    double complex * vector;
} qstate_t;
#endif

qstate_t * 
qstate_new(size_t nqbits);

void
qstate_dealloc(qstate_t * state);

void
qstate_switch_vectors(qstate_t * state);

#endif
