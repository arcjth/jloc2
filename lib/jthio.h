#ifndef JTH_IOLIB

#define JTH_IOLIB

#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define COR0 "\033[0m" // reseta cores
#define COR1 "\033[34m" // azul
#define COR2 "\033[36m" // ciano
#define COR3 "\033[35m" // roxo
// https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

#define MAX 0xFFFF
#define ioInvalid ("\nComando inválido.\a")
#define ioExit ("\nSaindo...")
#define ioSizeError ("\nO valor máximo é %d.")
#define I2S_MAX_SAMPLES 4096
#define I2S_CHANNELS    4

typedef struct i2s_buffer_t {
    signed int samples[I2S_MAX_SAMPLES][I2S_CHANNELS];  // raw 32-bit do I2S
    unsigned int num_samples;
    unsigned int fs;          // sampling rate (Hz)
    bool overflow;
} i2sBuffer;

// I/O
unsigned int getnof(const char *prompt, unsigned int max);
char *get_input(char *input, int max);
double get_value(double *value);

void i2s_init(void);                              // platform-specific init (STM32/ESP/etc.)
bool i2s_start_capture(i2sBuffer *buf);          // start DMA
void i2s_stop_capture(void);
int32_t i2s_convert_24bit_signed(int32_t raw);   // handles sign extension

#endif
