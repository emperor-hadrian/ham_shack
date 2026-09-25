# 5V 3A USB C Charger

## Regulation

Analog PID controller for adjusting duty cycle, will be run from seperate LM7805

## Specs

5V
Max 6A (future proofing in case multiple USB C ports)
Switch speed 10 KHz
Input 7.5V to 15 V

## Resources

ti.com/lit/an/slva477b/slva477b.pdf

hackaday.com/2023/01/04/all-about-usb-c-resistors-and-emarkers

## Power stage calculations

Max duty cycle = Vout / (Vin * efficiency) = 5 / (15 * 0.9) = 0.37

Inductor: L = Vout * (Vin - Vout) / (DeltaIL * fs * Vin) = 185 uH
Where DeltaIL = L ripple current = 0.3 * Iout = 1.8 A

Capacitors: Ceramic Low ESR (equivalent series resistance) X5R dielectric or better

1/CW=X
C=1/WX