# Waveshare RP2350-LCD-0.96 LVGL Demo (Compatible with LVGL v9)

## Overview

Waveshare社が出している、0.96インチのLCD付きRaspberry Pi Pico 2 互換ボード[RP2350-LCD-0.96](https://www.waveshare.com/rp2350-lcd-0.96.htm)上で、**LVGL v9**を動かすデモです。

LVGLのデモは[公式Wiki](https://www.waveshare.com/wiki/RP2350-LCD-0.96)にも存在しますが、これはLVGL v8系列向けのコードでそのままではLVGL v9では動作しないので、LVGLドライバを修正しました。

## How to use

本プロジェクトをVS CodeのRaspberry Pi Pico拡張機能でPico 2向けプロジェクトとしてImportします。

次に、**Configure CMake**を実行することでビルドディレクトリの作成とLVGLライブラリのダウンロードが行われます。ダウンロードするLVGLライブラリのバージョンは最上位のCMakeLists内で指定できます。

最後に、**Complie Project**を押すことでuf2ファイルが作成されます。

あるいは、単にデモを行うだけであれば```build/RP2_LCD0in96_Demo.uf2```を書き込んでください。

## Demonstration

デモコードである```RP2_LCD0in96_Demo.c```では、RP2350チップ内蔵の温度センサの値を取得し、それをLVGLでメモリ付きバーとラベルで表示します。ただし、チップ内蔵温度センサは外気温とは**大きく異なる値を示す**ので、気温計としては使い物にはなりません（いちおう```temp_comp_factor```で補正をかけてはいる）。

## License

本コードには、Waveshare社が公開しているサンプルコードが含まれています（externalフォルダ内）。これらのうちLCDフォルダ内のものは**ライセンスが明記されていない**ため、利用に際しては各自の判断でお願いします。
