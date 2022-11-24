
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

if(LACI_EXT_LIB_NIST_API)
    set(SOURCES
        nist_api/fips202/fips202.c 
        nist_api/hash/hash.c
        nist_api/rng/rng.c
        )
    
    set(HEADERS
        nist_api/fips202/fips202.h
        nist_api/hash/hash.h
        nist_api/rng/rng.h
        )


    add_library(ext_lib STATIC ${SOURCES} ${HEADERS})
    
    find_package(OpenSSL REQUIRED)
    if(OPENSSL_FOUND)
        set(OPENSSL_USE_STATIC_LIBS TRUE)
        message("OPENSSL FOUND!")
    endif()
    target_link_libraries(ext_lib OpenSSL::Crypto)
    
    install(FILES
        nist_api/fips/fips202.h
        nist_api/hash/hash.h
        nist_api/rng/rng.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

elseif(LACI_EXT_LIB_PQCLEAN_API)
    set(SOURCES
        pqclean/aes.c
        pqclean/fips202.c
        pqclean/nistseedexpander.c
        pqclean/randombytes.c
        pqclean/sha2.c 
        )
    
    set(HEADERS
        pqclean/aes.h
        pqclean/fips202.h
        pqclean/nistseedexpander.h
        pqclean/randombytes.h
        pqclean/sha2.h 
        )

    add_library(ext_lib STATIC ${SOURCES} ${HEADERS})
    
    install(FILES
        pqclean/aes.h
        pqclean/fips202.h
        pqclean/nistseedexpander.h
        pqclean/randombytes.h
        pqclean/sha2.h 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

elseif(LACI_EXT_LIB_ARM_STM32)

endif()

install(TARGETS ext_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})


