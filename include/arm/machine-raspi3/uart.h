/**
 * @file include/arm/machine-raspi3/uart.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef	__MCUBE_ARM_MACHINE_RASPI3_UART_H__
#define	__MCUBE_ARM_MACHINE_RASPI3_UART_H__


#define AUX_IRQ_REG            (PERIPHERAL_BASE + 0x00215000)
#define AUX_ENABLES            (PERIPHERAL_BASE + 0x00215004)
#define AUX_MINI_UART_IO_REG   (PERIPHERAL_BASE + 0x00215040)
#define AUX_MINI_UART_IER_REG  (PERIPHERAL_BASE + 0x00215044)
#define AUX_MINI_UART_IIR_REG  (PERIPHERAL_BASE + 0x00215048)
#define AUX_MINI_UART_LCR_REG  (PERIPHERAL_BASE + 0x0021504c)
#define AUX_MINI_UART_MCR_REG  (PERIPHERAL_BASE + 0x00215050)
#define AUX_MINI_UART_LSR_REG  (PERIPHERAL_BASE + 0x00215054)
#define AUX_MINI_UART_MSR_REG  (PERIPHERAL_BASE + 0x00215058)
#define AUX_MINI_UART_SCRATCH  (PERIPHERAL_BASE + 0x0021505c)
#define AUX_MINI_UART_CNTL_REG (PERIPHERAL_BASE + 0x00215060)
#define AUX_MINI_UART_STAT_REG (PERIPHERAL_BASE + 0x00215064)
#define AUX_MINI_UART_BAUD_REG (PERIPHERAL_BASE + 0x00215068)

  
// The base address for UART.
#define UART0_BASE (PERIPHERAL_BASE + 0x00201000) // for raspi2 & 3, 0x20201000 for raspi1



#endif /*	__MCUBE_ARM_MACHINE_RASPI3_UART_H__ */

