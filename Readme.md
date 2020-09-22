# **O**pen **S**ource **S**cientific **C**alculator
## An open-source alternative to standard school calculators

I was unsatisfied with the unhackability of our school-issued calculators,
so I decided to make my own. The OSSC.

The OSSC will sport two Atmel microcontrollers : an ATmega8A (as a **K**eypad **C**ontroller)
connected to an ATmega2561 (the **M**ain **P**rocessing **U**nit) via UART.
Having two chips is important, as it enables me to pack more features into the
final product.

The contraption (in the way that I'm envisioning it) will be powered by either
3 AAA batteries at 1.5V each or 4.5V total, or one Lithium Polymer cell at 3.7V,
both of these satisfy the voltage requirements of both controllers (2.7V-5.5V).

Unlike some calculators I've used previously, this one will be
easy to hack into, due to the chips and their programming interfaces being exposed
on the PCB. No tar or rubber covering them up!


Tasks ahead:
- [ ] write a comprehensive Readme
  - [x] add technical details
  - [x] explain differences between the OSSC and already available calculators
  - [ ] add flowcharts to explain what is going on inside the thing
  - [ ] add a "planned features" overview
- [ ] add schematics
- [ ] make PCBs
	- [ ] add pads and circuitry for batteries
- [ ] write code for the KC
  - [X] Fix ```lvalue required as left operand of assignment``` errors
  - [X] add UART functionality
  - [ ] test circuit and code in Proteus
- [ ] write code for the MPU
- [ ] design case
