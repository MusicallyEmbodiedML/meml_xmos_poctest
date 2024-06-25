extern "C" {

#include "user_main.h"
#include <xua_conf.h>

void UserBufferManagement (
unsigned output_samples [ NUM_USB_CHAN_OUT ],
unsigned input_samples [ NUM_USB_CHAN_IN ]);

void UserBufferManagementInit (unsigned int);

}  // extern "C"

#include <stdio.h>
#include <cmath>
#include <cstdint>

#warning You're building me, great!

/***
 * Static definitions
 */

static const float kSawtoothRate = 440.f;
static const float kSawtoothAmplitude = 0.1f;
static const unsigned int kOutputChan = 0;
static const unsigned int kInputChan = 0;

static int32_t _sawtooth_accumulator;
static int32_t _sample_rate;
static int32_t _sawtooth_increment;

#define IN_OUT_BYPASS    0
#define IN1_MODULATION    0

/***
 * Function declarations
 */
void UserBufferManagementInit(unsigned int sample_rate) {
    printf("=== Sawtooth test program ===\n");
    printf("Listen for a sawtooth on channel %d.\n", kOutputChan);
    printf("\n");
    printf("Sample rate is: %d.\n", sample_rate);
    _sample_rate = sample_rate;
    
    // Sawtooth constants calculation
    float float_sawtooth_increment = kSawtoothRate / _sample_rate;
    _sawtooth_increment = static_cast<int32_t>(std::pow(2.f, 32.f) * float_sawtooth_increment);
    _sawtooth_accumulator = 0;
}


void UserBufferManagement(unsigned output_samples [NUM_USB_CHAN_OUT],
unsigned input_samples [NUM_USB_CHAN_IN]) {

    // Make sawtooth
    float accum_value = static_cast<float>(_sawtooth_accumulator);
    accum_value *= kSawtoothAmplitude;
#if IN1_MODULATION
    // Modulate sawtooth
    float modulation_signal = static_cast<float>(static_cast<int32_t>(input_samples[kInputChan]));
    modulation_signal *= std::pow(2.f, -31.f);
    accum_value *= modulation_signal;
#endif
    // Output
#if IN_OUT_BYPASS
    output_samples[kOutputChan] = input_samples[kInputChan];
#else
    output_samples[kOutputChan] = static_cast<unsigned>(accum_value);
#endif
    // Update saw
    _sawtooth_accumulator += _sawtooth_increment;

}