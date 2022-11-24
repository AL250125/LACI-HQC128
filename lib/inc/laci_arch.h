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
 * 
 * This code is the property of CEA. It shall be subject to the obligations 
 * of the contract CEA/ANR: Convention de Financementi ANR-10-AIRT-05 and of 
 * the IRT Nanoelec consortium agreement Ref C17848 and its Appendices. 
 *
 * Ce code est la propriété de CEA. Il est soumis aux obligations de la convention 
 * CEA /ANR : Convention de Financement ANR-10-AIRT-05 et à l’accord de 
 * consortium IRT Nanoelec Ref. C17848 et ses avenants.
 *
 */

#ifndef LACI_ARCH_H
#define LACI_ARCH_H

#include "laci.h"

#if LACI_ARCH==LACI_GEN_32

#define LACI_WORD_BIT_LENGTH 32             /**< Word length in bits */
#define LACI_WORD_BIT_POW_LENGTH 5          /**< Word power of 2 of bit length */
#define LACI_WORD_BYTE_LENGTH 4             /**< Word length in bytes */

#define LACI_WORD_MOD_MASK	0x1F			/**< Mask to reduce modulo word length */

#define LACI_WORD_MASK      0xFFFFFFFF      /**< Mask of word */
#define LACI_HWORD_MASK0    0x0000FFFF      /**< Mask of inf half-word */
#define LACI_HWORD_MASK1    0xFFFF0000      /**< Mask of sup half-word */
#define LACI_BYTE_MASK0     0x000000FF      /**< Mask of the first byte of a word */
#define LACI_BYTE_MASK1     0x0000FF00      /**< Mask of the second byte of a word */
#define LACI_BYTE_MASK2     0x00FF0000      /**< Mask of the third byte of a word */
#define LACI_BYTE_MASK3     0xFF000000      /**< Mask of the fourth byte of a word */


#elif LACI_ARCH==LACI_GEN_64

#define LACI_WORD_BIT_LENGTH 64             /**< Length in bits of words */

#elif LACI_ARCH==LACI_ARM_32

#define LACI_WORD_BIT_LENGTH 32             /**< Length in bits of words */

#elif LACI_ARCH==LACI_ARM_64

#define LACI_WORD_BIT_LENGTH 64             /**< Length in bits of words */

#else
#error "No Architecture"
#endif

#endif /* LACI_ARCH_H */ 

