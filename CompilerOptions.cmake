
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
# This work is supported by the French National Research Agency in the framework 
# of the “Programme d’Investissement d’Avenir IRT Nanoelec” (ANR-10-AIRT-05).

set(EXTRA_C_WARNING_FLAGS "")

if(GCC_COMPILER)
    set(CMAKE_C_COMPILER "gcc")
    
    if(LACI_WARNINGS)
        set(GCC_EXTRA_WARNING_FLAGS
            -pedantic
            -Wall
            -Wextra
            -Werror=return-type
            -Werror=address
            -Werror=sequence-point
            -Wundef
            -Winit-self
            -Wpointer-arith
            -Wshadow
            -Wcast-align
            -Wredundant-decls
            )
    else()
        set(GCC_EXTRA_WARNING_FLAGS "")
    endif()
   
    if(LACI_OPTI)
        set(GCC_EXTRA_OPTI_FLAGS 
            -O3
            -funroll-all-loops
            -flto
            )
    else()
        set(GCC_EXTRA_OPTI_FLAGS"" )
    endif()

    add_compile_options(${GCC_EXTRA_OPTI_FLAGS})
    add_compile_options(${GCC_EXTRA_WARNING_FLAGS})
    add_compile_options(-D__GCC__)

    if(${LACI_HQC})
        add_compile_options(-DLACI_HQC)
    endif()
        
     if(LACI_EXT_LIB)
         if(LACI_EXT_LIB_NIST_API)
             add_compile_options(-lcrypto)
             add_compile_options(-DLACI_EXT_LIB_NIST_API)
         elseif(LACI_EXT_LIB_PQCLEAN_API)
             add_compile_options(-DLACI_EXT_LIB_PQCLEAN_API)
         elseif(LACI_EXT_LIB_ARM_STM32_API)
             add_compile_options(-DLACI_EXT_LIB_ARM_STM32_API)
         endif()
    endif()

    if(LACI_RAND_LINUX)
        add_compile_options(-DLACI_LINUX_RAND)
    elseif(LACI_RAND_STM32)
        add_compile_options(-DLACI_STM32_RAND)
    endif()

    if(LACI_CONSTANT_TIME_HQC)
        add_compile_options(-DLACI_CONSANT_TIME_HQC_STM32)
    endif()

endif()



