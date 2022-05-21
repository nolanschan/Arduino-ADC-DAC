# Analog-to-Digital and Digital-to-Analog Conversion using Arduino and MCP4921 #

## About ## 
Part 2 of Benchtop Labs for my Digital Control course.

In this lab project, an analog input (sine wave) from an external function generator is converted to a digital signal using the Arduino's onboard ADC. The digital signal is then converted back to analog using a MCP4921 IC chip, and outputted to an external oscilloscope to view the waveform.

The full lab report with details and results can be found on my Github.io site <a href="http://nolanschan.github.io/projects/adcdac">here</a>.

## Credit ##
The base code was written by Dr. Gary Hill at California State University Long Beach, and provided as part of the lab instructions.

## Modifications ##
- Pin declarations were changed to match the pinout of the Arudino Mega2560.
- Additional code was added to write to the ADC clock registers in order to change the clock rate.
