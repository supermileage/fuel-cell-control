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
  
  //Serial11.begin(9600);
  Serial1.begin(9600);

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
  //Serial11.write(12);
  Serial1.write(12);
  qsort(muxVals, 16, sizeof (float), compar);
  volVals[0] = muxVals[0];
  //Serial11.print("0: ");
  Serial1.print("0: ");
  //Serial11.print((float)volVals[0]);
  Serial1.print((float)volVals[0]);
  //Serial11.print("V\t");
  Serial1.print("V\t");
  for (int i = 1; i < 16; ++i){
    volVals[i] = muxVals[i] - muxVals[i-1];
    //Serial11.print(i);
    Serial1.print(i);
    //Serial11.print(": ");
    Serial1.print(": ");
    //Serial11.print((float)volVals[i]);
    Serial1.print((float)volVals[i]);
    //Serial11.print("V     ");
    Serial1.print("V     "); 
  }

  // Debug LED - 
  digitalWrite(13, led);
  led = !led;
  
  // Getting derivatives
  //Serial11.print(led);
  Serial1.print(led);
  minIndex = get_min(volVals, 16);
  minVol = volVals[minIndex];
  totalVol = get_total(volVals,  16);
  avgVol = get_avg(volVals, 16);
  qsort(rawVals, 16, sizeof(int), compar);
  
  rawCurrent = analogRead(HE_1);
  //finalCurrent = rawCurrent / 1023 * 3.3;
  
  //Serial11.println("\t");

  //Serial11.print("min: ");
  //Serial11.print(minVol);
  //Serial11.print("\ton cell ");
  //Serial11.println(minIndex);

  //Serial11.print("total: ");
  //Serial11.println(totalVol);

  //Serial11.print("average: ");
  //Serial11.println(avgVol);

  //Serial11.print("raw max: ");
  //Serial11.println(rawVals[15]);
  
  //Serial11.print("raw current: ");
  //Serial11.println(rawCurrent);

  Serial1.println("\t");

  Serial1.print("min: ");
  Serial1.print(minVol);
  Serial1.print("\ton cell ");
  Serial1.println(minIndex);

  Serial1.print("total: ");
  Serial1.println(totalVol);

  Serial1.print("average: ");
  Serial1.println(avgVol);

  Serial1.print("raw max: ");
  Serial1.println(rawVals[15]);
  
  Serial1.print("raw current: ");
  Serial1.println(rawCurrent);
  
//
//  if (Serial11.available()){
//    Serial11.print("Serial11 received - ");
//    unsigned char killMe = Serial11.read();
//    
//    if (killMe == '1'){
//      Serial11.println("Starting");
//      start = true;
//      error = false;
//      first = true;
//      analogWrite(SMALLPUMP, PAS); // 30%
//      digitalWrite(RELAY, LOW); 
//    }.println("Stopped");
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
