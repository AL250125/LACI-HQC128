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


#ifdef LACI_HQC_CONST_TIME
static laci_word_t laci_hqc_reduce_by_n(laci_word_t * const a, const laci_word_t length)
{
	laci_dword_t red;
	laci_word_t i;

	red = 0;
	for (i = 0; i < length; i++)
	{
		red = (laci_dword_t ) (a[i] + (red << LACI_WORD_BIT_LENGTH));
		red = red % LACI_HQC128_N;
	}

	return red;
}


laci_error_t laci_hqc_gf2x_rand_fixed_weight_coor(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
{
	laci_word_t i, j, exist, tmp;
	laci_word_t max_weight, count, not_enough, needed;

    if ((ctx == NULL) || (a == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    max_weight = laci_MAX(LACI_HQC128_OMEGA, LACI_HQC128_OMEGA_E);
    max_weight = laci_MAX(max_weight, LACI_HQC128_OMEGA_R);
    if (weight > max_weight)
    {
        return LACI_ERROR_HQC_TOO_HEAVY_WEIGHT;
    }

    seedexpander(ctx, (laci_byte_t *)  hqc_mem->random_bytes, LACI_HQC128_KAPPA * LACI_HQC128_RNG_BYTES);

    count = 0;
    for (i = 0; i < LACI_HQC128_KAPPA; i++)
    {
    	tmp = (laci_word_t ) laci_hqc_reduce_by_n(&(hqc_mem->random_bytes[i * LACI_HQC128_RNG_WORDS]), LACI_HQC128_RNG_WORDS);

    	exist = 0;
    	for(j = 0; j < i; j++)
    	{
    	    exist = laci_MUX(exist, 1, laci_EQ(tmp, hqc_mem->random_bytes[j]));
    	}

    	not_enough = count < weight;
    	needed = (!exist) & not_enough;
    	a[count] = laci_MUX(a[count], tmp, needed);
    	count = count + needed;
    }

	return LACI_SUCCESS;
}


laci_error_t laci_hqc_gf2x_rand_fixed_weight(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
{
	laci_word_t i, j, exist, tmp, index, pos;
	laci_word_t max_weight, count, not_enough, needed;

    if ((ctx == NULL) || (a == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    max_weight = laci_MAX(LACI_HQC128_OMEGA, LACI_HQC128_OMEGA_E);
    max_weight = laci_MAX(max_weight, LACI_HQC128_OMEGA_R);
    if (weight > max_weight)
    {
        return LACI_ERROR_HQC_TOO_HEAVY_WEIGHT;
    }

    laci_memset((laci_byte_t *) a, 0, LACI_HQC128_N_BYTE_LENGTH + LACI_HQC128_N_BYTE_LENGTH % LACI_WORD_BYTE_LENGTH);

    seedexpander(ctx, (laci_byte_t *)  hqc_mem->random_bytes, LACI_HQC128_KAPPA * LACI_HQC128_RNG_BYTES);

    count = 0;
    for (i = 0; i < LACI_HQC128_KAPPA; i++)
    {
    	tmp = (laci_word_t ) laci_hqc_reduce_by_n(&(hqc_mem->random_bytes[i * LACI_HQC128_RNG_WORDS]), LACI_HQC128_RNG_WORDS);

    	exist = 0;
    	for(j = 0; j < i; j++)
    	{
    	    exist = laci_MUX(exist, 1, laci_EQ(tmp, hqc_mem->random_bytes[j]));
    	}

    	not_enough = count < weight;
    	needed = (!exist) & not_enough;

    	index = (laci_word_t ) (tmp / LACI_WORD_BIT_LENGTH);
    	pos = tmp % LACI_WORD_BIT_LENGTH;
    	tmp = a[index] | (1 << pos);
    	a[index] = laci_MUX(a[index], tmp, needed);

    	count = count + needed;
    }

	return LACI_SUCCESS;
}


#else
laci_error_t laci_hqc_gf2x_rand_fixed_weight_coor(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
{ 
    laci_word_t i, j, k, exist, tmp;
    laci_word_t random_bytes_size;

    if ((ctx == NULL) || (a == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    if (weight >= 3 * LACI_HQC128_OMEGA_R)
    {
        return LACI_ERROR_HQC_TOO_HEAVY_WEIGHT;
    }

    random_bytes_size = 3 * weight;
    seedexpander(ctx, (laci_byte_t *)  hqc_mem->random_bytes, random_bytes_size);

    j = 0;
    for (i = 0; i < weight; i++)
    {
        exist = 0;
        do {
            if (j == random_bytes_size)
            {
                seedexpander(ctx, (laci_byte_t *) hqc_mem->random_bytes, random_bytes_size);
                j = 0;
            }

            tmp = (laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++] << 16;
            tmp = ((laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++] << 8) | tmp;
            tmp = ((laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++]) | tmp;
        } while (tmp >= LACI_HQC128_REJECTION_THRESHOLD);

        tmp = tmp % LACI_HQC128_N;

        for (k = 0; k < i; k++)
        {
            if (a[k] == tmp)
            {
                exist = 1;
            }
        }

        if (exist == 1)
        {
            i = i - 1;
        }
        else
        {
            a[i] = tmp;
        }
    }

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_gf2x_rand_fixed_weight(AES_XOF_struct * const ctx, laci_word_t * const a, const laci_word_t weight, laci_hqc_mem_t * const hqc_mem)
{ 
    laci_word_t i, j, tmp, index, pos;
    laci_word_t random_bytes_size;

    if ((ctx == NULL) || (a == NULL) || (hqc_mem == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

    if (weight >= 3 * LACI_HQC128_OMEGA_R)
    {
        return LACI_ERROR_HQC_TOO_HEAVY_WEIGHT;
    }

    random_bytes_size = 3 * weight;
    seedexpander(ctx, (laci_byte_t *)  hqc_mem->random_bytes, random_bytes_size);

    laci_memset((laci_byte_t *) a, 0, LACI_HQC128_N_BYTE_LENGTH + LACI_HQC128_N_BYTE_LENGTH % LACI_WORD_BYTE_LENGTH);

    j = 0;
    for (i = 0; i < weight; i++)
    {
        do {
            if (j == random_bytes_size)
            {
                seedexpander(ctx, (laci_byte_t *) hqc_mem->random_bytes, random_bytes_size);
                j = 0;
            }

            tmp = (laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++] << 16;
            tmp = ((laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++] << 8) | tmp;
            tmp = ((laci_word_t ) ((laci_byte_t *) hqc_mem->random_bytes)[j++]) | tmp;
        } while (tmp >= LACI_HQC128_REJECTION_THRESHOLD);

        tmp = tmp % LACI_HQC128_N;

        index = (laci_word_t ) (tmp / LACI_WORD_BIT_LENGTH);
        pos = tmp % LACI_WORD_BIT_LENGTH;

        if (0 != (a[index] & (1 << pos)))
        {
            i = i - 1;
        }
        else
        {
            a[index] = a[index] | (1 << pos);
        }
    }

    return LACI_SUCCESS;
}
#endif

laci_error_t laci_hqc_gf2x_rand(laci_word_t * const a, const laci_word_t word_len, const laci_word_t mask)
{
    laci_word_t i;

    if (a == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    for (i = 0; i < word_len; i++)
    {
        a[i] = laci_get_rand_word();
    }

    a[word_len - 1] = mask & a[word_len - 1];

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_gf2x_add(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t word_size)
{
    laci_word_t i;
    
    if ((res == NULL) || (a == NULL) || (b == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

#ifdef LACI_ASM_ARMV7
    laci_hqc_gf2x_add_asm_armv7(res, a, b);

    for (i = 550; i < word_size; i++)
    {
    	res[i] = a[i] ^ b[i];
    }
#else
    for (i = 0; i < word_size; i++)
    {
        res[i] = a[i] ^ b[i];
    }
#endif

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_gf2x_mul(laci_word_t * const res, const laci_word_t * const a, const laci_word_t * const b, const laci_word_t weight)
{
#ifndef LACI_ASM_ARMV7
    laci_word_t i, j, index, pos, carry;
#endif

    if ((res == NULL) || (a == NULL) || (b == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }

#ifdef LACI_ASM_ARMV7
    laci_hqc_gf2x_mul_asm_armv7(res, a, b, weight);
#else
    for (i = 0; i < (LACI_HQC128_N_WORD_LENGTH << 1); i++)
    {
        res[i] = 0;
    }

    for (i = 0; i < weight; i++)
    {
        index = (laci_word_t ) (b[i] / LACI_WORD_BIT_LENGTH);
        pos = b[i] % LACI_WORD_BIT_LENGTH;
        carry = 0;
        for (j = 0; j < LACI_HQC128_N_WORD_LENGTH; j++)
        {
            res[index + j] = res[index + j] ^ (a[j] << pos) ^ carry;
            // TODO Bug gcc x86 : if pos = 0 (check on arm)
            // carry = a[j] >> (LACI_WORD_BIT_LENGTH - pos);
            // Workaround
            carry = laci_MUX((a[j] >> (LACI_WORD_BIT_LENGTH - pos)), 0, laci_EQ0(pos)); 
        }
        res[index + LACI_HQC128_N_WORD_LENGTH] = res[index + LACI_HQC128_N_WORD_LENGTH] ^ carry;
    }
#endif

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_gf2x_reduce(laci_word_t * const res, const laci_word_t * const a)
{
#ifndef LACI_ASM_ARMV7
	laci_word_t i, carry, index, pos, tmp;
#endif

    if ((res == NULL) || (a == NULL))
    {
        return LACI_ERROR_NULL_POINTER;
    }
#ifdef LACI_ASM_ARMV7
    laci_hqc_gf2x_reduce_asm_armv7(res, a);
#else
    index = (laci_word_t ) (LACI_HQC128_N / LACI_WORD_BIT_LENGTH);
    pos = LACI_HQC128_N & (LACI_WORD_BIT_LENGTH - 1);
   
    for (i = 0; i < index + 1; i++)
    {
    	tmp = a[i + LACI_HQC128_N_WORD_LENGTH-1] >> pos;
    	carry = a[i + LACI_HQC128_N_WORD_LENGTH] << (LACI_WORD_BIT_LENGTH - pos);
    	res[i] = a[i] ^ tmp ^ carry;
    }
    
    res[LACI_HQC128_N_WORD_LENGTH - 1] = res[LACI_HQC128_N_WORD_LENGTH - 1] & LACI_HQC128_N_BIT_MASK;
#endif
    
    return LACI_SUCCESS;
}


