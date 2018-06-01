//Programa : Projeto Monitoramento Ergonomico em Trator Agrícola
//Fernando Ferreira Lima dos Santos

#include "math.h" 
// Pino ligado ao CS do modulo
const int chipSelect = 4;
#include <SdFat.h>
SdFat sd;
SdFile myFile;
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <DHT.h>
  //Definicao dos pinos sensor Sparkfun
int pino_analogico = A0;
int valor_A0 = 0;
//  Definicao do pino do switch 
int key = 7; 
//  Definicao dos pinos das LEDs
int red = 6; 
int green = 5; 
int red2 = 2; 
int green2 = 8; 
int yellow = 9; 
//  Definicao do pino e tipo do sensor DHT
DHT dht(3, DHT22);
//  //Definicao dos pinos do modulo RTC
DS3231  rtc(SDA, SCL);
  //Definicao do endereco do modulo LCD
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

void setup()
{
pinMode(key, INPUT);    
pinMode(red, OUTPUT); 
pinMode(yellow, OUTPUT); 
pinMode(green, OUTPUT); 
pinMode(red2, OUTPUT); 
pinMode(green2, OUTPUT); 
pinMode(pino_analogico, INPUT);

Serial.begin(9600);
lcd.begin(16,2); 
dht.begin();
rtc.begin();
 if(!sd.begin(chipSelect,SPI_HALF_SPEED))sd.initErrorHalt();
  
}
void loop()
{      
float h = dht.readHumidity();
float t = dht.readTemperature();
int valor_A0 = analogRead(pino_analogico);
float dB = 10.878*log(valor_A0) + 28.071; 
int stateKey = digitalRead(key);
// Abre o arquivo DAT.TXT  
if (!myFile.open("DAT.txt", O_RDWR | O_CREAT | O_AT_END))
  {
    sd.errorHalt("Erro na abertura do arquivo DAT.TXT!");
  }  
  delay(1000);
  if (stateKey == 1) {      
digitalWrite(green, 250);
digitalWrite(red, 0);
  Serial.print("Data : "); 
  Serial.print(rtc.getDateStr()); 
  Serial.print("/ Tempo : "); 
  Serial.print(rtc.getTimeStr()); 
  Serial.print("/ Temperatura : ");
  Serial.print(t); 
  Serial.print(" Celsius  ");
  Serial.print("/ Umidade : ");
  Serial.print(h); 
  Serial.print(" %  ");
  Serial.print("/ Intensidade do som: ");
  Serial.print(dB);
  Serial.print(" db");  
//   Grava dados em DAT.TXT
myFile.print(rtc.getDateStr());
myFile.print(" ");
myFile.print(rtc.getTimeStr());
myFile.print(" ");
myFile.print(t);
myFile.print(" ");
myFile.print(h);
myFile.print(" "); 
myFile.println(dB);
myFile.close();
delay(1000); 
   }   
   else {     
  Serial.println("Processo de gravacao interrompido. Retire o Cartao!");
  myFile.close();
  digitalWrite(green, 0);
  digitalWrite(red, 250);
  delay(1000); 
}
 if (t<=20 || t>=23) {   
    digitalWrite(yellow, HIGH);    
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
 }
 else {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
digitalWrite(yellow,LOW);  
 }
  if (h<=40){
    digitalWrite(green2, HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
 }
  else{
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
digitalWrite(green2,LOW);    
    }
    if (dB>85){
    digitalWrite(red2, HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
   
}  else { 
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("H:");
   lcd.setCursor(2,0);
   lcd.print(h,1);
   lcd.setCursor(0,1);
   lcd.print("T:");
   lcd.setCursor(2,1);
   lcd.print(t,1);
   lcd.setCursor(8,1);
   lcd.print("dB:");
   lcd.setCursor(11,1);
   lcd.print(dB,1);
digitalWrite(red2,LOW);
 }   
 delay(1500);
   }  

