# arduino-detect-adress-lcd

Arduino code to detect the address needed to print in a LCD I2C.

Este proyecto contiene un **escáner de bus I2C** para Arduino que recorre las direcciones `0x01` a `0x7E` y muestra por el **Monitor Serial** qué dispositivos responden (por ejemplo, un LCD I2C con backpack).

## Tabla de contenido

- [Descripción](#descripción)
- [Características](#características)
- [Requisitos](#requisitos)
- [Hardware recomendado](#hardware-recomendado)
- [Conexiones (cableado)](#conexiones-cableado)
- [Instalación y uso](#instalación-y-uso)
- [Salida esperada](#salida-esperada)
- [Configuración](#configuración)
- [Solución de problemas](#solución-de-problemas)
- [Seguridad y buenas prácticas](#seguridad-y-buenas-prácticas)
- [Estructura del repositorio](#estructura-del-repositorio)
- [Licencia](#licencia)
- [Mantenimiento / Soporte](#mantenimiento--soporte)

## Descripción

Cuando se trabaja con pantallas **LCD I2C** (p. ej. 16x2 o 20x4 con adaptador PCF8574), a menudo la dirección I2C puede variar (comúnmente `0x27` o `0x3F`, pero no siempre).  
Este sketch escanea el bus I2C y reporta por Serial todas las direcciones donde encuentra un dispositivo.

## Características

- Escaneo de direcciones I2C de `1` a `126`.
- Reporte por **Serial** de cada dispositivo detectado en formato hexadecimal.
- Mensajes de estado: inicio, “escaneo completo” y caso sin dispositivos.

## Requisitos

### Software
- **Arduino IDE** (1.8.x o 2.x) o plataforma compatible (p. ej. PlatformIO).
- Librería estándar:
  - `Wire.h` (incluida con Arduino)

### Conocimientos mínimos recomendados
- Cómo cargar un sketch a una placa Arduino.
- Cómo abrir el **Monitor Serial** y seleccionar el baud rate.

## Hardware recomendado

- Cualquier placa compatible con Arduino (ejemplos):
  - Arduino UNO / Nano / Mega
  - ESP8266 / ESP32 (también funciona, ajustando cableado y niveles si aplica)
- 1 dispositivo I2C para probar:
  - LCD I2C (con adaptador/backpack), o cualquier sensor/módulo I2C.

## Conexiones (cableado)

> Importante: I2C usa dos líneas: **SDA** y **SCL**, además de **VCC** y **GND**.

### Ejemplo: Arduino UNO / Nano
- **SDA → A4**
- **SCL → A5**
- **VCC → 5V** (o 3.3V dependiendo del módulo)
- **GND → GND**

### Arduino Mega 2560
- **SDA → 20**
- **SCL → 21**

### ESP32 / ESP8266
- Depende del modelo/board. Revisa el pinout de tu placa.
- Frecuentemente (ESP32): SDA=21, SCL=22 (puede variar).

## Instalación y uso

1. Clona el repositorio o descarga el ZIP:
   - Repo: `Orlandho/arduino-detect-adress-lcd`

2. Abre el archivo:
   - `codigo_detectar_direccion_LCD.ino`

3. Conecta tu dispositivo I2C (por ejemplo el LCD I2C) a la placa.

4. Conecta la placa por USB.

5. En Arduino IDE:
   - Selecciona **Tools → Board** (tu placa)
   - Selecciona **Tools → Port** (puerto correcto)

6. Carga el sketch (**Upload**).

7. Abre el **Monitor Serial**:
   - Baud rate: **9600**
   - Verás el resultado del escaneo.

## Salida esperada

Ejemplo de salida (puede variar):

```text
Escaneando dispositivos I2C...
¡Dispositivo I2C encontrado en la dirección 0x27 !
Escaneo completo
```

Si no hay nada conectado o hay un problema de cableado:

```text
Escaneando dispositivos I2C...
No se encontraron dispositivos I2C
```

## Configuración

En el código actual:

- Baud rate:
  - `Serial.begin(9600);`

- Rango de escaneo:
  - `for (address = 1; address < 127; address++)`

Si tu entorno requiere otro baud rate, puedes cambiarlo (y ajustar el Monitor Serial al mismo valor).

## Solución de problemas

- **No detecta ningún dispositivo**
  - Revisa **GND común** entre placa y módulo.
  - Revisa cableado SDA/SCL (pines correctos para tu placa).
  - Revisa alimentación (¿tu módulo es 5V o 3.3V?).
  - Prueba con otro cable o protoboard.

- **Detecta direcciones “raras” o inestables**
  - Puede haber falsos contactos o ruido.
  - Usa cables más cortos.
  - Asegura buenas conexiones.
  - Verifica si tu módulo requiere resistencias pull-up (muchos módulos ya las incluyen).

- **Se queda esperando al Serial**
  - El sketch contiene `while (!Serial);` que en algunas placas (p.ej. con USB nativo) puede esperar a abrir el Monitor Serial.
  - Si tu placa no lo necesita, puedes comentar o eliminar esa línea.

## Seguridad y buenas prácticas

Para uso empresarial / integración en producto:

- Valida niveles lógicos (3.3V vs 5V) para evitar dañar módulos.
- Evita hot-plug de I2C en producción si no está diseñado para ello.
- Documenta el pinout específico por modelo de placa en tu firmware final.
- Considera manejar timeouts y reporting más estructurado si se integrará a un proceso de QA/producción.

## Estructura del repositorio

- `codigo_detectar_direccion_LCD.ino` — Sketch principal (escáner I2C).
- `LICENSE` — Licencia MIT.

## Licencia

Este proyecto está bajo licencia **MIT**. Ver el archivo `LICENSE` para más detalles.

## Mantenimiento / Soporte

- Autor/maintainer: **Orlando Dorival**
- Recomendación: usar **Issues** del repositorio para reportar bugs, proponer mejoras o solicitar soporte interno.
