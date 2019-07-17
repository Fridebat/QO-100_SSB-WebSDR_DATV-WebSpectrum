/*
 * SDR-Library by DJ0ABR
 * 
 * downmixer.c
 * ===========
 * the downmixer works like a real anaog mixer, it shifts the frequency down by some amount.
 * 
 * Example:
 * The input signal is 1 MHz,
 * the LO frequency is 900 kHz
 * the output of the down mixer is the input signal shifted
 * down to 1MHz-900kHz = 100 kHz
 * 
 * this function is mainly used to shift a signal down to the baseband (0 Hz) 
 * for SSB demodulation.
 * 
 * Functional blocks:
 * 1) NCO ... digital oscillator, made with a simulated DDS Synthesizer
 *    and a sine wave lookup table.
 * 2) Multiplier ... mixing is done by multiplication of the input signal
 *    with the LO frequency (the NCO output)
 * 3) low pass filter ... pass only the wanted frequencies are passed
 * 
 * NCO ... theory of operation
 * ==========================
 * 
 * NCO's reference clock:
 * ----------------------
 * In an SDR we already have a sampling frequency generated by the receiver/soundcard.
 * We use this also as the reference clock for the NCO, which means that we increment
 * the NCO's accumulator with every sample.
 * 
 * Increment:
 * ----------
 * the increment (FSW) defines the out frequency of the NCO:
 * Fout = FSW * Fclk / 2^N
 * i.e.:
 * N = 32 bit (the accumulator has 32 bits)
 * Fclk = 2,4MHz (the SDRs sampling rate is 2.4 Msamples/s)
 * FSW = i.e. 1e9 (frequency control word to the the wanted output frequency)
 * 
 * Fout = 1e9 * 2.4e6 / (2^32) = 558 794 Hz
 * 
 * the other way round: which FSW do we need for a given output frequency ?
 * FCW = Fout * 2^N / Fclk
 * FCW = 558 794 * 2^32 / 2.4e6 = 1e9
 * (this is the formular we need to the the mixer LO frequency)
 * 
 * sine wave lookup table:
 * -----------------------
 * we do not need all 32 bits from the accumulator because the lookup table would be
 * much too long. Instead we throw away the lower 16 bits and just use the upper 16
 * bits. A 16 bit table gives a good SNR, much better than only 8 bits.
 * 
 * multiplier:
 * -----------
 * this is a simple multiplication ob the samples and the LO
 * 
 * low pass filter:
 * ----------------
 * is required to remove the mirror. The filter must be broad enough for the wanted frequencies, i.e.
 * 4 kHz for voice
 * 
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "qo100websdr.h"
#include "downmixer.h"
#include "fir_table_calc.h"
#include "setqrg.h"
#include "cat.h"

void init_downmixer_fir_filters();
int fir_filter_i_ssb(double sample);
int fir_filter_q_ssb(double sample);

#define SINETABSIZE 65536
short sinetable[SINETABSIZE];   // 16 bit sine wave lookup table, each value is a signed short, like the soundcard samples
int samplerate;
unsigned int fcw;               // frequency control word, used to set the NCOs frequency

// initialize the mixer, must be called once at program start
void downmixer_init()
{
    samplerate = SAMPLERATE_FIRST;

    // fill the sinewave lookup table
    double v = 0;
    for(int i=0; i<SINETABSIZE; i++)
    {
        sinetable[i] = sin(v) *32768;
        v += (2*M_PI)/SINETABSIZE;
    }
    
    // set a default frequency of 10kHz
    downmixer_setFrequency(10000);
}

// calculate the fcw from the wanted frequency
void downmixer_setFrequency(int fr)
{
    printf("set mixer qrg: %d\n",fr);
    
    // set in TRX via CAT
    trx_frequency = fr + TUNED_FREQUENCY;
    ser_command = 2;
    
    fcw = (unsigned int)((double)fr * pow(2,32) / (double)samplerate);
}

// get next NCO sine wave value
// this increments the NCO to the next step
// do this for every sample
short increment_NCO()
{
static unsigned int accu = 0;

    // advance the NCO to the next step
    // accu automatically overflows at 2^32 
    accu += fcw;
    accu &= 0xffffffff;     // if uint has > 32 bits, just to be sure
    return sinetable[accu >> 16];
}

// does the mixer job
// call it for every sample
// i and q samples are downmixed in exactly the same way
// information is not changed, just frequency shifted
// and is used for SDR hardware delivering I and Q signals
// (Remark: if this mixer should be use for a mono input channel (only real, no q)
// then we need also a cosine table to generate the q channel)
// isample, qsample ... input, original sample from SDR hardware
// *pi, *pq ... downmixed result
//int xx=0,xxo=0;
void downmixer_process(short *pisample , short *pqsample)
{
    // get the LO
    int lo = increment_NCO();
    
    // mixing
    int ix = (int)(*pisample) * lo;
    int qx = (int)(*pqsample) * lo;
    
    // above multiplication expanded the sample to 32 bit, reduce it to 16 bit
    // (a level regulation could be implemented here)
    *pisample = (short)(ix >> 15);
    *pqsample = (short)(qx >> 15);
}

