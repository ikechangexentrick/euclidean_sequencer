EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
L Device:Rotary_Encoder SW2
U 1 1 6107E3BF
P 1400 1350
F 0 "SW2" V 1389 1120 50  0000 R CNN
F 1 "Rotary_Encoder" V 1298 1120 50  0000 R CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E_Vertical_H20mm" H 1250 1510 50  0001 C CNN
F 3 "~" H 1400 1610 50  0001 C CNN
	1    1400 1350
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_BJT:2SC1815 Q1
U 1 1 6107E3C5
P 2650 4750
F 0 "Q1" H 2840 4796 50  0000 L CNN
F 1 "2SC1815" H 2840 4705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2850 4675 50  0001 L CIN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Toshiba%20PDFs/2SC1815.pdf" H 2650 4750 50  0001 L CNN
	1    2650 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 6107E3CB
P 1400 1650
F 0 "#PWR019" H 1400 1400 50  0001 C CNN
F 1 "GND" H 1405 1477 50  0000 C CNN
F 2 "" H 1400 1650 50  0001 C CNN
F 3 "" H 1400 1650 50  0001 C CNN
	1    1400 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1650 1500 1900
$Comp
L Device:R R4
U 1 1 6107E3D2
P 1850 1750
F 0 "R4" H 1920 1796 50  0000 L CNN
F 1 "10k" H 1920 1705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1780 1750 50  0001 C CNN
F 3 "~" H 1850 1750 50  0001 C CNN
	1    1850 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 6107E3D8
P 2150 1900
F 0 "R8" V 1943 1900 50  0000 C CNN
F 1 "10k" V 2034 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2080 1900 50  0001 C CNN
F 3 "~" H 2150 1900 50  0001 C CNN
	1    2150 1900
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 6107E3DE
P 2350 2050
F 0 "C3" H 2465 2096 50  0000 L CNN
F 1 "0.1u" H 2465 2005 50  0000 L CNN
F 2 "Attenuverter:C_Axial_L4.8mm_D3.1mm_P5.08mm_Horizontal" H 2388 1900 50  0001 C CNN
F 3 "~" H 2350 2050 50  0001 C CNN
	1    2350 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 6107E3E4
P 2350 2200
F 0 "#PWR024" H 2350 1950 50  0001 C CNN
F 1 "GND" H 2355 2027 50  0000 C CNN
F 2 "" H 2350 2200 50  0001 C CNN
F 3 "" H 2350 2200 50  0001 C CNN
	1    2350 2200
	1    0    0    -1  
$EndComp
Text Label 1850 1600 0    50   ~ 0
Vcc
Wire Wire Line
	1500 1900 1850 1900
Connection ~ 1850 1900
Wire Wire Line
	1850 1900 2000 1900
Wire Wire Line
	2300 1900 2350 1900
Connection ~ 2350 1900
Wire Wire Line
	2350 1900 2550 1900
$Comp
L Device:R R5
U 1 1 6107E3F1
P 1850 2450
F 0 "R5" H 1920 2496 50  0000 L CNN
F 1 "10k" H 1920 2405 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1780 2450 50  0001 C CNN
F 3 "~" H 1850 2450 50  0001 C CNN
	1    1850 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6107E3F7
P 2150 2600
F 0 "R9" V 1943 2600 50  0000 C CNN
F 1 "10k" V 2034 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2080 2600 50  0001 C CNN
F 3 "~" H 2150 2600 50  0001 C CNN
	1    2150 2600
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 6107E3FD
P 2350 2750
F 0 "C4" H 2465 2796 50  0000 L CNN
F 1 "0.1u" H 2465 2705 50  0000 L CNN
F 2 "Attenuverter:C_Axial_L4.8mm_D3.1mm_P5.08mm_Horizontal" H 2388 2600 50  0001 C CNN
F 3 "~" H 2350 2750 50  0001 C CNN
	1    2350 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 6107E403
P 2350 2900
F 0 "#PWR025" H 2350 2650 50  0001 C CNN
F 1 "GND" H 2355 2727 50  0000 C CNN
F 2 "" H 2350 2900 50  0001 C CNN
F 3 "" H 2350 2900 50  0001 C CNN
	1    2350 2900
	1    0    0    -1  
$EndComp
Text Label 1850 2300 0    50   ~ 0
Vcc
Connection ~ 1850 2600
Wire Wire Line
	1850 2600 2000 2600
Wire Wire Line
	2300 2600 2350 2600
Connection ~ 2350 2600
Wire Wire Line
	2350 2600 2550 2600
Wire Wire Line
	1300 1650 1300 2600
Wire Wire Line
	1300 2600 1850 2600
Text Label 2550 1900 0    50   ~ 0
rsw_1
Text Label 2550 2600 0    50   ~ 0
rsw_2
$Comp
L Device:R R6
U 1 1 6107E419
P 2250 4900
F 0 "R6" H 2180 4854 50  0000 R CNN
F 1 "100k" H 2180 4945 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2180 4900 50  0001 C CNN
F 3 "~" H 2250 4900 50  0001 C CNN
	1    2250 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 6107E41F
P 2750 5150
F 0 "R10" H 2680 5104 50  0000 R CNN
F 1 "100k" H 2680 5195 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2680 5150 50  0001 C CNN
F 3 "~" H 2750 5150 50  0001 C CNN
	1    2750 5150
	-1   0    0    1   
$EndComp
Text Label 2750 4550 1    50   ~ 0
Vcc
Wire Wire Line
	2250 4750 2450 4750
Wire Wire Line
	2750 4950 2750 5000
Wire Wire Line
	2750 5000 3050 5000
Connection ~ 2750 5000
$Comp
L power:GND #PWR026
U 1 1 6107E42C
P 2750 5300
F 0 "#PWR026" H 2750 5050 50  0001 C CNN
F 1 "GND" H 2755 5127 50  0000 C CNN
F 2 "" H 2750 5300 50  0001 C CNN
F 3 "" H 2750 5300 50  0001 C CNN
	1    2750 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 6107E432
P 2250 5050
F 0 "#PWR023" H 2250 4800 50  0001 C CNN
F 1 "GND" H 2255 4877 50  0000 C CNN
F 2 "" H 2250 5050 50  0001 C CNN
F 3 "" H 2250 5050 50  0001 C CNN
	1    2250 5050
	1    0    0    -1  
$EndComp
Text Label 3050 5000 0    50   ~ 0
clock
$Comp
L Device:LED D1
U 1 1 6107E44C
P 9900 3150
F 0 "D1" V 9939 3032 50  0000 R CNN
F 1 "led_beat" V 9848 3032 50  0000 R CNN
F 2 "LED_THT:LED_D4.0mm" H 9900 3150 50  0001 C CNN
F 3 "~" H 9900 3150 50  0001 C CNN
	1    9900 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 6107E452
P 9900 3450
F 0 "R1" H 9830 3404 50  0000 R CNN
F 1 "10k" H 9830 3495 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 9830 3450 50  0001 C CNN
F 3 "~" H 9900 3450 50  0001 C CNN
	1    9900 3450
	-1   0    0    1   
$EndComp
Text Label 9800 3000 2    50   ~ 0
beat_out
$Comp
L Device:R R11
U 1 1 6107E46F
P 10250 3000
F 0 "R11" V 10457 3000 50  0000 C CNN
F 1 "1k" V 10366 3000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 10180 3000 50  0001 C CNN
F 3 "~" H 10250 3000 50  0001 C CNN
	1    10250 3000
	0    -1   -1   0   
$EndComp
$Comp
L Connector:AudioJack2_SwitchT J4
U 1 1 6107E475
P 10600 3000
F 0 "J4" H 10420 2933 50  0000 R CNN
F 1 "beat_out" H 10420 3024 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 10600 3000 50  0001 C CNN
F 3 "~" H 10600 3000 50  0001 C CNN
	1    10600 3000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 6107E47B
P 9900 3600
F 0 "#PWR018" H 9900 3350 50  0001 C CNN
F 1 "GND" H 9905 3427 50  0000 C CNN
F 2 "" H 9900 3600 50  0001 C CNN
F 3 "" H 9900 3600 50  0001 C CNN
	1    9900 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 6107E481
P 10400 3100
F 0 "#PWR027" H 10400 2850 50  0001 C CNN
F 1 "GND" H 10405 2927 50  0000 C CNN
F 2 "" H 10400 3100 50  0001 C CNN
F 3 "" H 10400 3100 50  0001 C CNN
	1    10400 3100
	1    0    0    -1  
$EndComp
NoConn ~ 10400 2900
$Comp
L Switch:SW_Push SW?
U 1 1 610916DB
P 1850 3650
AR Path="/610916DB" Ref="SW?"  Part="1" 
AR Path="/611959D0/610916DB" Ref="SW3"  Part="1" 
F 0 "SW3" H 1850 3935 50  0000 C CNN
F 1 "enter" H 1850 3844 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1850 3850 50  0001 C CNN
F 3 "~" H 1850 3850 50  0001 C CNN
	1    1850 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610916F0
P 1650 3650
AR Path="/610916F0" Ref="#PWR?"  Part="1" 
AR Path="/611959D0/610916F0" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1650 3400 50  0001 C CNN
F 1 "GND" H 1655 3477 50  0000 C CNN
F 2 "" H 1650 3650 50  0001 C CNN
F 3 "" H 1650 3650 50  0001 C CNN
	1    1650 3650
	1    0    0    -1  
$EndComp
Text Label 2050 3650 0    50   ~ 0
btn_enter
$Comp
L Device:LED D2
U 1 1 610951A6
P 1550 4900
F 0 "D2" V 1589 4782 50  0000 R CNN
F 1 "led_clock" V 1498 4782 50  0000 R CNN
F 2 "LED_THT:LED_D4.0mm" H 1550 4900 50  0001 C CNN
F 3 "~" H 1550 4900 50  0001 C CNN
	1    1550 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R20
U 1 1 610951D8
P 1550 5200
F 0 "R20" H 1480 5154 50  0000 R CNN
F 1 "10k" H 1480 5245 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1480 5200 50  0001 C CNN
F 3 "~" H 1550 5200 50  0001 C CNN
	1    1550 5200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 610951EE
P 1550 5350
F 0 "#PWR0102" H 1550 5100 50  0001 C CNN
F 1 "GND" H 1555 5177 50  0000 C CNN
F 2 "" H 1550 5350 50  0001 C CNN
F 3 "" H 1550 5350 50  0001 C CNN
	1    1550 5350
	1    0    0    -1  
$EndComp
NoConn ~ 1350 4650
$Comp
L power:GND #PWR020
U 1 1 6107E43E
P 1350 4850
F 0 "#PWR020" H 1350 4600 50  0001 C CNN
F 1 "GND" H 1355 4677 50  0000 C CNN
F 2 "" H 1350 4850 50  0001 C CNN
F 3 "" H 1350 4850 50  0001 C CNN
	1    1350 4850
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack2_SwitchT J3
U 1 1 6107E438
P 1150 4750
F 0 "J3" H 971 4683 50  0000 R CNN
F 1 "clock_in" H 971 4774 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 1150 4750 50  0001 C CNN
F 3 "~" H 1150 4750 50  0001 C CNN
	1    1150 4750
	1    0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 6107E413
P 1950 4750
F 0 "R2" V 1743 4750 50  0000 C CNN
F 1 "100k" V 1834 4750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 1880 4750 50  0001 C CNN
F 3 "~" H 1950 4750 50  0001 C CNN
	1    1950 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 4750 2100 4750
Connection ~ 2250 4750
Wire Wire Line
	1350 4750 1550 4750
Connection ~ 1550 4750
Wire Wire Line
	1550 4750 1800 4750
$Comp
L Device:R R28
U 1 1 6310AAC6
P 4700 1550
F 0 "R28" V 4493 1550 50  0000 C CNN
F 1 "100k" V 4584 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4630 1550 50  0001 C CNN
F 3 "~" H 4700 1550 50  0001 C CNN
	1    4700 1550
	0    1    1    0   
$EndComp
$Comp
L Connector:AudioJack2_SwitchT J1
U 1 1 6310D27B
P 4250 1550
F 0 "J1" H 4071 1483 50  0000 R CNN
F 1 "CV_len" H 4071 1574 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 4250 1550 50  0001 C CNN
F 3 "~" H 4250 1550 50  0001 C CNN
	1    4250 1550
	1    0    0    1   
$EndComp
Text Label 4850 1550 0    50   ~ 0
cv_len_in
$Comp
L power:GND #PWR046
U 1 1 6312A5A7
P 4450 1650
F 0 "#PWR046" H 4450 1400 50  0001 C CNN
F 1 "GND" H 4455 1477 50  0000 C CNN
F 2 "" H 4450 1650 50  0001 C CNN
F 3 "" H 4450 1650 50  0001 C CNN
	1    4450 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1550 4550 1550
$Comp
L power:GND #PWR050
U 1 1 6312CAB0
P 4500 1450
F 0 "#PWR050" H 4500 1200 50  0001 C CNN
F 1 "GND" H 4505 1277 50  0000 C CNN
F 2 "" H 4500 1450 50  0001 C CNN
F 3 "" H 4500 1450 50  0001 C CNN
	1    4500 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 1450 4500 1450
$Comp
L Device:R R29
U 1 1 63143008
P 4700 2350
F 0 "R29" V 4493 2350 50  0000 C CNN
F 1 "100k" V 4584 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4630 2350 50  0001 C CNN
F 3 "~" H 4700 2350 50  0001 C CNN
	1    4700 2350
	0    1    1    0   
$EndComp
$Comp
L Connector:AudioJack2_SwitchT J5
U 1 1 6314301A
P 4250 2350
F 0 "J5" H 4071 2283 50  0000 R CNN
F 1 "CV_num" H 4071 2374 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 4250 2350 50  0001 C CNN
F 3 "~" H 4250 2350 50  0001 C CNN
	1    4250 2350
	1    0    0    1   
$EndComp
Text Label 4850 2350 0    50   ~ 0
cv_num_in
$Comp
L power:GND #PWR047
U 1 1 63143063
P 4450 2450
F 0 "#PWR047" H 4450 2200 50  0001 C CNN
F 1 "GND" H 4455 2277 50  0000 C CNN
F 2 "" H 4450 2450 50  0001 C CNN
F 3 "" H 4450 2450 50  0001 C CNN
	1    4450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2350 4550 2350
$Comp
L power:GND #PWR051
U 1 1 6314306A
P 4500 2250
F 0 "#PWR051" H 4500 2000 50  0001 C CNN
F 1 "GND" H 4505 2077 50  0000 C CNN
F 2 "" H 4500 2250 50  0001 C CNN
F 3 "" H 4500 2250 50  0001 C CNN
	1    4500 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 2250 4500 2250
$Comp
L Device:R R30
U 1 1 63182651
P 4700 3100
F 0 "R30" V 4493 3100 50  0000 C CNN
F 1 "100k" V 4584 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4630 3100 50  0001 C CNN
F 3 "~" H 4700 3100 50  0001 C CNN
	1    4700 3100
	0    1    1    0   
$EndComp
$Comp
L Connector:AudioJack2_SwitchT J6
U 1 1 63182663
P 4250 3100
F 0 "J6" H 4071 3033 50  0000 R CNN
F 1 "CV_sft" H 4071 3124 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 4250 3100 50  0001 C CNN
F 3 "~" H 4250 3100 50  0001 C CNN
	1    4250 3100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR048
U 1 1 631826AC
P 4450 3200
F 0 "#PWR048" H 4450 2950 50  0001 C CNN
F 1 "GND" H 4455 3027 50  0000 C CNN
F 2 "" H 4450 3200 50  0001 C CNN
F 3 "" H 4450 3200 50  0001 C CNN
	1    4450 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3100 4550 3100
$Comp
L power:GND #PWR052
U 1 1 631826B3
P 4500 3000
F 0 "#PWR052" H 4500 2750 50  0001 C CNN
F 1 "GND" H 4505 2827 50  0000 C CNN
F 2 "" H 4500 3000 50  0001 C CNN
F 3 "" H 4500 3000 50  0001 C CNN
	1    4500 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 3000 4500 3000
$Comp
L Connector:AudioJack2_SwitchT J7
U 1 1 6329B62E
P 4250 4050
F 0 "J7" H 4071 3983 50  0000 R CNN
F 1 "CV_select" H 4071 4074 50  0000 R CNN
F 2 "Attenuverter:mono_jack_3.5mm" H 4250 4050 50  0001 C CNN
F 3 "~" H 4250 4050 50  0001 C CNN
	1    4250 4050
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR049
U 1 1 6329B634
P 4450 4150
F 0 "#PWR049" H 4450 3900 50  0001 C CNN
F 1 "GND" H 4455 3977 50  0000 C CNN
F 2 "" H 4450 4150 50  0001 C CNN
F 3 "" H 4450 4150 50  0001 C CNN
	1    4450 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR053
U 1 1 6329B63B
P 4500 3950
F 0 "#PWR053" H 4500 3700 50  0001 C CNN
F 1 "GND" H 4505 3777 50  0000 C CNN
F 2 "" H 4500 3950 50  0001 C CNN
F 3 "" H 4500 3950 50  0001 C CNN
	1    4500 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 3950 4500 3950
$Comp
L Diode:1N4148 D12
U 1 1 632A60CF
P 5150 4200
F 0 "D12" V 5104 4280 50  0000 L CNN
F 1 "1N4148" V 5195 4280 50  0000 L CNN
F 2 "Diode_THT:D_DO-34_SOD68_P2.54mm_Vertical_AnodeUp" H 5150 4025 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5150 4200 50  0001 C CNN
	1    5150 4200
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D11
U 1 1 632A60D5
P 5150 3900
F 0 "D11" V 5104 3980 50  0000 L CNN
F 1 "1N4148" V 5195 3980 50  0000 L CNN
F 2 "Diode_THT:D_DO-34_SOD68_P2.54mm_Vertical_AnodeUp" H 5150 3725 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5150 3900 50  0001 C CNN
	1    5150 3900
	0    1    1    0   
$EndComp
Connection ~ 5150 4050
Wire Wire Line
	5150 4050 5300 4050
$Comp
L power:GND #PWR055
U 1 1 632A60DE
P 5150 4350
F 0 "#PWR055" H 5150 4100 50  0001 C CNN
F 1 "GND" H 5155 4177 50  0000 C CNN
F 2 "" H 5150 4350 50  0001 C CNN
F 3 "" H 5150 4350 50  0001 C CNN
	1    5150 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR054
U 1 1 632A60E4
P 5150 3750
F 0 "#PWR054" H 5150 3600 50  0001 C CNN
F 1 "+5V" H 5165 3923 50  0000 C CNN
F 2 "" H 5150 3750 50  0001 C CNN
F 3 "" H 5150 3750 50  0001 C CNN
	1    5150 3750
	1    0    0    -1  
$EndComp
Text Label 5300 4050 0    50   ~ 0
cv_select_in
Wire Wire Line
	4850 4050 5150 4050
$Comp
L Arduino_compatible:OLED_Display_SSD1306 U5
U 1 1 632DC531
P 2000 6150
F 0 "U5" H 2528 6038 50  0000 L CNN
F 1 "OLED_Display_SSD1306" H 2528 5947 50  0000 L CNN
F 2 "Attenuverter:aki_OLED_0.96in" H 2000 6150 50  0001 C CNN
F 3 "" H 2000 6150 50  0001 C CNN
	1    2000 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 632DC537
P 1600 7400
F 0 "#PWR044" H 1600 7150 50  0001 C CNN
F 1 "GND" H 1605 7227 50  0000 C CNN
F 2 "" H 1600 7400 50  0001 C CNN
F 3 "" H 1600 7400 50  0001 C CNN
	1    1600 7400
	1    0    0    -1  
$EndComp
Text Label 2600 6950 0    50   ~ 0
scl
Text Label 2600 6700 0    50   ~ 0
sda
$Comp
L Device:CP C12
U 1 1 632DC53F
P 1750 7400
F 0 "C12" V 1495 7400 50  0000 C CNN
F 1 "100u" V 1586 7400 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 1788 7250 50  0001 C CNN
F 3 "~" H 1750 7400 50  0001 C CNN
	1    1750 7400
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 7000 1900 7400
Wire Wire Line
	1700 6600 1600 6600
Wire Wire Line
	1600 7000 1600 7400
Connection ~ 1600 7400
$Comp
L Device:R R26
U 1 1 632DC549
P 2450 6700
F 0 "R26" H 2520 6746 50  0000 L CNN
F 1 "1k" H 2520 6655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2380 6700 50  0001 C CNN
F 3 "~" H 2450 6700 50  0001 C CNN
	1    2450 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R R27
U 1 1 632DC54F
P 2450 6950
F 0 "R27" H 2520 6996 50  0000 L CNN
F 1 "1k" H 2520 6905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2380 6950 50  0001 C CNN
F 3 "~" H 2450 6950 50  0001 C CNN
	1    2450 6950
	0    1    1    0   
$EndComp
Wire Wire Line
	2300 6600 2300 6700
Wire Wire Line
	2100 6600 2100 6950
Wire Wire Line
	2100 6950 2300 6950
$Comp
L power:+5V #PWR045
U 1 1 632E170B
P 1900 7400
F 0 "#PWR045" H 1900 7250 50  0001 C CNN
F 1 "+5V" V 2000 7450 50  0000 L CNN
F 2 "" H 1900 7400 50  0001 C CNN
F 3 "" H 1900 7400 50  0001 C CNN
	1    1900 7400
	0    1    1    0   
$EndComp
Connection ~ 1900 7400
Wire Wire Line
	9800 3000 9900 3000
Connection ~ 9900 3000
Wire Wire Line
	9900 3000 10100 3000
Text Label 4850 3100 0    50   ~ 0
cv_sft_in
Text Label 7700 3150 0    50   ~ 0
rsw_1
Text Label 6400 3450 0    50   ~ 0
rsw_2
Text Label 7700 3250 0    50   ~ 0
cv_len_in
Text Label 7700 3350 0    50   ~ 0
cv_num_in
Text Label 7700 3550 0    50   ~ 0
cv_sft_in
Text Label 7700 3850 0    50   ~ 0
beat_out
Text Label 6400 3850 0    50   ~ 0
cv_select_in
Text Label 6400 3350 0    50   ~ 0
btn_enter
Text Label 7700 3750 0    50   ~ 0
clock
Text Label 6400 3150 0    50   ~ 0
sda
Text Label 6400 3250 0    50   ~ 0
scl
$Comp
L power:GND #PWR056
U 1 1 633CB46C
P 6400 3550
F 0 "#PWR056" H 6400 3300 50  0001 C CNN
F 1 "GND" H 6405 3377 50  0000 C CNN
F 2 "" H 6400 3550 50  0001 C CNN
F 3 "" H 6400 3550 50  0001 C CNN
	1    6400 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR057
U 1 1 633CB78B
P 7700 3450
F 0 "#PWR057" H 7700 3300 50  0001 C CNN
F 1 "+5V" H 7715 3623 50  0000 C CNN
F 2 "" H 7700 3450 50  0001 C CNN
F 3 "" H 7700 3450 50  0001 C CNN
	1    7700 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R31
U 1 1 633CC6D5
P 4700 4050
F 0 "R31" V 4493 4050 50  0000 C CNN
F 1 "100k" V 4584 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4630 4050 50  0001 C CNN
F 3 "~" H 4700 4050 50  0001 C CNN
	1    4700 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 4050 4450 4050
$Comp
L power:GND #PWR060
U 1 1 631340B2
P 7700 3650
F 0 "#PWR060" H 7700 3400 50  0001 C CNN
F 1 "GND" H 7705 3477 50  0000 C CNN
F 2 "" H 7700 3650 50  0001 C CNN
F 3 "" H 7700 3650 50  0001 C CNN
	1    7700 3650
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR059
U 1 1 631346AC
P 6400 3750
F 0 "#PWR059" H 6400 3600 50  0001 C CNN
F 1 "+5V" H 6415 3923 50  0000 C CNN
F 2 "" H 6400 3750 50  0001 C CNN
F 3 "" H 6400 3750 50  0001 C CNN
	1    6400 3750
	0    1    1    0   
$EndComp
Text Label 6400 3750 0    50   ~ 0
Vcc
$Comp
L Connector:Conn_01x08_Female J8
U 1 1 6313A700
P 6200 3450
F 0 "J8" H 6092 3935 50  0000 C CNN
F 1 "Conn_Left" H 6092 3844 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 6200 3450 50  0001 C CNN
F 3 "~" H 6200 3450 50  0001 C CNN
	1    6200 3450
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J9
U 1 1 6313CA4A
P 7500 3450
F 0 "J9" H 7392 3935 50  0000 C CNN
F 1 "Conn_Right" H 7392 3844 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 7500 3450 50  0001 C CNN
F 3 "~" H 7500 3450 50  0001 C CNN
	1    7500 3450
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR058
U 1 1 63140D09
P 6400 3650
F 0 "#PWR058" H 6400 3400 50  0001 C CNN
F 1 "GND" H 6405 3477 50  0000 C CNN
F 2 "" H 6400 3650 50  0001 C CNN
F 3 "" H 6400 3650 50  0001 C CNN
	1    6400 3650
	0    -1   -1   0   
$EndComp
Text HLabel 6900 3150 2    50   Input ~ 0
sda
Text HLabel 6900 3250 2    50   Input ~ 0
scl
Text HLabel 6900 3350 2    50   Input ~ 0
btn_enter
Text HLabel 6900 3450 2    50   Input ~ 0
rsw_2
Text HLabel 6900 3850 2    50   Input ~ 0
cv_select_in
Wire Wire Line
	6400 3150 6900 3150
Wire Wire Line
	6900 3250 6400 3250
Wire Wire Line
	6400 3350 6900 3350
Wire Wire Line
	6900 3450 6400 3450
Wire Wire Line
	6400 3850 6900 3850
Text HLabel 8150 3150 2    50   Input ~ 0
rsw_1
Text HLabel 8150 3250 2    50   Input ~ 0
cv_len_in
Text HLabel 8150 3350 2    50   Input ~ 0
cv_num_in
Text HLabel 8150 3550 2    50   Input ~ 0
cv_sft_in
Text HLabel 8150 3750 2    50   Input ~ 0
clock
Text HLabel 8150 3850 2    50   Input ~ 0
beat_out
Wire Wire Line
	7700 3150 8150 3150
Wire Wire Line
	8150 3250 7700 3250
Wire Wire Line
	7700 3350 8150 3350
Wire Wire Line
	8150 3550 7700 3550
Wire Wire Line
	7700 3750 8150 3750
Wire Wire Line
	8150 3850 7700 3850
$Comp
L Device:C C13
U 1 1 634DD5D6
P 1750 7000
F 0 "C13" H 1865 7046 50  0000 L CNN
F 1 "0.1u" H 1865 6955 50  0000 L CNN
F 2 "Attenuverter:C_Axial_L4.8mm_D2.0mm_P2.54mm_Horizontal" H 1788 6850 50  0001 C CNN
F 3 "~" H 1750 7000 50  0001 C CNN
	1    1750 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1900 6600 1900 7000
Connection ~ 1900 7000
Wire Wire Line
	1600 7000 1600 6600
Connection ~ 1600 7000
$EndSCHEMATC
