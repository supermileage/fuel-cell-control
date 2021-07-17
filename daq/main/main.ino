#define MUX_SEL_0 5
#define MUX_SEL_1 7
#define MUX_SEL_2 9

#define MUX_EN_0 10
#define MUX_EN_1 11

#define MUX_OUT A5

float muxVals[16] = {};
float volVals[16] = {};
int rawVals[16] = {};
bool led = LOW;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(MUX_SEL_0, OUTPUT);
  pinMode(MUX_SEL_1, OUTPUT);
  pinMode(MUX_SEL_2, OUTPUT);
  pinMode(MUX_EN_0, OUTPUT);
  pinMode(MUX_EN_1, OUTPUT);
  pinMode(13, OUTPUT);

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

    // Serial.print(muxSel);
    // Serial.print(" ");
    // Serial.print(muxSel & 1);
    // Serial.print((muxSel & 2) >> 1);
    // Serial.print((muxSel & 4) >> 2);
    // Serial.print((muxSel & 8) >> 3);
    // Serial.println(((~muxSel) & 8) >> 3);

    muxVals[muxSel] = (float)analogRead(MUX_OUT) / 1023 * 16.921;
    rawVals[muxSel] = analogRead(MUX_OUT);
  }
  qsort(muxVals, 16, sizeof (float), compar);
  volVals[0] = muxVals[0];
  for (int i = 1; i < 16; ++i){
    volVals[i] = muxVals[i] - muxVals[i-1];

    
  }
  
  digitalWrite(13, led);
  led = !led;
  Serial.write(12);
  
  for (int i = 0; i < 16; i++){
    Serial.print((float)volVals[i]);
    Serial.print("V\t");
  }
  Serial.print(led);
  Serial.print("\t");
  Serial.print("\n");

  Serial.print("min: ");
  Serial.print(get_min(volVals,16));
  Serial.print("\n");

  Serial.print("total: ");
  Serial.print(get_total(volVals, 16));
  Serial.print("\n");

  Serial.print("average: ");
  Serial.print(get_avg(volVals, 16));
  Serial.print("\n");

  Serial.print("raw max: ");
  qsort(rawVals, 16, sizeof(int), compar); 
  Serial.print(rawVals[15]);
  Serial.print("\n");
  
}

int compar (const void* p1, const void* p2){
  if(*(float*)p1 < *(float*)p2) return -1;
  if(*(float*)p1 == *(float*)p2) return 0;
  if(*(float*)p1 > *(float*)p2) return 1;
}

float get_min (float arr[], int len){
  float ret = 420;
  for (int i = 1; i < len; ++i){
    if (arr[i] != 0 && arr[i] < ret) ret = arr[i];
  }
  return ret;
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
