// =====================================================
// SMART TRAFFIC LIGHT SYSTEM
// 2 Roads + 2 Ultrasonic Sensors + 6 LEDs
// =====================================================


// =====================================================
// ROAD 1 LED PINS
// =====================================================

int red1 = 8;       // Road 1 Red LED
int yellow1 = 7;    // Road 1 Yellow LED
int green1 = 6;     // Road 1 Green LED


// =====================================================
// ROAD 2 LED PINS
// =====================================================

int red2 = 3;       // Road 2 Red LED
int yellow2 = 4;    // Road 2 Yellow LED
int green2 = 5;     // Road 2 Green LED


// =====================================================
// ULTRASONIC SENSOR 1 PINS
// =====================================================

int trig1 = 10;     // Sensor 1 Trigger Pin
int echo1 = 9;      // Sensor 1 Echo Pin


// =====================================================
// ULTRASONIC SENSOR 2 PINS
// =====================================================

int trig2 = 12;     // Sensor 2 Trigger Pin
int echo2 = 11;     // Sensor 2 Echo Pin


// =====================================================
// SETUP FUNCTION
// =====================================================

void setup() {

  // LED pins ko OUTPUT banate hain
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);

  // Ultrasonic sensor pins set karte hain
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  // Serial Monitor start karte hain
  Serial.begin(9600);

  // Starting condition:
  // Dono roads par red light ON
  allLightsOff();

  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);

  delay(1000);
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Dono sensors se distance read karte hain
  long distance1 = getDistance(trig1, echo1);
  long distance2 = getDistance(trig2, echo2);

  // Serial Monitor par distance show karte hain
  Serial.print("Road 1 Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Road 2 Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.println("----------------------");


  // ===================================================
  // SENSOR ERROR CHECK
  // ===================================================

  // Agar sensor reading invalid hai,
  // to dono roads par red light ON rahegi
  if (distance1 == -1 || distance2 == -1) {

    allLightsOff();

    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);

    delay(1000);

    return;
  }


  // ===================================================
  // TRAFFIC DENSITY COMPARISON
  // ===================================================

  // Chhoti distance ka matlab:
  // Sensor ke paas zyada traffic hai

  if (distance1 < distance2) {

    // Road 1 par zyada traffic hai
    controlTraffic(1);

  } else if (distance2 < distance1) {

    // Road 2 par zyada traffic hai
    controlTraffic(2);

  } else {

    // Agar dono roads ki distance same hai,
    // to Road 1 ko priority denge
    controlTraffic(1);
  }

  delay(500);
}


// =====================================================
// DISTANCE MEASUREMENT FUNCTION
// =====================================================

long getDistance(int trigPin, int echoPin) {

  // Trigger pin ko LOW karte hain
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 10 microseconds ka trigger pulse bhejte hain
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo signal ka duration read karte hain
  long duration = pulseIn(echoPin, HIGH, 30000);

  // Agar signal receive nahi hua
  if (duration == 0) {
    return -1;
  }

  // Distance calculate karte hain
  // Speed of sound = approximately 0.034 cm per microsecond
  long distance = duration * 0.034 / 2;

  return distance;
}


// =====================================================
// TRAFFIC CONTROL FUNCTION
// =====================================================

void controlTraffic(int selectedRoad) {

  // ---------------------------------------------------
  // STEP 1: Dono roads ki green lights OFF
  // ---------------------------------------------------

  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);


  // ---------------------------------------------------
  // STEP 2: Dono roads ki yellow lights ON
  // Warning signal
  // ---------------------------------------------------

  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, HIGH);

  delay(1000);


  // ---------------------------------------------------
  // STEP 3: Yellow lights OFF
  // ---------------------------------------------------

  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);


  // ---------------------------------------------------
  // STEP 4: Selected road ko GREEN
  // Dusri road ko RED
  // ---------------------------------------------------

  if (selectedRoad == 1) {

    // Road 1 GREEN
    digitalWrite(green1, HIGH);

    // Road 1 RED OFF
    digitalWrite(red1, LOW);

    // Road 2 RED ON
    digitalWrite(red2, HIGH);

    // Road 2 GREEN OFF
    digitalWrite(green2, LOW);

    // Road 1 ko 5 seconds ka green signal
    delay(5000);

  } else {

    // Road 2 GREEN
    digitalWrite(green2, HIGH);

    // Road 2 RED OFF
    digitalWrite(red2, LOW);

    // Road 1 RED ON
    digitalWrite(red1, HIGH);

    // Road 1 GREEN OFF
    digitalWrite(green1, LOW);

    // Road 2 ko 5 seconds ka green signal
    delay(5000);
  }


  // ---------------------------------------------------
  // STEP 5: Green lights OFF
  // Dono roads par RED ON
  // ---------------------------------------------------

  allLightsOff();

  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);

  delay(1000);
}


// =====================================================
// ALL LIGHTS OFF FUNCTION
// =====================================================

void allLightsOff() {

  // Road 1 LEDs OFF
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(green1, LOW);

  // Road 2 LEDs OFF
  digitalWrite(red2, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}