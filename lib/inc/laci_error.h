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

#ifndef LACI_ERROR_H
#define LACI_ERROR_H

#include "laci.h"

#define LACI_VAL_ERROR_OFFSET	(1)                                                         /**< Definition of the offset for error definition */

#define LACI_VAL_SUCCESS		(1)                                                         /**< Definition of initial value for a SUCCESS */
#define LACI_VAL_ERROR_GENERIC	(0)                                                         /**< Definition of initial value for an ERROR */

#define LACI_VAL_ERROR_NULL_POINTER		(LACI_VAL_ERROR_GENERIC - LACI_VAL_ERROR_OFFSET)    /**< Definition null pointer error value */

#ifdef LACI_HQC
#define LACI_VAL_ERROR_HQC_TOO_HEAVY_WEIGHT     (LACI_VAL_ERROR_NULL_POINTER - LACI_VAL_ERROR_OFFSET)               /**< Definition too heavy weight error value */
#define LACI_VAL_ERROR_HQC_BAD_SHARED_SECRET    (LACI_VAL_ERROR_HQC_TOO_HEAVY_WEIGHT - LACI_VAL_ERROR_OFFSET)       /**< Definition bad shared secret error value */
#endif


#define LACI_ERROR_CHECK(a, b)      a = b;                 \
                                    if(LACI_SUCCESS != a)  \
                                    {                      \
                                        return a;          \
                                    }

/**
 * \enum laci_error_e
 * Internal errors.
 */

enum laci_error_e
{
	LACI_SUCCESS = LACI_VAL_SUCCESS,                                                        /**< Definition of LACI success return code */
	LACI_ERROR_GENERIC = LACI_VAL_ERROR_GENERIC,                                            /**< Definition of LACI generic error return code */
	LACI_ERROR_NULL_POINTER = LACI_VAL_ERROR_NULL_POINTER,                                  /**< Definition of LACI null pointer error return code */

#ifdef LACI_HQC
    LACI_ERROR_HQC_TOO_HEAVY_WEIGHT = LACI_VAL_ERROR_HQC_TOO_HEAVY_WEIGHT,                   /**< Definition of LACI HQC too heavy weight error return code */
    LACI_ERROR_HQC_BAD_SHARED_SECRET = LACI_VAL_ERROR_HQC_BAD_SHARED_SECRET                 /**< Definition of LACI HQC bad shared secret error return code */
#endif
};


/**
 * \typedef laci_error_t
 * Typedef for errors.
 */
typedef enum laci_error_e laci_error_t;

#endif /* LACI_ERROR_H */

