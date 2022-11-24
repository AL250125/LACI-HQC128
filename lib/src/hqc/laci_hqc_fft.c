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

static const laci_byte_t laci_hqc128_betas_sums[128] = {0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
    0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
    0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
    0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
    0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
    0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE};

static const laci_byte_t laci_hqc128_gammas_sums_L1[64] = {0x00, 0xB6, 0xB3, 0x05, 0xED, 0x5B, 0x5E, 0xE8, 0x78, 0xCE, 0xCB, 0x7D, 0x95, 0x23, 0x26, 0x90,
    0x1C, 0xAA, 0xAF, 0x19, 0xF1, 0x47, 0x42, 0xF4, 0x64, 0xD2, 0xD7, 0x61, 0x89, 0x3F, 0x3A, 0x8C,
    0x06, 0xB0, 0xB5, 0x03, 0xEB, 0x5D, 0x58, 0xEE, 0x7E, 0xC8, 0xCD, 0x7B, 0x93, 0x25, 0x20, 0x96,
    0x1A, 0xAC, 0xA9, 0x1F, 0xF7, 0x41, 0x44, 0xF2, 0x62, 0xD4, 0xD1, 0x67, 0x8F, 0x39, 0x3C, 0x8A};
static const laci_byte_t laci_hqc128_betas_m_pow_L1[8] = {0x00, 0x06, 0x14, 0x78, 0x0D, 0x2E, 0xE4, 0x62};

static const laci_byte_t laci_hqc128_deltas_L2[5] = {0x5C, 0xD8, 0x46, 0xD9, 0x1F};
static const laci_byte_t laci_hqc128_gammas_sums_L2[32] = {0x00, 0x0C, 0xB7, 0xBB, 0x26, 0x2A, 0x91, 0x9D, 0x61, 0x6D, 0xD6, 0xDA, 0x47, 0x4B, 0xF0, 0xFC, 
    0x16, 0x1A, 0xA1, 0xAD, 0x30, 0x3C, 0x87, 0x8B, 0x77, 0x7B, 0xC0, 0xCC, 0x51, 0x5D, 0xE6, 0xEA};
static const laci_byte_t laci_hqc128_betas_m_pow_L2[4] = {0x00, 0x12, 0x19, 0xBF};


static void laci_hqc_fft_radix(laci_byte_t * const f0, laci_byte_t * const f1, const laci_byte_t * const f, const laci_word_t m_f)
{
    switch(m_f) 
    {
        case 4:
            f0[4] = f[8] ^ f[12];
			f0[6] = f[12] ^ f[14];
			f0[7] = f[14] ^ f[15];
			f1[5] = f[11] ^ f[13];
			f1[6] = f[13] ^ f[14];
			f1[7] = f[15];
			f0[5] = f[10] ^ f[12] ^ f1[5];
			f1[4] = f[9] ^ f[13] ^ f0[5];

			f0[0] = f[0];
			f1[3] = f[7] ^ f[11] ^ f[15];
			f0[3] = f[6] ^ f[10] ^ f[14] ^ f1[3];
			f0[2] = f[4] ^ f0[4] ^ f0[3] ^ f1[3];
			f1[1] = f[3] ^ f[5] ^ f[9] ^ f[13] ^ f1[3];
			f1[2] = f[3] ^ f1[1] ^ f0[3];
			f0[1] = f[2] ^ f0[2] ^ f1[1];
			f1[0] = f[1] ^ f0[1];
            break;

        case 3:
            f0[0] = f[0];
			f0[2] = f[4] ^ f[6];
			f0[3] = f[6] ^ f[7];
			f1[1] = f[3] ^ f[5] ^ f[7];
			f1[2] = f[5] ^ f[6];
			f1[3] = f[7];
			f0[1] = f[2] ^ f0[2] ^ f1[1];
			f1[0] = f[1] ^ f0[1];
            break;

        case 2:
            f0[0] = f[0];
			f0[1] = f[2] ^ f[3];
			f1[0] = f[1] ^ f0[1];
			f1[1] = f[3];
            break;

        case 1:
            f0[0] = f[0];
            f1[0] = f[1];
            break;

        default:
            /* TODO */
            break;
    }
}



static void laci_hqc_fft_rec_L3(laci_byte_t * const w, const laci_byte_t * const f, const laci_byte_t * const betas)
{
    laci_byte_t tmp0, tmp1, tmp2, tmp3, tmp4;
    
    tmp0 = laci_hqc_gf256_mul(betas[0], f[1]);
    tmp1 = laci_hqc_gf256_mul(betas[1], f[1]);
    tmp2 = laci_hqc_gf256_mul(betas[2], f[1]);
    tmp3 = laci_hqc_gf256_mul(betas[3], f[1]);
    tmp4 = laci_hqc_gf256_mul(betas[4], f[1]);

    w[0] = f[0];

    w[1] = w[0] ^ tmp0;

    w[2] = w[0] ^ tmp1;
    w[3] = w[1] ^ tmp1;

    w[4] = w[0] ^ tmp2;
    w[5] = w[1] ^ tmp2;
    w[6] = w[2] ^ tmp2;
    w[7] = w[3] ^ tmp2;
    
    w[8] = w[0] ^ tmp3;
    w[9] = w[1] ^ tmp3;
    w[10] = w[2] ^ tmp3;
    w[11] = w[3] ^ tmp3;
    w[12] = w[4] ^ tmp3;
    w[13] = w[5] ^ tmp3;
    w[14] = w[6] ^ tmp3;
    w[15] = w[7] ^ tmp3;
    
    w[16] = w[0] ^ tmp4;
    w[17] = w[1] ^ tmp4;
    w[18] = w[2] ^ tmp4;
    w[19] = w[3] ^ tmp4;
    w[20] = w[4] ^ tmp4;
    w[21] = w[5] ^ tmp4;
    w[22] = w[6] ^ tmp4;
    w[23] = w[7] ^ tmp4;
    w[24] = w[8] ^ tmp4;
    w[25] = w[9] ^ tmp4;
    w[26] = w[10] ^ tmp4;
    w[27] = w[11] ^ tmp4;
    w[28] = w[12] ^ tmp4;
    w[29] = w[13] ^ tmp4;
    w[30] = w[14] ^ tmp4;
    w[31] = w[15] ^ tmp4;
}


static void laci_hqc_fft_rec_L2(laci_byte_t * const w, laci_byte_t * const f, laci_hqc_mem_t * const hqc_mem)
{
    laci_word_t i;
    laci_byte_t * u;
    laci_byte_t * v;
    laci_byte_t * f0;
    laci_byte_t * f1;
    
    u = (laci_byte_t *) hqc_mem->RS.u_L2;
    v = (laci_byte_t *) hqc_mem->RS.v_L2;
    f0 = (laci_byte_t *) hqc_mem->RS.f0_L2;
    f1 = (laci_byte_t *) hqc_mem->RS.f1_L2;

    f[1] = laci_hqc_gf256_mul(f[1], laci_hqc128_betas_m_pow_L2[1]); 
    f[2] = laci_hqc_gf256_mul(f[2], laci_hqc128_betas_m_pow_L2[2]); 
    f[3] = laci_hqc_gf256_mul(f[3], laci_hqc128_betas_m_pow_L2[3]);

    laci_hqc_fft_radix(f0, f1, f, 2); 

    laci_hqc_fft_rec_L3(u, f0, laci_hqc128_deltas_L2);
    laci_hqc_fft_rec_L3(v, f1, laci_hqc128_deltas_L2);

    laci_memcpy(w + LACI_HQC128_RS_FFT_W_L2_LENGTH, v, LACI_HQC128_RS_FFT_W_L2_LENGTH);
    w[0] = u[0];
    w[LACI_HQC128_RS_FFT_W_L2_LENGTH] = w[LACI_HQC128_RS_FFT_W_L2_LENGTH] ^ u[0];

    for(i = 1; i < LACI_HQC128_RS_FFT_W_L2_LENGTH; i++)
    {
        w[i] = u[i] ^ laci_hqc_gf256_mul(laci_hqc128_gammas_sums_L2[i], v[i]);
        w[LACI_HQC128_RS_FFT_W_L2_LENGTH + i] = w[LACI_HQC128_RS_FFT_W_L2_LENGTH + i] ^ w[i]; 
    }
}



static void laci_hqc_fft_rec_L1(laci_byte_t * const w, laci_byte_t * const f, laci_hqc_mem_t * const hqc_mem)
{
    laci_word_t i;
    laci_byte_t * u;
    laci_byte_t * v;
    laci_byte_t * f0;
    laci_byte_t * f1;
    
    u = (laci_byte_t *) hqc_mem->RS.u_L1;
    v = (laci_byte_t *) hqc_mem->RS.v_L1;
    f0 = (laci_byte_t *) hqc_mem->RS.f0_L1;
    f1 = (laci_byte_t *) hqc_mem->RS.f1_L1;

    f[1] = laci_hqc_gf256_mul(f[1], laci_hqc128_betas_m_pow_L1[1]); 
    f[2] = laci_hqc_gf256_mul(f[2], laci_hqc128_betas_m_pow_L1[2]); 
    f[3] = laci_hqc_gf256_mul(f[3], laci_hqc128_betas_m_pow_L1[3]);
    f[4] = laci_hqc_gf256_mul(f[4], laci_hqc128_betas_m_pow_L1[4]);
    f[5] = laci_hqc_gf256_mul(f[5], laci_hqc128_betas_m_pow_L1[5]);
    f[6] = laci_hqc_gf256_mul(f[6], laci_hqc128_betas_m_pow_L1[6]);
    f[7] = laci_hqc_gf256_mul(f[7], laci_hqc128_betas_m_pow_L1[7]);

    laci_hqc_fft_radix(f0, f1, f, 3); 
    
    laci_hqc_fft_rec_L2(u, f0, hqc_mem);
    laci_hqc_fft_rec_L2(v, f1, hqc_mem);

    laci_memcpy(w + LACI_HQC128_RS_FFT_W_L1_LENGTH, v, LACI_HQC128_RS_FFT_W_L1_LENGTH);
    w[0] = u[0];
    w[LACI_HQC128_RS_FFT_W_L1_LENGTH] = w[LACI_HQC128_RS_FFT_W_L1_LENGTH] ^ u[0];

    for(i = 1; i < LACI_HQC128_RS_FFT_W_L1_LENGTH; i++)
    {
        w[i] = u[i] ^ laci_hqc_gf256_mul(laci_hqc128_gammas_sums_L1[i], v[i]);
        w[LACI_HQC128_RS_FFT_W_L1_LENGTH + i] = w[LACI_HQC128_RS_FFT_W_L1_LENGTH + i] ^ w[i]; 
    } 
}


void laci_hqc_fft(laci_byte_t * const w, const laci_byte_t * const f, laci_hqc_mem_t * const hqc_mem)
{
    laci_word_t i;
    laci_byte_t * u;
    laci_byte_t * v;
    laci_byte_t * f0;
    laci_byte_t * f1;
    
    u = (laci_byte_t *) hqc_mem->RS.u_L0;
    v = (laci_byte_t *) hqc_mem->RS.v_L0;
    f0 = (laci_byte_t *) hqc_mem->RS.f0_L0;
    f1 = (laci_byte_t *) hqc_mem->RS.f1_L0; 
    
    laci_hqc_fft_radix(f0, f1, f, 4);
    
    laci_hqc_fft_rec_L1(u, f0, hqc_mem);
    laci_hqc_fft_rec_L1(v, f1, hqc_mem);

    laci_memcpy(w + LACI_HQC128_RS_FFT_W_L0_LENGTH, v, LACI_HQC128_RS_FFT_W_L0_LENGTH);
    w[0] = u[0];
    w[LACI_HQC128_RS_FFT_W_L0_LENGTH] = w[LACI_HQC128_RS_FFT_W_L0_LENGTH] ^ u[0];

    for(i = 1; i < LACI_HQC128_RS_FFT_W_L0_LENGTH; i++)
    {
        w[i] = u[i] ^ laci_hqc_gf256_mul(laci_hqc128_betas_sums[i], v[i]);
        w[LACI_HQC128_RS_FFT_W_L0_LENGTH + i] = w[LACI_HQC128_RS_FFT_W_L0_LENGTH + i] ^ w[i]; 
    }    
}


void laci_hqc_fft_error_poly(laci_byte_t * const error, const laci_byte_t * w)
{
    laci_word_t i, k, index;

    k= 1 << (LACI_HQC128_M - 1);

    error[0] = 1 ^ ((laci_hword_t ) -w[0] >> 15);
    error[0] = error[0] ^ 1 ^ ((laci_hword_t ) -w[k] >> 15);

    for(i = 1; i < k; i++)
    {
        index = LACI_HQC128_GF_MUL_ORDER - laci_hqc_gf256_log(laci_hqc128_betas_sums[i]);
        error[index] = error[index] ^ 1 ^ ((laci_hword_t ) -w[i] >> 15);
        
        index = LACI_HQC128_GF_MUL_ORDER - laci_hqc_gf256_log(laci_hqc128_betas_sums[i] ^ 1);
        error[index] = error[index] ^ 1 ^ ((laci_hword_t ) -w[k + i] >> 15);
    }
}


