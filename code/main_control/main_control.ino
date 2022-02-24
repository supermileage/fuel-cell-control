/* Mode switch guide:
 0; Stop state //big pump off, little pump off, relay on
 1: Start state // little pump on, relay off
 2: Big Pump On
 3: Big Pump Off
 4: Debugging = True, -> print the voltage values without sorting the cells
 5: Debugging = False, -> normal mode
 6: iterate through pwm of little pump 
 */

#define RELAY 8
#define BIG_PUMP 9
#define LITTLE_PUMP 10 //temp fix //nvm

#define PUMP_PWM 255

#define MUX_SEL_0 4
#define MUX_SEL_1 5
#define MUX_SEL_2 6
#define MUX_SEL_3 7

#define MUX_OUT_1 A0
#define MUX_OUT_2 A1

#define NUM_CELLS 20

#define LED 13

float muxVals[NUM_CELLS] = {};
float volVals[NUM_CELLS] = {};
int rawVals[NUM_CELLS] = {};

float voltage_divider = 5.0*(820+430)/430; ////14.53
bool led = LOW;

bool bigPump = false;
bool initializing = true;

bool start = true;
bool first = false;
bool error = false;

bool debugging = false;

bool one_pump = false;

int errorCell = -1;
float errorVol = 0;

float time = 0.0;
int delay_time = 1000;

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
  delay(delay_time); //add when debugging to view values easily
  //Serial.print("test");

  // Iterate through each mux to get an analog reading
  for(uint8_t muxSel = 0; muxSel < 16; muxSel++){
    digitalWrite(MUX_SEL_0, muxSel & 1);
    digitalWrite(MUX_SEL_1, (muxSel & 2) >> 1);
    digitalWrite(MUX_SEL_2, (muxSel & 4) >> 2);
    digitalWrite(MUX_SEL_3, (muxSel & 8) >> 3);

    //delay is added here to take into account switching time between the muxes 
    // Enable turn-on/off time is approxiamtely 150 ns each, will use 5ms to be safe 
    delay(5);
    
    // get mux readings and convert them to 1
    rawVals[muxSel] = analogRead(MUX_OUT_1);
    muxVals[muxSel] = (float) rawVals[muxSel] / 1023 * voltage_divider;

    // add values from second mux to the array
    if (muxSel < NUM_CELLS - 16){ //only need the space for the number of pins there are
      rawVals[muxSel+16] = analogRead(MUX_OUT_2);
      muxVals[muxSel+16] = (float) rawVals[muxSel+16] / 1023 * voltage_divider;
    } 
  }
  //print raw unsorted for debugging each individual pin of board
  if(debugging){
    //Serial.println("raw and unsorted");
    for (int i = 0; i < NUM_CELLS; i++){
    Serial.print(rawVals[i]);
    Serial.print("\t");
  }  
  Serial.println("\n");
  }


  //sort muxes in order of smallest to largest
  //this allows us to plug in the cells in any order
  qsort(muxVals,NUM_CELLS, sizeof (float), compar);

////print raw values for debugging purposes
  // Serial.println("\nraw");
  // for (int i = 0; i < NUM_CELLS; i++){
  //   Serial.print((float)muxVals[i]);
  //   Serial.print("\t");
  // }  
  
  //calculate voltage values of each individual cell
  volVals[0] = muxVals[0];
  if(!debugging){
    Serial.println("\nvol");
    Serial.print((float)volVals[0]);
    Serial.print("\t");
  }

  for (int i = 1; i < NUM_CELLS; i++){
    volVals[i] = muxVals[i] - muxVals[i-1];
    if(!debugging){
      Serial.print((float)volVals[i]);
      Serial.print("\t");
    }
    
  }  
  // todo: find number of expected zeroes, based on number of cells plugged in, and ignore that number of zeroes

  // get min, avg and total voltage values
  //qsort(volVals,NUM_CELLS, sizeof (float), compar);
  int trailing_zeros = 4;
  int leading_zeros = 1;
  //volVals[expected_zeroes] = muxVals[expected_zeroes];// takes into account the weird not exactly zero readings we have from a few cells

  float volMin = volVals[trailing_zeros];
  float volTotal = 0;
  float volAvg = 0;
  int count = 0;
  int minIndex = 0;


  // calculate averages, total, minimums etc...
  for (int i = leading_zeros; i < NUM_CELLS - trailing_zeros; i++){
    volTotal += volVals[i];
    count++;
    
    if(volVals[i] < volMin){
      volMin = volVals[i];
      minIndex = i;
    } 
  }

  volAvg = volTotal / count;
  
  // print info:
  if(!debugging){
    Serial.print("\n");
    Serial.print("m ");
    Serial.println(volMin);
    Serial.print("i ");
    Serial.println(minIndex);

    Serial.print("t ");
    Serial.println(volTotal);

    Serial.print("a ");
    Serial.println(volAvg);
  }
  

  //check if user has entered information into the serial monitor
   if (Serial.available()){
    Serial.print("Serial received - ");
    unsigned char modeSwitch = Serial.read();
    // todo print char here
    
    if (modeSwitch == '1'){
      Serial.println("Starting");
      time = 0.0;
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

    // 2 and 3 are for turning on and off big pump without affecting anything else in the system
    else if(modeSwitch == '2'){
      Serial.println("Big Pump High");
      digitalWrite(BIG_PUMP, HIGH);
      bigPump = true;
    }
    else if(modeSwitch == '3'){
      Serial.println("Big Pump Low");
      digitalWrite(BIG_PUMP, LOW);
      bigPump = false;
    }

    //determines what information is printed to serial, when debugging is true, we print the raw unsorted values
    else if(modeSwitch == '4'){
      debugging = true;
    }
    else if(modeSwitch == '5'){
      debugging = false;
    }
    else if(modeSwitch == '6'){ //test pump pwm on little pump
      for (int j=0; j<255; j++){
        analogWrite(LITTLE_PUMP, j);
        delay(10);
      }
    }
    //7 and 8 are for indivually testing the safety without turning on other pumps
    else if(modeSwitch == '7'){
      Serial.println("Relay Low");
      digitalWrite(RELAY, LOW);
    }
    else if(modeSwitch == '8'){
      Serial.println("Relay High");
      digitalWrite(RELAY, HIGH);
    }
    //turn off little pump without turning on relay
    else if(modeSwitch == '9'){
      Serial.println("Little pump Low");
      digitalWrite(LITTLE_PUMP, LOW);
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
        Serial.println("Error");
        Serial.print("Error Cell: ");
        Serial.println(errorCell);
        Serial.print("Error Voltage: ");
        Serial.println(errorVol);
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

      
      
      if (volMin < 0.5){
        digitalWrite(RELAY, HIGH);
        digitalWrite(LITTLE_PUMP, LOW);
        digitalWrite(BIG_PUMP, LOW);
        error = true;
        bigPump = false;
        errorCell = minIndex;
        errorVol = volMin;
      }

      
    } // wait until capacitor charges up to 12 Volts
    else if (volMin > 0.75) {
        initializing = false;
        //delay(2000);
    }
    // todo: add if still in initialization state
    else if(time>15000){
      digitalWrite(RELAY, HIGH);
      digitalWrite(LITTLE_PUMP, LOW);
      digitalWrite(BIG_PUMP, LOW);
      error = true;
      bigPump = false;
      errorCell = minIndex;
      errorVol = volMin;
      Serial.println("stuck in intialization");
    }
    
    else{
      // initialization state
      //time += delay_time; //comment this out to disable startup shutdown
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


/*
Notes from our session 2/23/2022, change the code to account for:
- plan hard wire connection so we know what cells are what
- ignore first 4 and last cell
- should decend from 13-14ish down to 0.8 ish for the cells that we are not ignoring
- purple wire on bottom left
*/

