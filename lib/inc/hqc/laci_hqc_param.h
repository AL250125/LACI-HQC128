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

#ifndef LACI_HQC_PARAM_H
#define LACI_HQC_PARAM_H

#include "laci.h"


#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1))
#define LACI_HQC_CONST_TIME

#define LACI_HQC128_SECRET_KEY_BYTE_LENGTH               2289
#define LACI_HQC128_PUBLIC_KEY_BYTE_LENGTH               2249
#define LACI_HQC128_CIPHERTEXT_BYTE_LENGTH               4481

#define LACI_HQC128_N                       17669
#define LACI_HQC128_N1                      46
#define LACI_HQC128_N2                      384
#define LACI_HQC128_N1N2                    17664
#define LACI_HQC128_OMEGA                   66
#define LACI_HQC128_OMEGA_E                 75
#define LACI_HQC128_OMEGA_R                 75
#define LACI_HQC128_SECU                    128
#define LACI_HQC128_DFR                     128

#define LACI_HQC128_DELTA                  	15
#define LACI_HQC128_M                  		8
#define LACI_HQC128_GF_POLY                	0x11D
#define LACI_HQC128_GF_MUL_ORDER           	255
#define LACI_HQC128_K                      	16
#define LACI_HQC128_G                      	31
#define LACI_HQC128_FFT                    	4

#ifdef LACI_HQC_CONST_TIME
#define LACI_HQC128_KAPPA					99
#define LACI_HQC128_RNG_BITS				128
#endif

#define LACI_HQC128_REJECTION_THRESHOLD     16767881

#define LACI_HQC128_RM_MULTIPLICITY         CEIL_DIVIDE(LACI_HQC128_N2, 128)

#define LACI_HQC128_N_BYTE_LENGTH           CEIL_DIVIDE(LACI_HQC128_N, 8) 
#define LACI_HQC128_K_BYTE_LENGTH           LACI_HQC128_K 
#define LACI_HQC128_N1_BYTE_LENGTH          LACI_HQC128_N1 
#define LACI_HQC128_G_BYTE_LENGTH           LACI_HQC128_G 
#define LACI_HQC128_N1N2_BYTE_LENGTH        CEIL_DIVIDE(LACI_HQC128_N1N2, 8) 


#if LACI_WORD_BIT_LENGTH==32
#define LACI_HQC128_N_WORD_LENGTH           CEIL_DIVIDE(LACI_HQC128_N, 32) 
#define LACI_HQC128_K_WORD_LENGTH           CEIL_DIVIDE(LACI_HQC128_K, 4) 
#define LACI_HQC128_N1_WORD_LENGTH          CEIL_DIVIDE(LACI_HQC128_N1, 4) 
#define LACI_HQC128_G_WORD_LENGTH           CEIL_DIVIDE(LACI_HQC128_G, 4) 
#define LACI_HQC128_N1N2_WORD_LENGTH        CEIL_DIVIDE(LACI_HQC128_N1N2, 32) 
#define LACI_HQC128_RM_CW_WORD_LENGTH       4

#define LACI_HQC128_N_BIT_MASK              (0x0000001f)
#define LACI_HQC128_N_BIT_MASK_LENGTH       5

#define LACI_HQC_SHA512_BYTES               64
#define LACI_HQC_SHARED_SECRET_BYTES        LACI_HQC_SHA512_BYTES
#define LACI_HQC_SEED_BYTES                 40
#define LACI_HQC_SEED_WORDS                 CEIL_DIVIDE(LACI_HQC_SEED_BYTES, 4)
#ifdef LACI_HQC_CONST_TIME
#define LACI_HQC_RANDOM_BYTES_WORDS 		CEIL_DIVIDE(LACI_HQC128_KAPPA * LACI_HQC128_RNG_BITS, 32)
#define LACI_HQC128_RNG_BYTES				CEIL_DIVIDE(LACI_HQC128_RNG_BITS, 8)
#define LACI_HQC128_RNG_WORDS				CEIL_DIVIDE(LACI_HQC128_RNG_BITS, 32)
#else
#define LACI_HQC_RANDOM_BYTES_WORDS         CEIL_DIVIDE(3 * LACI_HQC128_OMEGA_R, 4)
#endif
#define SEEDEXPANDER_MAX_LENGTH             4294967295

#define LACI_HQC128_SECRET_KEY_BYTE_LENGTH               2289
#define LACI_HQC128_PUBLIC_KEY_BYTE_LENGTH               2249
#define LACI_HQC128_CIPHERTEXT_BYTE_LENGTH               4481

#endif

#endif


