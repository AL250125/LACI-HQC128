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


static laci_word_t laci_hqc_tab_mem[LACI_HQC_MEM_SIZE];


laci_error_t laci_hqc_init_mem(laci_hqc_mem_t * memory)
{
    if (memory == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }

    memory->hqc_mem.mem_size = LACI_HQC_MEM_SIZE;
    memory->hqc_mem.mem = laci_hqc_tab_mem;

    memory->sk.seed = laci_hqc_tab_mem + LACI_HQC_SEED_SK_OFFSET;    
    memory->sk.x = laci_hqc_tab_mem + LACI_HQC_X_OFFSET;
    memory->sk.y = laci_hqc_tab_mem + LACI_HQC_Y_OFFSET;

    memory->pk.seed = laci_hqc_tab_mem + LACI_HQC_SEED_PK_OFFSET;    
    memory->pk.h = laci_hqc_tab_mem + LACI_HQC_H_OFFSET;
    memory->pk.s = laci_hqc_tab_mem + LACI_HQC_S_OFFSET;
    
    memory->ct.u = laci_hqc_tab_mem + LACI_HQC_U_OFFSET;
    memory->ct.v = laci_hqc_tab_mem + LACI_HQC_V_OFFSET;
    memory->ct.d = laci_hqc_tab_mem + LACI_HQC_D_OFFSET;
    
    memory->ct_tmp.u = laci_hqc_tab_mem + LACI_HQC_U_TMP_OFFSET;
    memory->ct_tmp.v = laci_hqc_tab_mem + LACI_HQC_V_TMP_OFFSET;
    memory->ct_tmp.d = laci_hqc_tab_mem + LACI_HQC_D_TMP_OFFSET;
    
    memory->random_bytes = laci_hqc_tab_mem + LACI_HQC_RANDOM_BYTES_OFFSET;
    memory->m = laci_hqc_tab_mem + LACI_HQC_M_OFFSET;

    memory->RS.codeword = laci_hqc_tab_mem + LACI_HQC_RS_CODEWORD_OFFSET;
    memory->RS.tmp = laci_hqc_tab_mem + LACI_HQC_RS_TMP_OFFSET; 
    memory->RS.syndrome = laci_hqc_tab_mem + LACI_HQC_RS_SYNDROME_OFFSET; 
    memory->RS.sigma = laci_hqc_tab_mem + LACI_HQC_RS_SIGMA_OFFSET; 
    memory->RS.sigma_copy = laci_hqc_tab_mem + LACI_HQC_RS_SIGMA_COPY_OFFSET; 
    memory->RS.X_sigma_p = laci_hqc_tab_mem + LACI_HQC_RS_X_SIGMA_P_OFFSET; 
    memory->RS.error = laci_hqc_tab_mem + LACI_HQC_RS_ERROR_OFFSET; 
    memory->RS.w = laci_hqc_tab_mem + LACI_HQC_RS_W_OFFSET;
    memory->RS.z = laci_hqc_tab_mem + LACI_HQC_RS_Z_OFFSET;
    memory->RS.beta_j = laci_hqc_tab_mem + LACI_HQC_RS_BETA_J_OFFSET;
    memory->RS.e_j = laci_hqc_tab_mem + LACI_HQC_RS_E_J_OFFSET;
    memory->RS.error_values = laci_hqc_tab_mem + LACI_HQC_RS_ERROR_VALUES_OFFSET;

    memory->RS.u_L0 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_U_L0_OFFSET;
    memory->RS.v_L0 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_V_L0_OFFSET;
    memory->RS.f0_L0 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F0_L0_OFFSET;
    memory->RS.f1_L0 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F1_L0_OFFSET;
    memory->RS.u_L1 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_U_L1_OFFSET;
    memory->RS.v_L1 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_V_L1_OFFSET;
    memory->RS.f0_L1 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F0_L1_OFFSET;
    memory->RS.f1_L1 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F1_L1_OFFSET;
    memory->RS.u_L2 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_U_L2_OFFSET;
    memory->RS.v_L2 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_V_L2_OFFSET;
    memory->RS.f0_L2 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F0_L2_OFFSET;
    memory->RS.f1_L2 = laci_hqc_tab_mem + LACI_HQC_RS_FFT_F1_L2_OFFSET;

    memory->RM.codeword = laci_hqc_tab_mem + LACI_HQC_RM_CODEWORD_OFFSET;
    memory->RM.ex_codeword = (laci_shword_t *) (laci_hqc_tab_mem + LACI_HQC_RM_EX_CODEWORD_OFFSET);
    memory->RM.had_ex_codeword = (laci_shword_t *) (laci_hqc_tab_mem + LACI_HQC_RM_HAD_EX_CODEWORD_OFFSET);

    laci_hqc_clean_mem(memory);

    return LACI_SUCCESS;
}


laci_error_t laci_hqc_clean_mem(laci_hqc_mem_t * const memory)
{
    if (memory == NULL)
    {
        return LACI_ERROR_NULL_POINTER;
    }
    
    laci_memset((laci_byte_t *) (memory->hqc_mem.mem), 0, LACI_WORD_BYTE_LENGTH * LACI_HQC_MEM_SIZE);
    
    return LACI_SUCCESS;
}

