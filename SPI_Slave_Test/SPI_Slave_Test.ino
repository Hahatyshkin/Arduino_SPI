#include "SPI.h"
// Определям размер буфера
#define BUFFER_SIZE 100

//Создаем буффер для данных
char buff[BUFFER_SIZE];
//Создаем переменную индекса буфера
// volatile - указание для препроцессора о том, что переменная может измениться при прерывании и с ней нельзя производить оптимизаций при компилировании.
volatile uint8_t index = 0;

//Создаем флаг готовности данных
volatile bool data_ready = false;

//создаем переменную для получения числа
long i;

//создаем индекс заголовка целого числа
volatile uint8_t int_index =0;

void setup() {
  // put your setup code here, to run once:
//Активируем последовательный порт для вывода информации на ПК
Serial.begin(9600);
//Устанавливаем вывод MISO в режим выхода
pinMode(MISO, OUTPUT);
//Устанавливаем режим ведомого в контрольном регистре SPI 
SPCR |= _BV(SPE);
//Подключаем прерывание SPI
SPI.attachInterrupt();
}

// Вызываем функцию обработки перываний о вектору SPI
// STC - Serial Transfer Comlete
ISR(SPI_STC_vect)
{
    // Получае байт из регистра данных SPI
    byte c = SPDR;

    //Добавляем байт в буфер
    if (index < sizeof(buff)) {
        buff[index++] = c;
        // Как пример 
        if (c == 0xAD){
          int_index = index;
        }
        if (c == 0xAF){
          data_ready = true;
        }
    }
}
void loop() {
  // put your main code here, to run repeatedly:
//Если установлен флаг готовых данных
if (data_ready == true);

//Обнуляем индекс
index = 0;
/*
//Создаем строку и записываем в нее полученный буфер
String message = String(buff);
// Форматируем строку убирая из нее все заголовки
message = message.substring(0, int_index - 1);
//Выводим отформатированную строку в последовательный порт 
Serial.println(message);
//Обнуляем переменную для хранения полученного целого числа
i=0;0x
*/
//Записываем целое число через указатель на элемент массива.
i = *((long *)(buff + int_index));
//обнуляем флаг готовности
data_ready = false;

Serial.print("long integer over SPI is : ");

Serial.println(i);
}
