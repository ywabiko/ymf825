# ESP32 YMF825 サンプル (ESP32 YMF825 Sample)

[YMF825ボード](https://yamaha-webmusic.github.io/ymf825board/intro/)がESP32で動くように[YAMAHA公式サンプルコード](https://github.com/yamaha-webmusic/ymf825board)を改修したものです。

環境：
  - ESP32 ([WEMOS Lolin32](https://wiki.wemos.cc/products:lolin32:lolin32)で動作確認済み)
  - arduino-esp32 (Arudino IDE)
  - YMF825ボードは3.3V/5V対応の[改造](http://uda.la/fm/)が必要です。

<a href="https://raw.github.com/ywabiko/esp32/master/images/ESP32_YMF825_VSPI.jpg">
<img src="https://raw.github.com/ywabiko/esp32/master/images/ESP32_YMF825_VSPI.jpg"
 alt="ESP32_YMF825_VSPI" title="ESP32_YMF825_VSPI" width="300" />
</a>
<a href="https://raw.github.com/ywabiko/esp32/master/images/ESP32_YMF825_HSPI.jpg">
<img src="https://raw.github.com/ywabiko/esp32/master/images/ESP32_YMF825_HSPI.jpg"
 alt="ESP32_YMF825_HSPI" title="ESP32_YMF825_HSPI" width="300" />
</a>


接続方法： ハードウェアSPI である VSPI または HSPI を利用します。ただしハードウェアCSは使用しません。（使用すると動作しません）

    VSPIの場合

      YMF825 - ESP32
      --------------
      RST_N  - GPIO 32   
      SS     - GPIO 5
      MOSI   - GPIO 23
      MISO   - GPIO 19
      SCK    - GPIO 18
      5V     - 5V
      3.3V   - 3.3V
      GND    - GND

    HSPIの場合

      YMF825 - ESP32
      --------------
      RST_N  - GPIO 32   
      SS     - GPIO 15
      MOSI   - GPIO 13
      MISO   - GPIO 12
      SCK    - GPIO 14
      5V     - 5V
      3.3V   - 3.3V
      GND    - GND

ライセンス：MIT


[YMF825 board](https://yamaha-webmusic.github.io/ymf825board/intro/) sample code for ESP32 platform.
This code is derived from 
[YAMAHA official sample code](https://github.com/yamaha-webmusic/ymf825board)
so that it works on ESP32 platform.

System:
  - ESP32 (confirmed with [WEMOS Lolin32](https://wiki.wemos.cc/products:lolin32:lolin32))
  - arduino-esp32 (Arudino IDE)
  - YMF825 board requires [a hack](http://uda.la/fm/) to enable dual voltage support (3.3V/5V).

Wiring: This code uses VSPI or HSPI here (i.e. hardware SPI). Hardware CS is disabled, though, as it does not work well with YMF825 at this point.

    VSPI case

      YMF825 - ESP32
      --------------
      RST_N  - GPIO 32   
      SS     - GPIO 5
      MOSI   - GPIO 23
      MISO   - GPIO 19
      SCK    - GPIO 18
      5V     - 5V
      3.3V   - 3.3V
      GND    - GND

    HSPI case

      YMF825 - ESP32
      --------------
      RST_N  - GPIO 32   
      SS     - GPIO 15
      MOSI   - GPIO 13
      MISO   - GPIO 12
      SCK    - GPIO 14
      5V     - 5V
      3.3V   - 3.3V
      GND    - GND

License: MIT
