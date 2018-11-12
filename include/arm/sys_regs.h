/**
 * @file include/arm/sys_regs.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_ARM_SYS_REGS_H__
#define __MCUBE_ARM_SYS_REGS_H__

/* CNTV_CTL_EL0, Counter-timer Virtual Timer Control register
 * Page 2188 of AArch64-Reference-Manual.
 */
/* 31-3: reserved */
/* 2: ISTATUS
 * The status of the timer interrupt. This bit is read-only. Permitted values are:
 * 0 : Interrupt not asserted.
 * 1 : Interrupt asserted.
 * A register write that sets IMASK to 1 latches this bit to reflect the status
 * of the interrupt immediately before that write.
 * Reset value is architecturally UNKNOWN.
 */
#define CNTV_CTL_EL0_ISTATUS_NOT_ASSERTED (0x0 << 2)
#define CNTV_CTL_EL0_ISTATUS_ASSERTED (0x1 << 2)
/* 1: IMASK
 * Timer interrupt mask bit. Permitted values are:
 * 0 : Timer interrupt is not masked.
 * 1 : Timer interrupt is masked.
 * Reset value is architecturally UNKNOWN.
 */
#define CNTV_CTL_EL0_IMASK_NOT_MASKED (0x0 << 1)
#define CNTV_CTL_EL0_IMASK_MASKED (0x1 << 1)
/* 0: ENABLE
 * Enables the timer. Permitted values are:
 * 0 : Timer disabled.
 * 1 : Timer enabled.
 * Disabling the timer masks the timer interrupt, but the timer value
 * continues to count down. Resets to 0.
 */
#define CNTV_CTL_EL0_DISABLE (0x0 << 0)
#define CNTV_CTL_EL0_ENABLE (0x1 << 0)


/* ESR_EL1, Exception Syndrome Register (EL1).
 * Page 1899 of AArch64-Reference-Manual.
 */
/* 31-26: Exception Class.
 * Indicates the reason for the exception that this register holds information about.
 */
#define ESR_ELx_EC_SHIFT 26

#define ESR_ELx_EC_UNKNOWN_REASON 0x1
#define ESR_ELx_EC_WFI_OR_WFE_INSTRUCTION_EXCEPTION 0x2
#define ESR_ELx_EC_MCR_OR_MRC_ACCESS_TO_CP15 0x3
#define ESR_ELx_EC_MCRR_OR_MRRC_ACCESS_TO_CP15 0x4
#define ESR_ELx_EC_MCR_OR_MRC_ACCESS_TO_CP14 0x5
#define ESR_ELx_EC_LDC_OR_STC_ACCESS_TO_CP14 0x6
#define ESR_ELx_EC_ACCESS_TO_SIMD_OR_FP_REG 0x7
#define ESR_ELx_EC_MCR_MRC_ACCESS_TO_CP10 0x8
/* 0x9-0xb: reserved */
#define ESR_ELx_EC_MRRC_ACCESS_TO_CP14 0xc
/* 0xd: reserved */
#define ESR_ELx_EC_ILLEGAL_EXECUTION_STATE 0xe
#define ESR_ELx_EC_SVC_INSTRUCTION_EXCEPTION32 0x11
#define ESR_ELx_EC_HVC_INSTRUCTION_EXCEPTION32 0x12
#define ESR_ELx_EC_SMC_INSTRUCTION_EXCEPTION32 0x13
/* 0x14: reserved */
#define ESR_ELx_EC_SVC_INSTRUCTION_EXCEPTION64 0x15
#define ESR_ELx_EC_HVC_INSTRUCTION_EXCEPTION64 0x16
#define ESR_ELx_EC_SMC_INSTRUCTION_EXCEPTION64 0x17
#define ESR_ELx_EC_MSR_MRS_SYSTEM_EXCEPTION64 0x18
/* 0x19-0x1f: reserved */
#define ESR_ELx_EC_INSTRUCTION_ABORT_FROM_LOWER_EXCEPTION_LEVEL 0x20
#define ESR_ELx_EC_INSTRUCTION_ABORT_TAKEN_WITHOUT_A_CHANGE_IN_EXCEPTION_LEVEL 0x21
#define ESR_ELx_EC_MISALIGNED_PC_EXCEPTION 0x22
/* 0x23: reserved */
#define ESR_ELx_EC_DATA_ABORT_FROM_A_LOWER_EXCEPTION_LEVEL 0x24
#define ESR_ELx_EC_DATA_ABORT_TAKEN_WITHOUT_A_CHANGE_IN_EXCEPTION_LEVEL 0x25
#define ESR_ELx_EC_STACK_POINTER_ALIGNMENT_EXCEPTION 0x26
/* 0x27: reserved */
#define ESR_ELx_EC_FLOATING_POINT_EXCEPTION32 0x28
/* 0x29-0x2b: reserved */
#define ESR_ELx_EC_FLOATING_POINT_EXCEPTION64 0x2c
/* 0x2d-0x2e: reserved */
#define ESR_ELx_EC_SERROR_INTERRUPT 0x2f
#define ESR_ELx_EC_BREAKPOINT_EXCEPTION_FROM_A_LOWER_EXCEPTION_LEVEL 0x30
#define ESR_ELx_EC_BREAKPOINT_EXCEPTION_WITHOUT_A_CHANGE_IN_EXCEPTION_LEVEL 0x31
#define ESR_ELx_EC_SOFTWARE_STEP_EXCEPTION_FROM_A_LOWER_EXCEPTION_LEVEL 0x32
#define ESR_ELx_EC_SOFTWARE_STEP_EXCEPTION_TAKEN_WITHOUT_A_CHANGE_IN_EXCEPTION_LEVEL 0x33
#define ESR_ELx_EC_WATCHPOINT_EXCEPTION_FROM_A_LOWER_EXCEPTION_LEVEL 0x34
#define ESR_ELx_EC_WATCHPOINT_EXCEPTION_WITHOUT_A_CHANGE_IN_EXCEPTION_LEVEL 0x35
/* 0x36-0x37: reserved */
#define ESR_ELx_EC_BKPT_INSTRUCTION_EXCEPTION 0x38
/* 0x39: reserved */
#define ESR_ELx_EC_VECTOR_CATCH_EXCEPTION_FROM_AARCH32_STATE 0x3a
/* 0x3b: reserved */
#define ESR_ELx_EC_BRK_INSTRUCTION_EXCEPTION 0x3c
/* 0x3d-0x3f: reserved */


/* 25: Instruction Length for synchronous exceptions. Possible values of this bit are:
 * 0 16-bit instruction trapped.
 * 1 32-bit instruction trapped. This value also applies to the following exceptions:
 ** An SError interrupt.
 ** An Instruction Abort exception.
 ** A Misaligned PC exception.
 ** A Misaligned Stack Pointer exception.
 ** A Data Abort for which the value of the ISV bit is 0.
 ** An Illegal Execution State exception.
 ** Any debug exception except for Software Breakpoint Instruction exceptions.
 ** For Software Breakpoint Instruction exceptions, this bit has its standard meaning:
 ** 0 : 16-bit T32 BKPT instruction.
 ** 1 : 32-bit A32 BKPT instruction or A64 BRK instruction.
 ** An exception reported using EC value 0b000000.
 */
#define ESR_ELx_IL_16BIT_INSTRUCTION_TRAPPED (0x0 << 25)
#define ESR_ELx_IL_32BIT_INSTRUCTION_TRAPPED (0x1 << 25)
/* 24-0: Instruction Specific Syndrome.
 * Architecturally, this field can be defined independently for each defined 
 * Exception class. However, in practice, some ISS encodings are used for more than
 * one Exception class. See the description of the EC field for more information
 * about the ISS formats.
 */




#endif /* __MCUBE_ARM_SYS_REGS_H__ */
