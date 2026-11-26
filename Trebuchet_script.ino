#include <Servo.h>

Servo servo360; // Сервопривод постоянного вращения (пин 9)
Servo servo180; // Сервопривод ворот (пин 10)

const int pinServo360 = 9;
const int pinServo180 = 10;
const int pinButton = 2;

// Углы для ворот
const int GATE_OPEN = 30;
const int GATE_CLOSE = 145;

// Настройки для серво на 360 градусов
const int STOP_360 = 90;       // Значение остановки (обычно 90, иногда 88-92)
const int SPEED_360 = 0;     // Скорость вращения (95..180 в одну сторону, 0..85 в другую)
const int TIME_5_TURNS = 36000; // Время в мс, ВОТ ЭТО НУЖНО ОТКАЛИБРОВАТЬ !!!

void setup() {
  // Настраиваем кнопку со встроенным подтягивающим резистором
  pinMode(pinButton, INPUT_PULLUP);

  // Подключаем сервоприводы
  servo360.attach(pinServo360);
  servo180.attach(pinServo180);

  // При инициализации серво на 360 молчит, а ворота открываются
  servo360.write(STOP_360);
  servo180.write(GATE_OPEN);
  delay(1000); // Пауза для завершения поворота ворот
}

void loop() {

  // Ждем нажатия кнопки (при INPUT_PULLUP нажатие дает LOW)
  if (digitalRead(pinButton) == LOW) {
    delay(50); // Защита от дребезга контактов
    if (digitalRead(pinButton) == LOW) {
      
      // 1. Быстро закрываем ворота (поворот в положение 90)
      servo180.write(GATE_CLOSE);
      delay(600); // Ждем, пока ворота физически закроются

      // 2. Серво на 360 делает 5 поворотов
      servo360.write(SPEED_360);
      delay(TIME_5_TURNS);
      servo360.write(STOP_360);
      delay(500);

      // 3. Быстро открываем ворота обратно (поворот в положение 180)
      servo180.write(GATE_OPEN);
      delay(600); // Ждем, пока ворота физически откроются

      // Ждем отпускания кнопки, чтобы цикл не повторился случайно
      while (digitalRead(pinButton) == LOW) {
          delay(10);
      }
    }
  }
  
}
