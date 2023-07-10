//----------------------------
// LESSON1：LED、millis
//
// 2023-07-10 ohguma 初版
//----------------------------
// Arduino Mega 拡張基板
// https://github.com/ohguma/mega_board
//
// ■ピン設定
// LED
// ・LED1,LED2,LED3：D45,D47,D49から接続される。
// ・OUTPUTモードで使用する。
// ・各LEDは電流制限抵抗を経由してGNDに接続している。
const int PIN_LED1 = 45;
//

void setup() {
  // LED1 出力設定
  pinMode(PIN_LED1, OUTPUT);
}

void loop() {
  // 変数tm1は1秒(1000ミリ秒)ごとに0,1,2,3,…となる。
  long tm1 = millis() / 1000;
  // 1000ミリ秒ごとにLEDをON/OFFする。
  if (tm1 % 2 == 1) {
    // 変数tm1を2で割った余りが1の時、LED：ON
    digitalWrite(PIN_LED1, HIGH);
  } else {
    // 変数tm1を2で割った余りが0の時、LED：OFF
    digitalWrite(PIN_LED1, LOW);
  }
  // 少し待つ
  delay(10);
}

//  ■課題
//  (1) 「Arduinoを始めよう」の「Arduino 公式リファレンス」で以下を調べる。
//    ・const
//    ・pinMode()
//    ・digitalWrite()
//    ・millis()
//    ・long
//    ・%（パーセント記号）
//    ・delay()
//
//  (2) LED1の点滅間隔を更新する。最初に0.5秒ごとにON/OFFさせる。
//
//  (3) だんだん間隔を短くしてみる。点滅して見えるの最小の間隔を調べる。
//
//  (4) 複数のLEDを同時に同様に異なるタイミングで点滅させる。
//
//  ※スケッチ例の「01.Basics」→「Blink」のように点滅間隔をdelay()で設
//    定するのは禁止する。
//