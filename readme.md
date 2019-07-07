# 🧪 Chlorine monitor

Push both buttons at once when booting to get it into bootloader mode.
If that's working the little red light will stay on.


## 📍Pins

```
o
o TX
o RX
o
o
o GND
```
## 🕵️‍♀️ Secrets
Don't forget to populate `secrets.cpp` for WIFI deedts see example.

```cpp
#define SSID        ""
#define PSK         ""
```

Chlorine range is 0 - 4 ppm for 4-20ma.
The resistor in here is about 51.6Ω. Full range of ADC is 1024 when it's getting 1 volt. This is 18.5ma so the ranged is mapped to that.

## 🔋 Circuit
```
https://www.falstad.com/circuit/circuitjs.html?cct=$+1+0.000005+10.20027730826997+64+5+43%0Ar+160+288+160+384+0+50%0Ac+288+288+288+384+0+1e-7+0.9995002498750972%0Aw+80+384+160+384+0%0Ad+368+384+368+288+2+default%0Aw+288+288+368+288+0%0AR+480+176+528+176+0+0+40+3.3+0+0+0.5%0Ag+432+384+528+384+0%0Aw+368+288+432+288+0%0A370+160+160+160+288+1+0%0Aw+368+176+480+176+0%0Aw+160+384+288+384+0%0Aw+288+384+368+384+0%0Aw+368+384+432+384+0%0Ap+432+288+496+288+1+0%0Ai+80+160+160+160+0+0.02%0Aw+80+160+80+384+0%0Ad+368+288+368+176+2+default%0Ar+432+288+432+384+0+100000%0Aw+288+288+160+288+0%0A
```
