#define LED_DEBUG

// Multiplexer input selector
#define MUX1A0 P2_2 
#define MUX1A1 P1_6
#define MUX1A2 P2_5

// Multiplexer output
#define MUX1_IN P1_1
#define MUX2_IN P1_0

// Debug LEDs
#define LED0 P1_2
#define LED1 P1_3
#define LED2 P1_4
#define LED3 P1_5
#define LED4 P1_7

// Multiplexor input selector value
uint8_t out;
int mux_vals[16];


void setup() {
  pinMode(MUX1A0, OUTPUT);
  pinMode(MUX1A1, OUTPUT);
  pinMode(MUX1A2, OUTPUT);

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  pinMode(MUX1_IN, INPUT_PULLDOWN);
  pinMode(MUX2_IN, INPUT_PULLDOWN);

  out = 0;    // Initiate out to 0b000 (actual multiplexer input is inverted)
}

void loop() {
  mux_vals = {0}
  // reads all the voltage values
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
    
    // Read in values
    int m1 = digitalRead(MUX1_IN);
    int m2 = digitalRead(MUX2_IN);

    // Write MUX outputs to mux arr
    mux_vals[out] = m1;
    mux_vals[out + 8] = m2;

    #if defined(LED_DEBUG)
    //Write debug MUX out values
    digitalWrite(LED0, m1);
    digitalWrite(LED1, m2);
    #endif
  
    delay(100);
  }
}
