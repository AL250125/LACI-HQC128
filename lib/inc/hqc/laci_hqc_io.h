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

#ifndef LACI_HQC_IO_H
#define LACI_HQC_IO_H

#include "laci.h"

#ifdef LACI_EXT_LIB_NIST_API
#include <openssl/sha.h>
#endif


/**
 * \fn laci_error_t laci_hqc_get_sk_str(laci_byte_t * const sk, const laci_hqc_mem_t * const hqc_mem)
 *
 * Convert in string the current secret key in HQC memory
 *
 * \param[out]	sk			Pointer to output buffer
 * \param[in]	hqc_mem		Pointer to HQC memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_get_sk_str(laci_byte_t * const sk, const laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_get_pk_str(laci_byte_t * const pk, const laci_hqc_mem_t * const hqc_mem)
 *
 * Convert in string the current public key in HQC memory
 *
 * \param[out]	pk			Pointer to output buffer
 * \param[in]	hqc_mem		Pointer to HQC memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_get_pk_str(laci_byte_t * const pk, const laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_get_ct_str(laci_byte_t * const ct, const laci_hqc_mem_t * const hqc_mem)
 *
 * Convert in string the current cipher text in HQC memory
 *
 * \param[out]	ct			Pointer to output buffer
 * \param[in]	hqc_mem		Pointer to HQC memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_get_ct_str(laci_byte_t * const ct, const laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_get_ss_str(laci_byte_t * const ss, const laci_hqc_mem_t * const hqc_mem)
 *
 * Compute and convert in string the shared secret in HQC memory
 *
 * \param[out]	ss			Pointer to output buffer
 * \param[in]	hqc_mem		Pointer to HQC memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_get_ss_str(laci_byte_t * const ss, const laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_set_sk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const sk)
 *
 * Load a secret key in HQC memory
 *
 * \param[out]	hqc_mem		Pointer to HQC memory
 * \param[in]	sk			Pointer to input buffer of secret key
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_set_sk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const sk);


/**
 * \fn laci_error_t laci_hqc_set_pk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const pk)
 *
 * Load a public key in HQC memory
 *
 * \param[out]	hqc_mem		Pointer to HQC memory
 * \param[in]	pk			Pointer to input buffer of public key
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_set_pk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const pk);


/**
 * \fn laci_error_t laci_hqc_set_ct_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const ct)
 *
 * Load a cipher text in HQC memory
 *
 * \param[out]	hqc_mem		Pointer to HQC memory
 * \param[in]	ct			Pointer to input buffer of cipher text
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_set_ct_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const ct);


#endif

