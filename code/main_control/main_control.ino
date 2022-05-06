/* Mode switch guide:
 0; Stop state //big pump off, little pump off, relay on
 1: Start state // little pump on, relay off
 2: Big Pump On
 3: Big Pump Off
 4: Debugging = True, -> print the voltage values with reference to ground instead of cell values
 5: Debugging = False, -> normal mode
 6: iterate through pwm of little pump 
 7: Relay Low
 8: Relay High
 9: Little Pump Low
 a: Little Pump High
 b: loop read only the mux select of last voltage reading - for testing

 Common operation: 07a
 */
 //let's us switch between Serial (USB) and Serial1 (TX and RX pins) for telemetry data
#define SERIAL Serial

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

int leading_zeros = 2; //should be 4
int trailing_zeros = 1; //should be 1? or maybe 2 - probably 1

float muxVals[NUM_CELLS] = {};
float volVals[NUM_CELLS] = {};
int rawVals[NUM_CELLS] = {};

float voltage_divider = 5.0*(820+430)/427; ////14.54 //need to calibrate properly
bool led = LOW;

bool bigPump = false;
bool initializing = true;

bool start = true;
bool first = false;
bool error = false;

bool debugging = false;

bool one_pump = false;

int errorIndex = -1;
int errorCell = 0;
float errorVol = 0;

float time = 0.0;
int mux_delay = 5;
int extra_delay = 200;
int delay_time = mux_delay*16+extra_delay;

bool read_last_volt = false;
float last_reading = 0.0;

int cellTable[NUM_CELLS] = {16,-1,-1,16,15,14,13,12,11,10,9,8,7, 6, 5, 4, 3, 2, 1, 3};
float cell_calibration[NUM_CELLS] = {0.0143, 0.0143, 0.0155, 0.0156, 0.0155, 0.0156, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141, 0.0141};

// unsigned long lastErrorTime = 0;
// unsigned long lastBigPumpTime = 0;
// unsigned long debounceDelay = delay_time*4;

int bigPumpCounter = 0;
int errorCount = 0;
int countLimit = 2;

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
  
  SERIAL.begin(9600);
  //SERIAL.print("Hello");

}

void loop() {
  // put your main code here, to run repeatedly:
  // Debug LED
  digitalWrite(LED, led);
  led = !led;
  delay(extra_delay); //add when debugging to view values easily
  //SERIAL.print("test");

  // Iterate through each mux to get an analog reading
  for(uint8_t muxSel = 0; muxSel < 16; muxSel++){
//    digitalWrite(MUX_SEL_0, 19);
//    digitalWrite(MUX_SEL_1, 19);
//    digitalWrite(MUX_SEL_2, 19);
//    digitalWrite(MUX_SEL_3, 19);
//
//    delay(mux_delay);
    
    digitalWrite(MUX_SEL_0, (muxSel) & 1);
    digitalWrite(MUX_SEL_1, ((muxSel) & 2) >> 1);
    digitalWrite(MUX_SEL_2, ((muxSel) & 4) >> 2);
    digitalWrite(MUX_SEL_3, ((muxSel) & 8) >> 3);

    //delay is added here to take into account switching time between the muxes 
    // Enable turn-on/off time is approxiamtely 150 ns each, will use 5ms to be safe 
    delay(mux_delay);
    
    // get mux readings and convert them to 1
    rawVals[muxSel] = analogRead(MUX_OUT_1);
    muxVals[muxSel] = (float) rawVals[muxSel] * cell_calibration[muxSel];

    // add values from second mux to the array
    if (muxSel < NUM_CELLS - 16){ //only need the space for the number of pins there are
      rawVals[muxSel+16] = analogRead(MUX_OUT_2);
      muxVals[muxSel+16] = (float) rawVals[muxSel+16] * cell_calibration[muxSel + 16];
    } 
  }
  //int newCalibration = 0.0155;
  rawVals[2] = analogRead(A2);
  rawVals[3] = analogRead(A6);
  rawVals[4] = analogRead(A4);
  rawVals[5] = analogRead(A5);
  for(int i=2;i<=5;i++){
    muxVals[i] = rawVals[i]*cell_calibration[i];
  }
  

  //print raw unsorted for debugging each individual pin of board
  if(debugging){
    //SERIAL.println("raw and unsorted");
    for (int i = leading_zeros; i < NUM_CELLS - trailing_zeros; i++){
    //for (int i = 0; i < NUM_CELLS; i++){
    SERIAL.print(i);
    SERIAL.print(": ");
    SERIAL.print(muxVals[i]);
    SERIAL.print("\t");
  }  
  SERIAL.println("\n");
  }


  //sort muxes in order of smallest to largest
  //this allows us to plug in the cells in any order
  //qsort(muxVals,NUM_CELLS, sizeof (float), compar); //don't sort, we will hard code cell positions

////print raw values for debugging purposes
  // SERIAL.println("\nraw");
  // for (int i = 0; i < NUM_CELLS; i++){
  //   SERIAL.print((float)muxVals[i]);
  //   SERIAL.print("\t");
  // }  
  
  //calculate voltage values of each individual cell
  /*volVals[NUM_CELLS-trailing_zeros] = muxVals[NUM_CELLS-trailing_zeros];
  if(!debugging){
    SERIAL.println("\nvol");
    //SERIAL.print((float)volVals[0]);
    SERIAL.print("\t");
  }*/

  for (int i = leading_zeros; i < NUM_CELLS-trailing_zeros-1; i++){
    volVals[i] = muxVals[i] - muxVals[i+1];
    if(!debugging){
      SERIAL.print((float)volVals[i]);
      SERIAL.print("\t");
    }
    
  }  
  volVals[NUM_CELLS-trailing_zeros-1] = muxVals[NUM_CELLS-trailing_zeros-1];
  if(!debugging){
    //SERIAL.println("\nvol");
    SERIAL.print((float)volVals[NUM_CELLS-trailing_zeros-1]);
    SERIAL.print("\t");
  }
  // todo: find number of expected zeroes, based on number of cells plugged in, and ignore that number of zeroes

  // get min, avg and total voltage values
  //qsort(volVals,NUM_CELLS, sizeof (float), compar);
  
  //volVals[expected_zeroes] = muxVals[expected_zeroes];// takes into account the weird not exactly zero readings we have from a few cells

  //volVals[leading_zeros] = volVals[leading_zeros] + volVals[NUM_CELLS-trailing_zeros]; //shifting to account for the ground loop we were getting
  //SERIAL.print("\nbottom cell offset added: ");
  //SERIAL.println(volVals[NUM_CELLS-trailing_zeros]);
  float volMin = volVals[leading_zeros];
  float volTotal = 0;
  float volAvg = 0;
  int count = 0;
  int minIndex = leading_zeros;
  int secondMinIndex = leading_zeros+1;
  int secondVolMin = volVals[leading_zeros+1];



  // calculate averages, total, minimums etc...
  for (int i = leading_zeros; i < NUM_CELLS - trailing_zeros; i++){
    volTotal += volVals[i];
    count++;
    
    if(volVals[i] < volMin){
      secondMinIndex = minIndex;
      secondVolMin = volMin;
      volMin = volVals[i];
      minIndex = i;
    } 
  }

  volAvg = volTotal / count;
  
  // print info:
  if(!debugging){
    SERIAL.print("\n");
    SERIAL.print("m ");
    SERIAL.println(volMin);
    SERIAL.print("i ");
    SERIAL.println(minIndex);

    SERIAL.print("t ");
    SERIAL.println(volTotal);

    SERIAL.print("a ");
    SERIAL.println(volAvg);
  }
  

  //check if user has entered information into the serial monitor
   if (SERIAL.available()){
    SERIAL.print("Serial received - ");
    unsigned char modeSwitch = SERIAL.read();
    // todo print char here
    
    if (modeSwitch == '1'){
      SERIAL.println("Starting");
      time = 0.0;
      start = true;
      error = false;
      initializing = true;
      analogWrite(LITTLE_PUMP, PUMP_PWM); // 30%
      digitalWrite(RELAY, LOW); 
    }
    else if (modeSwitch == '0'){
      SERIAL.println("Stopping");
      start = false;
      digitalWrite(LITTLE_PUMP, LOW);
      digitalWrite(RELAY, HIGH);
      digitalWrite(BIG_PUMP, LOW);
      bigPump = false;
    }
    // todo: have other options and label them better

    // 2 and 3 are for turning on and off big pump without affecting anything else in the system
    else if(modeSwitch == '2'){
      SERIAL.println("Big Pump High");
      digitalWrite(BIG_PUMP, HIGH);
      bigPump = true;
    }
    else if(modeSwitch == '3'){
      SERIAL.println("Big Pump Low");
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
      SERIAL.println("Relay Low");
      digitalWrite(RELAY, LOW);
    }
    else if(modeSwitch == '8'){
      SERIAL.println("Relay High");
      digitalWrite(RELAY, HIGH);
    }
    //turn off little pump without turning on relay
    else if(modeSwitch == '9'){
      SERIAL.println("Little pump Low");
      digitalWrite(LITTLE_PUMP, LOW);
      start = false;
    }
    else if(modeSwitch == 'a'){
      SERIAL.println("Little pump High");
      digitalWrite(LITTLE_PUMP, HIGH);
    }

    //mux select the last voltage reading
    else if(modeSwitch == 'b'){
      while(true){
        if (SERIAL.available()){
          break;
        }
        int muxSel = 4;
        digitalWrite(MUX_SEL_0, muxSel & 1);
        digitalWrite(MUX_SEL_1, (muxSel & 2) >> 1);
        digitalWrite(MUX_SEL_2, (muxSel & 4) >> 2);
        digitalWrite(MUX_SEL_3, (muxSel & 8) >> 3);

        delay(5);

        last_reading = analogRead(MUX_OUT_1)  / (float)1023 * voltage_divider;

        SERIAL.println(last_reading);
        SERIAL.println("*");

        delay(200);

      }
    }
    delay(500);
  } 

  //comment this section out if we fix the top cell issue
  // if(minIndex = leading_zeros){
  //   volMin = secondVolMin;
  //   minIndex = secondMinIndex;
  // }
  
  // control logic
  // check if it is in the initialization state 
  // todo change this into a more clear state machine --> initialization state, error state, start/stop state
  if(start){
    if(!initializing){
      //add error state here
      if(error){
        SERIAL.println("Error");
        SERIAL.print("Error Index: ");
        SERIAL.println(errorIndex);
        if(errorIndex != -1){
          SERIAL.print("Error Cell: ");
          SERIAL.println(cellTable[errorIndex]);
        }
        SERIAL.print("Error Voltage: ");
        SERIAL.println(errorVol);
        return;
      }


      // if voltage is too low, turn on big pump until voltage exceeds a threshold 
      //Todo: add option for only one pump here
      if (!bigPump && volMin < 0.7 ) {
        bigPumpCounter += 1;
        if(bigPumpCounter>countLimit){
          digitalWrite(BIG_PUMP, HIGH);
          bigPump = true;
          bigPumpCounter = countLimit + 5; //placeholder to prevent overflow
        }
        
      } else if (bigPump, volMin > 0.75) {
        bigPump = false;
        digitalWrite(BIG_PUMP, LOW);
        bigPumpCounter = 0;
        
      } else{
        bigPumpCounter = 0;
      }

      
      
      if (volMin < 0.4){
        errorCount += 1;
        if(errorCount>countLimit){
          digitalWrite(RELAY, HIGH);
          digitalWrite(LITTLE_PUMP, LOW);
          digitalWrite(BIG_PUMP, LOW);
          error = true;
          bigPump = false;
          errorIndex = minIndex;
          errorVol = volMin;
        }
        
      }
      else{
        errorCount = 0;
      }

      
    } // wait until capacitor charges up to 12 Volts
    else if (volMin > 0.6) {
        initializing = false;
        //delay(2000);
    }
    // todo: add if still in initialization state
    else if(time>18000){
      time = 28000;
      digitalWrite(RELAY, HIGH);
      digitalWrite(LITTLE_PUMP, LOW);
      digitalWrite(BIG_PUMP, LOW);
      error = true;
      bigPump = false;
      errorIndex = minIndex;
      errorVol = volMin;
      SERIAL.println("stuck in init");
    }
    else if(time>10000 && !bigPump){
      digitalWrite(BIG_PUMP, HIGH);
      bigPump = true;
      errorIndex = minIndex;
      errorVol = volMin;
      SERIAL.println("big init");
    }
    
    
    else{
      // initialization state
      time += delay_time; //comment this out to disable startup shutdown
      analogWrite(LITTLE_PUMP, PUMP_PWM);
       SERIAL.println("init");
    }
  }
  //stop state
  else{
    SERIAL.println("Stop state");
  }
  
  //end character for sending data
  SERIAL.print("*");
}

int compar (const void* p1, const void* p2){
  if(*(float*)p1 < *(float*)p2) return -1;
  if(*(float*)p1 == *(float*)p2) return 0;
  if(*(float*)p1 > *(float*)p2) return 1;
}


/*
Notes from our session 2/23/2022, change the code to account for:
- plan hard wire connection so we know what cells are what
- ignore first 4 and last 1 cell
- should decend from 13-14ish down to 0.8 ish for the cells that we are not ignoring
- purple wire on bottom left


expected ish (I don't feel like doing actual calcs but assume they are about the same diff): 
0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19
n   n   n   n   14  13  12  11  10  9   8    7    6    5    4  3.2   2.4  1.6  0.8  0  
//very approximate idea
cell corresponding to index rearranged:
wiring cell:  16  n   n   n   15  14  13  12  11  10   9    8    7    6    5    4    n    2    1    3
index:        0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19
cell index:   16  -1  -1  16  15  14  13  12  11  10   9    8    7    6    5    4    3    2    1    3

// recheck voltage reading
*/
