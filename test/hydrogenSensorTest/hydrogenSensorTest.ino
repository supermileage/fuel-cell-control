/*
Document purpose: to test the hydrogen sensor MQ-8 and detemine the threshold value
Datasheet for H2 sensor can be found at this link:
https://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Biometric/MQ-8.pdf
*/

#define hydrogenSensor A0
float hydrogenThreshold = 50; // todo find a threshold value for hydrogen
float sensorInput;

void setup() {
  // put your setup code here, to run once:
  pinMode(hydrogenSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorInput = analogRead(hydrogenSensor);
  Serial.println(sensorInput);
  // put your main code here, to run repeatedly:
  if (sensorInput > hydrogenThreshold){
    Serial.println("Fault");
  }
  delay(500);

}
