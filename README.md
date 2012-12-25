Arduino library for signal filtering
------------------------------------

### Overview
This project is a free initiative to create an Arduino library for signal filtering.

 * Very short introduction to the filters: https://github.com/jeroendoggen/Arduino-signal-filtering-library/wiki/Signal-Filtering-Basics
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

### Version History:
 * Version 0.1: Low pass Chebychev and Bessel filters
 * Version 0.2: Median filter

### Roadmap:
 * Version 0.3+: More filters (band pass, running average, Kalman, ...)                                             
