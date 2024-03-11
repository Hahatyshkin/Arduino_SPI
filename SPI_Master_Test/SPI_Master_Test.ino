#include "SPI.h"

//Создаем переменную байтового массива
//byte data[] {'H','e','l','l','o'};

//char* cstring = " World!";

long value1 = 0x5A5A; //0x - 16 sys / 0b - 2 sys // 0b00110000
long value2 = 0xA934;
void setup() {
  // put your setup code here, to run once:
//Инициализируем SPI
SPI.begin();
//Устанавливаем логическую "1" на выводе Slave Select (SS)
pinMode(SS, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(SS, LOW);
//Начинаем передачу данных передавая в функцию объект настроек шины.
//SPISettings( Скорость в Гц, Порядок передачи битов, режим шины)
SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

//Передаем массив data
/*for (int i = 0; i < sizeof(data); i++){
  SPI.transfer(char(data[i]));
}*/

//Передаем один байт
//SPI.transfer(',');

//Передаем строку в формате Си
/*for(char* p = cstring; char c = *p; p++) {
  SPI.transfer(c);
}*/

//Передаем один байт - заголовок начала целого числа.
//Как пример байт 0xAD обозначает заголовок целого числа long 
SPI.transfer(0xAD);


// Побайтово передаем целое число.
for (int j =0; j < sizeof(value1); j++) {
  byte b = value1 >> 8 * j;
  SPI.transfer(b);
}
//Передаем байт конца пакета
SPI.transfer(0xAF);
delay(100);
/*
//Передаем один байт - заголовок начала целого числа.
//Как пример байт 0xAD обозначает заголовок целого числа long 
SPI.transfer(0xAD);


// Побайтово передаем целое число.
for (int j =0; j < sizeof(value2); j++) {
  byte b = value2 >> 8 * j;
  SPI.transfer(b);
}
//Передаем байт конца пакета
SPI.transfer(0xAF);
*/
//Завершаем передачу данных
SPI.endTransaction();
digitalWrite(SS, HIGH);
delay(1000);
}
