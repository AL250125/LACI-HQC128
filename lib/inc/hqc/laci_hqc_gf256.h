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

#ifndef LACI_HQC_GF256_H
#define LACI_HQC_GF256_H

#include "laci.h"


/**
 * \fn laci_byte_t laci_hqc_gf256_exp(const laci_byte_t a)
 *
 * Compute the polynomial representation from logarithm representation in GF256
 *
 * \param[in]	a			An element of GF256 in logarithm representation
 *
 * \return	  The polynomial representation of a
 */
laci_byte_t laci_hqc_gf256_exp(const laci_byte_t a);


/**
 * \fn laci_byte_t laci_hqc_gf256_log(const laci_byte_t a)
 *
 * Compute the logarithm representation from polynomial representation in GF256
 *
 * \param[in]	a			An element of GF256 in polynomial representation
 *
 * \return	  The logarithm representation of a
 */
laci_byte_t laci_hqc_gf256_log(const laci_byte_t a);


/**
 * \fn laci_byte_t laci_hqc_gf256_mul(const laci_byte_t a, const laci_byte_t b)
 *
 * Perform a*b in GF256
 *
 * \param[in]	a			An element of GF256 in polynomial representation
 * \param[in]	b			An element of GF256 in polynomial representation
 *
 * \return	  The polynomial representation of a*b
 */
laci_byte_t laci_hqc_gf256_mul(const laci_byte_t a, const laci_byte_t b);


/**
 * \fn laci_byte_t laci_hqc_gf256_square(const laci_byte_t a)
 *
 * Perform a^2 in GF256
 *
 * \param[in]	a			An element of GF256 in polynomial representation
 *
 * \return	  The polynomial representation of a^2
 */
laci_byte_t laci_hqc_gf256_square(const laci_byte_t a);


/**
 * \fn laci_byte_t laci_hqc_gf256_inv(const laci_byte_t a)
 *
 * Perform a^-1 in GF256
 *
 * \param[in]	a			An element of GF256 in polynomial representation
 *
 * \return	  The polynomial representation of a^-1
 */
laci_byte_t laci_hqc_gf256_inv(const laci_byte_t a);


/**
 * \fn laci_byte_t laci_hqc_gf256_mod(const laci_hword_t a)
 *
 * Perform reduction of an element in GF256
 *
 * \param[in]	a			An element of GF256 in logarithm representation
 *
 * \return	  The reduction of a in logarithm representation
 */
laci_byte_t laci_hqc_gf256_mod(const laci_hword_t a);


#endif /* LACI_HQC_GF256_H */



