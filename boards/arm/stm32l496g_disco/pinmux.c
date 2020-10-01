/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for STM32L476G-DISCO board */
static const struct pin_config pinconf[] = {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart1), okay) && CONFIG_SERIAL
	{STM32_PIN_PB6,  STM32L4X_PINMUX_FUNC_PB6_USART1_TX},
	{STM32_PIN_PG10, STM32L4X_PINMUX_FUNC_PG10_USART1_RX}, 
	{STM32_PIN_PG11, STM32L4X_PINMUX_FUNC_PG11_USART1_CTS},
	{STM32_PIN_PG12, STM32L4X_PINMUX_FUNC_PG12_USART1_RTS},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart2), okay) && CONFIG_SERIAL
	{STM32_PIN_PA2, STM32L4X_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PD6, STM32L4X_PINMUX_FUNC_PD6_USART2_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpuart1), okay) && CONFIG_SERIAL
	{STM32_PIN_PG7, STM32L4X_PINMUX_FUNC_PG7_LPUART1_TX},
	{STM32_PIN_PG8, STM32L4X_PINMUX_FUNC_PG8_LPUART1_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay) && CONFIG_I2C
	{STM32_PIN_PB8, STM32L4X_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB7, STM32L4X_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c2), okay) && CONFIG_I2C
	{STM32_PIN_PH4, STM32L4X_PINMUX_FUNC_PH4_I2C2_SCL},
	{STM32_PIN_PB14, STM32L4X_PINMUX_FUNC_PB14_I2C2_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay) && CONFIG_SPI
	{STM32_PIN_PA5, STM32L4X_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PB4, STM32L4X_PINMUX_FUNC_PB4_SPI1_MISO},
	{STM32_PIN_PB5, STM32L4X_PINMUX_FUNC_PB5_SPI1_MOSI},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi2), okay) && CONFIG_SPI
	{STM32_PIN_PI1, STM32L4X_PINMUX_FUNC_PI1_SPI2_CLK}, 		
	{STM32_PIN_PG11, STM32L4X_PINMUX_FUNC_PG11_SPI2_CS},
	{STM32_PIN_PI2, STM32L4X_PINMUX_FUNC_PI2_SPI2_MISO}, 
	{STM32_PIN_PB15, STM32L4X_PINMUX_FUNC_PB15_SPI2_MOSI}, 
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pwm2), okay) && CONFIG_PWM
	{STM32_PIN_PA0, STM32L4X_PINMUX_FUNC_PA0_PWM2_CH1},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(sdmmc1), okay) && \
	CONFIG_DISK_ACCESS_STM32_SDMMC
	{STM32_PIN_PC8, STM32L4X_PINMUX_FUNC_PC8_SDMMC1_D0},
	{STM32_PIN_PC9, STM32L4X_PINMUX_FUNC_PC9_SDMMC1_D1},
	{STM32_PIN_PC10, STM32L4X_PINMUX_FUNC_PC10_SDMMC1_D2},
	{STM32_PIN_PC11, STM32L4X_PINMUX_FUNC_PC11_SDMMC1_D3},
	{STM32_PIN_PC12, STM32L4X_PINMUX_FUNC_PC12_SDMMC1_CK},
	{STM32_PIN_PD2, STM32L4X_PINMUX_FUNC_PD2_SDMMC1_CMD},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(arduino_header),okay)
	{STM32_PIN_PC4, STM32L4X_PINMUX_FUNC_PC4_ARD_A0},
	{STM32_PIN_PC1, STM32L4X_PINMUX_FUNC_PC1_ARD_A1},
	{STM32_PIN_PC3, STM32L4X_PINMUX_FUNC_PC3_ARD_A2},
	{STM32_PIN_PF10, STM32L4X_PINMUX_FUNC_PF10_ARD_A3},
	{STM32_PIN_PA1, STM32L4X_PINMUX_FUNC_PA1_ARD_A4},
	{STM32_PIN_PC0, STM32L4X_PINMUX_FUNC_PC0_ARD_A5},
	{STM32_PIN_PG13, STM32L4X_PINMUX_FUNC_PG13_ARD_D2},
	{STM32_PIN_PH15, STM32L4X_PINMUX_FUNC_PH15_ARD_D3},
	{STM32_PIN_PI11, STM32L4X_PINMUX_FUNC_PI11_ARD_D4},
	{STM32_PIN_PB9, STM32L4X_PINMUX_FUNC_PB9_ARD_D5},
	{STM32_PIN_PI6, STM32L4X_PINMUX_FUNC_PI6_ARD_D6},
	{STM32_PIN_PG6, STM32L4X_PINMUX_FUNC_PG6_ARD_D7},
	{STM32_PIN_PG15, STM32L4X_PINMUX_FUNC_PG15_ARD_D8},
	{STM32_PIN_PH13, STM32L4X_PINMUX_FUNC_PH13_ARD_D9},
	{STM32_PIN_PA15, STM32L4X_PINMUX_FUNC_PA15_ARD_D10},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usbotg_fs),okay) && CONFIG_USB
	{STM32_PIN_PA9, STM32L4X_PINMUX_FUNC_PA9_USB_OTGFS_VBUS},
	{STM32_PIN_PA10, STM32L4X_PINMUX_FUNC_PA10_USB_OTGFS_ID},
	{STM32_PIN_PA11, STM32L4X_PINMUX_FUNC_PA11_USB_OTGFS_DM},
	{STM32_PIN_PA12, STM32L4X_PINMUX_FUNC_PA12_USB_OTGFS_DP},
#endif 
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
