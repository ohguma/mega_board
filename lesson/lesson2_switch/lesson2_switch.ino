//----------------------------
// LESSON2：スイッチ
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
// タクトスイッチ
// ・SW1,SW2,SW3：D51,D52,D53かから各SWを経由してGNDに接続。
// ・INPUT_PULLUPモードで使用する。
const int PIN_SW1 = 51;
//

void setup() {
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
  } else {
    // SW1が離された時、LED1：消灯
    digitalWrite(PIN_LED1, LOW);
  }
  // 少し待つ
  delay(10);
}

//  ■課題
//  (1) 「Arduinoを始めよう」の「Arduino 公式リファレンス」で以下を調べる。
//    ・INPUT_PULLUP
//    ・digitalRead()
//
//  (2) SW1を押したらLEDが消灯、離したらLEDが点灯するようスケッチを変更する。
//      変更内容をアップロードして動作確認できたら元に戻す。（押して点灯）
//      先とは違う変更で、押したら消灯・離して点灯させる。
//      [ヒント] 30行だけの変更で2パターン、30行以外の変更で最低1パターンの
//               変更ができる。
//
//  (3) SW1だけでなく、SW2とLED2、SW3とLED3も同様に動作させる。
//      [ヒント] setupより前の変数定義を３セット分用意する。
//