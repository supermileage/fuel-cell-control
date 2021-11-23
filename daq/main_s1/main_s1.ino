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
  
  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {
  //delay(2000);
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
  Serial.write(12);
  qsort(muxVals, 16, sizeof (float), compar);
  volVals[0] = muxVals[0];
  Serial.print((float)volVals[0]);
  Serial.print("\t");
  for (int i = 1; i < 16; ++i){
    volVals[i] = muxVals[i] - muxVals[i-1];
    Serial.print((float)volVals[i]);
    //Serial1.print("V     ");
    Serial.print("\t"); 
  }

  // Debug LED - 
  digitalWrite(13, led);
  led = !led;
  
  // Getting derivatives
  Serial.print(led);
  minIndex = get_min(volVals, 16);
  minVol = volVals[minIndex];
  totalVol = get_total(volVals,  16);
  avgVol = get_avg(volVals, 16);
  qsort(rawVals, 16, sizeof(int), compar);
  
  rawCurrent = analogRead(HE_1);
  Serial.println("\t");

  Serial.print("m ");
  Serial.print(minVol);
  Serial.print(" c");
  Serial.println(minIndex);

  Serial.print("t ");
  Serial.println(totalVol);

  Serial.print("a ");
  Serial.println(avgVol);

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
    }
    else if (killMe == '0'){
      Serial.println("Stopping");
      start = false;
      digitalWrite(SMALLPUMP, LOW);
      digitalWrite(RELAY, HIGH);
      digitalWrite(BIGPUMP, LOW);
      bigPump = false;
    }
    
    delay(1000);
  } 
  

  if (start){
    if (!first){
      // control logic
      if (error) {

        Serial.print("Err ");
        Serial.print(errVol);
        Serial.print(" C");
        Serial.print(errCell);
        return;
      } 

      // Pump logic
      if (!bigPump && minVol < 0.7 ) {
        digitalWrite(BIGPUMP, HIGH);
        bigPump = true;
      } else if (bigPump, minVol > 0.75) {
        bigPump = false;
        digitalWrite(BIGPUMP, LOW);
      }
      
      if ( minVol < 0.5 ) {
        digitalWrite(RELAY, HIGH);
        digitalWrite(SMALLPUMP, LOW);
        digitalWrite(BIGPUMP, LOW);
        bigPump = false;
        Serial.print("Err");
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
      Serial.println("in");
    }
    
  } else {
      Serial.println("St");
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
