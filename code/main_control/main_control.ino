#define RELAY 8
#define BIG_PUMP 9
#define LITTLE_PUMP 10

#define PUMP_PWM 255

#define MUX_SEL_0 4
#define MUX_SEL_1 5
#define MUX_SEL_2 6
#define MUX_SEL_3 7

#define MUX_OUT_1 A0
#define MUX_OUT_2 A1

#define NUM_CELLS 19

#define LED 13

float muxVals[NUM_CELLS] = {};
float volVals[NUM_CELLS] = {};
int rawVals[NUM_CELLS] = {};

float voltage_divider = 16.921; //TODO: calculate value
bool led = LOW;

bool bigPump = false;
bool initializing = true;

bool start = true;
bool first = false;
bool error = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LITTLE_PUMP, OUTPUT);
  pinMode(BIG_PUMP, OUTPUT);
  pinMode(RELAY, OUTPUT);

  pinMode(MUX_SEL_0, OUTPUT);
  pinMode(MUX_SEL_1, OUTPUT);
  pinMode(MUX_SEL_2, OUTPUT);
  pinMode(MUX_SEL_3, OUTPUT);

  pinMode(MUX_OUT_1, INPUT);
  pinMode(MUX_OUT_2, INPUT);
  
  pinMode(LED, OUTPUT);

  digitalWrite(RELAY, LOW);
  digitalWrite(BIG_PUMP, LOW);
  analogWrite(LITTLE_PUMP, PUMP_PWM);
  
  Serial.begin(9600);
  //Serial.print("Hello");

}

void loop() {
  // put your main code here, to run repeatedly:
  // Debug LED
  digitalWrite(LED, led);
  led = !led;
  //delay(1000);
  //Serial.print("test");

  // Iterate through each mux to get an analog reading
  for(uint8_t muxSel = 0; muxSel < 16; muxSel++){
    digitalWrite(MUX_SEL_0, muxSel & 1);
    digitalWrite(MUX_SEL_1, (muxSel & 2) >> 1);
    digitalWrite(MUX_SEL_2, (muxSel & 4) >> 2);
    digitalWrite(MUX_SEL_3, (muxSel & 8) >> 3);

    //note: previous code needed some delay, so we may need a delay here
    
    rawVals[muxSel] = analogRead(MUX_OUT_1);
    muxVals[muxSel] = (float) rawVals[muxSel] / 1023 * voltage_divider;

    // add values from second mux to the array
    if (muxSel < NUM_CELLS - 16){ 
      rawVals[muxSel+16] = analogRead(MUX_OUT_2);
      muxVals[muxSel+16] = (float) rawVals[muxSel] / 1023 * voltage_divider;
    } 
  }
  //sort muxes in order of smallest to largest
  //this allows us to plug in the cells in any order
  qsort(muxVals,NUM_CELLS, sizeof (float), compar);

//print raw values for debugging purposes
  Serial.println("raw");
  for (int i = 0; i < NUM_CELLS; i++){
    Serial.print((float)muxVals[i]);
    Serial.print("\t");
  }  
  Serial.println("vol");
  // calculate voltage values of each individual cell
  volVals[0] = muxVals[0];
  Serial.print((float)volVals[0]);
  Serial.print("\t");

  for (int i = 1; i < NUM_CELLS; i++){
    volVals[i] = muxVals[i] - muxVals[i-1];
    Serial.print((float)volVals[i]);
    Serial.print("\t");
  }  

  // get min, avg and total voltage values
  float volMin = volVals[0];
  float volTotal = 0;
  float volAvg = 0;
  int count = 0;
  int minIndex = 0;

  // calculate averages, total, minimums etc...
  for (int i = 0; i < NUM_CELLS; i++){
    volTotal += volVals[i];
    count++;
    
    if(volVals[i] < volMin){
      volMin = volVals[i];
      minIndex = i;
    } 
  }

  volAvg = volTotal / count;
  
  // print info:
  Serial.print("\n");
  Serial.print("m ");
  Serial.println(volMin);
  Serial.print("i ");
  Serial.println(minIndex);

  Serial.print("t ");
  Serial.println(volTotal);

  Serial.print("a ");
  Serial.println(volAvg);

  //check if user has entered information into the serial monitor
   if (Serial.available()){
    Serial.print("Serial received - ");
    unsigned char modeSwitch = Serial.read();
    
    if (modeSwitch == '1'){
      Serial.println("Starting");
      start = true;
      error = false;
      initializing = true;
      analogWrite(LITTLE_PUMP, PUMP_PWM); // 30%
      digitalWrite(RELAY, LOW); 
    }
    else if (modeSwitch == '0'){
      Serial.println("Stopping");
      start = false;
      digitalWrite(LITTLE_PUMP, LOW);
      digitalWrite(RELAY, HIGH);
      digitalWrite(BIG_PUMP, LOW);
      bigPump = false;
    }
    // todo: have other options and label them better
    else if(modeSwitch == '2'){
      Serial.println("Big Pump High");
      digitalWrite(BIG_PUMP, HIGH);
      bigPump = true;
    }
    else if(modeSwitch == '3'){
      Serial.println("Big Pump low");
      digitalWrite(BIG_PUMP, LOW);
      bigPump = false;
    }
    
    delay(1000);
  } 

  
  // control logic
  // check if it is in the initialization state 
  // todo change this into a more clear state machine --> initialization state, error state, start/stop state
  if(start){
    if(!initializing){
      //add error state here
      if(error){
        Serial.print("Error");
        //add more stuff here
        return;
      }


      // if voltage is too low, turn on big pump until voltage exceeds a threshold 
      if (!bigPump && volMin < 0.7 ) {
        digitalWrite(BIG_PUMP, HIGH);
        bigPump = true;
      } else if (bigPump, volMin > 0.75) {
        bigPump = false;
        digitalWrite(BIG_PUMP, LOW);
      }

      //todo add when voltage is less that 0.5 error

      
    } // wait until capacitor charges up to 12 Volts
    else if (volTotal > 12) {
        initializing = false;
        delay(3000);
    } 
    else{
      // initialization state
      analogWrite(LITTLE_PUMP, PUMP_PWM);
    }
  }
  //stop state
  else{
    Serial.println("Stop state");
  }
  


}

int compar (const void* p1, const void* p2){
  if(*(float*)p1 < *(float*)p2) return -1;
  if(*(float*)p1 == *(float*)p2) return 0;
  if(*(float*)p1 > *(float*)p2) return 1;
}

