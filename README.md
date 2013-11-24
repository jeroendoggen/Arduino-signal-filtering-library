# Arduino Signal Filtering Library
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

### Customizing the filters
If you want create your own filter, I suggest you:
 * Use my library as a template (to have some working code to start with)
 * Option 1: Generate the exact filtering code you need on the filtuino website (filter type, ripple, frequencies,...)
 * Option 2: Calculate & simulate your filters
 * Use the 'newFilter.h' & 'newFilter.cpp' templates to create your own filter. (by implementing a new "run()" function and writing a new example)

### Contribute a filter
To add your filters to the project:
 * Fork this project on GitHub
 * Follow the procedure to create your own filter
 * Write a short 'readme_myfiltername.md' to describe your filter (place it in the 'Documention' folder) 

## Version History:
 * Version 0.3.0: OOP version, better documentation, various cleanup, MIT license,...
 * Version 0.2.0: Median filter
 * Version 0.1.0: Low pass Chebychev and Bessel filters

## Roadmap:
 * Version 0.3.1+: More filters (band pass, moving average, Kalman, ...)                                             
