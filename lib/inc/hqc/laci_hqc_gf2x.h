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

/**
 * This code is the property of CEA. The research that allowed the development 
 * of this code was partly funded by the French National Research Agency, 
 * within the framework of the “Investissements d’avenir” program (ANR-10-AIRT-05). 
 */

#ifndef LACI_HQC_GF2X_H
#define LACI_HQC_GF2X_H

#include "laci.h"

#ifdef LACI_EXT_LIB_NIST_API
#include "fips202.h"
#include "hash.h"
#include "rng.h"
#endif

#ifdef LACI_EXT_LIB_PQCLEAN_API
#include "aes.h"
#include "fips202.h"
#include "nistseedexpander.h"
#include "randombytes.h"
#include "sha2.h"
#endif

#ifdef LACI_EXT_LIB_PQM4_API
#include "aes.h"
#include "nistseedexpander.h"
#include "randombytes.h"
#include "sha2.h"
#include "SimpleFIPS202.h"
#endif


/**
 * \fn laci_error_t laci_hqc_gf2x_rand_fixed_weight_coor(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
 *
 * Error sampling with fixed Hamming weight (coordinates representation).
 *
 * \param[in]	ctx			Pointer to AES context for PRNG
 * \param[out]	a			Pointer to output list of coordinates
 * \param[in]	weight		Hamming weight of the output error vector
 * \param[in]	hqc_mem		Pointer to the memory to perform computation
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_rand_fixed_weight_coor(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_gf2x_rand_fixed_weight(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
 *
 * Error sampling with fixed Hamming weight (extended representation).
 *
 * \param[in]	ctx			Pointer to AES context for PRNG
 * \param[out]	a			Pointer to output vector
 * \param[in]	weight		Hamming weight of the output error vector
 * \param[in]	hqc_mem		Pointer to the memory to perform computation
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_rand_fixed_weight(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_gf2x_rand(laci_word_t * const a, const laci_word_t word_len, const laci_word_t mask)
 *
 * Generate a random element in GF2[X].
 *
 * \param[out]	a				Pointer to output vector
 * \param[in]	word_len		Word length of the vector
 * \param[in]	mask			Mask of the last word
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_rand(laci_word_t * const a, const laci_word_t word_len, const laci_word_t mask);


/**
 * \fn laci_error_t laci_hqc_gf2x_add(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t word_size)
 *
 * Add two elements of GF2[X]
 *
 * \param[out]	res				Output pointer for a + b
 * \param[in]	a				Element of GF2[X]
 * \param[in]	b				Element of GF2[X]
 * \param[in]	word_size		Word length of vectors
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_add(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t word_size);


#ifdef LACI_ASM_ARMV7
/**
 * \fn void laci_hqc_gf2x_add_asm_armv7(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b)
 *
 * Add two elements of GF2[X] of word length 550 (ASM implementation)
 *
 * \param[out]	res				Output pointer for a + b
 * \param[in]	a				Element of GF2[X]
 * \param[in]	b				Element of GF2[X]
 */
void laci_hqc_gf2x_add_asm_armv7(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b);
#endif


/**
 * \fn laci_error_t laci_hqc_gf2x_mul(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t weight)
 *
 * Multiply two elements of GF2[X]
 *
 * \param[out]	res				Output pointer for a*b
 * \param[in]	a				Element of GF2[X]
 * \param[in]	b				Sparse element of GF2[X] in coordinate representation
 * \param[in]	weight			Hamming weight of b
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_mul(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t weight);


#ifdef LACI_ASM_ARMV7
/**
 * \fn laci_hqc_gf2x_mul_asm_armv7(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t weight)
 *
 * Multiply two elements of GF2[X] (ASM implementation)
 *
 * \param[out]	res				Output pointer for a*b
 * \param[in]	a				Element of GF2[X]
 * \param[in]	b				Sparse element of GF2[X] in coordinate representation
 * \param[in]	weight			Hamming weight of b
 *
 * \return	  Error code
 */
void laci_hqc_gf2x_mul_asm_armv7(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t weight);
#endif


/**
 * \fn laci_error_t laci_hqc_gf2x_reduce(laci_word_t * const res, const laci_word_t * const a)
 *
 * Reduce an element modulo X^n + 1 for an element of length 2n
 *
 * \param[out]	res				Output pointer for a [X^n + 1]
 * \param[in]	a				Element of GF2[X] of length 2n
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_gf2x_reduce(laci_word_t * const res, const laci_word_t * const a);


#ifdef LACI_ASM_ARMV7
/**
 * \fn laci_error_t laci_hqc_gf2x_reduce(laci_word_t * const res, const laci_word_t * const a)
 *
 * Reduce an element modulo X^n + 1 for an element of length 2n (ASM implementation)
 *
 * \param[out]	res				Output pointer for a [X^n + 1]
 * \param[in]	a				Element of GF2[X] of length 2n
 *
 * \return	  Error code
 */
void laci_hqc_gf2x_reduce_asm_armv7(laci_word_t * const res, const laci_word_t * const a);
#endif

#endif /*  */

