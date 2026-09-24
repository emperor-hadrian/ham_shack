# My first attempt at an actual radio, not just accessories like a tuner

## Resources

* Image rejection: https://rahsoft.com/2021/08/21/how-to-remove-the-image-signal-in-heterodyne-receiver/
* Filter calculator: https://markimicrowave.com/technical-resources/tools/lc-filter-design-tool/
* Mixers: https://blog.minicircuits.com/a-quick-guide-to-mixer-topologies/
* IQ Mixing video: https://www.microwaves101.com/encyclopedias/i-q-mixers
* RX image-reject demo: https://www.desmos.com/calculator/maszbj538v
* Practical electronics for inventors: https://archive.org/details/fe_Practical_Electronics_For_Inventors/page/150/mode/1up

## Design requirements

* Multi-band from 160m to 10m
* The ONLY digital part will be the calibration/tuning for the VFOs wrt. a crystal.
* Output power 20W
* Reciever input close to 50 ohms (idk if this is important, seems good though to make reciever efficient)

## Receiver

I&Q Image reject mixer

## Transmitter

VFO TX -> Power MOSFETs -> Low pass filter to remove harmonics (selectable by band)

## VFOs

There are 2 VFOs, both voltage controlled by a microcontroller. The digital display shows the frequency of VFO A.
Discrete logic ICs will be used to frequency-count all VFOs which will be read by the microcontroller in a feedback loop to adjust the control voltages.
The timing reference will be a crystal oscillator, possibly GPS in the future.

| Name | Freq range (MHz) | Purpose |
| - | - | - |
| VFO A | 1.8 - 29.7 | TX |
| VFO B | 1.7994 - 29.6996 | RX LO for 600 Hz sidetone |