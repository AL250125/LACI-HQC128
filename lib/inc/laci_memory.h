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

#ifndef LACI_MEMORY_H
#define LACI_MEMORY_H

#include "laci.h"

/**
 * \struct laci_mem_s
 * Structure for general memory
 */
struct laci_mem_s 
{
    laci_word_t mem_size;       /**< Total size of memory */
    laci_word_t * mem;          /**< Pointer to the memory */
};


/**
 * \typedef laci_mem_t
 * Typedef for memory structure
 */
typedef struct laci_mem_s laci_mem_t;


/**
 * \fn void laci_memcpy(laci_byte_t * const res, const laci_byte_t * const a, const laci_word_t n)
 * Copy a in res.
 * \param[out]	res	Copy of a
 * \param[in]	a	Table to copy
 * \param[in]	n	Size of a in byte
 */
void laci_memcpy(laci_byte_t * const res, const laci_byte_t * const a, const laci_word_t n);


/**
 * \fn void laci_memset(laci_byte_t * const res, const laci_byte_t w, const laci_word_t n)
 * Set res by w..
 * \param[out]	res	Table to set
 * \param[in]	w	Word
 * \param[in]	n	Size of res in byte
 */
void laci_memset(laci_byte_t * const res, const laci_byte_t w, const laci_word_t n);


/**
 * \fn void laci_memcmp(const laci_byte_t * const a, const laci_byte_t * const b, const laci_word_t n)
 * Compare a and b.
 * \param[in]	a	Table
 * \param[in]	b	Table
 * \param[in]	n	Size of a and b in byte
 * \return 0 if a = b, nonzero otherwise
 */
laci_word_t laci_memcmp(const laci_byte_t * const a, const laci_byte_t * const b, const laci_word_t n);


/**
 * \fn void laci_mem_clean(laci_mem_t * const mem)
 * Clean memory.
 * \param[in, out]	mem     Memory to be cleaned
 */
void laci_mem_clean(laci_mem_t * const mem);

#endif /* LACI_MEMORY_H */


