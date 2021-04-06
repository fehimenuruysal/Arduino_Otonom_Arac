#define ECHO 4
#define TRIG 5
#define LDR_LEFT A0
#define LDR_RIGHT A1
#define LED_RED 3
#define LED_GREEN 2
#define BUZZER 6

#define LEFT_ENGINE_FORWARD 9
#define LEFT_ENGINE_BACK 10
#define RIGHT_ENGINE_FORWARD 11
#define RIGHT_ENGINE_BACK 12

int FLAG = 0;

void setup() {
 Serial.begin(9600);
 pinMode(ECHO, INPUT);
 pinMode(TRIG, OUTPUT);

 pinMode(LDR_LEFT, INPUT);
 pinMode(LDR_RIGHT, INPUT);
 pinMode(LED_RED, OUTPUT);
 //pinMode(LED_YELLOW, OUTPUT);
 pinMode(LED_GREEN, OUTPUT);
 pinMode(BUZZER, OUTPUT);
 pinMode(LEFT_ENGINE_FORWARD, OUTPUT);
 pinMode(LEFT_ENGINE_BACK, OUTPUT);
 pinMode(RIGHT_ENGINE_FORWARD, OUTPUT);
 pinMode(RIGHT_ENGINE_BACK, OUTPUT);

 Serial.println("Started!");
 digitalWrite(LEFT_ENGINE_FORWARD, LOW);
 digitalWrite(LEFT_ENGINE_BACK, LOW);
 digitalWrite(RIGHT_ENGINE_FORWARD, LOW);
 digitalWrite(RIGHT_ENGINE_BACK, LOW);

}

void loop() {
 _move();
 int dist = measure_distance();
 flash_leds(dist);
 if (dist < 150){
 _break();
 // Dönme işlemi
 move_back(900);
 turn_right(500);

 return;
 }else {
 FLAG = 1;
 }
 check_ldrs();
}

int measure_distance(){
 int duration, distance;

 digitalWrite(TRIG, LOW);
 delayMicroseconds(10);
 digitalWrite(TRIG, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG, LOW);
 duration = pulseIn(ECHO, HIGH);
 distance = (duration/2) / 2.91;
 return distance;
}

void flash_leds(int measure){

 digitalWrite(LED_RED, LOW);
 digitalWrite(LED_GREEN, LOW);
 //digitalWrite(LED_YELLOW, LOW);
 digitalWrite(BUZZER, LOW);

 
 if (measure >= 300){
 digitalWrite(LED_GREEN, HIGH);
 }
 else if (measure < 300 && measure >= 150){
 //digitalWrite(LED_YELLOW, HIGH);
 }
 else {
 digitalWrite(LED_RED, HIGH);
 digitalWrite(BUZZER, HIGH);
 }
}

void check_ldrs(){
 int left_brightness;
 int right_brightness;
 left_brightness = analogRead(LDR_LEFT);
 right_brightness = analogRead(LDR_RIGHT);
 Serial.println(left_brightness);
 Serial.println(right_brightness);
 if (right_brightness >= 890){
 _break();
 turn_right(400);
 }else if (left_brightness >= 890 ){
 _break();
 turn_left(400);
 }else{
 //stay();
 }
}

// Yön Fonksiyonları
void turn_left(int duration){
 digitalWrite(LEFT_ENGINE_FORWARD, LOW);
 digitalWrite(LEFT_ENGINE_BACK, HIGH);
 digitalWrite(RIGHT_ENGINE_FORWARD, HIGH);
 digitalWrite(RIGHT_ENGINE_BACK, LOW);

 Serial.println("Sola Dönülüyor");
 delay(duration);
}

void turn_right(int duration){
 digitalWrite(LEFT_ENGINE_FORWARD, HIGH);
 digitalWrite(LEFT_ENGINE_BACK, LOW);
 digitalWrite(RIGHT_ENGINE_FORWARD, LOW);
 digitalWrite(RIGHT_ENGINE_BACK, HIGH);

 Serial.println("Sağa Dönülüyor");
 delay(duration);
}

void stay(){
 digitalWrite(LEFT_ENGINE_FORWARD, LOW);
 digitalWrite(LEFT_ENGINE_BACK, LOW);
 digitalWrite(RIGHT_ENGINE_FORWARD, LOW);
 digitalWrite(RIGHT_ENGINE_BACK, LOW);
 Serial.println("Bekleniyor. Sistem Boşta");
}

void _break(){
 FLAG = 0;
 digitalWrite(LEFT_ENGINE_FORWARD, LOW);
 digitalWrite(LEFT_ENGINE_BACK, LOW);
 digitalWrite(RIGHT_ENGINE_FORWARD, LOW);
 digitalWrite(RIGHT_ENGINE_BACK, LOW);

 Serial.println("Acil Fren");
}

void _move(){
 if (FLAG == 0){
 return;
 }
 digitalWrite(LEFT_ENGINE_FORWARD, HIGH);
 digitalWrite(LEFT_ENGINE_BACK, LOW);
 digitalWrite(RIGHT_ENGINE_FORWARD, HIGH);
 digitalWrite(RIGHT_ENGINE_BACK, LOW);

 Serial.println("İlerliyor");
}

void move_back(int duration){
 digitalWrite(LEFT_ENGINE_FORWARD, LOW);
 digitalWrite(LEFT_ENGINE_BACK, HIGH);
 digitalWrite(RIGHT_ENGINE_FORWARD, LOW);
 digitalWrite(RIGHT_ENGINE_BACK, HIGH);
 Serial.println("Geri gidiliyor");
 delay(duration);
}