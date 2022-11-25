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

#include "laci.h"


laci_error_t laci_hqc_kem_keygen(laci_byte_t * const pk, laci_byte_t * const sk, laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;

    
    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    LACI_ERROR_CHECK(status, laci_hqc_init_mem(hqc_mem);) 

    LACI_ERROR_CHECK(status, laci_hqc_pke_keygen(hqc_mem);)

    LACI_ERROR_CHECK(status, laci_hqc_get_sk_str(sk, hqc_mem);)
    LACI_ERROR_CHECK(status, laci_hqc_get_pk_str(pk, hqc_mem);)

    LACI_ERROR_CHECK(status, laci_hqc_clean_mem(hqc_mem);)

    return LACI_SUCCESS;   
}


laci_error_t laci_hqc_kem_encrypt(laci_byte_t * const ss, laci_byte_t * const ct, const laci_byte_t * const pk, laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;

    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    LACI_ERROR_CHECK(status, laci_hqc_init_mem(hqc_mem);)   
    LACI_ERROR_CHECK(status, laci_hqc_set_pk_str(hqc_mem, pk);)

    randombytes((laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);

    sha3_512((laci_byte_t *) hqc_mem->random_bytes, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);

    LACI_ERROR_CHECK(status, laci_hqc_pke_encrypt(hqc_mem->m, &hqc_mem->ct, (laci_byte_t *) hqc_mem->random_bytes, hqc_mem);)

    sha512((laci_byte_t *) hqc_mem->ct.d, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);
    
    LACI_ERROR_CHECK(status, laci_hqc_get_ct_str(ct, hqc_mem);)
    LACI_ERROR_CHECK(status, laci_hqc_get_ss_str(ss, hqc_mem);)

    LACI_ERROR_CHECK(status, laci_hqc_clean_mem(hqc_mem);)   

    return LACI_SUCCESS;   
}


laci_error_t laci_hqc_kem_decrypt(laci_byte_t * const ss, const laci_byte_t * const ct, const laci_byte_t * const pk, const laci_byte_t * const sk, laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status, res;
    laci_word_t i;

    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    LACI_ERROR_CHECK(status, laci_hqc_init_mem(hqc_mem);) 
    LACI_ERROR_CHECK(status, laci_hqc_set_sk_str(hqc_mem, sk);) 
    LACI_ERROR_CHECK(status, laci_hqc_set_ct_str(hqc_mem, ct);)

    LACI_ERROR_CHECK(status, laci_hqc_pke_decrypt(hqc_mem->m, &hqc_mem->ct, hqc_mem);)

    sha3_512((laci_byte_t *) hqc_mem->random_bytes, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH); 

    LACI_ERROR_CHECK(status, laci_hqc_set_pk_str(hqc_mem, pk);)

    LACI_ERROR_CHECK(status, laci_hqc_pke_encrypt(hqc_mem->m, &hqc_mem->ct_tmp, (laci_byte_t *) hqc_mem->random_bytes, hqc_mem);) 

    sha512((laci_byte_t *) hqc_mem->ct_tmp.d, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);

    LACI_ERROR_CHECK(status, laci_hqc_get_ss_str(ss, hqc_mem);)

    res = LACI_ERROR_HQC_BAD_SHARED_SECRET;
    res = (laci_memcmp((laci_byte_t *) hqc_mem->ct.u, (laci_byte_t *) hqc_mem->ct_tmp.u, LACI_HQC128_N_BYTE_LENGTH) == 0);
    res = res && (laci_memcmp((laci_byte_t *) hqc_mem->ct.v, (laci_byte_t *) hqc_mem->ct_tmp.v, LACI_HQC128_N1N2_BYTE_LENGTH) == 0);
    res = res && (laci_memcmp((laci_byte_t *) hqc_mem->ct.d, (laci_byte_t *) hqc_mem->ct_tmp.d, LACI_HQC_SHA512_BYTES) == 0); 
    
    for (i = 0; i < LACI_HQC_SHARED_SECRET_BYTES; i++)
    {
        ss[i] = res * ss[i];
    } 
    
    LACI_ERROR_CHECK(status, laci_hqc_clean_mem(hqc_mem);)
    
    LACI_ERROR_CHECK(status, res)

    return LACI_SUCCESS;   
}



