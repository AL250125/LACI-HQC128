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


#define BIT0MASK(x)     (int32_t )(-((x) & 1))

/**
 * \fn static void encode_rm(laci_word_t * const codeword, const laci_word_t msg)
 * \brief Encode a message with the RM(1,7) code
 *
 * \param[out]  codeword    Pointer to 128 bits code word
 * \param[in]   msg         The byte to be encoded
 *
 * This function multiply a byte msg with the generator matrix of thr RM(1,7) code
 * which is equivalent to an Augmented Hadamard code
 *
 *      AAAAAAAA AAAAAAAA AAAAAAAA AAAAAAAA | bit 0
 *      CCCCCCCC CCCCCCCC CCCCCCCC CCCCCCCC | bit 1
 *      F0F0F0F0 F0F0F0F0 F0F0F0F0 F0F0F0F0 | bit 2
 * G =  FF00FF00 FF00FF00 FF00FF00 FF00FF00 | bit 3
 *      FFFF0000 FFFF0000 FFFF0000 FFFF0000 | bit 4
 *      FFFFFFFF 00000000 FFFFFFFF 00000000 | bit 5
 *      FFFFFFFF FFFFFFFF 00000000 00000000 | bit 6
 *      FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF | bit 7
 *
 */
static void encode_rm(laci_word_t * const codeword, const laci_word_t msg)
{
    int32_t first_word;

    first_word = BIT0MASK(msg >> 7);
    first_word = first_word ^ (BIT0MASK(msg >> 0) & 0xAAAAAAAA);
    first_word = first_word ^ (BIT0MASK(msg >> 1) & 0xCCCCCCCC);
    first_word = first_word ^ (BIT0MASK(msg >> 2) & 0xF0F0F0F0);
    first_word = first_word ^ (BIT0MASK(msg >> 3) & 0xFF00FF00);
    first_word = first_word ^ (BIT0MASK(msg >> 4) & 0xFFFF0000);
    codeword[0] = first_word;

    first_word = first_word ^ BIT0MASK(msg >> 5);
    codeword[1] = first_word;

    first_word = first_word ^ BIT0MASK(msg >> 6);
    codeword[3] = first_word;
    
    first_word = first_word ^ BIT0MASK(msg >> 5);
    codeword[2] = first_word;
}

#ifdef LACI_ASM_ARMV7
extern void expand_and_sum_rm_asm_armv7(laci_shword_t * const ex_codeword, const laci_word_t * const codeword);
extern void hadamard_transform_asm_armv7(laci_shword_t * had_ex_codeword, laci_shword_t * ex_codeword);
extern laci_byte_t find_peak_asm_armv7(laci_shword_t * had_ex_codeword);
#else
static void expand_and_sum_rm(laci_shword_t * const ex_codeword, const laci_word_t * const codeword)
{
    laci_word_t word, bit, multiplicity;

    for (word = 0; word < 4; word++)
    {
        for (bit = 0; bit < 32; bit++)
        {
            ex_codeword[word * 32 + bit] = (laci_char_t ) ((codeword[word] >> bit) & 1);
        }
    }

    for (multiplicity = 1; multiplicity < LACI_HQC128_RM_MULTIPLICITY; multiplicity++)
    {
        for (word = 0; word < 4; word++)
        {
            for (bit = 0; bit < 32; bit++)
            {
                ex_codeword[word * 32 + bit] = ex_codeword[word * 32 + bit] + (laci_char_t ) ((codeword[multiplicity * 4 + word] >> bit) & 1);
            }
        }
    } 
}


static void hadamard_transform(laci_shword_t * had_ex_codeword, laci_shword_t * ex_codeword)
{
	laci_shword_t * p1 = ex_codeword;
	laci_shword_t * p2 = had_ex_codeword;
	laci_shword_t * p3;
    laci_word_t i, j;

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 64; j++)
        {
            p2[j] = p1[2 * j] + p1[2 * j + 1];
            p2[j + 64] = p1[2 * j] - p1[2 * j + 1];
        }
        p3 = p1;
        p1 = p2;
        p2 = p3;
    }
}


static laci_byte_t find_peak(const laci_shword_t * const had_ex_codeword)
{
    laci_word_t i, abs_tmp, pos_mask_tmp, peak_abs_value, peak_pos;
    laci_sword_t peak_value, tmp;

    peak_abs_value = 0;
    peak_value = 0;
    peak_pos = 0;

    for (i = 0; i < 128; i++)
    {
        tmp = had_ex_codeword[i];
        pos_mask_tmp = -(tmp > 0);
        abs_tmp = (pos_mask_tmp & tmp) | ((~pos_mask_tmp) & (-tmp));
        peak_value = (abs_tmp > peak_abs_value) ? tmp : peak_value;
        peak_pos = (abs_tmp > peak_abs_value) ? i : peak_pos;
        peak_abs_value = (abs_tmp > peak_abs_value) ? abs_tmp : peak_abs_value;
    }
    peak_pos = peak_pos | (128 * (peak_value > 0));

    return (laci_byte_t ) (peak_pos);
}
#endif

laci_error_t laci_hqc_RM_encode(const laci_word_t * const msg, laci_hqc_mem_t * const hqc_mem)
{
    laci_word_t i, j, offset;
    laci_byte_t * msg_byte;
    laci_word_t * codeword;

    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    msg_byte = (laci_byte_t *)(msg);
    codeword = hqc_mem->RM.codeword;

    for (i = 0; i < LACI_HQC128_N1_BYTE_LENGTH; i++)
    {
        offset = i * LACI_HQC128_RM_MULTIPLICITY * LACI_HQC128_RM_CW_WORD_LENGTH;

        encode_rm(&(codeword[offset]), msg_byte[i]); 
        
        for (j = 1; j < LACI_HQC128_RM_MULTIPLICITY; j++)
        {
            laci_memcpy((laci_byte_t *) (&(codeword[offset + j * LACI_HQC128_RM_CW_WORD_LENGTH])), (laci_byte_t *) (&(codeword[offset])), LACI_WORD_BYTE_LENGTH * LACI_HQC128_RM_CW_WORD_LENGTH);
        }
    }

    return LACI_SUCCESS;
} 


laci_error_t laci_hqc_RM_decode(laci_word_t * const msg, laci_hqc_mem_t * const hqc_mem)
{
    laci_word_t i, offset;
    laci_byte_t * msg_byte;
    
    if (hqc_mem == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    msg_byte = (laci_byte_t *) (msg);

    for (i = 0; i < LACI_HQC128_N1_BYTE_LENGTH; i++)
    {
        offset = i * LACI_HQC128_RM_MULTIPLICITY * LACI_HQC128_RM_CW_WORD_LENGTH;

#ifdef LACI_ASM_ARMV7
        expand_and_sum_rm_asm_armv7(hqc_mem->RM.ex_codeword, &(hqc_mem->RM.codeword[offset]));
        hadamard_transform_asm_armv7(hqc_mem->RM.had_ex_codeword, hqc_mem->RM.ex_codeword);
        hqc_mem->RM.had_ex_codeword[0] = hqc_mem->RM.had_ex_codeword[0] - 64 * LACI_HQC128_RM_MULTIPLICITY; 
        msg_byte[i] = find_peak_asm_armv7(hqc_mem->RM.had_ex_codeword);
#else
        expand_and_sum_rm(hqc_mem->RM.ex_codeword, &(hqc_mem->RM.codeword[offset]));
        hadamard_transform(hqc_mem->RM.had_ex_codeword, hqc_mem->RM.ex_codeword);
        hqc_mem->RM.had_ex_codeword[0] = hqc_mem->RM.had_ex_codeword[0] - 64 * LACI_HQC128_RM_MULTIPLICITY;
        msg_byte[i] = find_peak(hqc_mem->RM.had_ex_codeword);
#endif
    }

    return LACI_SUCCESS;
} 




