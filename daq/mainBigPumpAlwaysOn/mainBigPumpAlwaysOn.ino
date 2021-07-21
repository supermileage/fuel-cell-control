#define MUX_SEL_0 5
#define MUX_SEL_1 7
#define MUX_SEL_2 9

#define MUX_EN_0 10
#define MUX_EN_1 11

#define SMALLPUMP 3
#define BIGPUMP 12
#define PAS 255
#define HE_1 A2
#define HE_2 A3

#define RELAY A4

#define MUX_OUT A5

float muxVals[16] = {};
float volVals[16] = {};
int rawVals[16] = {};
bool led = LOW;
bool error = false;
bool first = true;
float errVol = 0;
bool start = true;

float minVol, avgVol, totalVol;
int minIndex, errCell;
int rawCurrent, finalCurrent;
bool bigPump;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(MUX_SEL_0, OUTPUT);
  pinMode(MUX_SEL_1, OUTPUT);
  pinMode(MUX_SEL_2, OUTPUT);
  pinMode(MUX_EN_0, OUTPUT);
  pinMode(MUX_EN_1, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(HE_1, INPUT);
  pinMode(HE_2, INPUT);

  pinMode(SMALLPUMP, OUTPUT);
  pinMode(BIGPUMP, OUTPUT);
  pinMode(RELAY, OUTPUT);

  analogWrite(SMALLPUMP, PAS);
  digitalWrite(RELAY, LOW);
  digitalWrite(BIGPUMP, HIGH);
  
  //Serial1.begin(9600);
  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {
  for (uint8_t muxSel = 0; muxSel < 16; muxSel ++){
    digitalWrite(MUX_SEL_0, muxSel & 1);
    digitalWrite(MUX_SEL_1, (muxSel & 2) >> 1);
    digitalWrite(MUX_SEL_2, (muxSel & 4) >> 2);
    digitalWrite(MUX_EN_0, (muxSel & 8) >> 3);
    digitalWrite(MUX_EN_1, ((~muxSel) & 8) >> 3);
    delay(5);
    rawVals[muxSel] = analogRead(MUX_OUT);
    muxVals[muxSel] = (float)rawVals[muxSel] / 1023 * 16.921;
  }
  //Serial1.write(12);
  Serial.write(12);
  qsort(muxVals, 16, sizeof (float), compar);
  volVals[0] = muxVals[0];
  //Serial1.print("0: ");
  Serial.print("0: ");
  //Serial1.print((float)volVals[0]);
  Serial.print((float)volVals[0]);
  //Serial1.print("V\t");
  Serial.print("V\t");
  for (int i = 1; i < 16; ++i){
    volVals[i] = muxVals[i] - muxVals[i-1];
    //Serial1.print(i);
    Serial.print(i);
    //Serial1.print(": ");
    Serial.print(": ");
    //Serial1.print((float)volVals[i]);
    Serial.print((float)volVals[i]);
    //Serial1.print("V     ");
    Serial.print("V     "); 
  }

  // Debug LED - 
  digitalWrite(13, led);
  led = !led;
  
  // Getting derivatives
  //Serial1.print(led);
  Serial.print(led);
  minIndex = get_min(volVals, 16);
  minVol = volVals[minIndex];
  totalVol = get_total(volVals,  16);
  avgVol = get_avg(volVals, 16);
  qsort(rawVals, 16, sizeof(int), compar);
  
  rawCurrent = analogRead(HE_1);
  //finalCurrent = rawCurrent / 1023 * 3.3;
  
  //Serial1.println("\t");

  //Serial1.print("min: ");
  //Serial1.print(minVol);
  //Serial1.print("\ton cell ");
  //Serial1.println(minIndex);

  //Serial1.print("total: ");
  //Serial1.println(totalVol);

  //Serial1.print("average: ");
  //Serial1.println(avgVol);

  //Serial1.print("raw max: ");
  //Serial1.println(rawVals[15]);
  
  //Serial1.print("raw current: ");
  //Serial1.println(rawCurrent);

  Serial.println("\t");

  Serial.print("min: ");
  Serial.print(minVol);
  Serial.print("\ton cell ");
  Serial.println(minIndex);

  Serial.print("total: ");
  Serial.println(totalVol);

  Serial.print("average: ");
  Serial.println(avgVol);

  Serial.print("raw max: ");
  Serial.println(rawVals[15]);
  
  Serial.print("raw current: ");
  Serial.println(rawCurrent);
  
//
//  if (Serial1.available()){
//    Serial1.print("Serial1 received - ");
//    unsigned char killMe = Serial1.read();
//    
//    if (killMe == '1'){
//      Serial1.println("Starting");
//      start = true;
//      error = false;
//      first = true;
//      analogWrite(SMALLPUMP, PAS); // 30%
//      digitalWrite(RELAY, LOW); 
//    }
//    else if (killMe == '0'){
//      Serial1.println("Stopping");
//      start = false;
//      digitalWrite(SMALLPUMP, LOW);
//      digitalWrite(RELAY, HIGH);
//      digitalWrite(BIGPUMP, HIGH);
//      bigPump = false;
//    }
//    
//    delay(1000);
//  } 

  digitalWrite(bigPump, HIGH);
  
  if (Serial.available()){
    Serial.print("Serial1 received - ");
    unsigned char killMe = Serial.read();
    
    if (killMe == '1'){
      Serial.println("Starting");
      start = true;
      error = false;
      first = true;
      analogWrite(SMALLPUMP, PAS); // 30%
      digitalWrite(RELAY, LOW); 
      digitalWrite(BIGPUMP, HIGH);
    }
    else if (killMe == '0'){
      Serial.println("Stopping");
      start = false;
      digitalWrite(SMALLPUMP, LOW);
      digitalWrite(RELAY, HIGH);
      digitalWrite(BIGPUMP, HIGH);
      bigPump = false;
    }
    
    delay(1000);
  } 
  

  if (start){
    if (!first){
      // control logic
      if (error) {
        //Serial1.print("-ERROR- IN ERROR STATE Voltage: ");
        //Serial1.print(errVol);
        //Serial1.print(" Cell: ");
        //Serial1.print(errCell);

        Serial.print("-ERROR- IN ERROR STATE Voltage: ");
        Serial.print(errVol);
        Serial.print(" Cell: ");
        Serial.print(errCell);
        return;
      } 

      // Pump logic
      if (/*!bigPump &&*/ minVol < 0.7 ) {
        digitalWrite(BIGPUMP, HIGH);
        bigPump = true;
      } else if (bigPump, minVol > 0.75) {
        bigPump = false;
        digitalWrite(BIGPUMP, HIGH);
      }
      
      if ( minVol < 0.5 ) {
        digitalWrite(RELAY, HIGH);
        digitalWrite(SMALLPUMP, LOW);
        digitalWrite(BIGPUMP, LOW);
        bigPump = false;
        //Serial1.print("-ERROR- Minimum voltage is lower than 0.5V");
        Serial.print("-ERROR- Minimum voltage is lower than 0.5V");
        errVol = minVol;
        errCell = minIndex;
        error = true;
      }
    } else if (totalVol > 12) {
      first = false;
      delay(3000);
    } else {
      //digitalWrite(SMALLPUMP, HIGH);
      analogWrite(SMALLPUMP, PAS); // 30%
      digitalWrite(RELAY, LOW);
      digitalWrite(BIGPUMP, HIGH);
      //Serial1.println("In init");
      Serial.println("In init");
    }
    
  } else {
      //Serial1.println("Stopped");
      Serial.println("Stopped");
  }
  
}

int compar (const void* p1, const void* p2){
  if(*(float*)p1 < *(float*)p2) return -1;
  if(*(float*)p1 == *(float*)p2) return 0;
  if(*(float*)p1 > *(float*)p2) return 1;
}

int get_min (float arr[], int len){
  float ret = 420;
  bool first_zero = false;
  int i;
  int index;
  for (i = 0; i < len; ++i){
    if (arr[i] <= 0.05 && !first_zero){
      first_zero = true;
      continue;
    }
    if (arr[i] < ret) {
      ret = arr[i];
      index = i;
    }
  }
  return index;
}

float get_total (float arr[], int len){
  float ret = 0;
  for (int i = 1; i < len; ++i){
    ret += arr[i];
  }
  return ret;
}

float get_avg(float arr[], int len){
  int count = 0;
  for (int i = 0; i < len; i ++){
    if (arr[i] != 0)
      count ++;
  }
  return get_total(arr, len) / count;
}
