
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

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(laci 
    VERSION 0.0.1
    LANGUAGES C ASM)

set(CMAKE_C_STANDARD 99)

set(CMAKE_INSTALL_LIBDIR "${PROJECT_BINARY_DIR}/build/lib/")
set(CMAKE_INSTALL_INCLUDEDIR "${PROJECT_BINARY_DIR}/build/include/")
set(CMAKE_INSTALL_TESTDIR "${PROJECT_BINARY_DIR}/build/test/")

include(CMakeConfig.cmake)
include(CompilerOptions.cmake)

if(ARM_STM32)
    set(TARGET "ARM STM32")    
else()
    message(WARNING "TARGET variable unspecified, using default value 'generic'")
    set(TARGET "generic")
endif()

if(LACI_BUILD_DOC)
    message(STATUS "Add documentation build target")
    set(doxyfile_in ${PROJECT_BINARY_DIR}/doc/Doxyfile.in)
    set(doxyfile ${PROJECT_BINARY_DIR}/doc/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    
    add_custom_target(doc
        COMMAND doxygen ${doxyfile}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc
        COMMENT "Generate API documentation"
        VERBATIM)
endif()

message(STATUS "Building for TARGET=${TARGET}")

if(LACI_EXT_LIB)
    add_subdirectory(ext_lib)
endif()

add_subdirectory(lib)

