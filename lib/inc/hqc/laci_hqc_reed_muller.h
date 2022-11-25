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

#ifndef LACI_HQC_REED_MULLER_H
#define LACI_HQC_REED_MULLER_H

#include "laci.h"


/**
 * \fn laci_error_t laci_hqc_RM_encode(laci_word_t * const codeword, const laci_word_t * const msg)
 * \brief Encode the Reed-Muller code
 *
 * \param[in]       	msg       		Pointer to the input message
 * \param[in/out]       hqc_mem         Pointer to memory
 *
 * HQC use 3 times the same Reed-Muller code : RM(1,7). This code is equivalent to augmented Hadamard code. The output codeword is in hqc_mem->RM.codeword.
 *
 * return error
 */
laci_error_t laci_hqc_RM_encode(const laci_word_t * const msg, laci_hqc_mem_t * const hqc_mem);


/**
 * \fn laci_error_t laci_hqc_RM_decode(laci_word_t * const msg, laci_hqc_mem_t * const hqc_mem)
 * \brief Decode the Reed-Muller code
 *
 * \param[out]       	msg         	Pointer to the input message
 * \param[in/out]       hqc_mem         Pointer to memory
 *
 * HQC use 3 times the same Reed-Muller code : RM(1,7). This code is equivalent to augmented Hadamard code. The input codeword shall be in hqc_mem->RM.codeword.
 *
 * return error
 */
laci_error_t laci_hqc_RM_decode(laci_word_t * const msg, laci_hqc_mem_t * const hqc_mem);


#endif /* LACI_HQC_REED_MULLER_H  */

