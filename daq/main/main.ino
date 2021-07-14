#define MUX_SEL_0 5
#define MUX_SEL_1 7
#define MUX_SEL_2 9

#define MUX_EN_0 10
#define MUX_EN_1 11

#define MUX_OUT A5

float muxVals[16] = {};
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

    muxVals[muxSel] = (float)analogRead(MUX_OUT) / 1024 * 13.9;
  }
  digitalWrite(13, led);
  led = !led;
  Serial.write(12);
  for (int i = 0; i < 16; i++){
    Serial.print((float)muxVals[i]);
    Serial.print("V\t");
  }
  Serial.print(led);
  Serial.print("\t");
  Serial.print("\n");
}