# Progress on obtaining/making/fixing parts

| Part | Status | Problem(s) | TODO(s) |
| - | - | - | - |
| QMX+ | Bad | Low TX power | Fix finals |
| Power amplifier | Not yet obtained | - | Get it |
| ATU-100 tuner | Bad | Not assembled | Assemble it |
| NanoVNA | Good | - | - |
| DIY Tuner | Good | - | - |
| Battery Pack | Good | - | - |
| Solar panel | Not yet obtained | - | Get it |
| MISC Connectors | Good | - | - |
| Antenna + Feedline | Good | - | - |
| Waterproof box | Not yet obtained | - | - |
| Dummy load | Not great | Only 1W | Upgrade |
| 1:1 Balun | Good | - | - |
| USB C Buck converter | Not built | - | Build it |

## Shopping list

| Part | Qty | Link/ID | Website |
| - | - | - | - |
| BS170 MOSFETs | 24 | BS170-ND | DigiKey |
| Waterproof case 0.5 ft^3 | 1 | https://www.ebay.com/itm/146049791419 | Ebay |
| Powerpole connectors kit | 1 | https://www.ebay.com/itm/255475339167 | Ebay |
| FT 240 43 ferrite | 1 | https://www.ebay.com/itm/389082167356 | Ebay |
| Solder | 1 | TODO | Digi-key |

## OCFD Design

Really cool article: https://old.w1yca.org/tech/ant/dipolefund.pdf

https://www.hamradiosecrets.com/off-center-fed-dipole.html

9:1 transformer will be used at the feedpoint to make it match ok with coax between that and the tuner and reject common mode current.

Dimensions: total length = 300 / 3.75 / 2 = 40 meters
Feedpoint: 22.5% offset means 9 meters and 31 meters
Conversion to 'Murican units: 29.5 ft, 101.7 ft

## 80 meters dipole for CW

Center at lower part of band: 3.51 MHz, 85.47 meters WL, dipole is 42.73 meters total, 21.4 meters or 70 ft per element

## Quarter wave vertical for 10 meters (plain), lower bands w/ loading coil

Loading coil calculator: https://m0ukd.com/calculators/loaded-quarter-wave-antenna-inductance-calculator/

Another one: https://www.66pacific.com/calculators/coil-shortened-vertical-antenna-calculator.aspx

The feedpoint will be at ground level, possible balun for common mode/matching.

Loading coil: Right at feedpoint for verticle element, highest setting (for 1.8 MHz) should be 207 uH or 148 depending on the calculator

TODO: Number and langth of radials