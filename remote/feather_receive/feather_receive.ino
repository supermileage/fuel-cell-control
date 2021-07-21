

#include <SPI.h>
#include <RH_RF95.h>

 

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

 

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0

 

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

 

// Blinky on receipt
#define LED 13

 

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

 

    if (rf95.recv(buf, &len))
    {
      digitalWrite(LED, HIGH);
      Serial.println((char*)buf);
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
