// Arduino Mega 拡張基板
// https://github.com/ohguma/mega_board
//
// スイッチテスト
// 2023-04-08 ohguma
//
// ■マイコン情報
// arduino.cc
// Mega 2560 Rev3
// https://docs.arduino.cc/hardware/mega-2560
// Due
// https://docs.arduino.cc/hardware/due
//
// ■ピン設定
// タクトスイッチ
// ・SW1,SW2,SW3：D51,D52,D53かから各SWを経由してGNDに接続。
// ・INPUT_PULLUPモードで使用する。
const int PIN_SW1 = 51;
// LED
// ・LED1,LED2,LED3：D45,D47,D49から接続。LEDから電流制限抵抗を経由してGNDに接続。
const int PIN_LED1 = 45;

void setup() {
  Serial.begin(9600);
  // LED1 出力設定
  pinMode(PIN_LED1, OUTPUT);
  // スイッチ1 プルアップ入力設定
  pinMode(PIN_SW1, INPUT_PULLUP);
}

void loop() {
  // SW1が押されるとINPUT_PULLUPモードのdigitalRead()はLOWになる。
  if (digitalRead(PIN_SW1) == LOW) {
    // SW1を押している時、LED1：点灯
    digitalWrite(PIN_LED1, HIGH);
    Serial.println("SW1:ON");
  } else {
    // SW1が離された時、LED1：消灯
    digitalWrite(PIN_LED1, LOW);
    Serial.println("SW1:OFF");
  }
  // 少し待つ。delay()で指定する単位はミリ秒（1000分の1秒）
  delay(100);
}

//  ■課題
//  (1) シリアルモニタを見ながら、スケッチを実行する。
//  (2) SW1を押したらLED消灯、離したらLED点灯に変更する。
//  (3) SW1を押したらLED点灯に戻して、SW2・LED2、SW3・LED3も同様に動作刺させる。
//  (4) シリアルモニタで１行内にSW1、SW2、SW3の状態を表示する。
//