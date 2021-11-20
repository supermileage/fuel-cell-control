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
L Regulator_Linear:MCP1754S-3302xCB U1
U 1 1 6174AE03
P 3000 1000
F 0 "U1" H 3000 1242 50  0000 C CNN
F 1 "MCP1754S-3302xCB" H 3000 1151 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3000 1225 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002276C.pdf" H 3000 1000 50  0001 C CNN
F 4 "MCP1754ST-3302E/CBCT-ND" H 3000 1000 50  0001 C CNN "DigikeyPN"
	1    3000 1000
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_Every A1
U 1 1 617DB298
P 6900 4100
F 0 "A1" H 7400 3200 50  0000 C CNN
F 1 "Arduino_Nano_Every" H 7350 3100 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6900 4100 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 6900 4100 50  0001 C CNN
F 4 "1050-ABX00028-ND" H 6900 4100 50  0001 C CNN "DigikeyPN"
	1    6900 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 617E026D
P 6900 5500
F 0 "#PWR016" H 6900 5250 50  0001 C CNN
F 1 "GND" H 6905 5327 50  0000 C CNN
F 2 "" H 6900 5500 50  0001 C CNN
F 3 "" H 6900 5500 50  0001 C CNN
	1    6900 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5100 6900 5500
$Comp
L power:GND #PWR010
U 1 1 617E0879
P 3000 1400
F 0 "#PWR010" H 3000 1150 50  0001 C CNN
F 1 "GND" H 3005 1227 50  0000 C CNN
F 2 "" H 3000 1400 50  0001 C CNN
F 3 "" H 3000 1400 50  0001 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 617E306F
P 8550 4750
F 0 "#PWR017" H 8550 4500 50  0001 C CNN
F 1 "GND" H 8555 4577 50  0000 C CNN
F 2 "" H 8550 4750 50  0001 C CNN
F 3 "" H 8550 4750 50  0001 C CNN
	1    8550 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4550 8550 4750
$Comp
L Device:R R4
U 1 1 618552F2
P 8550 3950
F 0 "R4" H 8620 3996 50  0000 L CNN
F 1 "680k" H 8620 3905 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8480 3950 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1773204-3&DocType=DS&DocLang=English" H 8550 3950 50  0001 C CNN
F 4 "A129661CT-ND" H 8550 3950 50  0001 C CNN "DigikeyPN"
	1    8550 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 618556FF
P 8550 4400
F 0 "R5" H 8620 4446 50  0000 L CNN
F 1 "470k" H 8620 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8480 4400 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/te-connectivity-passive-product/CRGCQ1206F470K/8576444" H 8550 4400 50  0001 C CNN
F 4 "A129842CT-ND" H 8550 4400 50  0001 C CNN "DigikeyPN"
	1    8550 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 61865344
P 10350 3300
F 0 "#PWR021" H 10350 3050 50  0001 C CNN
F 1 "GND" H 10355 3127 50  0000 C CNN
F 2 "" H 10350 3300 50  0001 C CNN
F 3 "" H 10350 3300 50  0001 C CNN
	1    10350 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 6186C629
P 10800 1100
F 0 "#PWR024" H 10800 850 50  0001 C CNN
F 1 "GND" H 10805 927 50  0000 C CNN
F 2 "" H 10800 1100 50  0001 C CNN
F 3 "" H 10800 1100 50  0001 C CNN
	1    10800 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 1100 10800 1000
Wire Wire Line
	10800 1000 10700 1000
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 6186EB87
P 800 1250
F 0 "J1" H 908 1431 50  0000 C CNN
F 1 "Conn_01x02_Male" H 908 1340 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-02A2_2x01_P4.20mm_Horizontal" H 800 1250 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/ps/PS-5556-001.pdf" H 800 1250 50  0001 C CNN
F 4 "0050361758-ND" H 800 1250 50  0001 C CNN "DigikeyPN"
	1    800  1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1300 3000 1350
$Comp
L power:GND #PWR02
U 1 1 618789AA
P 1150 1500
F 0 "#PWR02" H 1150 1250 50  0001 C CNN
F 1 "GND" H 1155 1327 50  0000 C CNN
F 2 "" H 1150 1500 50  0001 C CNN
F 3 "" H 1150 1500 50  0001 C CNN
	1    1150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1350 1150 1350
Wire Wire Line
	1150 1350 1150 1450
Wire Wire Line
	1000 1250 1150 1250
$Comp
L power:PWR_FLAG #FLG01
U 1 1 6187D89B
P 1150 800
F 0 "#FLG01" H 1150 875 50  0001 C CNN
F 1 "PWR_FLAG" V 1150 928 50  0000 L CNN
F 2 "" H 1150 800 50  0001 C CNN
F 3 "~" H 1150 800 50  0001 C CNN
	1    1150 800 
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 6187E001
P 1150 1450
F 0 "#FLG02" H 1150 1525 50  0001 C CNN
F 1 "PWR_FLAG" V 1150 1578 50  0000 L CNN
F 2 "" H 1150 1450 50  0001 C CNN
F 3 "~" H 1150 1450 50  0001 C CNN
	1    1150 1450
	0    1    1    0   
$EndComp
Connection ~ 1150 1450
Wire Wire Line
	1150 1450 1150 1500
Wire Wire Line
	2500 1000 2700 1000
$Comp
L power:+5V #PWR013
U 1 1 618803DE
P 3750 1000
F 0 "#PWR013" H 3750 850 50  0001 C CNN
F 1 "+5V" H 3765 1173 50  0000 C CNN
F 2 "" H 3750 1000 50  0001 C CNN
F 3 "" H 3750 1000 50  0001 C CNN
	1    3750 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 618817AF
P 6800 2600
F 0 "#PWR015" H 6800 2450 50  0001 C CNN
F 1 "+5V" H 6815 2773 50  0000 C CNN
F 2 "" H 6800 2600 50  0001 C CNN
F 3 "" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2900 7100 3100
Text Label 10750 1500 0    50   ~ 0
MuxSelect0
Text Label 10750 1600 0    50   ~ 0
MuxSelect1
Text Label 10750 1700 0    50   ~ 0
MuxSelect2
Text Label 10750 1800 0    50   ~ 0
MuxSelect3
Text Label 5750 3800 2    50   ~ 0
MuxSelect0
Text Label 5750 3900 2    50   ~ 0
MuxSelect1
Text Label 5750 4000 2    50   ~ 0
MuxSelect2
Text Label 5750 4100 2    50   ~ 0
MuxSelect3
$Comp
L 74xGxx:74AHCT1G04 U2
U 1 1 6188FB20
P 8850 5850
F 0 "U2" H 9250 5900 50  0000 C CNN
F 1 "74AHCT1G04" H 9200 5800 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 8850 5850 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/74AHCT1G04.pdf" H 8850 5850 50  0001 C CNN
F 4 "74AHCT1G04W5-7DICT-ND" H 8850 5850 50  0001 C CNN "DigikeyPN"
	1    8850 5850
	1    0    0    -1  
$EndComp
Text Label 9850 3200 0    50   ~ 0
EnablePin
$Comp
L power:GND #PWR019
U 1 1 618C60F6
P 8850 5950
F 0 "#PWR019" H 8850 5700 50  0001 C CNN
F 1 "GND" H 8855 5777 50  0000 C CNN
F 2 "" H 8850 5950 50  0001 C CNN
F 3 "" H 8850 5950 50  0001 C CNN
	1    8850 5950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 618CAF84
P 8850 5750
F 0 "#PWR018" H 8850 5600 50  0001 C CNN
F 1 "+5V" H 8750 5850 50  0000 C CNN
F 2 "" H 8850 5750 50  0001 C CNN
F 3 "" H 8850 5750 50  0001 C CNN
	1    8850 5750
	1    0    0    -1  
$EndComp
Text Label 5750 4300 2    50   ~ 0
BigPump
Text Label 5750 4400 2    50   ~ 0
LittlePump
Wire Wire Line
	8550 4100 8550 4250
Wire Wire Line
	8550 1300 8550 3800
Wire Wire Line
	9850 3800 9850 4150
Wire Wire Line
	3300 1000 3550 1000
$Comp
L Device:Fuse F1
U 1 1 618EA324
P 1150 950
F 0 "F1" H 1210 996 50  0000 L CNN
F 1 "Fuse" H 1210 905 50  0000 L CNN
F 2 "digikey-footprints:3586KTR" V 1080 950 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/keystone-electronics/3586KTR/6817755?s=N4IgTCBcDaIMwFYAcA2A1gFwE4gLoF8g" H 1150 950 50  0001 C CNN
F 4 "36-3586KCT-ND" H 1150 950 50  0001 C CNN "DigikeyPN"
	1    1150 950 
	1    0    0    -1  
$EndComp
Text Label 5750 4200 2    50   ~ 0
Relay
$Comp
L Connector:TestPoint TP5
U 1 1 6190EBDF
P 3550 1000
F 0 "TP5" H 3492 1026 50  0000 R CNN
F 1 "TestPoint" H 3492 1117 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 3750 1000 50  0001 C CNN
F 3 "~" H 3750 1000 50  0001 C CNN
	1    3550 1000
	-1   0    0    1   
$EndComp
Connection ~ 3550 1000
Wire Wire Line
	3550 1000 3750 1000
$Comp
L Connector:TestPoint TP3
U 1 1 61910C0C
P 2200 1000
F 0 "TP3" H 2450 1050 50  0000 R CNN
F 1 "TestPoint" H 2600 1150 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 2400 1000 50  0001 C CNN
F 3 "~" H 2400 1000 50  0001 C CNN
	1    2200 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 1000 2400 1000
Connection ~ 2500 1000
$Comp
L Connector:TestPoint TP7
U 1 1 619664F1
P 8550 1300
F 0 "TP7" H 8608 1418 50  0000 L CNN
F 1 "TestPoint" H 8608 1327 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 8750 1300 50  0001 C CNN
F 3 "~" H 8750 1300 50  0001 C CNN
	1    8550 1300
	1    0    0    -1  
$EndComp
Connection ~ 8550 1300
$Comp
L Connector:Conn_01x15_Male J2
U 1 1 619EB417
P 1100 6800
F 0 "J2" H 1350 7750 50  0000 C CNN
F 1 "Conn_01x15_Male" H 1400 7650 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 1100 6800 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Sullins%20PDFs/Female_Headers.100_DS.pdf" H 1100 6800 50  0001 C CNN
F 4 "S7013-ND" H 1100 6800 50  0001 C CNN "DigikeyPN"
	1    1100 6800
	1    0    0    -1  
$EndComp
Wire Notes Line
	750  5700 750  7650
Wire Notes Line
	750  7650 3450 7650
Wire Notes Line
	3450 7650 3450 5700
Wire Notes Line
	3450 5700 750  5700
$Comp
L Connector:Conn_01x15_Male J5
U 1 1 619F3030
P 2700 6800
F 0 "J5" H 3050 5850 50  0000 R CNN
F 1 "Conn_01x15_Male" H 3300 5950 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 2700 6800 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Sullins%20PDFs/Female_Headers.100_DS.pdf" H 2700 6800 50  0001 C CNN
F 4 "S7013-ND" H 2700 6800 50  0001 C CNN "DigikeyPN"
	1    2700 6800
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 3300 5750 3300
Wire Wire Line
	6400 3400 5750 3400
Wire Wire Line
	6400 3700 5750 3700
Wire Wire Line
	6400 3600 5750 3600
Wire Wire Line
	6400 3800 5750 3800
Wire Wire Line
	6400 3900 5750 3900
Wire Wire Line
	6400 4000 5750 4000
Wire Wire Line
	6400 4100 5750 4100
Wire Wire Line
	6400 4200 5750 4200
Wire Wire Line
	6400 4300 5750 4300
Wire Wire Line
	6400 4400 5750 4400
Wire Wire Line
	6400 4600 5750 4600
Wire Wire Line
	5750 4700 6400 4700
Wire Wire Line
	6400 4800 5750 4800
Text Label 5750 3300 2    50   ~ 0
TX1
Text Label 5750 3400 2    50   ~ 0
RX1
Text Label 5750 3600 2    50   ~ 0
EnablePin
Text Label 5750 3700 2    50   ~ 0
D3_PWM
Text Label 5750 4600 2    50   ~ 0
MOSI
Text Label 5750 4700 2    50   ~ 0
MISO
Text Label 5750 4800 2    50   ~ 0
SCK
Text Label 1300 6100 0    50   ~ 0
TX1
Text Label 1300 6200 0    50   ~ 0
RX1
Text Label 1300 6300 0    50   ~ 0
RESET1
Text Label 1300 6400 0    50   ~ 0
GND
Text Label 1300 6500 0    50   ~ 0
EnablePin
Text Label 1300 6600 0    50   ~ 0
D3_PWM
Text Label 1300 6700 0    50   ~ 0
MuxSelect0
Text Label 1300 6800 0    50   ~ 0
MuxSelect1
Text Label 1300 6900 0    50   ~ 0
MuxSelect2
Text Label 1300 7000 0    50   ~ 0
MuxSelect3
Text Label 1300 7100 0    50   ~ 0
Relay
Text Label 1300 7200 0    50   ~ 0
BigPump
Text Label 1300 7300 0    50   ~ 0
LittlePump
Text Label 1300 7400 0    50   ~ 0
MOSI
Text Label 1300 7500 0    50   ~ 0
MISO
Text Label 2500 7500 2    50   ~ 0
SCK
Text Label 2500 7400 2    50   ~ 0
Nano3V3Out
Text Label 2500 7300 2    50   ~ 0
AREF
Text Label 2500 7200 2    50   ~ 0
MuxAnalog
Text Label 2500 7100 2    50   ~ 0
Analog1
Text Label 2500 7000 2    50   ~ 0
Analog2
Text Label 2500 6900 2    50   ~ 0
Analog3
Text Label 2500 6800 2    50   ~ 0
Analog4_SDA
Text Label 2500 6700 2    50   ~ 0
Analog5_SCL
Text Label 2500 6600 2    50   ~ 0
Analog6
Text Label 2500 6500 2    50   ~ 0
Analog7
Text Label 2500 6400 2    50   ~ 0
Nano5VOut
Text Label 2500 6300 2    50   ~ 0
RESET2
Text Label 2500 6100 2    50   ~ 0
VinNano
Text Label 7450 3500 0    50   ~ 0
RESET1
Text Label 7450 3600 0    50   ~ 0
RESET2
Text Label 7450 3900 0    50   ~ 0
AREF
Text Label 8000 4200 0    50   ~ 0
Analog1
Text Label 8000 4300 0    50   ~ 0
Analog2
Text Label 8000 4400 0    50   ~ 0
Analog3
Text Label 8000 4500 0    50   ~ 0
Analog4_SDA
Text Label 8000 4600 0    50   ~ 0
Analog5_SCL
Text Label 8000 4700 0    50   ~ 0
Analog6
Text Label 8000 4800 0    50   ~ 0
Analog7
Text Label 6900 5350 0    50   ~ 0
GND
Text Label 7100 2900 0    50   ~ 0
Nano5VOut
Text Label 6800 3000 1    50   ~ 0
VinNano
Text Label 7000 3050 1    50   ~ 0
Nano3V3Out
$Comp
L Connector:TestPoint TP4
U 1 1 61A7F380
P 3000 1400
F 0 "TP4" V 2954 1588 50  0000 L CNN
F 1 "TestPoint" V 3045 1588 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 3200 1400 50  0001 C CNN
F 3 "~" H 3200 1400 50  0001 C CNN
	1    3000 1400
	0    1    1    0   
$EndComp
Connection ~ 3000 1400
$Comp
L Device:C C1
U 1 1 61AEC261
P 2400 1200
F 0 "C1" H 2515 1246 50  0000 L CNN
F 1 "10uF" H 2515 1155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 2438 1050 50  0001 C CNN
F 3 "https://datasheets.kyocera-avx.com/TAJ.pdf" H 2400 1200 50  0001 C CNN
F 4 "478-8875-1-ND" H 2400 1200 50  0001 C CNN "DigikeyPN"
	1    2400 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1000 2400 1050
Connection ~ 2400 1000
Wire Wire Line
	2400 1000 2500 1000
Wire Wire Line
	2400 1350 3000 1350
Connection ~ 3000 1350
Wire Wire Line
	3000 1350 3000 1400
$Comp
L Device:CP C2
U 1 1 61B01389
P 3300 1150
F 0 "C2" H 3418 1196 50  0000 L CNN
F 1 "0.1uF" H 3418 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3338 1000 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/kyocera-avx/TAJR104K020RNJ/929918" H 3300 1150 50  0001 C CNN
F 4 "478-3286-1-ND" H 3300 1150 50  0001 C CNN "DigikeyPN"
	1    3300 1150
	1    0    0    -1  
$EndComp
Connection ~ 3300 1000
Wire Wire Line
	3000 1300 3300 1300
Connection ~ 3000 1300
$Comp
L Device:CP C3
U 1 1 61B08669
P 10700 850
F 0 "C3" H 10818 896 50  0000 L CNN
F 1 "0.1uF" H 10818 805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10738 700 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/kyocera-avx/TAJR104K020RNJ/929918" H 10700 850 50  0001 C CNN
F 4 "478-3286-1-ND" H 10700 850 50  0001 C CNN "DigikeyPN"
	1    10700 850 
	1    0    0    -1  
$EndComp
Connection ~ 10700 1000
Wire Wire Line
	10700 1000 10500 1000
Wire Wire Line
	10700 700  10350 700 
Wire Wire Line
	10350 700  10350 1000
Wire Wire Line
	7400 3500 7450 3500
Wire Wire Line
	7400 3600 7450 3600
Wire Wire Line
	7400 3900 7450 3900
Wire Wire Line
	7000 3100 7000 3050
Wire Wire Line
	6800 2600 6800 3100
Connection ~ 8550 4100
$Comp
L Connector:Conn_01x10_Male J8
U 1 1 618BDD04
P 9250 2800
F 0 "J8" H 8900 3000 50  0000 C CNN
F 1 "Conn_01x10_Male" H 8900 2900 50  0000 C CNN
F 2 "Connector_Phoenix_MC:PhoenixContact_MCV_1,5_10-G-3.5_1x10_P3.50mm_Vertical" H 9250 2800 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/phoenix-contact/1843680/2528306" H 9250 2800 50  0001 C CNN
F 4 "277-5774-ND" H 9250 2800 50  0001 C CNN "DigikeyPN"
	1    9250 2800
	1    0    0    -1  
$EndComp
$Comp
L fuelCellControl-rescue:MUX506IDWR-dk_Interface-Analog-Switches-Multiplexers-Demultiplexers U3
U 1 1 6185BBFB
P 10250 2100
F 0 "U3" H 10900 1300 60  0000 C CNN
F 1 "MUX506IDWR" H 10900 1200 60  0000 C CNN
F 2 "digikey-footprints:SOIC-28_W7.5mm" H 10950 2300 60  0001 L CNN
F 3 "https://www.ti.com/lit/ds/symlink/mux506.pdf" H 10950 2400 60  0001 L CNN
F 4 "296-47544-1-ND" H 10950 2500 60  0001 L CNN "Digi-Key_PN"
F 5 "" H 10950 2600 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 10950 2700 60  0001 L CNN "Category"
F 7 "Interface - Analog Switches, Multiplexers, Demultiplexers" H 10950 2800 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fcd74hc4067" H 10950 2900 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/CD74HC4067M96/296-29408-1-ND/2741760" H 10950 3000 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MUX/DEMUX 1X16 24SOIC" H 10950 3100 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 10950 3200 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10950 3300 60  0001 L CNN "Status"
	1    10250 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP8
U 1 1 619015B4
P 9100 5850
F 0 "TP8" H 9050 6200 50  0000 L CNN
F 1 "TestPoint" H 9000 6100 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 9300 5850 50  0001 C CNN
F 3 "~" H 9300 5850 50  0001 C CNN
	1    9100 5850
	1    0    0    -1  
$EndComp
Text Label 8550 5850 2    50   ~ 0
EnablePin
$Comp
L Connector:Conn_01x10_Male J7
U 1 1 61902D4B
P 9250 1800
F 0 "J7" H 8900 1900 50  0000 C CNN
F 1 "Conn_01x10_Male" H 8900 1800 50  0000 C CNN
F 2 "Connector_Phoenix_MC:PhoenixContact_MCV_1,5_10-G-3.5_1x10_P3.50mm_Vertical" H 9250 1800 50  0001 C CNN
F 3 "https://www.digikey.ca/en/products/detail/phoenix-contact/1843680/2528306" H 9250 1800 50  0001 C CNN
F 4 "277-5774-ND" H 9250 1800 50  0001 C CNN "DigikeyPN"
	1    9250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 3200 9850 3000
Wire Wire Line
	9450 3300 9500 3300
Wire Wire Line
	9500 3300 9500 4550
Wire Wire Line
	9450 2900 9850 2900
Wire Wire Line
	9450 2800 9850 2800
Wire Wire Line
	9450 2700 9850 2700
Wire Wire Line
	9450 2600 9850 2600
Wire Wire Line
	9450 2500 9850 2500
Wire Wire Line
	9450 2400 9850 2400
Wire Wire Line
	9450 2300 9850 2300
Wire Wire Line
	9450 2200 9850 2200
Wire Wire Line
	9450 2100 9850 2100
Wire Wire Line
	9450 2000 9850 2000
Wire Wire Line
	9450 1900 9850 1900
Wire Wire Line
	9450 1800 9850 1800
Wire Wire Line
	9450 1700 9850 1700
Wire Wire Line
	9450 1600 9850 1600
Wire Wire Line
	9450 1500 9850 1500
Wire Wire Line
	9450 1400 9850 1400
Wire Wire Line
	8550 1300 9850 1300
Text Label 10750 4350 0    50   ~ 0
MuxSelect0
Text Label 10750 4450 0    50   ~ 0
MuxSelect1
Text Label 10750 4650 0    50   ~ 0
MuxSelect3
Text Label 10750 4550 0    50   ~ 0
MuxSelect2
$Comp
L fuelCellControl-rescue:MUX506IDWR-dk_Interface-Analog-Switches-Multiplexers-Demultiplexers U4
U 1 1 6185FF4A
P 10250 4950
F 0 "U4" H 10900 4150 60  0000 C CNN
F 1 "MUX506IDWR" H 10900 4050 60  0000 C CNN
F 2 "digikey-footprints:SOIC-28_W7.5mm" H 10950 5150 60  0001 L CNN
F 3 "https://www.ti.com/lit/ds/symlink/mux506.pdf" H 10950 5250 60  0001 L CNN
F 4 "296-47544-1-ND" H 10950 5350 60  0001 L CNN "Digi-Key_PN"
F 5 "" H 10950 5450 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 10950 5550 60  0001 L CNN "Category"
F 7 "Interface - Analog Switches, Multiplexers, Demultiplexers" H 10950 5650 60  0001 L CNN "Family"
F 8 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=10&gotoUrl=http%3A%2F%2Fwww.ti.com%2Flit%2Fgpn%2Fcd74hc4067" H 10950 5750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/texas-instruments/CD74HC4067M96/296-29408-1-ND/2741760" H 10950 5850 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MUX/DEMUX 1X16 24SOIC" H 10950 5950 60  0001 L CNN "Description"
F 11 "Texas Instruments" H 10950 6050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10950 6150 60  0001 L CNN "Status"
	1    10250 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 3850 10800 3950
Wire Wire Line
	10500 3850 10800 3850
$Comp
L power:GND #PWR025
U 1 1 6186C2CD
P 10800 3950
F 0 "#PWR025" H 10800 3700 50  0001 C CNN
F 1 "GND" H 10805 3777 50  0000 C CNN
F 2 "" H 10800 3950 50  0001 C CNN
F 3 "" H 10800 3950 50  0001 C CNN
	1    10800 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 61864EE2
P 10350 6150
F 0 "#PWR023" H 10350 5900 50  0001 C CNN
F 1 "GND" H 10355 5977 50  0000 C CNN
F 2 "" H 10350 6150 50  0001 C CNN
F 3 "" H 10350 6150 50  0001 C CNN
	1    10350 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5850 9850 5850
Connection ~ 9100 5850
Wire Wire Line
	9500 4550 9850 4550
Wire Wire Line
	8550 3800 9850 3800
Connection ~ 8550 3800
Wire Wire Line
	9450 3200 9600 3200
Wire Wire Line
	9600 3200 9600 4450
Wire Wire Line
	9600 4450 9850 4450
Wire Wire Line
	9700 3100 9700 4350
Wire Wire Line
	9800 4250 9800 3000
Wire Wire Line
	9800 4250 9850 4250
Wire Wire Line
	9450 3000 9800 3000
Wire Wire Line
	9700 4350 9850 4350
Wire Wire Line
	9450 3100 9700 3100
NoConn ~ 9850 5750
NoConn ~ 9850 5650
NoConn ~ 9850 5550
NoConn ~ 9850 5450
NoConn ~ 9850 5350
NoConn ~ 9850 5250
NoConn ~ 9850 5150
NoConn ~ 9850 5050
NoConn ~ 9850 4950
NoConn ~ 9850 4850
NoConn ~ 9850 4750
NoConn ~ 9850 4650
$Comp
L power:GND #PWR08
U 1 1 61A65E94
P 2150 2950
F 0 "#PWR08" H 2150 2700 50  0001 C CNN
F 1 "GND" H 2155 2777 50  0000 C CNN
F 2 "" H 2150 2950 50  0001 C CNN
F 3 "" H 2150 2950 50  0001 C CNN
	1    2150 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q2
U 1 1 61A65E9B
P 2050 2750
F 0 "Q2" H 2300 2700 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 2300 2800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 2250 2850 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30934.pdf" H 2050 2750 50  0001 C CNN
F 4 "DMN2004WKDICT-ND" H 2050 2750 50  0001 C CNN "DigikeyPN"
	1    2050 2750
	1    0    0    -1  
$EndComp
Text Label 1700 2750 2    50   ~ 0
BigPump
$Comp
L Connector:TestPoint TP2
U 1 1 61A65EA8
P 2150 2550
F 0 "TP2" H 2208 2668 50  0000 L CNN
F 1 "TestPoint" H 2208 2577 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 2350 2550 50  0001 C CNN
F 3 "~" H 2350 2550 50  0001 C CNN
	1    2150 2550
	1    0    0    -1  
$EndComp
Connection ~ 2150 2550
$Comp
L Device:R R2
U 1 1 61A65EB0
P 1800 2900
F 0 "R2" H 2050 2850 50  0000 R CNN
F 1 "400ohms" H 2200 2950 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1730 2900 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RT_1-to-0.01_RoHS_L_12.pdf" H 1800 2900 50  0001 C CNN
F 4 "13-RT1206BRD07400RLCT-ND" H 1800 2900 50  0001 C CNN "DigikeyPN"
	1    1800 2900
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 61A65EB7
P 1800 3200
F 0 "D2" H 1750 3050 50  0000 C CNN
F 1 "LED" H 1850 3100 50  0000 C CNN
F 2 "LED_SMD:LED_0201_0603Metric" H 1800 3200 50  0001 C CNN
F 3 "https://www.sunledusa.com/products/spec/XZBGR155W5MAV.pdf" H 1800 3200 50  0001 C CNN
F 4 "1497-1295-1-ND" H 1800 3200 50  0001 C CNN "DigikeyPN"
	1    1800 3200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 61A65EBD
P 1800 3350
F 0 "#PWR05" H 1800 3100 50  0001 C CNN
F 1 "GND" H 1805 3177 50  0000 C CNN
F 2 "" H 1800 3350 50  0001 C CNN
F 3 "" H 1800 3350 50  0001 C CNN
	1    1800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2550 2150 2550
Wire Wire Line
	1600 2450 1950 2450
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 61A65EC6
P 1400 2450
F 0 "J4" H 1250 2550 50  0000 C CNN
F 1 "BigPump" H 1250 2650 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-02A2_2x01_P4.20mm_Horizontal" H 1400 2450 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/ps/PS-5556-001.pdf" H 1400 2450 50  0001 C CNN
F 4 "0050361758-ND" H 1400 2450 50  0001 C CNN "DigikeyPN"
	1    1400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2750 1850 2750
Wire Wire Line
	1700 2750 1800 2750
Connection ~ 1800 2750
$Comp
L power:GND #PWR014
U 1 1 61A6D33A
P 3850 2950
F 0 "#PWR014" H 3850 2700 50  0001 C CNN
F 1 "GND" H 3855 2777 50  0000 C CNN
F 2 "" H 3850 2950 50  0001 C CNN
F 3 "" H 3850 2950 50  0001 C CNN
	1    3850 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q3
U 1 1 61A6D341
P 3750 2750
F 0 "Q3" H 4000 2700 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 4000 2800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 3950 2850 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30934.pdf" H 3750 2750 50  0001 C CNN
F 4 "DMN2004WKDICT-ND" H 3750 2750 50  0001 C CNN "DigikeyPN"
	1    3750 2750
	1    0    0    -1  
$EndComp
Text Label 3400 2750 2    50   ~ 0
Relay
$Comp
L Connector:TestPoint TP6
U 1 1 61A6D34E
P 3850 2550
F 0 "TP6" H 3908 2668 50  0000 L CNN
F 1 "TestPoint" H 3908 2577 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 4050 2550 50  0001 C CNN
F 3 "~" H 4050 2550 50  0001 C CNN
	1    3850 2550
	1    0    0    -1  
$EndComp
Connection ~ 3850 2550
$Comp
L Device:R R3
U 1 1 61A6D356
P 3500 2900
F 0 "R3" H 3750 2850 50  0000 R CNN
F 1 "400ohms" H 3900 2950 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 3430 2900 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RT_1-to-0.01_RoHS_L_12.pdf" H 3500 2900 50  0001 C CNN
F 4 "13-RT1206BRD07400RLCT-ND" H 3500 2900 50  0001 C CNN "DigikeyPN"
	1    3500 2900
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 61A6D35D
P 3500 3200
F 0 "D3" H 3450 3050 50  0000 C CNN
F 1 "LED" H 3550 3100 50  0000 C CNN
F 2 "LED_SMD:LED_0201_0603Metric" H 3500 3200 50  0001 C CNN
F 3 "https://www.sunledusa.com/products/spec/XZBGR155W5MAV.pdf" H 3500 3200 50  0001 C CNN
F 4 "1497-1295-1-ND" H 3500 3200 50  0001 C CNN "DigikeyPN"
	1    3500 3200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 61A6D363
P 3500 3350
F 0 "#PWR011" H 3500 3100 50  0001 C CNN
F 1 "GND" H 3505 3177 50  0000 C CNN
F 2 "" H 3500 3350 50  0001 C CNN
F 3 "" H 3500 3350 50  0001 C CNN
	1    3500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2550 3850 2550
Wire Wire Line
	3300 2450 3650 2450
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 61A6D36C
P 3100 2450
F 0 "J6" H 2950 2550 50  0000 C CNN
F 1 "Relay" H 2950 2650 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-02A2_2x01_P4.20mm_Horizontal" H 3100 2450 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/ps/PS-5556-001.pdf" H 3100 2450 50  0001 C CNN
F 4 "0050361758-ND" H 3100 2450 50  0001 C CNN "DigikeyPN"
	1    3100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2750 3550 2750
Wire Wire Line
	3400 2750 3500 2750
Connection ~ 3500 2750
Wire Wire Line
	7400 4100 8550 4100
Text Label 7450 4100 0    50   ~ 0
MuxAnalog
Wire Wire Line
	7400 4200 8000 4200
Wire Wire Line
	7400 4300 8000 4300
Wire Wire Line
	7400 4400 8000 4400
Wire Wire Line
	7400 4500 8000 4500
Wire Wire Line
	7400 4600 8000 4600
Wire Wire Line
	7400 4700 8000 4700
Wire Wire Line
	7400 4800 8000 4800
$Comp
L power:+12V #PWR01
U 1 1 618E7A04
P 1150 800
F 0 "#PWR01" H 1150 650 50  0001 C CNN
F 1 "+12V" H 1165 973 50  0000 C CNN
F 2 "" H 1150 800 50  0001 C CNN
F 3 "" H 1150 800 50  0001 C CNN
	1    1150 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR07
U 1 1 618E8B3F
P 1950 2450
F 0 "#PWR07" H 1950 2300 50  0001 C CNN
F 1 "+12V" H 1965 2623 50  0000 C CNN
F 2 "" H 1950 2450 50  0001 C CNN
F 3 "" H 1950 2450 50  0001 C CNN
	1    1950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR012
U 1 1 618E9695
P 3650 2450
F 0 "#PWR012" H 3650 2300 50  0001 C CNN
F 1 "+12V" H 3665 2623 50  0000 C CNN
F 2 "" H 3650 2450 50  0001 C CNN
F 3 "" H 3650 2450 50  0001 C CNN
	1    3650 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR020
U 1 1 618EA28F
P 10350 700
F 0 "#PWR020" H 10350 550 50  0001 C CNN
F 1 "+12V" H 10365 873 50  0000 C CNN
F 2 "" H 10350 700 50  0001 C CNN
F 3 "" H 10350 700 50  0001 C CNN
	1    10350 700 
	1    0    0    -1  
$EndComp
Connection ~ 10350 700 
$Comp
L power:+12V #PWR022
U 1 1 618EABA2
P 10350 3850
F 0 "#PWR022" H 10350 3700 50  0001 C CNN
F 1 "+12V" H 10365 4023 50  0000 C CNN
F 2 "" H 10350 3850 50  0001 C CNN
F 3 "" H 10350 3850 50  0001 C CNN
	1    10350 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR09
U 1 1 618EB760
P 2500 1000
F 0 "#PWR09" H 2500 850 50  0001 C CNN
F 1 "+12V" H 2515 1173 50  0000 C CNN
F 2 "" H 2500 1000 50  0001 C CNN
F 3 "" H 2500 1000 50  0001 C CNN
	1    2500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1100 1150 1250
Connection ~ 1150 800 
Text Label 2500 6200 2    50   ~ 0
GND
$Comp
L Mechanical:MountingHole H1
U 1 1 618DD1AF
P 5000 6500
F 0 "H1" H 5100 6546 50  0000 L CNN
F 1 "MountingHole" H 5100 6455 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5000 6500 50  0001 C CNN
F 3 "~" H 5000 6500 50  0001 C CNN
	1    5000 6500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 618DE0A2
P 5000 6700
F 0 "H2" H 5100 6746 50  0000 L CNN
F 1 "MountingHole" H 5100 6655 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5000 6700 50  0001 C CNN
F 3 "~" H 5000 6700 50  0001 C CNN
	1    5000 6700
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 618DE2C0
P 5000 6900
F 0 "H3" H 5100 6946 50  0000 L CNN
F 1 "MountingHole" H 5100 6855 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5000 6900 50  0001 C CNN
F 3 "~" H 5000 6900 50  0001 C CNN
	1    5000 6900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 618DE51E
P 5000 7100
F 0 "H4" H 5100 7146 50  0000 L CNN
F 1 "MountingHole" H 5100 7055 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 5000 7100 50  0001 C CNN
F 3 "~" H 5000 7100 50  0001 C CNN
	1    5000 7100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR04
U 1 1 618E9CD7
P 1700 3950
F 0 "#PWR04" H 1700 3800 50  0001 C CNN
F 1 "+12V" H 1715 4123 50  0000 C CNN
F 2 "" H 1700 3950 50  0001 C CNN
F 3 "" H 1700 3950 50  0001 C CNN
	1    1700 3950
	1    0    0    -1  
$EndComp
Connection ~ 1550 4250
Wire Wire Line
	1450 4250 1550 4250
Wire Wire Line
	1550 4250 1600 4250
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 61C01CB7
P 1150 3950
F 0 "J3" H 1000 4050 50  0000 C CNN
F 1 "LittlePump" H 1000 4150 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-02A2_2x01_P4.20mm_Horizontal" H 1150 3950 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/ps/PS-5556-001.pdf" H 1150 3950 50  0001 C CNN
F 4 "0050361758-ND" H 1150 3950 50  0001 C CNN "DigikeyPN"
	1    1150 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 3950 1700 3950
Wire Wire Line
	1350 4050 1900 4050
$Comp
L power:GND #PWR03
U 1 1 61942DE9
P 1550 4850
F 0 "#PWR03" H 1550 4600 50  0001 C CNN
F 1 "GND" H 1555 4677 50  0000 C CNN
F 2 "" H 1550 4850 50  0001 C CNN
F 3 "" H 1550 4850 50  0001 C CNN
	1    1550 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 61930CD1
P 1550 4700
F 0 "D1" H 1500 4550 50  0000 C CNN
F 1 "LED" H 1600 4600 50  0000 C CNN
F 2 "LED_SMD:LED_0201_0603Metric" H 1550 4700 50  0001 C CNN
F 3 "https://www.sunledusa.com/products/spec/XZBGR155W5MAV.pdf" H 1550 4700 50  0001 C CNN
F 4 "1497-1295-1-ND" H 1550 4700 50  0001 C CNN "DigikeyPN"
	1    1550 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 61930842
P 1550 4400
F 0 "R1" H 1800 4350 50  0000 R CNN
F 1 "400ohms" H 1950 4450 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1480 4400 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RT_1-to-0.01_RoHS_L_12.pdf" H 1550 4400 50  0001 C CNN
F 4 "13-RT1206BRD07400RLCT-ND" H 1550 4400 50  0001 C CNN "DigikeyPN"
	1    1550 4400
	-1   0    0    1   
$EndComp
Connection ~ 1900 4050
$Comp
L Connector:TestPoint TP1
U 1 1 61914A29
P 1900 4050
F 0 "TP1" H 1958 4168 50  0000 L CNN
F 1 "TestPoint" H 1958 4077 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 2100 4050 50  0001 C CNN
F 3 "~" H 2100 4050 50  0001 C CNN
	1    1900 4050
	1    0    0    -1  
$EndComp
Text Label 1450 4250 2    50   ~ 0
LittlePump
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 617F4C2D
P 1800 4250
F 0 "Q1" H 2050 4200 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 2050 4300 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70" H 2000 4350 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30934.pdf" H 1800 4250 50  0001 C CNN
F 4 "DMN2004WKDICT-ND" H 1800 4250 50  0001 C CNN "DigikeyPN"
	1    1800 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6185881C
P 1900 4450
F 0 "#PWR06" H 1900 4200 50  0001 C CNN
F 1 "GND" H 1905 4277 50  0000 C CNN
F 2 "" H 1900 4450 50  0001 C CNN
F 3 "" H 1900 4450 50  0001 C CNN
	1    1900 4450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
