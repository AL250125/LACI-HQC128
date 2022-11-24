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

#include "laci.h"


laci_error_t laci_hqc_pke_keygen(laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;
    AES_XOF_struct sk_seedexpander;
	AES_XOF_struct pk_seedexpander;

    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    randombytes((laci_byte_t *) hqc_mem->sk.seed, LACI_HQC_SEED_BYTES);
    seedexpander_init(&sk_seedexpander, (laci_byte_t *) hqc_mem->sk.seed, ((laci_byte_t *) hqc_mem->sk.seed) + 32, SEEDEXPANDER_MAX_LENGTH);
 
    randombytes((laci_byte_t *) hqc_mem->pk.seed, LACI_HQC_SEED_BYTES);
    seedexpander_init(&pk_seedexpander, (laci_byte_t *) hqc_mem->pk.seed, ((laci_byte_t *) hqc_mem->pk.seed) + 32, SEEDEXPANDER_MAX_LENGTH);
    
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight(&sk_seedexpander, hqc_mem->sk.x, LACI_HQC128_OMEGA, hqc_mem);)
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight_coor(&sk_seedexpander, hqc_mem->sk.y, LACI_HQC128_OMEGA, hqc_mem);)

    seedexpander(&pk_seedexpander, (laci_byte_t *) hqc_mem->pk.h, LACI_HQC128_N_BYTE_LENGTH);
    hqc_mem->pk.h[LACI_HQC128_N_WORD_LENGTH - 1] = hqc_mem->pk.h[LACI_HQC128_N_WORD_LENGTH - 1] & LACI_HQC128_N_BIT_MASK;

    LACI_ERROR_CHECK(status, laci_hqc_gf2x_mul(hqc_mem->ct.u, hqc_mem->pk.h, hqc_mem->sk.y, LACI_HQC128_OMEGA);)
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_reduce(hqc_mem->pk.s, hqc_mem->ct.u);)

    LACI_ERROR_CHECK(status, laci_hqc_gf2x_add(hqc_mem->pk.s, hqc_mem->pk.s, hqc_mem->sk.x, LACI_HQC128_N_WORD_LENGTH);)

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_pke_encrypt(const laci_word_t * const m, laci_hqc_ct_t * const ct, const laci_byte_t * const seed, laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;
    AES_XOF_struct seedexpander;

    if ((m == NULL) || (hqc_mem == NULL) || (seed == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    seedexpander_init(&seedexpander, seed, seed + 32, SEEDEXPANDER_MAX_LENGTH);
    
    /* Sample r2 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight_coor(&seedexpander, (laci_word_t *) hqc_mem->RM.ex_codeword, LACI_HQC128_OMEGA_R, hqc_mem);)
    
    /* u = h * r2 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_mul(hqc_mem->sk.x, hqc_mem->pk.h, (laci_word_t *) hqc_mem->RM.ex_codeword, LACI_HQC128_OMEGA_R);)
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_reduce(ct->u, hqc_mem->sk.x);)

	/* v = s * r2 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_mul(hqc_mem->sk.x, hqc_mem->pk.s, (laci_word_t *) hqc_mem->RM.ex_codeword, LACI_HQC128_OMEGA_R);)
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_reduce(ct->v, hqc_mem->sk.x);)

	/* Sample r1 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight(&seedexpander, hqc_mem->RM.codeword, LACI_HQC128_OMEGA_R, hqc_mem);)

	/* u = h * r2 + r1 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_add(ct->u, ct->u, hqc_mem->RM.codeword, LACI_HQC128_N_WORD_LENGTH);)

	/* mG */
    LACI_ERROR_CHECK(status, laci_hqc_RS_encode(m, hqc_mem);)
    LACI_ERROR_CHECK(status, laci_hqc_RM_encode(hqc_mem->RS.codeword, hqc_mem);)

	/* v = mG + s * r2 */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_add(ct->v, ct->v, hqc_mem->RM.codeword, LACI_HQC128_N_WORD_LENGTH);)

	/* Sample e */
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_rand_fixed_weight(&seedexpander, hqc_mem->RM.codeword, LACI_HQC128_OMEGA_E, hqc_mem);)

	/* v = mG + s * r2 + e*/
	LACI_ERROR_CHECK(status, laci_hqc_gf2x_add(ct->v, ct->v, hqc_mem->RM.codeword, LACI_HQC128_N_WORD_LENGTH);)

    ct->v[LACI_HQC128_N1N2_WORD_LENGTH] = 0;    

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_pke_decrypt(laci_word_t * const m, laci_hqc_ct_t * const ct, laci_hqc_mem_t * const hqc_mem)
{
    laci_error_t status;

    if ((m == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    hqc_mem->ct.v[LACI_HQC128_N1N2_WORD_LENGTH] = 0;
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_mul(hqc_mem->pk.h, ct->u, hqc_mem->sk.y, LACI_HQC128_OMEGA);)
    LACI_ERROR_CHECK(status, laci_hqc_gf2x_reduce(hqc_mem->RM.codeword, hqc_mem->pk.h);)

	LACI_ERROR_CHECK(status, laci_hqc_gf2x_add(hqc_mem->RM.codeword, hqc_mem->RM.codeword, ct->v, LACI_HQC128_N_WORD_LENGTH);)

	LACI_ERROR_CHECK(status, laci_hqc_RM_decode(hqc_mem->RS.codeword, hqc_mem);)
    LACI_ERROR_CHECK(status, laci_hqc_RS_decode(m, hqc_mem);)

    return LACI_SUCCESS;
}





