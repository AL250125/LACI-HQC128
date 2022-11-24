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

.macro LACI_HQC_GF2X_RDC_6_STEPS
	ldmia r1!, {r8-r12, lr}					/* Load a[i+553]..a[i+558] */
	eor r2, r2, r8,	lsl #27					/* res[i-1] <- a[i-1] ^ (a[i+551] >> 5) ^ (a[i+552] << 27) */
	str r2, [r0], #4						/* Store res[i-1] */
	sub r1, r1, #2232						/* Go to a[i] */
	ldmia r1!, {r2-r7}						/* Load a[i]..a[i+5] */

	eor r2, r2, r8, lsr #5					/* res[i] <- a[i] ^ (a[i+553] >> 5) */
	eor r2, r2, r9, lsl #27					/* res[i] <- a[i] ^ (a[i+553] >> 5) ^ (a[i+554] << 27) */
	eor r3, r3, r9, lsr #5					/* res[i+1] <- a[i+1] ^ (a[i+554] >> 5) */
	eor r3, r3, r10, lsl #27				/* res[i+1] <- a[i+1] ^ (a[i+554] >> 5) ^ (a[i+555] << 27) */
	eor r4, r4, r10, lsr #5					/* res[i+2] <- a[i+2] ^ (a[i+555] >> 5) */
	eor r4, r4, r11, lsl #27				/* res[i+2] <- a[i+2] ^ (a[i+555] >> 5) ^ (a[i+556] << 27) */
	eor r5, r5, r11, lsr #5					/* res[i+3] <- a[i+3] ^ (a[i+556] >> 5) */
	eor r5, r5, r12, lsl #27				/* res[i+3] <- a[i+3] ^ (a[i+556] >> 5) ^ (a[i+557] << 27) */
	eor r6, r6, r12, lsr #5					/* res[i+4] <- a[i+4] ^ (a[i+557] >> 5) */
	eor r6, r6, lr, lsl #27					/* res[i+4] <- a[i+4] ^ (a[i+557] >> 5) ^ (a[i+558] << 27) */
	stmia r0!, {r2-r6}						/* Store res[i]..res[i+4] */
	eor r2, r7, lr, lsr #5					/* res[i+5] <- a[i+5] ^ (a[i+558] >> 5) */
	add r1, r1, #2208
.endm

.macro LACI_HQC_GF2X_RDC_60_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
	LACI_HQC_GF2X_RDC_6_STEPS
.endm

.macro LACI_HQC_GF2X_RDC_540_STEPS
	LACI_HQC_GF2X_RDC_60_STEPS				/* 60 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 120 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 180 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 240 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 300 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 360 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 420 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 480 Steps */
	LACI_HQC_GF2X_RDC_60_STEPS				/* 540 Steps */
.endm

.align 4
.global laci_hqc_gf2x_reduce_asm_armv7
.type	laci_hqc_gf2x_reduce_asm_armv7, %function
laci_hqc_gf2x_reduce_asm_armv7:
	/*
	 * r0 : res
	 * r1 : a
	 *
	 * index = (552 << 2) = 2208
	 * pos = 5
	 */

	push {r4-r12, lr}						/* Store state */

	/* The sixth first steps */
	ldmia r1, {r2-r7}						/* Load a[0]..a[5] */
	add r1, r1, #2208						/* Go to a[552] */
	ldmia r1!, {r8-r12, lr}					/* Load a[552]..a[557] */

	eor r2, r2, r8, lsr #5					/* res[0] <- a[0] ^ (a[552] >> 5) */
	eor r2, r2, r9, lsl #27					/* res[0] <- a[0] ^ (a[552] >> 5) ^ (a[553] << 27) */
	eor r3, r3, r9, lsr #5					/* res[1] <- a[1] ^ (a[553] >> 5) */
	eor r3, r3, r10, lsl #27				/* res[1] <- a[1] ^ (a[553] >> 5) ^ (a[554] << 27) */
	eor r4, r4, r10, lsr #5					/* res[2] <- a[2] ^ (a[554] >> 5) */
	eor r4, r4, r11, lsl #27				/* res[2] <- a[2] ^ (a[554] >> 5) ^ (a[555] << 27) */
	eor r5, r5, r11, lsr #5					/* res[3] <- a[3] ^ (a[555] >> 5) */
	eor r5, r5, r12, lsl #27				/* res[3] <- a[3] ^ (a[555] >> 5) ^ (a[556] << 27) */
	eor r6, r6, r12, lsr #5					/* res[4] <- a[4] ^ (a[556] >> 5) */
	eor r6, r6, lr, lsl #27					/* res[4] <- a[4] ^ (a[556] >> 5) ^ (a[556] << 27) */
	stmia r0!, {r2-r6}						/* Store res[0]..res[4] */
	eor r2, r7, lr, lsr #5					/* res[5] <- a[5] ^ (a[557] >> 5) */

	LACI_HQC_GF2X_RDC_540_STEPS				/* 546 Steps */
	LACI_HQC_GF2X_RDC_6_STEPS				/* 552 Steps */

	ldmia r1!, {r8, r9}						/* Load a[1104], a[1105] */
	sub r1, r1, #2216						/* Go to a[551] */
	ldr r3, [r1]							/* Load a[552] */

	//eor r2, r2, r8, lsr #5					/* res[551] <- a[551] ^ (a[1104] >> 5) */
	eor r2, r2, r8, lsl #27					/* res[551] <- a[551] ^ (a[1104] >> 5) ^ (a[1105] << 27) */
	eor r3, r3, r9, lsr #5					/* res[552] <- a[552] ^ (a[1105] >> 5) */
	and r3, r3, #0x0000001f
	stmia r0, {r2, r3}						/* Store res[551], res[552] */

	pop {r4-r12, lr}						/* Reload state */
	bx lr									/* Return */


#endif
