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

.macro LACI_HQC_RM_ACC_BIT 		dst:req, a:req, b:req, c:req
	lsrs \a, \a, #1						/* Extract LSB in carry flag */
	adc	\dst, \dst, #0					/* Accumulate extracted bit */
	lsrs \b, \b, #1						/* Extract LSB in carry flag */
	adc	\dst, \dst, #0					/* Accumulate extracted bit */
	lsrs \c, \c, #1						/* Extract LSB in carry flag */
	adc	\dst, \dst, #0					/* Accumulate extracted bit */
.endm


.macro LACI_HQC_RM_ACC_12_INT16
	mov r5, #0						/* Clear r5 */
	mov r6, #0						/* Clear r6 */
	mov r7, #0						/* Clear r7 */
	mov r8, #0						/* Clear r8 */
	mov r9, #0						/* Clear r9 */
	mov r10, #0						/* Clear r10 */
	mov r11, #0						/* Clear r11 */
	mov r12, #0						/* Clear r12 */
	mov lr, #0						/* Clear lr */

	/* Compute ex_codeword[0] .. ex_codeword[3] */
	LACI_HQC_RM_ACC_BIT r5, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r6, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r7, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r8, r2, r3, r4
	orr r5, r5, r6, lsl #16
	orr r6, r7, r8, lsl #16

	/* Compute ex_codeword[4] .. ex_codeword[7] */
	LACI_HQC_RM_ACC_BIT r9, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r10, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r11, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r12, r2, r3, r4
	orr r7, r9, r10, lsl #16
	orr r8, r11, r12, lsl #16

	mov r9, #0						/* Clear r9 */
	mov r10, #0						/* Clear r10 */
	mov r11, #0						/* Clear r11 */
	mov r12, #0						/* Clear r12 */

	/* Compute ex_codeword[8] .. ex_codeword[11] */
	LACI_HQC_RM_ACC_BIT r9, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r10, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r11, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r12, r2, r3, r4
	orr r9, r9, r10, lsl #16
	orr r10, r11, r12, lsl #16

	stmia r0!, {r5, r6, r7, r8, r9, r10} 			/* Store 12 int16 of ex_codeword */
.endm


.macro LACI_HQC_RM_ACC_8_INT16
	mov r5, #0						/* Clear r5 */
	mov r6, #0						/* Clear r6 */
	mov r7, #0						/* Clear r7 */
	mov r8, #0						/* Clear r8 */
	mov r9, #0						/* Clear r9 */
	mov r10, #0						/* Clear r10 */
	mov r11, #0						/* Clear r11 */
	mov r12, #0						/* Clear r12 */
	mov lr, #0						/* Clear lr */

	/* Compute ex_codeword[0] .. ex_codeword[3] */
	LACI_HQC_RM_ACC_BIT r5, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r6, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r7, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r8, r2, r3, r4
	orr r5, r5, r6, lsl #16
	orr r6, r7, r8, lsl #16

	/* Compute ex_codeword[4] .. ex_codeword[7] */
	LACI_HQC_RM_ACC_BIT r9, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r10, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r11, r2, r3, r4
	LACI_HQC_RM_ACC_BIT r12, r2, r3, r4
	orr r7, r9, r10, lsl #16
	orr r8, r11, r12, lsl #16

	stmia r0!, {r5, r6, r7, r8}				/* Store 8 int16 of ex_codeword */
.endm


.align 4
.global expand_and_sum_rm_asm_armv7
.type	expand_and_sum_rm_asm_armv7, %function;
expand_and_sum_rm_asm_armv7:
	/**
	*	r0 : ex_codeword
	*	r1 : codeword
	*/

	push {r4-r12, lr}

	ldr r2, [r1]						/* Load codeword[0] */
	ldr r3, [r1, #16]					/* Load codeword[4] */
	ldr r4, [r1, #32]					/* Load codeword[8] */
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_8_INT16

	ldr r2, [r1, #4]					/* Load codeword[1] */
	ldr r3, [r1, #20]					/* Load codeword[5] */
	ldr r4, [r1, #36]					/* Load codeword[9] */
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_8_INT16

	ldr r2, [r1, #8]					/* Load codeword[2] */
	ldr r3, [r1, #24]					/* Load codeword[6] */
	ldr r4, [r1, #40]					/* Load codeword[10] */
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_8_INT16

	ldr r2, [r1, #12]					/* Load codeword[3] */
	ldr r3, [r1, #28]					/* Load codeword[7] */
	ldr r4, [r1, #44]					/* Load codeword[11] */
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_12_INT16
	LACI_HQC_RM_ACC_8_INT16

	pop {r4-r12, lr}
	bx lr


.macro LACI_HQC_RM_HAD_STEP
	ldmia r1!, {r5, r6, r7, r8, r9, r10, r11, r12} 	/* Load a[i] - a[i+16] */

	/* res[i] - res[i+3] */
	add r2, r5, r5, lsr #16			/* r2 <- a[i] + a[i+1] */
	sub r3, r5, r5, lsr #16			/* r3 <- a[i] - a[i+1] */
	add r4, r6, r6, lsr #16			/* r4 <- a[i+2] + a|i+3] */
	sub r5, r6, r6, lsr #16			/* r5 <- a[i+2] - a|i+3] */
	bfi r2, r4, #16, #16			/* r2 <- (a[i+2] + a[i+3]) << 16 | (a[i] + a[i+1])  */
	bfi r3, r5, #16, #16			/* r3 <- (a[i+2] - a[i+3]) << 16 | (a[i] - a[i+1]) */

	/* res[i+4] - res[i+7] */
	add r4, r7, r7, lsr #16			/* r4 <- a[i+4] + a[i+5] */
	sub r5, r7, r7, lsr #16			/* r5 <- a[i+4] - a[i+5] */
	add r6, r8, r8, lsr #16			/* r6 <- a[i+6] + a|i+7] */
	sub r7, r8, r8, lsr #16			/* r7 <- a[i+6] - a|i+7] */
	bfi r4, r6, #16, #16			/* r4 <- (a[i+6] + a[i+7]) << 16 | (a[i+4] + a[i+5])  */
	bfi r5, r7, #16, #16			/* r5 <- (a[i+6] - a[i+7]) << 16 | (a[i+4] - a[i+5]) */

	/* res[i+8] - res[i+11] */
	add r6, r9, r9, lsr #16			/* r6 <- a[i+8] + a[i+9] */
	sub r7, r9, r9, lsr #16			/* r7 <- a[i+8] - a[i+9] */
	add r8, r10, r10, lsr #16		/* r8 <- a[i+10] + a|i+11] */
	sub r9, r10, r10, lsr #16		/* r9 <- a[i+10] - a|i+11] */
	bfi r6, r8, #16, #16			/* r6 <- (a[i+10] + a[i+11]) << 16 | (a[i+8] + a[i+9])  */
	bfi r7, r9, #16, #16			/* r7 <- (a[i+10] - a[i+11]) << 16 | (a[i+8] - a[i+9]) */

	/* res[i+12] - res[i+15] */
	add r8, r11, r11, lsr #16		/* r8 <- a[i+12] + a[i+13] */
	sub r9, r11, r11, lsr #16		/* r9 <- a[i+12] - a[i+13] */
	add r10, r12, r12, lsr #16		/* r10 <- a[i+14] + a|i+15] */
	sub r11, r12, r12, lsr #16		/* r11 <- a[i+14] - a|i+15] */
	bfi r8, r10, #16, #16			/* r8 <- (a[i+14] + a[i+15]) << 16 | (a[i+12] + a[i+13])  */
	bfi r9, r11, #16, #16			/* r9 <- (a[i+14] - a[i+15]) << 16 | (a[i+12] - a[i+13]) */

	add r10, r0, #128
	stmia r0!, {r2, r4, r6, r8}
	stmia r10, {r3, r5, r7, r9}
.endm

.align 4
.global hadamard_transform_asm_armv7
.type	hadamard_transform_asm_armv7, %function;
hadamard_transform_asm_armv7:
	/**
	*	r0 : ex_codeword
	*	r1 : had_ex_codeword
	*/

	push {r4-r12, lr}

	mov r2, #7

	/* Loop */
hadamard_transform_asm_loop:
	push {r2}

	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP
	LACI_HQC_RM_HAD_STEP

	sub r0, r0, #128
	sub r1, r1, #256
	mov r2, r1
	mov r1, r0
	mov r0, r2

	pop {r2}
	sub r2, r2, #1
	cmp r2, #0
	bne hadamard_transform_asm_loop

	pop {r4-r12, lr}
	bx lr


.macro LACI_HQC_RM_ABS_STEP reg:req
	bic r4, r2, \reg		/* Find byte sign */
	lsr r4, r4, 15
	ssub16 r4, r3, r4		/* Compute sign mask */
	ssub16 r5, r4, \reg
	eor \reg, r5, r4		/* Absolute value */
.endm

.macro LACI_HQC_RM_ABS
	mov r2, #0x80008000
	mov r3, #0
	LACI_HQC_RM_ABS_STEP r6
	LACI_HQC_RM_ABS_STEP r7
	LACI_HQC_RM_ABS_STEP r8
	LACI_HQC_RM_ABS_STEP r9
	LACI_HQC_RM_ABS_STEP r10
	LACI_HQC_RM_ABS_STEP r11
	LACI_HQC_RM_ABS_STEP r12
	LACI_HQC_RM_ABS_STEP lr
.endm

.macro LACI_HQC_RM_CMP_PEAK 	reg:req, shift:req, cnt:req
	and r4, r3, \reg, lsr \shift		/* Extract a[i] */
	cmp r4, r2							/* Compare abs_max_value to a[i] */
	itt	hi
	movhi r2, r4						/* Update abs_max_value */
	movhi r1, \cnt						/* Update idx */
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L1
	LACI_HQC_RM_CMP_PEAK r6, #16, #1

	LACI_HQC_RM_CMP_PEAK r7, #0, #2
	LACI_HQC_RM_CMP_PEAK r7, #16, #3

	LACI_HQC_RM_CMP_PEAK r8, #0, #4
	LACI_HQC_RM_CMP_PEAK r8, #16, #5

	LACI_HQC_RM_CMP_PEAK r9, #0, #6
	LACI_HQC_RM_CMP_PEAK r9, #16, #7

	LACI_HQC_RM_CMP_PEAK r10, #0, #8
	LACI_HQC_RM_CMP_PEAK r10, #16, #9

	LACI_HQC_RM_CMP_PEAK r11, #0, #10
	LACI_HQC_RM_CMP_PEAK r11, #16, #11

	LACI_HQC_RM_CMP_PEAK r12, #0, #12
	LACI_HQC_RM_CMP_PEAK r12, #16, #13

	LACI_HQC_RM_CMP_PEAK lr, #0, #14
	LACI_HQC_RM_CMP_PEAK lr, #16, #15
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L2
	LACI_HQC_RM_CMP_PEAK r6, #0, #16
	LACI_HQC_RM_CMP_PEAK r6, #16, #17

	LACI_HQC_RM_CMP_PEAK r7, #0, #18
	LACI_HQC_RM_CMP_PEAK r7, #16, #19

	LACI_HQC_RM_CMP_PEAK r8, #0, #20
	LACI_HQC_RM_CMP_PEAK r8, #16, #21

	LACI_HQC_RM_CMP_PEAK r9, #0, #22
	LACI_HQC_RM_CMP_PEAK r9, #16, #23

	LACI_HQC_RM_CMP_PEAK r10, #0, #24
	LACI_HQC_RM_CMP_PEAK r10, #16, #25

	LACI_HQC_RM_CMP_PEAK r11, #0, #26
	LACI_HQC_RM_CMP_PEAK r11, #16, #27

	LACI_HQC_RM_CMP_PEAK r12, #0, #28
	LACI_HQC_RM_CMP_PEAK r12, #16, #29

	LACI_HQC_RM_CMP_PEAK lr, #0, #30
	LACI_HQC_RM_CMP_PEAK lr, #16, #31
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L3
	LACI_HQC_RM_CMP_PEAK r6, #0, #32
	LACI_HQC_RM_CMP_PEAK r6, #16, #33

	LACI_HQC_RM_CMP_PEAK r7, #0, #34
	LACI_HQC_RM_CMP_PEAK r7, #16, #35

	LACI_HQC_RM_CMP_PEAK r8, #0, #36
	LACI_HQC_RM_CMP_PEAK r8, #16, #37

	LACI_HQC_RM_CMP_PEAK r9, #0, #38
	LACI_HQC_RM_CMP_PEAK r9, #16, #39

	LACI_HQC_RM_CMP_PEAK r10, #0, #40
	LACI_HQC_RM_CMP_PEAK r10, #16, #41

	LACI_HQC_RM_CMP_PEAK r11, #0, #42
	LACI_HQC_RM_CMP_PEAK r11, #16, #43

	LACI_HQC_RM_CMP_PEAK r12, #0, #44
	LACI_HQC_RM_CMP_PEAK r12, #16, #45

	LACI_HQC_RM_CMP_PEAK lr, #0, #46
	LACI_HQC_RM_CMP_PEAK lr, #16, #47
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L4
	LACI_HQC_RM_CMP_PEAK r6, #0, #48
	LACI_HQC_RM_CMP_PEAK r6, #16, #49

	LACI_HQC_RM_CMP_PEAK r7, #0, #50
	LACI_HQC_RM_CMP_PEAK r7, #16, #51

	LACI_HQC_RM_CMP_PEAK r8, #0, #52
	LACI_HQC_RM_CMP_PEAK r8, #16, #53

	LACI_HQC_RM_CMP_PEAK r9, #0, #54
	LACI_HQC_RM_CMP_PEAK r9, #16, #55

	LACI_HQC_RM_CMP_PEAK r10, #0, #56
	LACI_HQC_RM_CMP_PEAK r10, #16, #57

	LACI_HQC_RM_CMP_PEAK r11, #0, #58
	LACI_HQC_RM_CMP_PEAK r11, #16, #59

	LACI_HQC_RM_CMP_PEAK r12, #0, #60
	LACI_HQC_RM_CMP_PEAK r12, #16, #61

	LACI_HQC_RM_CMP_PEAK lr, #0, #62
	LACI_HQC_RM_CMP_PEAK lr, #16, #63
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L5
	LACI_HQC_RM_CMP_PEAK r6, #0, #64
	LACI_HQC_RM_CMP_PEAK r6, #16, #65

	LACI_HQC_RM_CMP_PEAK r7, #0, #66
	LACI_HQC_RM_CMP_PEAK r7, #16, #67

	LACI_HQC_RM_CMP_PEAK r8, #0, #68
	LACI_HQC_RM_CMP_PEAK r8, #16, #69

	LACI_HQC_RM_CMP_PEAK r9, #0, #70
	LACI_HQC_RM_CMP_PEAK r9, #16, #71

	LACI_HQC_RM_CMP_PEAK r10, #0, #72
	LACI_HQC_RM_CMP_PEAK r10, #16, #73

	LACI_HQC_RM_CMP_PEAK r11, #0, #74
	LACI_HQC_RM_CMP_PEAK r11, #16, #75

	LACI_HQC_RM_CMP_PEAK r12, #0, #76
	LACI_HQC_RM_CMP_PEAK r12, #16, #77

	LACI_HQC_RM_CMP_PEAK lr, #0, #78
	LACI_HQC_RM_CMP_PEAK lr, #16, #79
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L6
	LACI_HQC_RM_CMP_PEAK r6, #0, #80
	LACI_HQC_RM_CMP_PEAK r6, #16, #81

	LACI_HQC_RM_CMP_PEAK r7, #0, #82
	LACI_HQC_RM_CMP_PEAK r7, #16, #83

	LACI_HQC_RM_CMP_PEAK r8, #0, #84
	LACI_HQC_RM_CMP_PEAK r8, #16, #85

	LACI_HQC_RM_CMP_PEAK r9, #0, #86
	LACI_HQC_RM_CMP_PEAK r9, #16, #87

	LACI_HQC_RM_CMP_PEAK r10, #0, #88
	LACI_HQC_RM_CMP_PEAK r10, #16, #89

	LACI_HQC_RM_CMP_PEAK r11, #0, #90
	LACI_HQC_RM_CMP_PEAK r11, #16, #91

	LACI_HQC_RM_CMP_PEAK r12, #0, #92
	LACI_HQC_RM_CMP_PEAK r12, #16, #93

	LACI_HQC_RM_CMP_PEAK lr, #0, #94
	LACI_HQC_RM_CMP_PEAK lr, #16, #95
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L7
	LACI_HQC_RM_CMP_PEAK r6, #0, #96
	LACI_HQC_RM_CMP_PEAK r6, #16, #97

	LACI_HQC_RM_CMP_PEAK r7, #0, #98
	LACI_HQC_RM_CMP_PEAK r7, #16, #99

	LACI_HQC_RM_CMP_PEAK r8, #0, #100
	LACI_HQC_RM_CMP_PEAK r8, #16, #101

	LACI_HQC_RM_CMP_PEAK r9, #0, #102
	LACI_HQC_RM_CMP_PEAK r9, #16, #103

	LACI_HQC_RM_CMP_PEAK r10, #0, #104
	LACI_HQC_RM_CMP_PEAK r10, #16, #105

	LACI_HQC_RM_CMP_PEAK r11, #0, #106
	LACI_HQC_RM_CMP_PEAK r11, #16, #107

	LACI_HQC_RM_CMP_PEAK r12, #0, #108
	LACI_HQC_RM_CMP_PEAK r12, #16, #109

	LACI_HQC_RM_CMP_PEAK lr, #0, #110
	LACI_HQC_RM_CMP_PEAK lr, #16, #111
.endm

.macro LACI_HQC_RM_CMP_PEAK_LOOP_L8
	LACI_HQC_RM_CMP_PEAK r6, #0, #112
	LACI_HQC_RM_CMP_PEAK r6, #16, #113

	LACI_HQC_RM_CMP_PEAK r7, #0, #114
	LACI_HQC_RM_CMP_PEAK r7, #16, #115

	LACI_HQC_RM_CMP_PEAK r8, #0, #116
	LACI_HQC_RM_CMP_PEAK r8, #16, #117

	LACI_HQC_RM_CMP_PEAK r9, #0, #118
	LACI_HQC_RM_CMP_PEAK r9, #16, #119

	LACI_HQC_RM_CMP_PEAK r10, #0, #120
	LACI_HQC_RM_CMP_PEAK r10, #16, #121

	LACI_HQC_RM_CMP_PEAK r11, #0, #122
	LACI_HQC_RM_CMP_PEAK r11, #16, #123

	LACI_HQC_RM_CMP_PEAK r12, #0, #124
	LACI_HQC_RM_CMP_PEAK r12, #16, #125

	LACI_HQC_RM_CMP_PEAK lr, #0, #126
	LACI_HQC_RM_CMP_PEAK lr, #16, #127
.endm

.align 4
.global find_peak_asm_armv7
.type	find_peak_asm_armv7, %function;
find_peak_asm_armv7:
	/*
	 *	r0 : had_ex_codeword
	 */

	push {r4-r12, lr}

	/* Loop 1 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[0] .. a[15] */
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[0] .. a[15] */
	mov r3, #0xFFFF
	mov r1, #0					/* Init max idx to 0 */
	and r2, r6, r3				/* Init max abs value to |a[0]| */
	LACI_HQC_RM_CMP_PEAK_LOOP_L1

	/* Loop 2 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[16] .. a[31] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[16] .. a[31] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L2

	/* Loop 3 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[32] .. a[47] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[32] .. a[47] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L3

	/* Loop 4 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[48] .. a[63] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[48] .. a[63] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L4

	/* Loop 5 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[64] .. a[79] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[64] .. a[79] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L5

	/* Loop 6 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[80] .. a[95] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[90] .. a[95] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L6

	/* Loop 7 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[96] .. a[111] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[96] .. a[111] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L7

	/* Loop 8 */
	ldmia r0!,{r6, r7, r8, r9, r10, r11, r12, lr}		/* Load a[112] .. a[127] */
	push {r2}
	LACI_HQC_RM_ABS				/* Compute the absolute value of a[11] .. a[127] */
	pop {r2}
	mov r3, #0xFFFF
	LACI_HQC_RM_CMP_PEAK_LOOP_L8

	sub r0, r0, #256
	add r0, r0, r1, lsl #1
	ldrh r2, [r0]			/* Load the right value */
	mov r3, #0x8000
	bic r3, r3, r2			/* Test if positive */
	orr r0, r1, r3, lsr #8	/* Return value */

	pop {r4-r12, lr}
	bx lr


#endif
