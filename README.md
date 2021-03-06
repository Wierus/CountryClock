## Часы с датчиком температуры DS18B20 и датчиком влажности DHT22 на одном индикаторе

**Контроллер:** PIC16F88 (PIC16F88-I/P, DIP18)

**Частота:** 4 МГц (кварцевый резонатор)

**Режим:** HS (High Speed Crystal/Resonator)

**Компилятор:** XC8 v1.33

**IDE:** MPLAB X IDE v3.20

**Индикаторы:** GNS-15011BUE-21 (1 знак, красный, общий анод) (5 шт.)

**Сдвиговый регистр:** 74HC164 (74HC164D, SO14)

**Часы реального времени:** реализованы на контроллере

### Описание работы устройства

Устройство может работать в одном из 5 режимов:

1. Отображение всех значений по порядку: времени, температуры с датчика DS18B20, температуры с датчика DHT22, влажности с датчика DHT22. Каждое значение отображается по 3 секунды.
2. Отображение времени.
3. Отображение температуры с датчика DS18B20.
4. Отображение температуры с датчика DHT22.
5. Отображение влажности с датчика DHT22.

Режим работы изменяется нажатием (на 1 секунду) кнопки "Режим" ("Mode"). При включении устройство работает в режиме отображения всех значений по порядку (режим 1).

#### Режим отображения времени (режим 2)

В этом режиме активны следующие функции кнопок:
* Кнопка "Часы" ("Hours") увеличивает часы на 1 (2 раза в секунду).
* Кнопка "Минуты" ("Minutes") увеличивает часы на 1 (2 раза в секунду).
* Одновременное нажатие кнопок "Часы" и "Минуты" обнуляет минуты и секунды. Если минут больше или равно 30, то часы дополнительно увеличиваются на 1.

В этом режиме секундная черта мигает с частотой 1 Гц (0.5 секунды горит, 0.5 секунды не горит).

Кнопки активны только в этом режиме, в остальных режимах кнопки не активны.

#### Режимы отображения температуры с датчиков DS18B20 и DHT22 (режимы 2 и 3)

Обновление температуры с обоих датчиков выполняется каждые 10 секунд.

#### Режим отображения влажности с датчика DHT22 (режим 4)

Обновление влажности с датчика DHT22 выполняется каждые 10 секунд (одновременно с обновлением температуры с этого датчика).
