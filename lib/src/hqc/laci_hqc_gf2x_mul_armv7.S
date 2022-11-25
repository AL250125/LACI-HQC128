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

.syntax unified
.thumb
.text

#ifdef LACI_ASM_ARMV7

.macro LACI_HQC_GF2X_CLEAR_RES_100_STEPS
	stmia r0!, {r4-r12, lr}						/* Clear res[i]    - res[i+9] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+10] - res[i+19] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+20] - res[i+29] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+30] - res[i+39] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+40] - res[i+49] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+50] - res[i+59] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+60] - res[i+69] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+70] - res[i+79] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+80] - res[i+89] */
	stmia r0!, {r4-r12, lr}						/* Clear res[i+90] - res[i+99] */
.endm

.macro LACI_HQC_GF2X_MUL_END_STEPS
	/* Loop step */
	ldr r6, [r1], #4						/* Load a[i] */
	ldmia r0, {r9, r10}						/* Load res[i], res[i+1] */

	eor r9, r9, r4							/* r9 <- r9 ^ carry */

	lsl r7, r6, r2							/* r2 <- a[i] << r5 */
	eor r9, r9, r7							/* r9 <- r9 ^ (a[i] << r5) */

	lsr r7, r6, r3							/* r2 <- r6 >> r3 */

	eor r10, r10, r7						/* r10 <- r10 ^ carry */
	stmia r0, {r9, r10}
	/* End loop step */
.endm

.macro LACI_HQC_GF2X_MUL_4_STEPS
	/* Loop step */
	ldmia r1!, {r9, r10, r11, r12}			/* Load a[i], a[i+1], a[i+2], a[i+3] */
	lsl r5, r9, r2							/* r5 <- a[i] << r2 */
	lsl r6, r10, r2							/* r6 <- a[i+1] << r2 */
	lsl r7, r11, r2							/* r7 <- a[i+2] << r2 */
	lsl r8, r12, r2							/* r8 <- a[i+3] << r2 */

	eor r5, r5, r4							/* r5 <- a[i] << r2 ^ carry */

	lsr r9, r9, r3							/* r9 <- a[i] >> r3 */
	lsr r10, r10, r3						/* r10 <- a[i+1] >> r3 */
	lsr r11, r11, r3						/* r11 <- a[i+2] >> r3 */
	lsr r4, r12, r3							/* carry <- a[i+3] >> r3 */

	eor r6, r6, r9							/* r5 <- a[i+1] << r2 ^ a[i] >> r3 */
	eor r7, r7, r10							/* r7 <- a[i+2] << r2 ^ a[i+1] >> r3 */
	eor r8, r8, r11							/* r8 <- a[i+3] << r2 ^ a[i+2] >> r3 */

	ldmia r0, {r9, r10, r11, r12}			/* Load res[i], res[i+1], res[i+2], res[i+3] */

	eor r5, r5, r9							/* res[i] <- res[i] ^ a[i] << r2 ^ carry */
	eor r6, r6, r10							/* res[i+1] <- res[i+1] ^ a[i+1] << r2 ^ a[i] >> r3 */
	eor r7, r7, r11							/* res[i+2] <- res[i+2] ^ a[i+2] << r2 ^ a[i+1] >> r3 */
	eor r8, r8, r12							/* res[i+3] <- res[i+3] ^ a[i+3] << r2 ^ a[i+2] >> r3 */

	stmia r0!, {r5, r6, r7, r8}				/* Store res[i], res[i+1], res[i+2], res[i+2] */
	/* End loop step */
.endm

.macro LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
.endm

.macro LACI_HQC_GF2X_MUL_400_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
.endm

.macro LACI_HQC_GF2X_MUL_552_STEPS
	LACI_HQC_GF2X_MUL_400_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_40_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
	LACI_HQC_GF2X_MUL_4_STEPS
.endm

.align 4
.global laci_hqc_gf2x_mul_asm_armv7
.type	laci_hqc_gf2x_mul_asm_armv7, %function
laci_hqc_gf2x_mul_asm_armv7:

	/**
	*	r0 : res
	*	r1 : a
	* 	r2 : b
	*	r3 : weight
	*/

	push {r4-r12, lr}						/* Store state */

	/* Clear res */
	push {r0}								/* Store res pointer */
	mov r4, #0
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	mov r9, #0
	mov r10, #0
	mov r11, #0
	mov r12, #0
	mov lr, #0
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 100 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 200 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 300 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 400 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 500 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 600 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 700 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 800 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 900 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 1000 cleared words */
	LACI_HQC_GF2X_CLEAR_RES_100_STEPS		/* 1100 cleared words */
	stmia r0!, {r4-r9}						/* 1106 cleared words */
	pop {r0}								/* Restore res pointer */

	subs r3, r3, #1							/* r3 <- weight - 1 */

laci_hqc_gf2x_mul_asm_armv7_loop:
	/* Compute indexes for shift and add */
	ldr r4, [r2], #4						/* r4 <- b[0] */
	push {r0-r3}							/* Save pointers and counter */
	and r2, r4, #0x1f						/* r2 <- r4 mod 32 */
	lsr r4, r4, #5							/* r4 <- r4 / 32 */
	rsb r3, r2, #32							/* r3 <- 32 - r2 */

	add r0, r0, r4, lsl #2					/* Goto wright index */
	mov r4, #0								/* Clear r4 */

	LACI_HQC_GF2X_MUL_552_STEPS
	LACI_HQC_GF2X_MUL_END_STEPS

	pop {r0-r3}								/* Restore pointers and counter */
	subs r3, r3, #1							/* r3 <- weight - 1 */
	bpl laci_hqc_gf2x_mul_asm_armv7_loop 	/* Goto start of the loop */

	pop {r4-r12, lr}						/* Reload state */
	bx lr									/* Return */


#endif
