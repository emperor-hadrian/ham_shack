# My first attempt at an actual radio, not just accessories like a tuner

## Resources

* Image rejection: https://rahsoft.com/2021/08/21/how-to-remove-the-image-signal-in-heterodyne-receiver/
* Filter calculator: https://markimicrowave.com/technical-resources/tools/lc-filter-design-tool/

## Design requirements

* Multi-band from 160m to 10m
* The ONLY digital part will be the calibration/tuning for the VFOs wrt. a crystal.
* Output power 20W
* Reciever input close to 50 ohms (idk if this is important, seems good though to make reciever efficient)

## Receiver

2-stage heterodyne for the purpose of image rejection.
Widest band is 10m at 1.7 MHz

RF -> HPF, selectable by band -> X (Band shifted to start at 1 MHz) -> LC filter in-band sweep -> X -> Audio 600 Hz fixed LC filter -> Audio out
(VFO A, band min - 1 MHz) -------^
(VFO B, in-band sweep from 1 MHz to 2.7 MHz (- sidetone)) ----------------------------------------^

The choice of the start frequency of the shifted band (1 MHz) is a compromise between the initial image-reject HPF and the highest frequency going into the 2nd mixer (which makes the 2nd image-reject filter need to have a higher Q).

## Transmitter

VFO TX -> Power MOSFETs -> Low pass filter to remove harmonics (selectable by band)

## VFOs

There are 3 VFOs, all voltage controlled by a microcontroller. The digital display shows the frequency of VFO TX.
Discrete logic ICs will be used to frequency-count all VFOs which will be read by the microcontroller in a feedback loop to adjust the control voltages.
The timing reference will be a crystal oscillator, possibly GPS in the future.

| Name | Freq range (MHz) | Purpose |
| - | - | - |
| VFO A | 0.8 - 27 | Band start - 1 MHz for initial mixer |
| VFO B | 0.9994 - 1.6994 | In-band sweep to generate 600 Hz sidetone |
| VFO TX | 1.8 - 29.7 | TX |