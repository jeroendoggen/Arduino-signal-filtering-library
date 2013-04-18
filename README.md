Arduino library for signal filtering
------------------------------------

### Overview
This project is a free initiative to create an Arduino library for signal filtering.

 * [Some information about the filters](https://github.com/jeroendoggen/Arduino-signal-filtering-library/wiki/Signal-Filtering-Basics)
 * Free ebook: "The Scientist and Engineer's Guide to Digital Signal Processing" http://www.dspguide.com/

### Available filters:
 * low pass filter (1st and 2nd order, Chebychev and Bessel)
 * median filter

### Library Usage
 * Download the source
 * Place the Filter folder in your Arduino1.0+ "libraries" folder
 * Open example sketch: "file", "Examples", "!SignalFilter", "Bessel" (or any other example)
 * Connect a (noisy) analog sensor to port A0
 * Compile & upload code
 * Original and filtered sensor data should be arriving over the serial port

### Changing filters:
This library is partially based on filters that are auto-generated on the [filtuino website](http://www.schwietering.com/jayduino/filtuino/).
Filtuino is a Filter Suite that generates source code for different digital filters (IIR Lowpass, Highpass, Bandpass, Bandstop, IIR Resonanz Filter, Proportional Integral Filter).

If you want your own filter properties, I suggest you:
 * Use my library as a template (to have a working code to start with)
 * Generate the filtering code on the filtuino website
 * Replace one of the filters with your own filter.

### Version History:
 * Version 0.1: Low pass Chebychev and Bessel filters
 * Version 0.2: Median filter

### Roadmap:
 * Version 0.3+: More filters (band pass, running average, Kalman, ...)                                             
