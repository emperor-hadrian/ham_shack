# My first attempt at an actual radio, not just accessories like a tuner

## Resources

* Image rejection: https://rahsoft.com/2021/08/21/how-to-remove-the-image-signal-in-heterodyne-receiver/
* Image rejection: https://www.youtube.com/watch?v=v9C76WgMO4s
* Filter calculator: https://markimicrowave.com/technical-resources/tools/lc-filter-design-tool/
* Mixers: https://blog.minicircuits.com/a-quick-guide-to-mixer-topologies/
* IQ Mixing video: https://www.microwaves101.com/encyclopedias/i-q-mixers
* RX image-reject demo: https://www.desmos.com/calculator/maszbj538v
* Practical electronics for inventors: https://archive.org/details/fe_Practical_Electronics_For_Inventors/page/150/mode/1up
* Circuit solver: https://onlinecircuitsolver.com/

## Design software

* KiCad
* Rusty Logic (https://github.com/emperor-hadrian/rusty_logic_core). The folder `rusty_logic_circuits` has to be added to the rusty logic library list.

## Design requirements

* Multi-band from 160m to 10m
* The ONLY digital part will be the calibration/tuning for the VFOs relative to a crystal or maybe GPS in the future.
* Output power 50W
* Reciever input close to 50 ohms (idk if this is important, seems good though to make reciever efficient)
* 700 Hz sidetone (fixed by hardware)

## Receiver

I&Q Image reject mixer
For LO I and Q generation, a digital phase splitter is used. It will be implemented using the 74AC11074N (Digikey 296-32790-5-ND) with a propagation delay from 1.5 to 8.2 ns. 2 D FFs are used except one's output goes to both inputs, which makes the phase offset deterministic. Extra gates (all on the same chip) will be used to make the propagation times identical for both I and Q signals.
4 XOR gates (SN74AC86N, digikey 296-4345-5-ND) will be used to invert the clock and provide extra delays.
There is a circuit `rusty_logic_circuits/phase_shifter.json` for simulating the phase shifter.

Need to phase shift sidetone by 90 degrees, very important to have same amplitude for image cancellation.

### Mixer design

A BJT amplifier which can be shorted by another BJT

### Audio 90 degree phase shift

https://ombhatia99.github.io/Oscillator-Vlab/RC%20Phase%20Shift%20Oscillator/main%20ckt/theory%20page/theory.html

Two stage RC lowpass filter to shift phase 45 degrees per stage
degrees = atan(Xc/R) where `Xc` is the imaginary reactance of the capacitor. 45 degrees is simple because that is where `Xc = R`
Starting with an arbitrary R value of 8K (10K pot with adjustment margin), `1/(wC)=10K`, solve for C: `C=1/(w*8K)`, plug in numbers: `C=1/(700Hz*2pi*8K)=28.4nF`. Actual values are rounded to a standard value of 27nF.
The circuit solver website was used to verify this solution as well as finding the loss to be 9.5dB. An amplifier before the network will be given a max gain of 11 (adjustable) which will compensate for this.

## Transmitter

VFO TX -> Power MOSFETs -> Chebyshev LPF to remove harmonics (selectable by band)
The filter can have some ripple in the passband which is fine, but it must have a steep cutoff to reduce harmonics.

## VFOs

There are 2 VFOs, both voltage controlled by a microcontroller. The digital display shows the frequency of VFO A.
Discrete logic ICs will be used to frequency-count all VFOs which will be read by the microcontroller in a feedback loop to adjust the control voltages.
The timing reference will be a crystal oscillator, possibly GPS in the future.

| Name | Freq range (MHz) | Purpose |
| - | - | - |
| VFO A | 1.8 - 29.7 | TX |
| VFO B | 2 x 1.7993 - 2 x 29.6993 | RX LO for 700 Hz sidetone |