#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "dht11.pio.h"

#include "common.h"

#define DHT_PIN    14

typedef struct {
    float humidity;
    float temperature;
} dht_measurement;

const PIO pio = pio0;
uint sm_dht;

void dht11_done(void) {
    pio0_hw->irq = 1;
    printf("pio triggered IRQ\n");

    uint32_t data = pio_sm_get(pio, sm_dht);
    uint8_t checksum = (uint8_t) pio_sm_get(pio, sm_dht);

    println_bin_32(data);
    println_bin_8(checksum);

    int RH_integral = *((uint8_t *)(&data) + 3);
    int RH_decimal = *((uint8_t *)(&data) + 2);
    int T_integral = *((uint8_t *)(&data) +1);
    int T_decimal = (uint8_t)data;

    printf("RH_integral: %i\n", RH_integral);
    printf("RH_decimal: %i\n", RH_decimal);
    printf("T_integral: %i\n", T_integral);
    printf("T_decimal: %i\n", T_decimal);
}

int main () {
    stdio_init_all();

    uint dht11_offset = pio_add_program(pio, &dht11_program);
    sm_dht = pio_claim_unused_sm(pio, true);
    
    dht11_program_init(pio, sm_dht, dht11_offset, DHT_PIN);
    irq_set_exclusive_handler(PIO0_IRQ_0, &dht11_done);
    irq_set_enabled(PIO0_IRQ_0, true);
    pio_sm_set_enabled(pio, sm_dht, true);

    

    printf("\n\n---- START ----\n");
    while(true)
        tight_loop_contents();

    return 0;
}
