// Arduino Mega 拡張基板
// https://github.com/ohguma/mega_board
//
// モーターテスト ON/OFF
// 2023-04-08 ohguma
//
// ■マイコン情報
// arduino.cc
// Mega 2560 Rev3
// https://docs.arduino.cc/hardware/mega-2560
// Due
// https://docs.arduino.cc/hardware/due
//
// ■ピン設定設定
// タクトスイッチ
// ・SW1,SW2,SW3：D51,D52,D53かから各SWを経由してGNDに接続。
// ・INPUT_PULLUPモードで使用する。
const int PIN_SW1 = 51;
//
// LED
// ・LED1,LED2,LED3：D45,D47,D49から接続。LEDから電流制限抵抗を経由してGNDに接続。
const int PIN_LED1 = 45;
//
// モータードライバ TOSHIBA TB67H450FNG
// https://toshiba.semicon-storage.com/info/TB67H450FNG_datasheet_ja_20201126.pdf?did=65345&prodName=TB67H450FNG
// ・no  IN1/IN2
//   --- -------
// ・MT1 D2/D3
// ・MT2 D4/D5
// ・MT3 D6/D7
// ・MT4 D8/D9
//
// IN1  IN2  動作
// ---- ---- -----------------
// 0    0    停止
// 数値 LOW  時計回り
// LOW  数値 半時計回り
// 数値 数値 ショートブレーキ（モーター端子を短絡した状態）
// ※数値はanalogWriteの0～255で指定する(255指定時が100%)。
// ※LOWはdigitalWriteでLOWを指定する。
//
// MOTOR1
const int PIN_MT1_IN1 = 2;
const int PIN_MT1_IN2 = 3;

void setup() {
  Serial.begin(9600);
  // LED1 出力設定
  pinMode(PIN_LED1, OUTPUT);
  // SW1 プルアップ入力設定
  pinMode(PIN_SW1, INPUT_PULLUP);
  // MOTOR1
  pinMode(PIN_MT1_IN1, OUTPUT);
  pinMode(PIN_MT1_IN2, OUTPUT);

  // スタートスイッチが押されるまで、オンボードLEDを点滅する。
  unsigned long tm = 0;
  // スタートスイッチが押されるとINPUT_PULLUPモードの
  // digitalRead()はLOWになり、whileを終了する。
  Serial.println("Wait until the start switch is pressed.");
  while (digitalRead(PIN_SW1) == HIGH) {
    // tmは500ミリ秒ごとに0,1,2,3,…となる。
    tm = millis() / 500;
    // 500ミリ秒ごとにLEDをON/OFFする。
    if (tm % 2 == 1) {
      // tmを2で割った余りが1の時、LED：ON
      digitalWrite(PIN_LED1, HIGH);
      Serial.print("o");
    } else {
      // tmを2で割った余りが0の時、LED：OFF
      digitalWrite(PIN_LED1, LOW);
      Serial.print(".");
    }
    //少し待つ。
    delay(100);
  }
  // LED1が点灯状態のままループしないよう消しておく。
  digitalWrite(PIN_LED1, LOW);
  Serial.print("Start loop.");
}

void loop() {
  // スピード設定（％指定）
  int speed = 30;
  // map() で 0～100[%] を 0～255 に変換。
  // constrain() は speed が0未満の場合は0、100超の場合100、0～100の場合はそのまま
  int pwm = map(constrain(speed, 0, 100), 0, 100, 0, 255);
  // MOTOR1 前進
  analogWrite(PIN_MT1_IN1, pwm);
  digitalWrite(PIN_MT1_IN2, LOW);
  Serial.print("O");
  delay(500);
  // MOTOR1 停止
  analogWrite(PIN_MT1_IN1, 0);
  analogWrite(PIN_MT1_IN2, 0);
  Serial.print("-");
  delay(500);
}

//  ■課題
//  (1) シリアルモニタを見ながら、スケッチを実行する。
//  (2) setup()中のスタート待ちの際のLEDの点滅間隔を更新する。
//  (3) 複数のモーターを同時に同様に動かす。
//