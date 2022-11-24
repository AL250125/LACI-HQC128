
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
#
#
# This code is the property of CEA. It shall be subject to the obligations 
# of the contract CEA/ANR: Convention de Financementi ANR-10-AIRT-05 and of 
# the IRT Nanoelec consortium agreement Ref C17848 and its Appendices. 
# 
# Ce code est la propriété de CEA. Il est soumis aux obligations de la convention 
# CEA /ANR : Convention de Financement ANR-10-AIRT-05 et à l’accord de 
# consortium IRT Nanoelec Ref. C17848 et ses avenants.


set(SOURCES
    src/misc/laci_misc.c
    src/misc/laci_memory.c
    src/random/laci_random.c
    )

set(HEADERS
    inc/laci.h
    inc/laci_arch.h
    inc/laci_config.h
    inc/laci_error.h
    inc/laci_io.h
    inc/laci_memory.h
    inc/laci_misc.h
    inc/laci_random.h
    inc/laci_types.h
    )

if(${LACI_HQC})
    set(SOURCES
        ${SOURCES}
        src/hqc/laci_hqc_fft.c
        src/hqc/laci_hqc_gf256.c
        src/hqc/laci_hqc_gf2x.c
        src/hqc/laci_hqc_io.c
        src/hqc/laci_hqc_kem.c
        src/hqc/laci_hqc_memory.c
        src/hqc/laci_hqc_pke.c
        src/hqc/laci_hqc_reed_muller.c
        src/hqc/laci_hqc_reed_solomon.c
        )
    
    set(HEADERS
        ${HEADERS}
        inc/hqc/laci_hqc_fft.h 
        inc/hqc/laci_hqc_gf256.h
        inc/hqc/laci_hqc_gf2x.h
        inc/hqc/laci_hqc_io.h
        inc/hqc/laci_hqc_kem.h
        inc/hqc/laci_hqc_memory.h
        inc/hqc/laci_hqc_pke.h
        inc/hqc/laci_hqc_param.h
        inc/hqc/laci_hqc_reed_muller.h
        inc/hqc/laci_hqc_reed_solomon.h
        )
endif()

add_library(laci STATIC ${SOURCES} ${HEADERS})
if(${LACI_EXT_LIB})
    target_link_libraries(laci ext_lib)
endif()

target_include_directories(laci PUBLIC inc inc/hqc)

if(${LACI_EXT_LIB})
    if(LACI_EXT_LIB_NIST_API)
        target_include_directories(laci PUBLIC ../ext_lib/nist_api/fips202 ../ext_lib/nist_api/hash ../ext_lib/nist_api/rng)
    elseif(LACI_EXT_LIB_PQCLEAN_API)
        target_include_directories(laci PUBLIC ../ext_lib/pqclean)
    elseif(LACI_EXT_LIB_ARM_STM32)

    endif()
endif()

install(FILES
    inc/laci.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS laci
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

