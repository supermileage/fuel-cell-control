//#define LED_DEBUG
#define SERIAL_DEBUG

// Multiplexer input selector
#define MUX1A0 P2_2 
#define MUX1A1 P1_6
#define MUX1A2 P2_5

// Multiplexer output
#define MUX1_IN P1_5
#define MUX2_IN P1_0

// Debug LEDs
#define LED1 P1_3
#define LED2 P1_4
#define LED3 P1_5
#define LED4 P1_7

// Multiplexor input selector value
uint8_t out;
int mux_vals[16] = {0};


void setup() {
  Serial.begin(9600);
  pinMode(MUX1A0, OUTPUT);
  pinMode(MUX1A1, OUTPUT);
  pinMode(MUX1A2, OUTPUT);

  #if defined(LED_DEBUG)
//  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
//  pinMode(LED3, OUTPUT);
//  pinMode(LED4, OUTPUT);
  #endif

//  pinMode(MUX1_IN, INPUT);
//  pinMode(MUX2_IN, INPUT);
  
  //establishContact(); // send a byte to establish contact until receiver responds 

  out = 0;    // Initiate out to 0b000 (actual multiplexer input is inverted)
}

void loop() {
//  mux_vals = {0}
  // reads all the voltage values
  //Serial.print("In loop");
  for (out = 0; out < 8; out ++){
    // Write MUX selector values
    digitalWrite(MUX1A0, out & 1);
    digitalWrite(MUX1A1, (out & 2) >> 1 );
    digitalWrite(MUX1A2, (out & 4) >> 2 );

    #if defined(LED_DEBUG)
    // Write output LED values
    digitalWrite(LED2, out & 1);
    digitalWrite(LED3, (out & 2) >> 1 );
    digitalWrite(LED4, (out & 4) >> 2 );
    #endif
    delay(1000);
    
    // Read in values
    int m1 = analogRead(MUX1_IN);
    int m2 = analogRead(MUX2_IN);

    // Write MUX outputs to mux arr
    mux_vals[out] = m1;
    mux_vals[out + 8] = m2;

    #if defined(LED_DEBUG)
    //Write debug MUX out values
    digitalWrite(LED1, m2);
    #endif
  
    
  }

  for(int i=0; i<16; i++){
    Serial.print( (float)mux_vals[i] ); /// 1023 * 16.921
    Serial.print("\t");
  } 
  Serial.print("\n");
}


//void establishContact() {
//  while (Serial.available() <= 0) {
//    Serial.println('A'); // send a capital A
//    delay(300);
//  }
// }
