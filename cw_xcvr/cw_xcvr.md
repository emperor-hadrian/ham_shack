# My first attempt at an actual radio, not just accessories like a tuner

## Resources

* Image rejection: https://rahsoft.com/2021/08/21/how-to-remove-the-image-signal-in-heterodyne-receiver/
* Image rejection: https://www.youtube.com/watch?v=v9C76WgMO4s
* Filter calculator: https://markimicrowave.com/technical-resources/tools/lc-filter-design-tool/
* Mixers: https://blog.minicircuits.com/a-quick-guide-to-mixer-topologies/
* IQ Mixing video: https://www.microwaves101.com/encyclopedias/i-q-mixers
* RX image-reject demo: https://www.desmos.com/calculator/maszbj538v
* Practical electronics for inventors: https://archive.org/details/fe_Practical_Electronics_For_Inventors/page/150/mode/1up

## Design software

* KiCad
* Rusty Logic (https://github.com/emperor-hadrian/rusty_logic_core). The folder `rusty_logic_circuits` has to be added to the rusty logic library list.

## Design requirements

* Multi-band from 160m to 10m
* The ONLY digital part will be the calibration/tuning for the VFOs relative to a crystal or maybe GPS in the future.
* Output power 50W
* Reciever input close to 50 ohms (idk if this is important, seems good though to make reciever efficient)
* 660 Hz sidetone (will probably be fixed by hardware)

## Receiver

I&Q Image reject mixer
For LO I and Q generation, a digital phase splitter is used. It will be implemented using the 74AC11074N (Digikey 296-32790-5-ND) with a propagation delay from 1.5 to 8.2 ns. 2 D FFs are used except one's output goes to both inputs, which makes the phase offset deterministic. Since one has the clock inverted, the clock edges have to arrive at the FFs at the same time.
2 XOR gates (SN74AC86N, digikey 296-4345-5-ND) will be used to invert one or the other latch clock.

Need to phase shift sidetone by 90 degrees, very important to have same amplitude for image cancellation

### Mixer design

two BJTs in common-emitter configuration both drawing current through a forward-biased 1N4148 diode

## Transmitter

VFO TX -> Power MOSFETs -> Low pass filter to remove harmonics (selectable by band)

## VFOs

There are 2 VFOs, both voltage controlled by a microcontroller. The digital display shows the frequency of VFO A.
Discrete logic ICs will be used to frequency-count all VFOs which will be read by the microcontroller in a feedback loop to adjust the control voltages.
The timing reference will be a crystal oscillator, possibly GPS in the future.

| Name | Freq range (MHz) | Purpose |
| - | - | - |
| VFO A | 1.8 - 29.7 | TX |
| VFO B | 2 x 1.79934 - 2 x 29.69934 | RX LO for 660 Hz sidetone |