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
L screen:i2c_screen i2c_scr1
U 1 1 5E72169C
P 8950 1575
F 0 "i2c_scr1" H 9579 2240 50  0000 C CNN
F 1 "i2c_screen" H 9579 2149 50  0000 C CNN
F 2 "i2c_screen:i2c_screen" H 9350 1875 50  0001 C CNN
F 3 "" H 9350 1875 50  0001 C CNN
	1    8950 1575
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 5E724353
P 8675 1375
F 0 "#PWR0101" H 8675 1225 50  0001 C CNN
F 1 "+3.3V" H 8690 1548 50  0000 C CNN
F 2 "" H 8675 1375 50  0001 C CNN
F 3 "" H 8675 1375 50  0001 C CNN
	1    8675 1375
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5E726D35
P 1125 1425
F 0 "#PWR0102" H 1125 1275 50  0001 C CNN
F 1 "+3.3V" H 1140 1598 50  0000 C CNN
F 2 "" H 1125 1425 50  0001 C CNN
F 3 "" H 1125 1425 50  0001 C CNN
	1    1125 1425
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E7273B8
P 8675 1475
F 0 "#PWR0103" H 8675 1225 50  0001 C CNN
F 1 "GND" H 8680 1302 50  0000 C CNN
F 2 "" H 8675 1475 50  0001 C CNN
F 3 "" H 8675 1475 50  0001 C CNN
	1    8675 1475
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E72786A
P 1150 2725
F 0 "#PWR0104" H 1150 2475 50  0001 C CNN
F 1 "GND" H 1155 2552 50  0000 C CNN
F 2 "" H 1150 2725 50  0001 C CNN
F 3 "" H 1150 2725 50  0001 C CNN
	1    1150 2725
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E72AAF9
P 3125 1325
F 0 "#PWR0105" H 3125 1075 50  0001 C CNN
F 1 "GND" H 3130 1152 50  0000 C CNN
F 2 "" H 3125 1325 50  0001 C CNN
F 3 "" H 3125 1325 50  0001 C CNN
	1    3125 1325
	-1   0    0    1   
$EndComp
$Comp
L esp32-wrover:ESP32-WROVER U1
U 1 1 5E72D18A
P 2150 2075
F 0 "U1" H 2125 3412 60  0000 C CNN
F 1 "ESP32-WROVER" H 2125 3306 60  0000 C CNN
F 2 "esp32-wrover:ESP32-WROVER" H 2600 1775 60  0001 C CNN
F 3 "" H 2600 1775 60  0001 C CNN
	1    2150 2075
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 2725 1150 2725
Wire Wire Line
	1250 1425 1125 1425
Wire Wire Line
	3000 1425 3125 1425
Wire Wire Line
	3125 1425 3125 1325
Wire Wire Line
	3000 1325 3125 1325
Connection ~ 3125 1325
$Comp
L power:GND #PWR0106
U 1 1 5E73E434
P 1125 1325
F 0 "#PWR0106" H 1125 1075 50  0001 C CNN
F 1 "GND" H 1130 1152 50  0000 C CNN
F 2 "" H 1125 1325 50  0001 C CNN
F 3 "" H 1125 1325 50  0001 C CNN
	1    1125 1325
	-1   0    0    1   
$EndComp
Wire Wire Line
	1250 1325 1125 1325
Text GLabel 3125 1625 2    50   UnSpc ~ 0
scr_scl
Text GLabel 3125 1925 2    50   UnSpc ~ 0
scr_sda
Text GLabel 8675 1275 0    50   UnSpc ~ 0
scr_scl
Text GLabel 8675 1175 0    50   UnSpc ~ 0
scr_sda
Wire Wire Line
	3000 1625 3125 1625
Wire Wire Line
	3000 1525 3125 1525
Wire Wire Line
	9000 1175 8675 1175
Wire Wire Line
	9000 1275 8675 1275
Wire Wire Line
	9000 1375 8675 1375
Wire Wire Line
	9000 1475 8675 1475
$Comp
L Connector:Micro_SD_Card J1
U 1 1 5E745444
P 9525 3800
F 0 "J1" H 9475 4517 50  0000 C CNN
F 1 "Micro_SD_Card" H 9475 4426 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3AT-SF-PEJM5" H 10675 4100 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 9525 3800 50  0001 C CNN
	1    9525 3800
	1    0    0    -1  
$EndComp
Text GLabel 8550 3600 0    50   Input ~ 0
SD_CS
Text GLabel 8550 3700 0    50   Input ~ 0
SD_MOSI
Text GLabel 8550 3900 0    50   Input ~ 0
SD_CLK
Text GLabel 8550 4100 0    50   Input ~ 0
SD_MISO
$Comp
L power:GND #PWR0107
U 1 1 5E748DDD
P 8550 4000
F 0 "#PWR0107" H 8550 3750 50  0001 C CNN
F 1 "GND" V 8555 3872 50  0000 R CNN
F 2 "" H 8550 4000 50  0001 C CNN
F 3 "" H 8550 4000 50  0001 C CNN
	1    8550 4000
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 5E7491B4
P 8550 3800
F 0 "#PWR0108" H 8550 3650 50  0001 C CNN
F 1 "+3.3V" V 8565 3928 50  0000 L CNN
F 2 "" H 8550 3800 50  0001 C CNN
F 3 "" H 8550 3800 50  0001 C CNN
	1    8550 3800
	0    -1   -1   0   
$EndComp
NoConn ~ 8625 3500
NoConn ~ 8625 4200
Wire Wire Line
	8550 3600 8625 3600
Wire Wire Line
	8550 3700 8625 3700
Wire Wire Line
	8550 3800 8625 3800
Wire Wire Line
	8550 3900 8625 3900
Wire Wire Line
	8550 4000 8625 4000
Wire Wire Line
	8550 4100 8625 4100
Text GLabel 3125 1525 2    50   Input ~ 0
SD_MOSI
Wire Wire Line
	3125 1925 3000 1925
Text GLabel 3125 2325 2    50   Input ~ 0
SD_CS
Text GLabel 3125 2225 2    50   Input ~ 0
SD_CLK
Text GLabel 3125 2125 2    50   Input ~ 0
SD_MISO
Wire Wire Line
	3125 2125 3000 2125
Wire Wire Line
	3000 2225 3125 2225
Wire Wire Line
	3125 2325 3000 2325
$Comp
L Connector:USB_A J2
U 1 1 5E74E25E
P 1425 5375
F 0 "J2" H 1482 5842 50  0000 C CNN
F 1 "USB_A" H 1482 5751 50  0000 C CNN
F 2 "Connector_USB:USB3_A_Plug_Wuerth_692112030100_Horizontal" H 1575 5325 50  0001 C CNN
F 3 " ~" H 1575 5325 50  0001 C CNN
	1    1425 5375
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E74F9A7
P 1325 5925
F 0 "#PWR0109" H 1325 5675 50  0001 C CNN
F 1 "GND" H 1330 5752 50  0000 C CNN
F 2 "" H 1325 5925 50  0001 C CNN
F 3 "" H 1325 5925 50  0001 C CNN
	1    1325 5925
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5E74FB7F
P 1850 5175
F 0 "#PWR0110" H 1850 5025 50  0001 C CNN
F 1 "+5V" V 1865 5303 50  0000 L CNN
F 2 "" H 1850 5175 50  0001 C CNN
F 3 "" H 1850 5175 50  0001 C CNN
	1    1850 5175
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 5175 1725 5175
Wire Wire Line
	1325 5925 1325 5775
Wire Wire Line
	1425 5775 1325 5775
Connection ~ 1325 5775
$Comp
L power:GND #PWR0111
U 1 1 5E75260C
P 10400 4400
F 0 "#PWR0111" H 10400 4150 50  0001 C CNN
F 1 "GND" H 10405 4227 50  0000 C CNN
F 2 "" H 10400 4400 50  0001 C CNN
F 3 "" H 10400 4400 50  0001 C CNN
	1    10400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10325 4400 10400 4400
$Comp
L AMS1117:AP1117-50 U2
U 1 1 5E789F4B
P 1650 7025
F 0 "U2" H 1650 7267 50  0000 C CNN
F 1 "AP1117-50" H 1650 7176 50  0000 C CNN
F 2 "AMS1117:SOT-223-3Lead_TabPin2" H 1650 7225 50  0001 C CNN
F 3 "" H 1750 6775 50  0001 C CNN
	1    1650 7025
	1    0    0    -1  
$EndComp
$Comp
L AMS1117:GND #PWR0112
U 1 1 5E78D3BD
P 1650 7550
F 0 "#PWR0112" H 1650 7300 50  0001 C CNN
F 1 "GND" H 1655 7377 50  0000 C CNN
F 2 "" H 1650 7550 50  0001 C CNN
F 3 "" H 1650 7550 50  0001 C CNN
	1    1650 7550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0113
U 1 1 5E78D7EA
P 2025 7025
F 0 "#PWR0113" H 2025 6875 50  0001 C CNN
F 1 "+3.3V" V 2040 7153 50  0000 L CNN
F 2 "" H 2025 7025 50  0001 C CNN
F 3 "" H 2025 7025 50  0001 C CNN
	1    2025 7025
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5E78DA6A
P 1275 7025
F 0 "#PWR0114" H 1275 6875 50  0001 C CNN
F 1 "+5V" V 1290 7153 50  0000 L CNN
F 2 "" H 1275 7025 50  0001 C CNN
F 3 "" H 1275 7025 50  0001 C CNN
	1    1275 7025
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1350 7025 1300 7025
Wire Wire Line
	1950 7025 2000 7025
$Comp
L AMS1117:C C3.3V1
U 1 1 5E79F846
P 2000 7250
F 0 "C3.3V1" H 2115 7296 50  0000 L CNN
F 1 "10µF" H 2115 7205 50  0000 L CNN
F 2 "AMS1117:C_1206_HandSoldering" H 2038 7100 50  0001 C CNN
F 3 "" H 2000 7250 50  0001 C CNN
	1    2000 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 7425 1300 7425
Wire Wire Line
	1300 7425 1300 7400
Wire Wire Line
	1650 7425 2000 7425
Wire Wire Line
	2000 7425 2000 7400
Wire Wire Line
	1650 7325 1650 7425
Connection ~ 1300 7025
Wire Wire Line
	1300 7025 1275 7025
Connection ~ 2000 7025
Wire Wire Line
	2000 7025 2025 7025
Wire Wire Line
	1300 7100 1300 7025
$Comp
L AMS1117:C C5V1
U 1 1 5E79EEA1
P 1300 7250
F 0 "C5V1" H 1025 7275 50  0000 L CNN
F 1 "10µF" H 1000 7200 50  0000 L CNN
F 2 "AMS1117:C_1206_HandSoldering" H 1338 7100 50  0001 C CNN
F 3 "" H 1300 7250 50  0001 C CNN
	1    1300 7250
	1    0    0    -1  
$EndComp
Connection ~ 1650 7425
Wire Wire Line
	1650 7425 1650 7550
Wire Wire Line
	2000 7025 2000 7100
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp2
U 1 1 5E7C39D9
P 5725 6550
F 0 "ctp2" H 5950 6550 50  0000 C CNN
F 1 "DOWN" H 5775 6475 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 6550 50  0001 C CNN
F 3 "" H 5725 6550 50  0001 C CNN
	1    5725 6550
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp3
U 1 1 5E7C5A3F
P 5725 6800
F 0 "ctp3" H 5950 6800 50  0000 C CNN
F 1 "LEFT" H 5775 6725 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 6800 50  0001 C CNN
F 3 "" H 5725 6800 50  0001 C CNN
	1    5725 6800
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp4
U 1 1 5E7C66E1
P 5725 7025
F 0 "ctp4" H 5950 7025 50  0000 C CNN
F 1 "RIGHT" H 5775 6950 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7025 50  0001 C CNN
F 3 "" H 5725 7025 50  0001 C CNN
	1    5725 7025
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp5
U 1 1 5E7C7158
P 5725 7275
F 0 "ctp5" H 5950 7275 50  0000 C CNN
F 1 "BACK" H 5775 7225 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7275 50  0001 C CNN
F 3 "" H 5725 7275 50  0001 C CNN
	1    5725 7275
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp6
U 1 1 5E7C7D4B
P 5725 7525
F 0 "ctp6" H 5950 7525 50  0000 C CNN
F 1 "OK" H 5775 7475 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7525 50  0001 C CNN
F 3 "" H 5725 7525 50  0001 C CNN
	1    5725 7525
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad ctp1
U 1 1 5E7C8769
P 5725 6300
F 0 "ctp1" H 5950 6300 50  0000 C CNN
F 1 "UP" H 5800 6225 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 6300 50  0001 C CNN
F 3 "" H 5725 6300 50  0001 C CNN
	1    5725 6300
	-1   0    0    1   
$EndComp
Text GLabel 5925 6300 2    50   Input ~ 0
touch_up
Text GLabel 5925 6550 2    50   Input ~ 0
touc_down
Text GLabel 5925 6800 2    50   Input ~ 0
touch_left
Text GLabel 5925 7025 2    50   Input ~ 0
touch_right
Text GLabel 5925 7275 2    50   Input ~ 0
touch_back
Text GLabel 5925 7525 2    50   Input ~ 0
touch_ok
Wire Wire Line
	5725 6300 5925 6300
Wire Wire Line
	5925 6550 5725 6550
Wire Wire Line
	5725 6800 5925 6800
Wire Wire Line
	5725 7025 5925 7025
Wire Wire Line
	5725 7275 5925 7275
Wire Wire Line
	5925 7525 5725 7525
Text GLabel 1125 2525 0    50   Input ~ 0
touch_up
Text GLabel 3150 2825 2    50   Input ~ 0
touc_down
Text GLabel 3150 2925 2    50   Input ~ 0
touch_left
Text GLabel 1125 2625 0    50   Input ~ 0
touch_right
Text GLabel 3150 2625 2    50   Input ~ 0
touch_back
Text GLabel 3150 2725 2    50   Input ~ 0
touch_ok
Wire Wire Line
	3000 2625 3150 2625
Wire Wire Line
	3150 2725 3000 2725
Wire Wire Line
	3000 2825 3150 2825
Wire Wire Line
	3150 2925 3000 2925
Wire Wire Line
	1125 2525 1250 2525
Wire Wire Line
	1250 2625 1125 2625
$EndSCHEMATC
