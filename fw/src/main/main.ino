#include <stdlib.h>

// Multiplexer input selector
#define MUX1A0 13
#define MUX1A1 10
#define MUX1A2 12

// SD card pins
#define SDCLK 7
#define SDCS 8
#define SDMOPI 15
#define SDMIPO 14

//Air pump mosfet
#define PUMP 9

//Hall Effect in
#define HALL_EFFECT_2 6
#define HALL_EFFECT_1 2

//Relays
#define RELAY1 19
#define RELAY2 18

// Multiplexer output
#define MUX_OUT 5

// Multiplexor selector
#define MUX_SEL 11

// Multiplexer input selector value
float muxVals[16] = {};
float volVals[16] = {};
int rawVals[16] = {};
bool relay_closed = 1;

void setup() {
  Serial.begin(9600);
  pinMode(MUX1A0, OUTPUT);
  pinMode(MUX1A1, OUTPUT);
  pinMode(MUX1A2, OUTPUT);
  pinMode(MUX_OUT, INPUT);
  pinMode(MUX_SEL, OUTPUT);
  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(PUMP, OUTPUT);

  pinMode(HALL_EFFECT_1, INPUT);
  pinMode(HALL_EFFECT_2, INPUT);

  /*
  pinMode(SDCLK, INPUT);
  pinMode(SDCS, INPUT);
  pinMode(SDMOPI, INPUT);
  pinMode(SDMIPO, INPUT);*/
  
}

void loop() {
  // reads all the voltage values
  //Serial.print("In loop");
  for (uint8_t out = 0; out < 16; out ++){
    // Write MUX selector values
    digitalWrite(MUX1A0, out & 1);
    digitalWrite(MUX1A1, (out & 2) >> 1 );
    digitalWrite(MUX1A2, (out & 4) >> 2 );
    digitalWrite(MUX_SEL, (out & 8) >> 3);

    Serial.print(out & 1);
    Serial.print((out & 2) >> 1);
    Serial.print((out & 4) >> 2);
    Serial.println((out & 8) >> 3);
    
    delay(500);
    
    // Read in values to raw vals
    rawVals[out] = analogRead(MUX_OUT);
  }

  // Sort rawVals in increasing order - should sort them by cell voltage as well
  sort(rawVals, 16);

  for (int i = 0; i < 16; ++i){
    muxVals[i] = (float)rawVals[i]/1023*16.291;    // muxVals is voltages of cells relative to ground
    volVals[i] = i ? muxVals[i] - muxVals[i-1] : muxVals[0];    //volVals is voltages of cells individually

    // Serial debug
    Serial.print(i);
    Serial.print(": ");
    Serial.print(volVals[i]);
    Serial.print("V");

    // Control logic
    if (volVals[i] <  0.5){
      Serial.print("\n");  // tis but a flesh wound
      Serial.print("-ERROR- Cell ");
      Serial.print(i);
      Serial.print(" at ");
      Serial.print(volVals[i]);
      Serial.print("V is most likely exploding.");

      // TODO: Turn off the fuel cell 
    }
    
    // control logic
  }
  Serial.print("\n");
}

int compar (const void* p1, const void* p2){
  if(*(float*)p1 < *(float*)p2) return -1;
  if(*(float*)p1 == *(float*)p2) return 0;
  if(*(float*)p1 > *(float*)p2) return 1;
}

/*
 * function get_min
 * gets minimum value from an array of values - ignores 0s
 * param arr - array of values to get value from
 * param len - length of arr
 */
float get_min (float arr[], int len){
  float ret = 420;
  for (int i = 1; i < len; ++i){
    if (arr[i] != 0 && arr[i] < ret) ret = arr[i];
  }
  return ret;
}

/*
 * function get_total
 * gets sum of values in an array
 * param arr - array of values to get total from
 * param len - length of arr
 */
float get_total (float arr[], int len){
  float ret = 0;
  for (int i = 1; i < len; ++i){
    ret += arr[i];
  }
  return ret;
}

/*
 * function get_avg
 * gets average in an array - ignores 0s
 * param arr - array of values to get average from
 * param len - length of array
 */
float get_avg(float arr[], int len){
  int count = 0;
  for (int i = 0; i < len; i ++){
    if (arr[i] != 0)
      count ++;
  }
  return get_total(arr, len) / count;
}

/*
 * function sort
 * sorts array
 * param arr - array to sort
 * param len - length of arr
 */
void sort( int * arr, int len ){
  int minIndex;
  int min;
  for( int i=0; i<len; i++ ){
    min = 69420;
    for( int j=i; j<len; j++ ){
      if (arr[j]<min){
        min = arr[j];
        minIndex = j;
      }    
    }
  arr[minIndex] = arr[i];
  arr[i] = min;
  }
}
