/**
 * @file drivers/uart/uart_arm.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

#if PL011_UART

/* PL011 UART in Raspberry Pi3 and SynQuacer */

uint8_t uart_pol_getc(uint8_t ch)
{
  // Wait for UART to have received something.
  while (mmio_in64(UART0_FLAG_REG) & UART_FLAG_REG_RECEIVE_FIFO_EMPTY)
    ;
  return mmio_in64(UART0_DATA_REG) & UART_DATA_REG_DATA_MASK;
}

void uart_pol_putc(uint8_t c, int32_t ch)
{
  // Wait for UART to become ready to transmit.
  while (mmio_in64(UART0_FLAG_REG) & UART_FLAG_REG_TRANSMIT_FIFO_FULL)
    ;
  mmio_out64(UART0_DATA_REG, c & UART_DATA_REG_DATA_MASK);
}

void init_uart(void)
{
  /* enable uart */
  mmio_out32(UART0_CTRL_REG,
             mmio_in32(UART0_CTRL_REG) | UART_CTRL_REG_UART_ENABLE);
  /* enable UART RX interrupt */
  mmio_out32(UART0_INTERRUPT_MASK_SET_CLEAR_REG, UART_IMSC_REG_RECEIVE_INTERRUPT_MASK);
#if CONFIG_ARCH_ARM_RASPI3
  /* set UART interrupt routing */
  mmio_out32(ENABLE_IRQS2, 1 << 25);
#elif CONFIG_ARCH_ARM_SYNQUACER
  /* TODO: implement */
#else
#error "Unknown Machine"
#endif /* CONFIG_ARCH_ARM_RASPI3 */
}

#elif MINI_UART

/* Mini UART in Raspberry Pi3 */

uint8_t uart_pol_getc(uint8_t ch)
{
  while (mmio_in32(IRQ_PENDING1) & (1 << 29))
    ;
  return mmio_in8(AUX_MU_IO_REG);
}

void uart_pol_putc(uint8_t c, int32_t ch)
{
  while (!(mmio_in8(AUX_MU_LSR_REG) & AUX_MU_LSR_REG_TRANSMITTER_EMPTY))
    ;
  mmio_out8(AUX_MU_IO_REG, c);
}


void init_uart(void)
{
  uint32_t selector = mmio_in32(GPFSEL1);

  /* clear gpio14 */
  selector &= ~(7 << 12);
  /* set alt5 for gpio14 */
  selector |= 2 << 12;
  /* clear gpio15 */
  selector &= ~(7 << 15);
  /* set alt5 for gpio15 */
  selector |= 2 << 15;
  
  mmio_out32(GPFSEL1, selector);

  mmio_out32(GPPUD, 0);

  delay(1000);
  mmio_out32(GPPUDCLK0, (1 << 14) | (1 << 15));
  delay(1000);
  mmio_out32(GPPUDCLK0, 0);

  /* enable mini UART */
  mmio_out32(AUX_ENABLES, AUX_ENABLES_MINI_UART_ENABLE);

  /* disable auto flow control and disable receiver and transmitter (for now) */
  mmio_out32(AUX_MU_CNTL_REG, 0);

  /* disable receive and transmit interrupts */
  mmio_out32(AUX_MU_IER_REG, 0);

  /* enable 8 bit mode */
  mmio_out32(AUX_MU_LCR_REG, mmio_in32(AUX_MU_LCR_REG) | AUX_MU_LCR_REG_8BIT_MODE);

  /* set RTS line to be always high */
  mmio_out32(AUX_MU_MCR_REG, 0);

  /* set baudrate to 115200 */
  mmio_out32(AUX_MU_BAUD_REG, 270);

  /* Finally, enable transmitter and receiver */
  mmio_out32(AUX_MU_CNTL_REG,
             mmio_in32(AUX_MU_CNTL_REG)
             | AUX_MU_CNTL_REG_TRANSMITTER_ENABLE
             | AUX_MU_CNTL_REG_RECEIVER_ENABLE);
  
  /* clear transmit/receive FIFOs */
  mmio_out32(AUX_MU_IIR_REG,
             AUX_MU_IIR_REG_CLEAR_TRANSMIT_FIFO
             | AUX_MU_IIR_REG_CLEAR_RECV_FIFO);

  /* enable transmit interrupt */
  //  mmio_out32(AUX_MU_IER_REG, AUX_MU_IER_REG_ENABLE_TRANSMIT_INTERRUPTS);

  /* set UART interrupt routing */
  mmio_out32(ENABLE_IRQS1, 1 << 29);
}

#else
#error "Unknown UART"
#endif

