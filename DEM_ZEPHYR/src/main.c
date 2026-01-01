/*
 * File: main.c
 * Description: Universal Firmware with UART Mirroring (MCU to PC)
 * Features: Dual LED Strobe & Dual UART Output
 *
 * Author: Harun Karaca
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>

/* -------------------------------------------------------------------------- */
/* HARDWARE DEFINITIONS & ALIASES                                             */
/* -------------------------------------------------------------------------- */

/* UART Port Aliases */
#define UART_PC_NODE  DT_ALIAS(uart_pc)  /* Connection to Computer */
#define UART_MCU_NODE DT_ALIAS(uart_mcu) /* Connection to Other Processor */

/* LED Aliases */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

/* Compile-time checks */
#if !DT_NODE_HAS_STATUS(UART_PC_NODE, okay) || !DT_NODE_HAS_STATUS(UART_MCU_NODE, okay)
    #error "Error: Both 'uart-pc' and 'uart-mcu' aliases must be defined in DTS."
#endif

/* -------------------------------------------------------------------------- */
/* DEVICE STRUCTURES                                                          */
/* -------------------------------------------------------------------------- */

static const struct device *const uart_pc  = DEVICE_DT_GET(UART_PC_NODE);
static const struct device *const uart_mcu = DEVICE_DT_GET(UART_MCU_NODE);

static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

/* -------------------------------------------------------------------------- */
/* HELPER FUNCTIONS                                                           */
/* -------------------------------------------------------------------------- */

/**
 * @brief Transmits a string to a specific UART device.
 */
void uart_transmit(const struct device *dev, const char *msg)
{
    if (!dev || !msg) return;
    while (*msg) {
        uart_poll_out(dev, *msg);
        msg++;
    }
}

/**
 * @brief Mirrors a message to both PC and MCU UART ports.
 */
void uart_log_dual(const char *msg)
{
    uart_transmit(uart_pc, msg);
    uart_transmit(uart_mcu, msg);
}

/* -------------------------------------------------------------------------- */
/* MAIN APPLICATION                                                           */
/* -------------------------------------------------------------------------- */

int main(void)
{
    /* --- 1. Readiness Checks --- */

    if (!device_is_ready(uart_pc) || !device_is_ready(uart_mcu)) {
        return -1;
    }

    if (!gpio_is_ready_dt(&led_0) || !gpio_is_ready_dt(&led_1)) {
        return -1;
    }

    /* --- 2. Configuration --- */

    gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_INACTIVE);

    /* Initial Greeting - Sent to both ports */
    uart_log_dual("\r\n[SYS] Dual UART Bridge Initialized.\r\n");
    uart_log_dual("[SYS] Hello Processor! (Sending to PC & MCU)\r\n");

    /* --- 3. Main Loop --- */

    while (1) {
        /* Toggle LEDs */
        gpio_pin_toggle_dt(&led_0);
        gpio_pin_toggle_dt(&led_1);

        /* Log activity to both ports */
        /* This allows you to see the "keep-alive" on your PC screen */
        uart_log_dual(".");

        k_msleep(500);
    }

    return 0;
}