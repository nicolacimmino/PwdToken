EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20SU U1
U 1 1 608558E4
P 3450 3450
F 0 "U1" H 3050 4000 50  0000 R CNN
F 1 "ATtiny85-20SU" H 4100 2850 50  0000 R CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3450 3450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3450 3450 50  0001 C CNN
	1    3450 3450
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0402 R2
U 1 1 60856623
P 5450 3400
F 0 "R2" H 5375 3500 45  0000 C CNN
F 1 "68R" H 5550 3500 45  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5450 3550 20  0001 C CNN
F 3 "" H 5450 3400 60  0001 C CNN
F 4 " " H 5350 3100 60  0000 C CNN "Field4"
	1    5450 3400
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0402 R3
U 1 1 60858241
P 5450 3600
F 0 "R3" H 5350 3500 45  0000 C CNN
F 1 "68R" H 5500 3500 45  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5450 3750 20  0001 C CNN
F 3 "" H 5450 3600 60  0001 C CNN
F 4 " " H 5450 3721 60  0000 C CNN "Field4"
	1    5450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3450 5000 3450
Wire Wire Line
	5000 3450 5000 3400
Wire Wire Line
	5000 3400 5250 3400
Wire Wire Line
	4050 3550 5000 3550
Wire Wire Line
	5000 3550 5000 3600
Wire Wire Line
	5000 3600 5250 3600
$Comp
L power:VCC #PWR05
U 1 1 6085C6FB
P 6000 2650
F 0 "#PWR05" H 6000 2500 50  0001 C CNN
F 1 "VCC" H 6015 2823 50  0000 C CNN
F 2 "" H 6000 2650 50  0001 C CNN
F 3 "" H 6000 2650 50  0001 C CNN
	1    6000 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2650 6000 2750
$Comp
L power:GND #PWR06
U 1 1 6085D0F0
P 6300 3700
F 0 "#PWR06" H 6300 3450 50  0001 C CNN
F 1 "GND" H 6400 3600 50  0000 C CNN
F 2 "" H 6300 3700 50  0001 C CNN
F 3 "" H 6300 3700 50  0001 C CNN
	1    6300 3700
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0402 R4
U 1 1 6085D8E8
P 5750 3000
F 0 "R4" V 5750 2850 45  0000 C CNN
F 1 "1K5" V 5850 2850 45  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5750 3150 20  0001 C CNN
F 3 "" H 5750 3000 60  0001 C CNN
F 4 " " H 5650 2700 60  0000 C CNN "Field4"
	1    5750 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 2800 5750 2750
Wire Wire Line
	5750 2750 6000 2750
Connection ~ 6000 2750
Wire Wire Line
	6000 2750 6000 3350
Wire Wire Line
	3450 2850 3450 2750
Wire Wire Line
	3450 2750 4500 2750
Connection ~ 5750 2750
$Comp
L Device:D_Zener D3
U 1 1 6085FA6B
P 6050 3850
F 0 "D3" V 6050 3900 50  0000 L CNN
F 1 "3V6" V 6150 3850 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-128" H 6050 3850 50  0001 C CNN
F 3 "~" H 6050 3850 50  0001 C CNN
	1    6050 3850
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 6086082E
P 5750 3850
F 0 "D2" V 5750 3700 50  0000 L CNN
F 1 "3V6" V 5850 3700 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-128" H 5750 3850 50  0001 C CNN
F 3 "~" H 5750 3850 50  0001 C CNN
	1    5750 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 3450 6050 3450
Wire Wire Line
	6000 3350 6350 3350
$Comp
L usb_a_pcb:USB_A_PCB J1
U 1 1 60853ED1
P 6650 3150
F 0 "J1" H 6878 2871 50  0000 L CNN
F 1 "USB_A_PCB" H 6878 2780 50  0000 L CNN
F 2 "PwdToken:usb-PCB" H 6650 3150 50  0001 C CNN
F 3 "" H 6650 3150 50  0001 C CNN
	1    6650 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3650 6350 3650
Wire Wire Line
	5750 4000 5750 4100
Wire Wire Line
	6050 4000 6050 4100
Wire Wire Line
	5750 4100 5900 4100
Wire Wire Line
	6050 3700 6050 3450
Connection ~ 6050 3450
Wire Wire Line
	6050 3450 6350 3450
$Comp
L Device:LED D1
U 1 1 608653BE
P 5150 3850
F 0 "D1" V 5189 3732 50  0000 R CNN
F 1 "LED" V 5098 3732 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5150 3850 50  0001 C CNN
F 3 "~" H 5150 3850 50  0001 C CNN
	1    5150 3850
	0    -1   -1   0   
$EndComp
$Comp
L SparkFun-Resistors:RESISTOR0402 R1
U 1 1 60868302
P 4750 3250
F 0 "R1" H 4850 3150 45  0000 C CNN
F 1 "470" H 4700 3150 45  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4750 3400 20  0001 C CNN
F 3 "" H 4750 3250 60  0001 C CNN
F 4 " " H 4650 2950 60  0000 C CNN "Field4"
	1    4750 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4050 3250 4300 3250
Wire Wire Line
	5150 3250 5150 3700
$Comp
L power:GND #PWR03
U 1 1 6086B17D
P 5150 4250
F 0 "#PWR03" H 5150 4000 50  0001 C CNN
F 1 "GND" H 5155 4077 50  0000 C CNN
F 2 "" H 5150 4250 50  0001 C CNN
F 3 "" H 5150 4250 50  0001 C CNN
	1    5150 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4250 5150 4000
Wire Wire Line
	6300 3650 6300 3700
$Comp
L power:GND #PWR04
U 1 1 6087103B
P 5900 4250
F 0 "#PWR04" H 5900 4000 50  0001 C CNN
F 1 "GND" H 5905 4077 50  0000 C CNN
F 2 "" H 5900 4250 50  0001 C CNN
F 3 "" H 5900 4250 50  0001 C CNN
	1    5900 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4100 5900 4250
Connection ~ 5900 4100
Wire Wire Line
	5900 4100 6050 4100
$Comp
L Switch:SW_Push SW1
U 1 1 60872912
P 4250 3900
F 0 "SW1" V 4300 3700 50  0000 L CNN
F 1 "A" V 4150 4200 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Tactile_Straight_KSA0Axx1LFTR" H 4250 4100 50  0001 C CNN
F 3 "~" H 4250 4100 50  0001 C CNN
	1    4250 3900
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 6087810F
P 4450 3900
F 0 "SW2" V 4500 4000 50  0000 L CNN
F 1 "B" V 4350 3550 50  0000 L CNN
F 2 "Button_Switch_THT:SW_Tactile_Straight_KSA0Axx1LFTR" H 4450 4100 50  0001 C CNN
F 3 "~" H 4450 4100 50  0001 C CNN
	1    4450 3900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 60878455
P 4350 4250
F 0 "#PWR02" H 4350 4000 50  0001 C CNN
F 1 "GND" H 4355 4077 50  0000 C CNN
F 2 "" H 4350 4250 50  0001 C CNN
F 3 "" H 4350 4250 50  0001 C CNN
	1    4350 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4250 4350 4100
Wire Wire Line
	4350 4100 4250 4100
Wire Wire Line
	4350 4100 4450 4100
Connection ~ 4350 4100
Wire Wire Line
	4250 3700 4250 3350
Wire Wire Line
	4250 3350 4050 3350
Wire Wire Line
	4450 3150 4200 3150
$Comp
L power:GND #PWR01
U 1 1 608806C2
P 3450 4250
F 0 "#PWR01" H 3450 4000 50  0001 C CNN
F 1 "GND" H 3455 4077 50  0000 C CNN
F 2 "" H 3450 4250 50  0001 C CNN
F 3 "" H 3450 4250 50  0001 C CNN
	1    3450 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4250 3450 4050
Wire Wire Line
	4450 3150 4450 3700
Wire Wire Line
	4950 3250 5150 3250
$Comp
L SparkFun-Connectors:JST_6_PIN_VERTICAL J2
U 1 1 608A5121
P 4100 2350
F 0 "J2" V 3963 2928 45  0000 L CNN
F 1 "JST_6_PIN_VERTICAL" V 4047 2928 45  0001 L CNN
F 2 "Connectors:1X06" H 4100 3050 20  0001 C CNN
F 3 "" H 4100 2350 50  0001 C CNN
F 4 "CONN-08249" V 4142 2928 60  0001 L CNN "Field4"
	1    4100 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 3650 4100 3650
Wire Wire Line
	4100 3650 4100 2450
Wire Wire Line
	4200 2450 4200 3150
Connection ~ 4200 3150
Wire Wire Line
	4200 3150 4050 3150
Wire Wire Line
	4300 3250 4300 2450
Connection ~ 4300 3250
Wire Wire Line
	4300 3250 4550 3250
Wire Wire Line
	4400 2450 4400 3350
Wire Wire Line
	4400 3350 4250 3350
Connection ~ 4250 3350
Wire Wire Line
	4500 2450 4500 2750
Connection ~ 4500 2750
Wire Wire Line
	4500 2750 5750 2750
$Comp
L power:GND #PWR07
U 1 1 608AA7BB
P 4600 2450
F 0 "#PWR07" H 4600 2200 50  0001 C CNN
F 1 "GND" H 4600 2300 50  0000 C CNN
F 2 "" H 4600 2450 50  0001 C CNN
F 3 "" H 4600 2450 50  0001 C CNN
	1    4600 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3200 5750 3400
Wire Wire Line
	5650 3400 5750 3400
Connection ~ 5750 3400
Wire Wire Line
	5750 3400 5750 3450
Wire Wire Line
	5750 3700 5750 3600
Wire Wire Line
	5750 3550 6350 3550
Wire Wire Line
	5650 3600 5750 3600
Connection ~ 5750 3600
Wire Wire Line
	5750 3600 5750 3550
$EndSCHEMATC
