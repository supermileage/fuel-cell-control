#define MUX_SEL_0 5
#define MUX_SEL_1 7
#define MUX_SEL_2 9

#define MUX_EN_0 10
#define MUX_EN_1 11

#define SMALLPUMP 3
#define BIGPUMP 12 // WHAT VALUE?
#define PAS 255

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

  pinMode(SMALLPUMP, OUTPUT);
  pinMode(BIGPUMP, OUTPUT);
  pinMode(RELAY, OUTPUT);

  analogWrite(SMALLPUMP, PAS);
  digitalWrite(RELAY, LOW);
  
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
  Serial.write(12);
  qsort(muxVals, 16, sizeof (float), compar);
  volVals[0] = muxVals[0];
  Serial.print((float)volVals[0]);
  Serial.print("V\t");
  for (int i = 1; i < 16; ++i){
    volVals[i] = muxVals[i] - muxVals[i-1];
    Serial.print((float)volVals[i]);
    Serial.print("V\t");
    
  }

  //debug LED
  digitalWrite(13, led);
  led = !led;
  
  Serial.print(led);
  minIndex = get_min(volVals, 16);
  minVol = volVals[minIndex];
  totalVol = get_total(volVals,  16);
  avgVol = get_avg(volVals, 16);
  qsort(rawVals, 16, sizeof(int), compar);
  
  Serial.print("\t");
  Serial.print("\n");

  Serial.print("min: ");
  Serial.print(minVol);
  Serial.print("\n");

  Serial.print("total: ");
  Serial.print(totalVol);
  Serial.print("\n");

  Serial.print("average: ");
  Serial.print(avgVol);
  Serial.print("\n");

  Serial.print("raw max: ");
  Serial.print(rawVals[15]);
  Serial.print("\n");

  if (Serial.available()){
    Serial.print("serial received");
    unsigned char killMe = Serial.read();
    
    if (killMe == 49){
      Serial.println("Start is read");
      start = true;
      error = false;
      first = true;
      analogWrite(SMALLPUMP, PAS); // 30%
      digitalWrite(RELAY, LOW); 
    }
    else if (killMe == 48){
      Serial.println("Stop is read");
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
        Serial.print("-ERROR- IN ERROR STATE Voltage: ");
        Serial.print(errVol);
        Serial.print(" Cell: ");
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
        Serial.print("-ERROR- Minimum voltage is lower than 0.5V");
        errVol = minVol;
        errCell = minIndex;
        error = true;
      }
    } else if (totalVol > 12) {
      first = false;
      delay(5000);
    } else {
      //digitalWrite(SMALLPUMP, HIGH);
      analogWrite(SMALLPUMP, PAS); // 30%
      digitalWrite(RELAY, LOW);
      Serial.println("In init");
    }
    
  } else {
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
  for (i = 1; i < len; ++i){
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
