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

#ifndef LACI_HQC_PKE_H
#define LACI_HQC_PKE_H

#include "laci.h"


/**
 * \fn laci_error_t laci_hqc_pke_keygen(laci_hqc_mem_t * const hqc_mem)
 *
 * Perform a key generation in IND-CPA security
 *
 * \param[in]	hqc_mem		Pointer to the memory to perform computation
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_pke_keygen(laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_pke_encrypt(const laci_word_t * const m, laci_hqc_ct_t * const ct, const laci_byte_t * const seed, laci_hqc_mem_t * const hqc_mem)
 *
 * Perform an encryption in IND-CPA security
 *
 * \param[in]	m			Pointer to input message buffer
 * \param[out]	ct			Pointer to output cipher text buffer
 * \param[in]	seed		Pointer to input seed buffer for error sampling
 * \param[in]	hqc_mem		Pointer to the memory to perform computation with pre-load public key
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_pke_encrypt(const laci_word_t * const m, laci_hqc_ct_t * const ct, const laci_byte_t * const seed, laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_pke_decrypt(laci_word_t * const m, laci_hqc_ct_t * const ct, laci_hqc_mem_t * const hqc_mem)
 *
 * Perform an decryption in IND-CPA security
 *
 * \param[out]	m			Pointer to output message buffer
 * \param[in]	ct			Pointer to input cipher text buffer
 * \param[in]	hqc_mem		Pointer to the memory to perform computation with pre-load secret key
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_pke_decrypt(laci_word_t * const m, laci_hqc_ct_t * const ct, laci_hqc_mem_t * const hqc_mem);


#endif /* LACI_HQC_PKE_H */

