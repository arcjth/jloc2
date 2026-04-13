#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "jthio.h"

static const char *str_i2s_init = "%sI2S interface initialized (24-bit, %d channels)%s\n";
static const char *str_i2s_capture = "%sCapture started - waiting for trigger...%s\n";

char *get_input(char *input, int max) {
    putchar('\n');
    fgets(input, max, stdin);
    input[strcspn(input, "\n")] = '\0';
    return input;
}
double get_value(double *value) {
    const char *conversion_error = "\nUm erro pode ter ocorrido na conversão, verifique o valor inserido \n(dica: utilize not. científica (ex: 1,7E-9 = 1,7 nano, 1,0e6 = 1 milhão)).";
    char input[MAX];
    *value = 0.0;
    while (*value <= 0.0) {
        get_input(input, MAX);
        for (char *pinput = input; *pinput != '\0'; pinput++) {
            if (*pinput == ',') *pinput = '.'; // pra permitir a notação brasileira
        }
        double t = atof(input);
        /*if (t <= 0.0e50) { // número minusculamente pequenos vao cair aqui mas funcionar igual, não sei se tenho o que fazer a respeito, malditos floating point numbers
            printf("%s", conversion_error); // não vejo razão pra não proibir 0 ou negativos
        } else *value = t;   
        usava isso no simulador de circuitos, mas não faz mais sentido. */
    }
    return *value;
}

unsigned int getnof(const char *prompt, unsigned int max) {
    unsigned int nof = 0;
    char input[MAX];
    while(nof == 0) {
        printf("%s", prompt);
        int value = atoi(get_input(input, MAX));
        if (value <= 0 ) {
            printf("%s", ioInvalid);
            continue;
        } else if (max >= 1 && value > max) {
            printf(ioSizeError, max);
            continue;
        } else nof = value;
    }
    return nof;
}

int32_t i2s_convert_24bit_signed(int32_t raw) {
    // Most digital mics send 24-bit left-justified in 32-bit word
    return raw >> 8;          // shift out padding bits → signed 24-bit becomes 32-bit
}

void i2s_init(void) {
    // TODO: your MCU-specific I2S + DMA config here (BCLK, LRCLK, 24-bit, slave mode)
    // Example: HAL_I2S_Init(...); DMA circular mode
    printf(str_i2s_init, COR2, I2S_CHANNELS, COR0);
}