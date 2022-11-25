
# Copyright or © or Copr. CEA Leti : contributor(s) : Antoine Loiseau (23/11/2022)
# 
# antoine.loiseau@cea.fr
# 
# This software is a computer program whose purpose is to provide
# an optimized implementation of HQC-128 for embedded systems with
# assembly optimisation for ARMv7.
#
# This software is governed by the CeCILL license under French law and
# abiding by the rules of distribution of free software.  You can  use, 
# modify and/ or redistribute the software under the terms of the CeCILL
# license as circulated by CEA, CNRS and INRIA at the following URL
# "http://www.cecill.info". 
# 
# As a counterpart to the access to the source code and  rights to copy,
# modify and redistribute granted by the license, users are provided only
# with a limited warranty  and the software's author,  the holder of the
# economic rights,  and the successive licensors  have only  limited
# liability. 
#
# In this respect, the user's attention is drawn to the risks associated
# with loading,  using,  modifying and/or developing or reproducing the
# software by the user in light of its specific status of free software,
# that may mean  that it is complicated to manipulate,  and  that  also
# therefore means  that it is reserved for developers  and  experienced
# professionals having in-depth computer knowledge. Users are therefore
# encouraged to load and test the software's suitability as regards their
# requirements in conditions enabling the security of their systems and/or 
# data to be ensured and,  more generally, to use and operate it in the 
# same conditions as regards security. 
#
# The fact that you are presently reading this means that you have had
# knowledge of the CeCILL license and that you accept its terms.
#
# This code is the property of CEA. The research that allowed the development 
# of this code was partly funded by the French National Research Agency, 
# within the framework of the “Investissements d’avenir” program (ANR-10-AIRT-05). 

option(GCC_COMPILER "Use GCC compiler" ON)

# STM32 build not yet supported in cmake framework : shall be off
option(ARM_STM32_M4 "Target ARM STM32 platform" OFF)

option(LACI_OPTI "Enable optimisation flags" ON)
option(LACI_WARNINGS "Enable lots of additional warning flags" ON)
option(LACI_BUILD_DOC "Build Doxygen Documentation" ON)

option(LACI_HQC "Build HQC implementation" ON)
option(LACI_EXT_LIB "Build external library implementation" ON)

option(LACI_EXT_LIB_NIST_API "Build NIST API (need OpenSSL)" OFF)
option(LACI_EXT_LIB_PQCLEAN_API "Build PQCLEAN API (C generic)" ON)

#STM32 API not yet supported in cmake framework : sall be OFF
option(LACI_EXT_LIB_ARM_STM32_API "Build ARM STM32 API (ASM optimisations)" OFF)

option(LACI_RAND_LINUX "Build random wrapper for Linux random" ON)
option(LACI_RAND_STM32 "Build random wrapper for standard STM32 API" OFF)

option(LACI_CONSANT_TIME_HQC_STM32 "Build constant time sampling" OFF)

