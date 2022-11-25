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

#ifndef LACI_HQC_MEMORY_H
#define LACI_HQC_MEMORY_H

#include "laci.h"


#define LACI_HQC_VEC_SIZE                       LACI_HQC128_N_WORD_LENGTH												/**< Definition of vector's size in word */
#define LACI_HQC_OMEGA_SIZE                     LACI_HQC128_OMEGA														/**< Definition of error's weight in word */
#define LACI_HQC_OMEGA_R_SIZE                   LACI_HQC128_OMEGA_R														/**< Definition of error's weight in word (for encryption) */
#define LACI_HQC_RS_CODEWORD_SIZE               LACI_HQC128_N1_WORD_LENGTH												/**< Definition of RS codeword size in word */
#define LACI_HQC_RS_TMP_SIZE                    LACI_HQC128_G_WORD_LENGTH												/**< Definition of error's weight in word */
#define LACI_HQC_RS_FFT_W_SIZE                  (8)																		/**< Definition of temp vector size in word for FFT */
#define LACI_HQC_RS_FFT_F_SIZE                  (1)																		/**< Definition of temp vector size in word for FFT */
#define LACI_HQC_RM_CODEWORD_SIZE               (16)																	/**< Definition of RM codeword size in word */
#define LACI_HQC_RM_EX_CODEWORD_SIZE            (128)																	/**< Definition of extended RM codeword size in word */

#define LACI_HQC_SEED_PK_OFFSET                 (0)																		/**< Address offset of public key seed */
#define LACI_HQC_H_OFFSET                       (LACI_HQC_SEED_PK_OFFSET + LACI_HQC_SEED_WORDS)							/**< Address offset of public key h vector */
#define LACI_HQC_S_OFFSET                       (LACI_HQC_H_OFFSET + LACI_HQC_VEC_SIZE)									/**< Address offset of public key s vector */

#define LACI_HQC_U_OFFSET                       (LACI_HQC_S_OFFSET + LACI_HQC_VEC_SIZE)									/**< Address offset of cipher text u vector */
#define LACI_HQC_V_OFFSET                       (LACI_HQC_U_OFFSET + LACI_HQC_VEC_SIZE)									/**< Address offset of cipher text v vector */
#define LACI_HQC_D_OFFSET                       (LACI_HQC_V_OFFSET + LACI_HQC_VEC_SIZE)									/**< Address offset of cipher text d vector */

#define LACI_HQC_U_TMP_OFFSET                   (LACI_HQC_D_OFFSET + (LACI_HQC_SHA512_BYTES >> 2))						/**< Address offset of cipher text u vector for re-encrypt */
#define LACI_HQC_V_TMP_OFFSET                   (LACI_HQC_U_TMP_OFFSET + LACI_HQC_VEC_SIZE)								/**< Address offset of cipher text v vector for re-encrypt */
#define LACI_HQC_D_TMP_OFFSET                   (LACI_HQC_V_TMP_OFFSET + LACI_HQC_VEC_SIZE)								/**< Address offset of cipher text d vector for re-encrypt */

#define LACI_HQC_RANDOM_BYTES_OFFSET            (LACI_HQC_D_TMP_OFFSET + (LACI_HQC_SHA512_BYTES >> 2))					/**< Address offset of random data for error sampling */
#define LACI_HQC_M_OFFSET                       (LACI_HQC_RANDOM_BYTES_OFFSET + LACI_HQC_RANDOM_BYTES_WORDS)			/**< Address offset of message */

#define LACI_HQC_SEED_SK_OFFSET                 (LACI_HQC_M_OFFSET + LACI_HQC128_K_WORD_LENGTH)							/**< Address offset of message */
#define LACI_HQC_X_OFFSET                       (LACI_HQC_SEED_SK_OFFSET + LACI_HQC_SEED_WORDS)							/**< Address offset of secret key x vector */
#define LACI_HQC_Y_OFFSET                       (LACI_HQC_X_OFFSET + LACI_HQC_VEC_SIZE)									/**< Address offset of secret key y vector */

#define LACI_HQC_RS_CODEWORD_OFFSET				(LACI_HQC_Y_OFFSET + LACI_HQC_OMEGA_SIZE )								/**< Address offset of RS codeword */
#define LACI_HQC_RS_TMP_OFFSET                  (LACI_HQC_RS_CODEWORD_OFFSET + LACI_HQC_RS_CODEWORD_SIZE)				/**< Address offset of RS temp vector */
#define LACI_HQC_RS_SYNDROME_OFFSET             (LACI_HQC_RS_TMP_OFFSET + LACI_HQC_RS_TMP_SIZE)							/**< Address offset of RS syndrome vector */
#define LACI_HQC_RS_SIGMA_OFFSET                (LACI_HQC_RS_SYNDROME_OFFSET + (((2 * LACI_HQC128_DELTA) >> 2) + 1))	/**< Address offset of RS sigma vector */
#define LACI_HQC_RS_SIGMA_COPY_OFFSET           (LACI_HQC_RS_SIGMA_OFFSET + (((1 << LACI_HQC128_FFT) >> 2) + 1))		/**< Address offset of RS sigma vector (copy) */
#define LACI_HQC_RS_X_SIGMA_P_OFFSET            (LACI_HQC_RS_SIGMA_COPY_OFFSET + (((1 << LACI_HQC128_FFT) >> 2) + 1))	/**< Address offset of RS X sigma P vector */
#define LACI_HQC_RS_ERROR_OFFSET                (LACI_HQC_RS_X_SIGMA_P_OFFSET + ((LACI_HQC128_DELTA + 1) >> 2))			/**< Address offset of RS errors vector */
#define LACI_HQC_RS_W_OFFSET                    (LACI_HQC_RS_ERROR_OFFSET + (((1 << LACI_HQC128_M) >> 2) + 1))			/**< Address offset of RS W vector */
#define LACI_HQC_RS_Z_OFFSET                    (LACI_HQC_RS_W_OFFSET + (1 << (LACI_HQC_RS_FFT_W_SIZE - 2)))			/**< Address offset of RS Z vector */
#define LACI_HQC_RS_BETA_J_OFFSET               (LACI_HQC_RS_Z_OFFSET + (LACI_HQC128_N1 >> 2) + 1)						/**< Address offset of RS Beta_j vector */
#define LACI_HQC_RS_E_J_OFFSET                  (LACI_HQC_RS_BETA_J_OFFSET + ((LACI_HQC128_DELTA >> 2) + 1))			/**< Address offset of RS E_j vector */
#define LACI_HQC_RS_ERROR_VALUES_OFFSET         (LACI_HQC_RS_E_J_OFFSET + ((LACI_HQC128_DELTA >> 2) + 1))				/**< Address offset of RS error values vector */

#define LACI_HQC_RS_FFT_U_L0_OFFSET             (LACI_HQC_RS_ERROR_VALUES_OFFSET + (LACI_HQC128_N1 >> 2) + 1)			/**< Address offset of RS u (layer 0) vector for FFT */
#define LACI_HQC_RS_FFT_V_L0_OFFSET             (LACI_HQC_RS_FFT_U_L0_OFFSET + 4*LACI_HQC_RS_FFT_W_SIZE)				/**< Address offset of RS v (layer 0) vector for FFT */
#define LACI_HQC_RS_FFT_F0_L0_OFFSET            (LACI_HQC_RS_FFT_V_L0_OFFSET + 4*LACI_HQC_RS_FFT_W_SIZE)				/**< Address offset of RS f0 (layer 0) vector for FFT */
#define LACI_HQC_RS_FFT_F1_L0_OFFSET            (LACI_HQC_RS_FFT_F0_L0_OFFSET + 2*LACI_HQC_RS_FFT_F_SIZE)				/**< Address offset of RS f1 (layer 0) vector for FFT */

#define LACI_HQC_RS_FFT_U_L1_OFFSET             (LACI_HQC_RS_FFT_F1_L0_OFFSET + 2*LACI_HQC_RS_FFT_F_SIZE)				/**< Address offset of RS u (layer 1) vector for FFT */
#define LACI_HQC_RS_FFT_V_L1_OFFSET             (LACI_HQC_RS_FFT_U_L1_OFFSET + 2*LACI_HQC_RS_FFT_W_SIZE)				/**< Address offset of RS v (layer 1) vector for FFT */
#define LACI_HQC_RS_FFT_F0_L1_OFFSET            (LACI_HQC_RS_FFT_V_L1_OFFSET + 2*LACI_HQC_RS_FFT_W_SIZE)				/**< Address offset of RS f0 (layer 1) vector for FFT */
#define LACI_HQC_RS_FFT_F1_L1_OFFSET            (LACI_HQC_RS_FFT_F0_L1_OFFSET + LACI_HQC_RS_FFT_F_SIZE)					/**< Address offset of RS f1 (layer 1) vector for FFT */

#define LACI_HQC_RS_FFT_U_L2_OFFSET             (LACI_HQC_RS_FFT_F1_L1_OFFSET + LACI_HQC_RS_FFT_F_SIZE)					/**< Address offset of RS u (layer 2) vector for FFT */
#define LACI_HQC_RS_FFT_V_L2_OFFSET             (LACI_HQC_RS_FFT_U_L2_OFFSET + LACI_HQC_RS_FFT_W_SIZE)					/**< Address offset of RS v (layer 2) vector for FFT */
#define LACI_HQC_RS_FFT_F0_L2_OFFSET            (LACI_HQC_RS_FFT_V_L2_OFFSET + LACI_HQC_RS_FFT_W_SIZE)					/**< Address offset of RS f0 (layer 2) vector for FFT */
#define LACI_HQC_RS_FFT_F1_L2_OFFSET            (LACI_HQC_RS_FFT_F0_L2_OFFSET + LACI_HQC_RS_FFT_F_SIZE)					/**< Address offset of RS f1 (layer 2) vector for FFT */

#define LACI_HQC_RM_CODEWORD_OFFSET             (LACI_HQC_RS_CODEWORD_OFFSET + LACI_HQC_RS_CODEWORD_SIZE)				/**< Address offset of RM codeword vector */
#define LACI_HQC_RM_EX_CODEWORD_OFFSET          (LACI_HQC_RM_CODEWORD_OFFSET + LACI_HQC_VEC_SIZE)						/**< Address offset of extended RM codeword vector */
#define LACI_HQC_RM_HAD_EX_CODEWORD_OFFSET      (LACI_HQC_RM_EX_CODEWORD_OFFSET + LACI_HQC_RM_EX_CODEWORD_SIZE)			/**< Address offset of Hadamard RM codeword vector */

#define LACI_HQC_MEM_END_OFFSET                 (LACI_HQC_RM_HAD_EX_CODEWORD_OFFSET + LACI_HQC_RM_EX_CODEWORD_SIZE)		/**< Address offset of the end of HQC memory */
#define LACI_HQC_MEM_SIZE                       LACI_HQC_MEM_END_OFFSET													/**< Size of HQC memory in word */


/**
 * \typedef laci_hqc_sk_t
 * Typedef for secret key
 */
typedef struct laci_hqc_sk_s 
{
    laci_word_t * seed;						/**< Pointer to seed memory vector */
    laci_word_t * x;						/**< Pointer to x memory vector */
    laci_word_t * y;						/**< Pointer to y memory vector */
} laci_hqc_sk_t;


/**
 * \typedef laci_hqc_pk_t
 * Typedef for public key
 */
typedef struct laci_hqc_pk_s
{
    laci_word_t * seed;						/**< Pointer to seed memory vector */
    laci_word_t * h;						/**< Pointer to h memory vector */
    laci_word_t * s;						/**< Pointer to s memory vector */
} laci_hqc_pk_t;


/**
 * \typedef laci_hqc_ct_t
 * Typedef for cipher text
 */
typedef struct laci_hqc_ct_s
{
    laci_word_t * u;						/**< Pointer to u memory vector */
    laci_word_t * v;						/**< Pointer to v memory vector */
    laci_word_t * d;						/**< Pointer to d memory vector */
} laci_hqc_ct_t;


/**
 * \typedef laci_hqc_RS_mem_t
 * Typedef for RS code
 */
typedef struct laci_hqc_RS_mem_s
{
    laci_word_t * codeword;					/**< Pointer to codeword memory vector */
    laci_word_t * tmp;						/**< Pointer to temp memory vector */
    
    laci_word_t * syndrome;					/**< Pointer to syndrome memory vector */
    laci_word_t * sigma;					/**< Pointer to sigma memory vector */
    laci_word_t * sigma_copy;				/**< Pointer to copy of sigma memory vector */
    laci_word_t * X_sigma_p;				/**< Pointer to X_sigma_p memory vector */
    laci_word_t * error;					/**< Pointer to errors memory vector */
    laci_word_t * w;						/**< Pointer to w memory vector */
    laci_word_t * z;						/**< Pointer to z memory vector */
    laci_word_t * beta_j;					/**< Pointer to beta_j memory vector */
    laci_word_t * e_j;						/**< Pointer to e_j memory vector */
    laci_word_t * error_values;				/**< Pointer to error values memory vector */

    laci_word_t * u_L0;						/**< Pointer to u (layer 0) memory vector for FFT */
    laci_word_t * v_L0;						/**< Pointer to v (layer 0) memory vector for FFT */
    laci_word_t * f0_L0;					/**< Pointer to f0 (layer 0) memory vector for FFT */
    laci_word_t * f1_L0;					/**< Pointer to f1 (layer 0) memory vector for FFT */
    laci_word_t * u_L1;						/**< Pointer to u (layer 1) memory vector for FFT */
    laci_word_t * v_L1;						/**< Pointer to v (layer 1) memory vector for FFT */
    laci_word_t * f0_L1;					/**< Pointer to f0 (layer 1) memory vector for FFT */
    laci_word_t * f1_L1;					/**< Pointer to f1 (layer 1) memory vector for FFT */
    laci_word_t * u_L2;						/**< Pointer to u (layer 2) memory vector for FFT */
    laci_word_t * v_L2;						/**< Pointer to v (layer 2) memory vector for FFT */
    laci_word_t * f0_L2;					/**< Pointer to f0 (layer 2) memory vector for FFT */
    laci_word_t * f1_L2;					/**< Pointer to f1 (layer 2) memory vector for FFT */
} laci_hqc_RS_mem_t;


/**
 * \typedef laci_hqc_RM_mem_t
 * Typedef for RM code
 */
typedef struct laci_hqc_RM_mem_s
{
    laci_word_t * codeword;					/**< Pointer to codeword memory vector */
    laci_shword_t * ex_codeword;			/**< Pointer to extended codeword memory vector */
    laci_shword_t * had_ex_codeword;		/**< Pointer to Hadamard extended codeword memory vector */
} laci_hqc_RM_mem_t;


/**
 * \typedef laci_hqc_mem_t
 * Typedef for HQC memory
 */
typedef struct laci_hqc_mem_s
{
    laci_mem_t hqc_mem; 					/**< HQC memory */
 
    laci_hqc_sk_t sk;						/**< Secret key memory */
    laci_hqc_pk_t pk;						/**< Public key memory */
    laci_hqc_ct_t ct;						/**< Cipher Text memory */
    laci_hqc_ct_t ct_tmp;					/**< Temp Cipher Text memory for re-encrypt */
    
    laci_word_t * random_bytes;				/**< Random bytes memory */

    laci_word_t * m;						/**< Message memory */

    laci_hqc_RS_mem_t RS;					/**< RS code memory */
    laci_hqc_RM_mem_t RM;					/**< RM code memory */
} laci_hqc_mem_t;


/**
 * \fn laci_error_t laci_hqc_init_mem(laci_hqc_mem_t * hqc_mem)
 *
 * Initialisation of HQC memory with memory clear
 *
 * \param[in/out]	hqc_mem		Pointer to the memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_init_mem(laci_hqc_mem_t * hqc_mem);


/**
 * \fn laci_error_t laci_hqc_init_mem(laci_hqc_mem_t * hqc_mem)
 *
 * De-initialisation of HQC memory with memory clear
 *
 * \param[in]	hqc_mem		Pointer to the memory
 *
 * \return	  Error code
 */
laci_error_t laci_hqc_clean_mem(laci_hqc_mem_t * const memory);


#endif


