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

#ifndef LACI_TYPES_H
#define LACI_TYPES_H

#include "laci.h"

/**
 * \typedef laci_byte_t
 * Byte type, uint8_t for all architecture.
 */
typedef uint8_t laci_byte_t;

/**
 * \typedef laci_char_t
 * Char type, int8_t for all architecture.
 */
typedef int8_t laci_char_t;


#if LACI_WORD_BIT_LENGTH==32

/**
 * \typedef laci_hword_t
 * Half-word type, uint16_t for 32 bits architecture.
 */
typedef uint16_t laci_hword_t;

/**
 * \typedef laci_word_t
 * Word type, uint32_t for 32 bits architecture.
 */
typedef uint32_t laci_word_t;

/**
 * \typedef laci_shword_t
 * Signed word type, int16_t for 16 bits architecture.
 */
typedef int16_t laci_shword_t;

/**
 * \typedef laci_sword_t
 * Signed word type, int32_t for 32 bits architecture.
 */
typedef int32_t laci_sword_t;

/**
 * \typedef laci_dword_t
 * Word type, uint64_t for 32 bits architecture.
 */
typedef uint64_t laci_dword_t;

#elif LACI_WORD_BIT_LENGTH==64

/**
 * \typedef laci_hword_t
 * Half-word type, uint32_t for 64 bits architecture.
 */
typedef uint32_t laci_hword_t;

/**
 * \typedef laci_word_t
 * Word type, uint64_t for 64 bits architecture.
 */
typedef uint64_t laci_word_t;

/**
 * \typedef laci_sword_t
 * Signed word type, int64_t for 64 bits architecture.
 */
typedef int64_t laci_sword_t;

/**
 * \typedef laci_dword_t
 * Word type, uint128_t for 64 bits architecture.
 */
typedef uint128_t laci_dword_t;

#else
#error "No Architecture."
#endif

#endif /* LACI_TYPES_H */


