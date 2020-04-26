# 🧪 Chlorine monitor



## 📍Pins

```
o
o TX
o RX
o
o
o GND
```

Connect up the GND to and VCC on the USB serial adapter.
Remember RX -> TX and TX -> RX.
Ensure the serial adapter is set to 3.3v.

## 🕵️‍♀️ Secrets
Don't forget to populate `secrets.cpp` for WIFI deedts see example.

```cpp
#define SSID        ""
#define PSK         ""
```

Chlorine range is 0 - 4 ppm for 4-20ma.
The resistor in here is about 51.6Ω. Full range of ADC is 1024 when it's getting 1 volt. This is 18.5ma so the ranged is mapped to that.

## 👨‍🌾 Uploading firmware
1. Connect up the wires, TX -> RX and RX -> TX.
2. Make sure the voltage on the serial adapter is 3.3v or it will fuck shit up.
3. Before plugging it in, push both buttons on the board at once when booting to get it into bootloader mode.
  If that's working the little red light will stay on.
5. Upload the firmware with the PIO command

```sh
pio run --target upload
```

You can see what it's doing with the serial monitor.

```sh
pio device monitor
```

## 🥣 Serial port
It might not be able to find the serial port, to see what ports are available run this:

```sh
pio device list
```
Which should show something that sounds like "usbserial"
```
/dev/cu.Bluetooth-Incoming-Port
-------------------------------
Hardware ID: n/a
Description: n/a

/dev/cu.usbserial
-------------------------------
Hardware ID: n/a
Description: n/a
```

## 🔋 Circuit
[View Circuit](https://www.falstad.com/circuit/circuitjs.html?cct=$+1+0.000005+10.20027730826997+64+5+43%0Ar+160+288+160+384+0+50%0Ac+288+288+288+384+0+1e-7+0.9995002498750972%0Aw+80+384+160+384+0%0Ad+368+384+368+288+2+default%0Aw+288+288+368+288+0%0AR+480+176+528+176+0+0+40+3.3+0+0+0.5%0Ag+432+384+528+384+0%0Aw+368+288+432+288+0%0A370+160+160+160+288+1+0%0Aw+368+176+480+176+0%0Aw+160+384+288+384+0%0Aw+288+384+368+384+0%0Aw+368+384+432+384+0%0Ap+432+288+496+288+1+0%0Ai+80+160+160+160+0+0.02%0Aw+80+160+80+384+0%0Ad+368+288+368+176+2+default%0Ar+432+288+432+384+0+100000%0Aw+288+288+160+288+0%0A)
