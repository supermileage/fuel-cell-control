#include <SPI.h>
#include <RH_RF95.h>

 

 
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

 


// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0

 

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

 

void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

 

  Serial1.begin(9600);

 

  delay(100);
  
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

 

  while (!rf95.init()) {
    while (1);
  }
  
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    while (1);
  }
  rf95.setTxPower(23, false);
}

 

int16_t packetnum = 0;  // packet counter, we increment per xmission

 

void loop()
{
  int i=0;
  //delay(1000); // Wait 1 second between transmits, could also 'sleep' here!
  
  char radiopacket[200] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";

 

  //dtostrf(one, 4, 2, radiopacket);
  


  if (Serial1.available()) {
    //delay(100); //allows all serial sent to be received together
    while (Serial1.read() != 12){
      while(!Serial1.available()){}
    }
    while(radiopacket[i] != 12 && i < 199) {
      while(!Serial1.available()){
      }
      radiopacket[++i] = Serial1.read();
    }
    radiopacket[0] = 12;
    radiopacket[i++]='\0';
  }

 

  if(i>0) {
    //delay(10);
    rf95.send((uint8_t *)radiopacket, 200);
    rf95.waitPacketSent();
    // Now wait for a reply
    
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
  
    if (rf95.waitAvailableTimeout(1000))
    { 
      // Should be a reply message for us now   
      if (rf95.recv(buf, &len))
     {
      
      }
      else
      {

 

      }
    }
    else
    {
 
    }
  
  }
}
