/**
 * Copyright or © or Copr. CEA Leti : contributor(s) : Antoine Loiseau (23/11/2022)
 * 
 * antoine.loiseau@cea.fr
 * 
 * This software is a computer program whose purpose is to provide
 * an optimized implementation of HQC-128 for embedded systems with
 * assembly optimisation for ARMv7.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 * This work is supported by the French National Research Agency in the framework 
 * of the “Programme d’Investissement d’Avenir IRT Nanoelec” (ANR-10-AIRT-05).
 */

#ifndef LACI_HQC_FFT_H
#define LACI_HQC_FFT_H

#include "laci.h"

#define LACI_HQC128_RS_FFT_W_L2_LENGTH      (32)
#define LACI_HQC128_RS_FFT_W_L1_LENGTH      (LACI_HQC128_RS_FFT_W_L2_LENGTH << 1)
#define LACI_HQC128_RS_FFT_W_L0_LENGTH      (LACI_HQC128_RS_FFT_W_L1_LENGTH << 1)


/**
 * \fn void laci_hqc_fft(laci_byte_t * const w, const laci_byte_t * const f, laci_hqc_mem_t * const hqc_mem)
 *
 * Perform an additive FFT to find zeros of a polynomial.
 *
 * \param[out]	w			Zeros of polynomial f
 * \param[in]	f			Pointer to polynomial
 * \param[in]	hqc_mem		Pointer to HQC's memory to perform computation
 */
void laci_hqc_fft(laci_byte_t * const w, const laci_byte_t * const f, laci_hqc_mem_t * const hqc_mem);


/**
 * \fn void laci_hqc_fft_error_poly(laci_byte_t * const error, const laci_byte_t * w)
 *
 * COmpute errors from zeros of ELP
 *
 * \param[out]	error		Ouput errors
 * \param[in]	w			Zeros of ELP
 */
void laci_hqc_fft_error_poly(laci_byte_t * const error, const laci_byte_t * w);


#endif /* LACI_HQC_FFT_H */


