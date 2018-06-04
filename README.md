# ParkSensors

# Overview
	University project. Main idea is to program Park Sensor based on STM32F4 Discovery.

# Description:
	Hardware used:
	- STM32F4 Discovery
	- 3x HC-SR04 Ultrasonic sensors
	- Module 4x8-segment display with common anode
	- Buzzer TMB12A05

	Code based on IRQ procedure.

	The goal of the project was to construct a prototype of a park sensor to assist the driver during a backdown.

	Each sensor measures the distance about 3 times per second, this distance is calculated on a 4-steps hazard scale by the following rule:

	Above 150 cm - 0. level
	Between 150 cm and 100 cm - 1st level
	Between 100 cm and 40 cm - 2nd level
	Below 40 cm - 3rd level

	This result is display on the display showing the right number of lines depending on the level of danger on specified side, additionally buzzer inform about it by beeping.

	0 level - silence
	1st level - 1 Hz beeping
	2nd level - 2 Hz beeping
	3rd level - 10 Hz beeping

# How it works
![How_it_works](https://raw.githubusercontent.com/PUT-PTM/ParkSensors/master/How_it_works.png)

# Watch the video
[![Watch the video](https://img.youtube.com/vi/Wq1tUOCfatI/0.jpg)](https://youtu.be/Wq1tUOCfatI)


# Tools:
	Used software is System WorkBench for STM32 (version 2.2.0)
	Code based on Standard Peripheral Library which is not supported on higher version of compiler.

# How to run:
	Download the code, build and run it on System WorkBench for STM32 (v. 2.2.0) or other compatible STM32 compiler remembering about the appropriate code adaptation.

	Connect following pins:
		HC-SR04:
		- Vcc ---> 5V pin
		- GND ---> GND pin
		1)
			Trig ---> PE5
			Echo ---> PE4
		2)
			Trig ---> PA3
			Echo ---> PA2
		3)
			Trig ---> PE1
			Echo ---> PE0

		DISPLAY:
		- Vcc ---> 3V pin
		- 1 ---> PD0
		- 2 ---> PD1
		- 3 ---> PD2
		- 4 ---> PD3
		- a ---> PD4
		- d ---> PD5
		- g ---> PD6

		BUZZER:
		- Short pin ---> GND pin
		- Long pin  ---> PC1

# Future improvements:
	1) Control of the buzzer through the transistor to protect against short-circuiting.
	2) Changing the ultrasonic sensors for a more reliable and weather resistant model.
	3) A better and easier to use display.

# License: MIT

# Credits:
	Rafał Isbrandt
	Konrad Grzelczyk

	The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
	Supervisor: Tomasz Mańkowski
