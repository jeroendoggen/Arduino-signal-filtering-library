# Arduino library for signal filtering

## Overview
The goals of this project is providing an Arduino library for basic signal filtering.
These filters can be used to clean up noisy signals by suppressing small (fast) signal changes while passing bigger (slow) signal changes. 
This is typically done by suppressing the "higher frequency" fluctuations.

## More info:
 * [Information about the filters](https://github.com/jeroendoggen/Arduino-signal-filtering-library/wiki/Signal-Filtering-Basics)
 * [Free ebook: "The Scientist and Engineer's Guide to Digital Signal Processing"] (http://www.dspguide.com)

## Available filters:
 * Low pass filters: Chebychev and Bessel (1st and 2nd order)
 * Median filter

## Library Usage
 * Download the source
 * Place the Filter folder in your Arduino1.0+ "libraries" folder
 * Open example sketch: "file", "Examples", "SignalFilter", "Bessel" (or any other example)
 * Connect a (noisy) analog sensor to port A0
 * Compile & upload code
 * Original and filtered sensor data should be arriving over the serial port

## Changing filters:
This library is partially based on filters that are auto-generated on the [filtuino website](http://www.schwietering.com/jayduino/filtuino/).
Filtuino is a Filter Suite that generates source code for different digital filters (IIR Lowpass, Highpass, Bandpass, Bandstop, IIR Resonanz Filter, Proportional Integral Filter).

If you want your own filter properties, I suggest you:
 * Use my library as a template (to have some working code to start with)
 * Option 1: Generate the exact filtering code you need on the filtuino website (filter type, ripple, frequencies,...)
 * Option 2: Calculate & simulate your filters
 * Replace one of the filters in my library with your own custom filter. (by replacing the "run()" function)

## Version History:
 * Version 0.2: Median filter
 * Version 0.1: Low pass Chebychev and Bessel filters

## Roadmap:
 * Version 0.3+: More filters (band pass, moving average, Kalman, ...)                                             
