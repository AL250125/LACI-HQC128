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

#ifndef LACI_CONFIG_H
#define LACI_CONFIG_H

#include<stdint.h>
#include<stdlib.h>

#define LACI_GEN_32     0                           /**< Definition of generic 32 bits arhitecture option */
#define LACI_GEN_64     (LACI_GEN_32 + 1)           /**< Definition of generic 64 bits arhitecture option */
#define LACI_ARM_32     (LACI_GEN_64 + 1)           /**< Definition of ARM 32 bits arhitecture option */
#define LACI_ARM_64     (LACI_ARM_64 + 1)           /**< Definition of ARM 64 bits arhitecture option */

#define LACI_ARCH LACI_GEN_32                       /**< Defined the choosen architecture */


#define LACI_STD_IO     0                           /**< Definition of standard input/ouput option */
#define LACI_CUSTOM_IO  (LACI_STD_IO + 1)           /**< Definition of custom input/ouput option */

#define LACI_IO LACI_STD_IO                         /**< Defined the choosen input/output option */

//#define LACI_MEM_API
#define LACI_STD_MEM_API

#endif /* LACI_CONFIG_H */

