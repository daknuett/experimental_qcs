#ifndef sampling_h_included_
#define sampling_h_included_

#include "qstate.h"

/*
 * Allocates *result according the number of qbits
 * and computes the probability amplitudes for each qbit.
 *
 * The results are stored in *result.
 * */
int
sampling_no_collapse_amplitudes(
        qstate_t * state
        , double ** result);


/*
 * Computes the probability amplitude for the given
 * bitstring without collapsing the state. The resulting
 * amplitude is stored in *result.
 *
 * Returns 0 on success.
 * */
int
sampling_no_collapse_bitstring_amplitude(
        qstate_t * state
        , uint64_t bitstring
        , double * result);

#endif
