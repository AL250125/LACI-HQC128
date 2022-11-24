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

#ifndef LACI_INC_LACI_H
#define LACI_INC_LACI_H

#include "laci_config.h"
#include "laci_arch.h"
#include "laci_types.h"
#include "laci_error.h"
#include "laci_io.h"
#include "laci_memory.h"
#include "laci_misc.h"
#include "laci_random.h"

#ifdef LACI_HQC
#include "laci_hqc_memory.h"
#include "laci_hqc_param.h"
#include "laci_hqc_gf256.h"
#include "laci_hqc_gf2x.h"
#include "laci_hqc_io.h"
#include "laci_hqc_kem.h"
#include "laci_hqc_pke.h"
#include "laci_hqc_reed_muller.h"
#include "laci_hqc_reed_solomon.h"
#include "laci_hqc_fft.h"
#endif

#ifdef LACI_EXT_LIB_NIST_API
#include "fips202.h"
#include "hash.h"
#include "rng.h"
#endif

#ifdef LACI_EXT_LIB_PQCLEAN_API
#include "aes.h"
#include "fips202.h"
#include "nistseedexpander.h"
#include "randombytes.h"
#include "sha2.h"
#endif

#ifdef LACI_EXT_LIB_PQM4_API
#include "aes.h"
#include "nistseedexpander.h"
#include "randombytes.h"
#include "sha2.h"
#include "SimpleFIPS202.h"
#endif

#endif /* LACI_INC_LACI_H_ */


