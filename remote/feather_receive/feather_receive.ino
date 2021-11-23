

#include <SPI.h>
#include <RH_RF95.h>
#include <MegunoLink.h>

 

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

 

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0

 

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

 

// Blinky on receipt
#define LED 13

InterfacePanel panel;
TimePlot plt;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

 

  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }
  delay(100);

 

  Serial.println("Feather LoRa RX Test!");

 

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

 

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

 

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  rf95.setTxPower(23, false);
}

 

void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    int volts[16] = {0};
    
 

    if (rf95.recv(buf, &len))
    {
      digitalWrite(LED, HIGH);
      Serial.print((char*)buf);

      // parse voltages
      bool everything_is_broken_and_i_hate_the_world = false;
      int volBuf[16] = {0};
      int startIndex = 0;
      char * volStr = strtok(buf, "\t");
      for ( int i = 0; i < 16 && !everything_is_broken_and_i_hate_the_world; ++i ){
        volBuf[i] = (int)(atof(volStr)*100);
        if (strlen(volStr) > 5 || strlen(volStr) < 4){
          everything_is_broken_and_i_hate_the_world = true;
          break;
        }
        volStr = strtok(NULL, "\t\n");
      }

      //second line
      strtok(NULL, "\n");
      strtok(NULL, "\t\n");
      strtok(NULL, "\t\n");
      char * infoStr=strtok(NULL, "\t\n");
      char tmpBuf[32] = {0};

      if (!everything_is_broken_and_i_hate_the_world){
        panel.SetNumber(F("voltage0"), volBuf[0]);
        panel.SetNumber(F("voltage1"), volBuf[1]);
        panel.SetNumber(F("voltage2"), volBuf[2]);
        panel.SetNumber(F("voltage3"), volBuf[3]);
        panel.SetNumber(F("voltage4"), volBuf[4]);
        panel.SetNumber(F("voltage5"), volBuf[5]);
        panel.SetNumber(F("voltage6"), volBuf[6]);
        panel.SetNumber(F("voltage7"), volBuf[7]);
        panel.SetNumber(F("voltage8"), volBuf[8]);
        panel.SetNumber(F("voltage9"), volBuf[9]);
        panel.SetNumber(F("voltage10"), volBuf[10]);
        panel.SetNumber(F("voltage11"), volBuf[11]);
        panel.SetNumber(F("voltage12"), volBuf[12]);
        panel.SetNumber(F("voltage13"), volBuf[13]);
        panel.SetNumber(F("voltage14"), volBuf[14]);
        panel.SetNumber(F("voltage15"), volBuf[15]);
        
        panel.SetText("textVoltage0", itoa(volBuf[0], tmpBuf, 10));
        panel.SetText("textVoltage1", itoa(volBuf[1], tmpBuf, 10));
        panel.SetText("textVoltage2", itoa(volBuf[2], tmpBuf, 10));
        panel.SetText("textVoltage3", itoa(volBuf[3], tmpBuf, 10));
        panel.SetText("textVoltage4", itoa(volBuf[4], tmpBuf, 10));
        panel.SetText("textVoltage5", itoa(volBuf[5], tmpBuf, 10));
        panel.SetText("textVoltage6", itoa(volBuf[6], tmpBuf, 10));
        panel.SetText("textVoltage7", itoa(volBuf[7], tmpBuf, 10));
        panel.SetText("textVoltage8", itoa(volBuf[8], tmpBuf, 10));
        panel.SetText("textVoltage9", itoa(volBuf[9], tmpBuf, 10));
        panel.SetText("textVoltage10", itoa(volBuf[10], tmpBuf, 10));
        panel.SetText("textVoltage11", itoa(volBuf[11], tmpBuf, 10));
        panel.SetText("textVoltage12", itoa(volBuf[12], tmpBuf, 10));
        panel.SetText("textVoltage13", itoa(volBuf[13], tmpBuf, 10));
        panel.SetText("textVoltage14", itoa(volBuf[14], tmpBuf, 10));
        panel.SetText("textVoltage15", itoa(volBuf[15], tmpBuf, 10));
        
        plt.SendData("Voltage0", (float)volBuf[0]/100);
        plt.SendData("Voltage1", (float)volBuf[1]/100);
        plt.SendData("Voltage2", (float)volBuf[2]/100);
        plt.SendData("Voltage3", (float)volBuf[3]/100);
        plt.SendData("Voltage4", (float)volBuf[4]/100);
        plt.SendData("Voltage5", (float)volBuf[5]/100);
        plt.SendData("Voltage6", (float)volBuf[6]/100);
        plt.SendData("Voltage7", (float)volBuf[7]/100);
        plt.SendData("Voltage8", (float)volBuf[8]/100);
        plt.SendData("Voltage9", (float)volBuf[9]/100);
        plt.SendData("Voltage10", (float)volBuf[10]/100);
        plt.SendData("Voltage11", (float)volBuf[11]/100);
        plt.SendData("Voltage12", (float)volBuf[12]/100);
        plt.SendData("Voltage13", (float)volBuf[13]/100);
        plt.SendData("Voltage14", (float)volBuf[14]/100);
        plt.SendData("Voltage15", (float)volBuf[15]/100);
        int sum = 0;
        for (int i = 0; i < 16; ++i){
          sum += volBuf[i];
        }
        plt.SendData("VoltageTotal", (float)sum/100);
        panel.SetText("textVoltage16", itoa(sum, tmpBuf, 10));
      }
      
      if (everything_is_broken_and_i_hate_the_world){
        Serial.println("everything is broken and i hate the world");
      }
      

      InterfacePanel panel;
      
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);

 

      // Send a reply
      uint8_t data[] = "ACK";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      digitalWrite(LED, LOW);
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}
