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
P 9325 1500
F 0 "i2c_scr1" H 9954 2165 50  0000 C CNN
F 1 "i2c_screen" H 9954 2074 50  0000 C CNN
F 2 "i2c_screen:i2c_screen" H 9725 1800 50  0001 C CNN
F 3 "" H 9725 1800 50  0001 C CNN
	1    9325 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0101
U 1 1 5E724353
P 9050 1300
F 0 "#PWR0101" H 9050 1150 50  0001 C CNN
F 1 "+3.3V" H 9065 1473 50  0000 C CNN
F 2 "" H 9050 1300 50  0001 C CNN
F 3 "" H 9050 1300 50  0001 C CNN
	1    9050 1300
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
P 9050 1400
F 0 "#PWR0103" H 9050 1150 50  0001 C CNN
F 1 "GND" H 9055 1227 50  0000 C CNN
F 2 "" H 9050 1400 50  0001 C CNN
F 3 "" H 9050 1400 50  0001 C CNN
	1    9050 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E72786A
P 1250 2725
F 0 "#PWR0104" H 1250 2475 50  0001 C CNN
F 1 "GND" H 1255 2552 50  0000 C CNN
F 2 "" H 1250 2725 50  0001 C CNN
F 3 "" H 1250 2725 50  0001 C CNN
	1    1250 2725
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
Text GLabel 9050 1200 0    50   UnSpc ~ 0
scr_scl
Text GLabel 9050 1100 0    50   UnSpc ~ 0
scr_sda
Wire Wire Line
	3000 1625 3125 1625
Wire Wire Line
	3000 1525 3125 1525
Wire Wire Line
	9375 1100 9050 1100
Wire Wire Line
	9375 1200 9050 1200
Wire Wire Line
	9375 1300 9050 1300
Wire Wire Line
	9375 1400 9050 1400
$Comp
L Connector:Micro_SD_Card J1
U 1 1 5E745444
P 10075 3275
F 0 "J1" H 10025 3992 50  0000 C CNN
F 1 "Micro_SD_Card" H 10025 3901 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3AT-SF-PEJM5" H 11225 3575 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 10075 3275 50  0001 C CNN
	1    10075 3275
	1    0    0    -1  
$EndComp
Text GLabel 9100 3075 0    50   Input ~ 0
SD_CS
Text GLabel 9100 3175 0    50   Input ~ 0
SD_MOSI
Text GLabel 9100 3375 0    50   Input ~ 0
SD_CLK
Text GLabel 9100 3575 0    50   Input ~ 0
SD_MISO
$Comp
L power:GND #PWR0107
U 1 1 5E748DDD
P 9100 3475
F 0 "#PWR0107" H 9100 3225 50  0001 C CNN
F 1 "GND" V 9105 3347 50  0000 R CNN
F 2 "" H 9100 3475 50  0001 C CNN
F 3 "" H 9100 3475 50  0001 C CNN
	1    9100 3475
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 5E7491B4
P 9100 3275
F 0 "#PWR0108" H 9100 3125 50  0001 C CNN
F 1 "+3.3V" V 9115 3403 50  0000 L CNN
F 2 "" H 9100 3275 50  0001 C CNN
F 3 "" H 9100 3275 50  0001 C CNN
	1    9100 3275
	0    -1   -1   0   
$EndComp
NoConn ~ 9175 2975
NoConn ~ 9175 3675
Wire Wire Line
	9100 3075 9175 3075
Wire Wire Line
	9100 3175 9175 3175
Wire Wire Line
	9100 3275 9175 3275
Wire Wire Line
	9100 3375 9175 3375
Wire Wire Line
	9100 3475 9175 3475
Wire Wire Line
	9100 3575 9175 3575
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
P 1475 4525
F 0 "J2" H 1532 4992 50  0000 C CNN
F 1 "USB_A" H 1532 4901 50  0000 C CNN
F 2 "Connector_USB:USB3_A_Plug_Wuerth_692112030100_Horizontal" H 1625 4475 50  0001 C CNN
F 3 " ~" H 1625 4475 50  0001 C CNN
	1    1475 4525
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E74F9A7
P 1375 5075
F 0 "#PWR0109" H 1375 4825 50  0001 C CNN
F 1 "GND" H 1380 4902 50  0000 C CNN
F 2 "" H 1375 5075 50  0001 C CNN
F 3 "" H 1375 5075 50  0001 C CNN
	1    1375 5075
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5E74FB7F
P 1900 4325
F 0 "#PWR0110" H 1900 4175 50  0001 C CNN
F 1 "+5V" V 1915 4453 50  0000 L CNN
F 2 "" H 1900 4325 50  0001 C CNN
F 3 "" H 1900 4325 50  0001 C CNN
	1    1900 4325
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 4325 1775 4325
Wire Wire Line
	1375 5075 1375 4925
Wire Wire Line
	1475 4925 1375 4925
Connection ~ 1375 4925
$Comp
L power:GND #PWR0111
U 1 1 5E75260C
P 10950 3875
F 0 "#PWR0111" H 10950 3625 50  0001 C CNN
F 1 "GND" H 10955 3702 50  0000 C CNN
F 2 "" H 10950 3875 50  0001 C CNN
F 3 "" H 10950 3875 50  0001 C CNN
	1    10950 3875
	1    0    0    -1  
$EndComp
Wire Wire Line
	10875 3875 10950 3875
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
L capacitive_touch_pads:capacitif_touch_pad DOWN1
U 1 1 5E7C39D9
P 5725 6550
F 0 "DOWN1" H 5950 6550 50  0000 C CNN
F 1 "DOWN" H 5775 6475 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 6550 50  0001 C CNN
F 3 "" H 5725 6550 50  0001 C CNN
	1    5725 6550
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad LEFT1
U 1 1 5E7C5A3F
P 5725 6800
F 0 "LEFT1" H 5950 6800 50  0000 C CNN
F 1 "LEFT" H 5775 6725 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 6800 50  0001 C CNN
F 3 "" H 5725 6800 50  0001 C CNN
	1    5725 6800
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad RIGHT1
U 1 1 5E7C66E1
P 5725 7025
F 0 "RIGHT1" H 5950 7025 50  0000 C CNN
F 1 "RIGHT" H 5775 6950 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7025 50  0001 C CNN
F 3 "" H 5725 7025 50  0001 C CNN
	1    5725 7025
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad BACK1
U 1 1 5E7C7158
P 5725 7275
F 0 "BACK1" H 5950 7275 50  0000 C CNN
F 1 "BACK" H 5775 7225 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7275 50  0001 C CNN
F 3 "" H 5725 7275 50  0001 C CNN
	1    5725 7275
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad Ok1
U 1 1 5E7C7D4B
P 5725 7525
F 0 "Ok1" H 5950 7525 50  0000 C CNN
F 1 "OK" H 5775 7475 50  0000 C CNN
F 2 "capacitive_touch_pads:simple_pad_solder" H 5725 7525 50  0001 C CNN
F 3 "" H 5725 7525 50  0001 C CNN
	1    5725 7525
	-1   0    0    1   
$EndComp
$Comp
L capacitive_touch_pads:capacitif_touch_pad UP1
U 1 1 5E7C8769
P 5725 6300
F 0 "UP1" H 5950 6300 50  0000 C CNN
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
Text GLabel 1250 2525 0    50   Input ~ 0
touch_up
Text GLabel 3000 2925 2    50   Input ~ 0
touch_left
Text GLabel 1250 2625 0    50   Input ~ 0
touch_right
Text GLabel 3000 2625 2    50   Input ~ 0
touch_back
Text GLabel 3000 2825 2    50   Input ~ 0
touch_ok
$Comp
L Connector:Conn_01x02_Male flash_jumper1
U 1 1 5E821F43
P 3775 6800
F 0 "flash_jumper1" H 3350 6625 50  0000 L CNN
F 1 "flash jmp" H 3350 6700 50  0000 L CNN
F 2 "keybox-esp:jumper_smd" H 3775 6800 50  0001 C CNN
F 3 "~" H 3775 6800 50  0001 C CNN
	1    3775 6800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female FTDI1
U 1 1 5E824EFD
P 3725 6300
F 0 "FTDI1" V 3663 6012 50  0000 R CNN
F 1 "FTDI" V 3572 6012 50  0000 R CNN
F 2 "Connector_Wire:SolderWirePad_1x04_P3.175mm_Drill0.8mm" H 3725 6300 50  0001 C CNN
F 3 "~" H 3725 6300 50  0001 C CNN
	1    3725 6300
	-1   0    0    1   
$EndComp
Text GLabel 3000 2725 2    50   Input ~ 0
flash_jmp
Text GLabel 3975 6900 2    50   Input ~ 0
flash_jmp
$Comp
L AMS1117:GND #PWR0115
U 1 1 5E831138
P 3975 6800
F 0 "#PWR0115" H 3975 6550 50  0001 C CNN
F 1 "GND" V 3975 6600 50  0000 C CNN
F 2 "" H 3975 6800 50  0001 C CNN
F 3 "" H 3975 6800 50  0001 C CNN
	1    3975 6800
	0    -1   -1   0   
$EndComp
$Comp
L AMS1117:GND #PWR0116
U 1 1 5E8334BE
P 3925 6100
F 0 "#PWR0116" H 3925 5850 50  0001 C CNN
F 1 "GND" V 3925 5900 50  0000 C CNN
F 2 "" H 3925 6100 50  0001 C CNN
F 3 "" H 3925 6100 50  0001 C CNN
	1    3925 6100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0117
U 1 1 5E83378D
P 3925 6200
F 0 "#PWR0117" H 3925 6050 50  0001 C CNN
F 1 "+3.3V" V 3925 6425 50  0000 C CNN
F 2 "" H 3925 6200 50  0001 C CNN
F 3 "" H 3925 6200 50  0001 C CNN
	1    3925 6200
	0    1    1    0   
$EndComp
Text GLabel 3000 1725 2    50   Input ~ 0
esp_TX
Text GLabel 3000 1825 2    50   Input ~ 0
esp_RX
Text GLabel 3925 6300 2    50   Input ~ 0
esp_TX
Text GLabel 3925 6400 2    50   Input ~ 0
esp_RX
Text GLabel 1250 1525 0    50   Input ~ 0
esp_reset
$Comp
L Connector:Conn_01x02_Male rst1
U 1 1 5E880025
P 3775 7175
F 0 "rst1" H 3575 7000 50  0000 L CNN
F 1 "rst" H 3575 7075 50  0000 L CNN
F 2 "keybox-esp:jumper_smd" H 3775 7175 50  0001 C CNN
F 3 "~" H 3775 7175 50  0001 C CNN
	1    3775 7175
	1    0    0    -1  
$EndComp
Text GLabel 3975 7275 2    50   Input ~ 0
esp_reset
$Comp
L AMS1117:GND #PWR0118
U 1 1 5E88002C
P 3975 7175
F 0 "#PWR0118" H 3975 6925 50  0001 C CNN
F 1 "GND" V 3975 6975 50  0000 C CNN
F 2 "" H 3975 7175 50  0001 C CNN
F 3 "" H 3975 7175 50  0001 C CNN
	1    3975 7175
	0    -1   -1   0   
$EndComp
Text GLabel 1250 2425 0    50   Input ~ 0
touc_down
$EndSCHEMATC
