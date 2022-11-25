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

laci_error_t laci_hqc_get_sk_str(laci_byte_t * const sk, const laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;

    if ((sk == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    laci_memcpy(sk, (laci_byte_t *) hqc_mem->sk.seed, LACI_HQC_SEED_BYTES);
    LACI_ERROR_CHECK(status, laci_hqc_get_pk_str(sk + LACI_HQC_SEED_BYTES, hqc_mem));

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_get_pk_str(laci_byte_t * const pk, const laci_hqc_mem_t * const hqc_mem)
{
    if ((pk == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    laci_memcpy(pk, (laci_byte_t *) hqc_mem->pk.seed, LACI_HQC_SEED_BYTES);
    laci_memcpy(pk + LACI_HQC_SEED_BYTES, (laci_byte_t *) hqc_mem->pk.s, LACI_HQC128_N_BYTE_LENGTH); 

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_get_ct_str(laci_byte_t * const ct, const laci_hqc_mem_t * const hqc_mem)
{
    if ((ct == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    laci_memcpy(ct, (laci_byte_t *) hqc_mem->ct.u, LACI_HQC128_N_BYTE_LENGTH);
    laci_memcpy(ct + LACI_HQC128_N_BYTE_LENGTH, (laci_byte_t *) hqc_mem->ct.v, LACI_HQC128_N1N2_BYTE_LENGTH);
    laci_memcpy(ct + LACI_HQC128_N_BYTE_LENGTH + LACI_HQC128_N1N2_BYTE_LENGTH, (laci_byte_t *) hqc_mem->ct.d, LACI_HQC_SHA512_BYTES);

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_get_ss_str(laci_byte_t * const ss, const laci_hqc_mem_t * const hqc_mem)
{
    if ((ss == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

#ifdef LACI_EXT_LIB_NIST_API
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    
    SHA512_Update(&sha512, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);
    SHA512_Update(&sha512, (laci_byte_t *) hqc_mem->ct.u, LACI_HQC128_N_BYTE_LENGTH);
    SHA512_Update(&sha512, (laci_byte_t *) hqc_mem->ct.v, LACI_HQC128_N1N2_BYTE_LENGTH);
    
    SHA512_Final(ss, &sha512);
#endif

#if defined(LACI_EXT_LIB_PQCLEAN_API) || defined(LACI_EXT_LIB_PQM4_API)
    sha512ctx sha512;
    
    sha512_inc_init(&sha512);
    laci_memcpy((laci_byte_t *) hqc_mem->RM.codeword, (laci_byte_t *) hqc_mem->m, LACI_HQC128_K_BYTE_LENGTH);
    laci_memcpy(((laci_byte_t *) hqc_mem->RM.codeword) + LACI_HQC128_K_BYTE_LENGTH, (laci_byte_t *) hqc_mem->ct.u, 112);
    sha512_inc_blocks(&sha512, (laci_byte_t *) hqc_mem->RM.codeword, 1);
    
    sha512_inc_blocks(&sha512, ((laci_byte_t *) hqc_mem->ct.u) + 112, 16);

    laci_memcpy((laci_byte_t *) hqc_mem->RM.codeword, ((laci_byte_t *) hqc_mem->ct.u) + 2160, 49);
    laci_memcpy(((laci_byte_t *) hqc_mem->RM.codeword) + 49, (laci_byte_t *) hqc_mem->ct.v, 79);
    sha512_inc_blocks(&sha512, (laci_byte_t *) hqc_mem->RM.codeword, 1);

    sha512_inc_finalize(ss, &sha512, ((laci_byte_t *) hqc_mem->ct.v) + 79, LACI_HQC128_N1N2_BYTE_LENGTH - 79);
#endif

    return LACI_SUCCESS;
}




laci_error_t laci_hqc_set_sk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const sk)
{
    laci_error_t status;
    AES_XOF_struct sk_seedexpander;
    
    if ((sk == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    laci_memcpy((laci_byte_t *) hqc_mem->sk.seed, sk, LACI_HQC_SEED_BYTES);
    seedexpander_init(&sk_seedexpander, (laci_byte_t *) hqc_mem->sk.seed, ((laci_byte_t *) hqc_mem->sk.seed) + 32, SEEDEXPANDER_MAX_LENGTH);

    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight(&sk_seedexpander, hqc_mem->sk.x, LACI_HQC128_OMEGA, hqc_mem);) 
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight_coor(&sk_seedexpander, hqc_mem->sk.y, LACI_HQC128_OMEGA, hqc_mem);) 
    
    return LACI_SUCCESS;
}


laci_error_t laci_hqc_set_pk_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const pk)
{
    AES_XOF_struct pk_seedexpander;

    if ((pk == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    laci_memcpy((laci_byte_t *) hqc_mem->pk.seed, pk, LACI_HQC_SEED_BYTES);
    seedexpander_init(&pk_seedexpander, (laci_byte_t *) hqc_mem->pk.seed, ((laci_byte_t *) hqc_mem->pk.seed) + 32, SEEDEXPANDER_MAX_LENGTH);
    seedexpander(&pk_seedexpander, (laci_byte_t *) hqc_mem->pk.h, LACI_HQC128_N_BYTE_LENGTH);
    hqc_mem->pk.h[LACI_HQC128_N_WORD_LENGTH - 1] = hqc_mem->pk.h[LACI_HQC128_N_WORD_LENGTH - 1] & LACI_HQC128_N_BIT_MASK;
    laci_memcpy((laci_byte_t *) hqc_mem->pk.s, pk + LACI_HQC_SEED_BYTES, LACI_HQC128_N_BYTE_LENGTH);

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_set_ct_str(laci_hqc_mem_t * const hqc_mem, const laci_byte_t * const ct)
{
    if ((ct == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    laci_memcpy((laci_byte_t *) hqc_mem->ct.u, ct, LACI_HQC128_N_BYTE_LENGTH);
    laci_memcpy((laci_byte_t *) hqc_mem->ct.v, ct + LACI_HQC128_N_BYTE_LENGTH, LACI_HQC128_N1N2_BYTE_LENGTH);
    laci_memcpy((laci_byte_t *) hqc_mem->ct.d, ct + LACI_HQC128_N_BYTE_LENGTH + LACI_HQC128_N1N2_BYTE_LENGTH, LACI_HQC_SHA512_BYTES);

    return LACI_SUCCESS;
}
