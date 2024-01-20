#include <Arduino.h>
#include <EncButton.h>
//кнопка для режимов 
EncButton<EB_TICK, 2> btn(INPUT_PULLUP);

//btn - режим
//BUTTON_PIN - пуск 
//DOOR_PIN - дверь 
//buzzerPin - пищалка 

int light = 10;
int light1 = 11;
int light2 = 12;
int light3 = 9;
int ENA= 4;
int IN1 = 5;
int IN2 = 6;


int DOOR_PIN = 7;

// Пин кнопки
#define BUTTON_PIN 3

int outSpeed = 6;    // PWM output

///////
const int buzzerPin = 8;   // пин, к которому подключена пищалка
int buttonState = 0;  // переменная для хранения состояния кнопки
///////

void setup() {
  Serial.begin(9600);

pinMode(DOOR_PIN, INPUT_PULLUP);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(ENA, OUTPUT);   
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);  
digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
///////
  pinMode(buzzerPin, OUTPUT);         // установка пина пищалки на выход  
///////
}
void loop() {

////
btn.tick();  // обработка нажатия кнопки для переключения режимов

//  BUTTON_PIN и состояния кнопки DOOR_PIN
  if (digitalRead(BUTTON_PIN)== LOW && digitalRead(DOOR_PIN) == HIGH) {
    tone(buzzerPin,300, 400);  // включить пищалку
  } else {
    noTone(buzzerPin);  // выключить пищалку
  }
/////// 

//переключение режимов 
static byte mode = 0;
btn.tick();
if (btn.isClick() && digitalRead(DOOR_PIN) == LOW) {
  if(++mode >=4) mode = 0;
}

switch (mode) {
  case 0: task1(); break;
  case 1: task2(); break;
  case 2: task3(); break;
  case 3: task4(); break;
  }
}
void task1(){ 
  if (digitalRead(DOOR_PIN) == LOW) {
  // код функции 
  digitalWrite(light,HIGH);
  digitalWrite(light1,LOW);
  digitalWrite(light2,LOW);
  digitalWrite(light3,LOW);
}
}

  void task2(){ 
    if (digitalRead(DOOR_PIN) == LOW) {
  // код функции
  digitalWrite(light,LOW);
  digitalWrite(light1,HIGH);
  digitalWrite(light2,LOW);
  digitalWrite(light3,LOW);
    // Ожидаем нажатие кнопки или другого события
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Включаем мотор на 10 секунд и выключаем
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 205);
    delay(5000);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);

        // Проигрываем мелодию
    tone(buzzerPin, 1500);
    delay(300);
    tone(buzzerPin, 1200);
    delay(300);
    tone(buzzerPin, 900);
    delay(300);
    tone(buzzerPin, 600);
    delay(800);
    noTone(buzzerPin); 
  }
}  
} 
  void task3(){
    if (digitalRead(DOOR_PIN) == LOW) {
  // код функции
  digitalWrite(light,LOW);
  digitalWrite(light1,LOW);
  digitalWrite(light2,HIGH);
  digitalWrite(light3,LOW);
}
}

  void task4(){
    if (digitalRead(DOOR_PIN) == LOW) {
  // код функции
  digitalWrite(light,LOW);
  digitalWrite(light1,LOW);
  digitalWrite(light2,LOW);
  digitalWrite(light3,HIGH);
} 
} 
