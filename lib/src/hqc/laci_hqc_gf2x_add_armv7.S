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

.syntax unified
.thumb
.text

#ifdef LACI_ASM_ARMV7

.macro LACI_HQC_GF2X_ADD_5_STEPS
	ldmia r1!, {r3, r4, r5, r6, r7}
	ldmia r2!, {r8, r9, r10, r11, r12}
	eor r3, r3, r8
	eor r4, r4, r9
	eor r5, r5, r10
	eor r6, r6, r11
	eor r7, r7, r12
	stmia r0!, {r3, r4, r5, r6, r7}
.endm

.macro LACI_HQC_GF2X_ADD_50_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
	LACI_HQC_GF2X_ADD_5_STEPS
.endm

.align 4
.global laci_hqc_gf2x_add_asm_armv7
.type	laci_hqc_gf2x_add_asm_armv7, %function
laci_hqc_gf2x_add_asm_armv7:
	push {r4-r12}							/* Store state */

	LACI_HQC_GF2X_ADD_50_STEPS				/* 50 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 100 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 150 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 200 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 250 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 300 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 350 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 400 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 450 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 500 steps */
	LACI_HQC_GF2X_ADD_50_STEPS				/* 550 steps */

	pop {r4-r12}							/* Reload state */
	bx lr									/* Return */

#endif

