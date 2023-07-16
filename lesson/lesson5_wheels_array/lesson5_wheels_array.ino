//----------------------------
// LESSON5：ホイールを複数回す。配列の練習
//
// 2023-07-15 ohguma 初版
//----------------------------
// Arduino Mega 拡張基板
// https://github.com/ohguma/mega_board
//
// ■ピン設定
// モータードライバ TOSHIBA TB67H450FNG
// https://toshiba.semicon-storage.com/info/TB67H450FNG_datasheet_ja_20201126.pdf?did=65345&prodName=TB67H450FNG
//   IN1   IN2   OUT1  OUT2  動作
//   ----  ----  ----  ----  -----------------
//   0     0     OFF   OFF   停止（モーター端子が接続されていない状態）
//   数値  0     ＋    －    時計回り（OUT1が電源＋、OUT2が電源－に接続される）
//   0     数値  －    ＋    反時計回り（OUT2が電源＋、OUT1が電源－に接続される）
//   数値  数値  －    －    ショートブレーキ（モーター端子を短絡した状態）
//
// ※最大4つのモータードライバは、IN1/IN2 に Arduino Mega のそれぞれ以下を
//   接続している。
//     MT1  D2/D3
//     MT2  D4/D5
//     MT3  D6/D7
//     MT4  D8/D9
//
// ※モーターの＋端子に赤線、反対側には黒線をハンダ付けし、XHコネクタには電
//   池ボックスと同じ向きに赤線・黒線を差し込むこと。
//   （コネクタの▲マークに赤線を接続する。）
//   このとき、モータードライバのOUT1にモーターの＋端子、OUT2には反対側端子
//   が接続される。
//
// ※モーターは＋端子に電池のプラス、反対側にマイナスを接続すると、ギヤを取
//   り付ける側からモーターを見た場合に、通常モーター軸が時計回りする。
//   ギヤボックスを使う場合は内部のギヤの組み合わせにより、出力軸がモーター
//   軸とは逆に回る場合がある。
//
// ※Arduino Megaでは数値はanalogWrite()の0～255で指定する。
//   0を指定した時が0%、255を指定した時が100%。
//
const int NUM_MOTOR = 2;
const int PIN_IN1[NUM_MOTOR] = { 2, 4 };
const int PIN_IN2[NUM_MOTOR] = { 3, 5 };
// タクトスイッチ
// ・SW1,SW2,SW3：D51,D52,D53かから各SWを経由してGNDに接続。
// ・INPUT_PULLUPモードで使用する。
const int PIN_SW1 = 51;

void setup() {
  setup_wheel();
  // スイッチ1 プルアップ入力設定
  pinMode(PIN_SW1, INPUT_PULLUP);
  // SW1が押されるとINPUT_PULLUPモードのdigitalRead()はLOWになる。
  while (digitalRead(PIN_SW1) == HIGH) {
    //SW1が押されていないときは少し待つ、を繰り返す
    delay(10);
  }
}

void loop() {
  int i = 0;
  int j = 0;
  // 約1秒でだんだん早くする。
  for (int j = 0; j <= 255; j++) {
    for (int i = 0; i < NUM_MOTOR; i++) {
      rotate_wheel(i, j);  // ホイール反時計回り。
    }
    delay(4);  //少し待つ。4ミリ秒
  }
  // 約1秒でだんだん遅くする。各ホイール逆回転に。

  // 停止して1秒待機
  stop_wheel_all();
  delay(1000);
}


// 複数ホイール準備
void setup_wheel() {
  for (int i = 0; i < NUM_MOTOR; i++) {
    pinMode(PIN_IN1[i], OUTPUT);
    pinMode(PIN_IN2[i], OUTPUT);
  }
}

//全ホイール停止
void stop_wheel_all() {
  for (int i = 0; i < NUM_MOTOR; i++) {
    rotate_wheel(i, 0);
  }
}

// １つのホイールを回転させる
// 引数 no  : 回すホイール番号：0の時MT1、1の時MT2、
// 引数 pwm : analogWrite()で使用するPWM値。
//            範囲は -255 <= pwm <= 255
//            ０以上で時計回り、マイナスで反時計回りとする。
void rotate_wheel(int no, int pwm) {
  if (no >= 0 && no < NUM_MOTOR) {
    if (pwm >= 0) {
      analogWrite(PIN_IN1[no], pwm);  //ピン指定は適宜調整する
      analogWrite(PIN_IN2[no], 0);
    } else {
      //alalogWrite()でセットするPWM値はプラスの値のみ
      analogWrite(PIN_IN1[no], 0);
      analogWrite(PIN_IN2[no], fabs(pwm));  // - pwm でも等価
    }
  }
}

//  ■課題
//  (1) 「Arduinoを始めよう」の「Arduino 公式リファレンス」で以下を調べる。
//    ・配列
//    ・while 文
//
//  (2) コメント「 // 約1秒でだんだん遅くする。各ホイール逆回転に。」の箇所
//      を補足する。
//
//  (3) 接続している全ホイールを動かす。
//
//  (4) 関数 setup_wheel()、rotate_wheel()、stop_wheel_all() の定義部分と、
//      そこで使用するピン指定を別ファイルに分割してみること。
//        [ヒント] 別ファイル内で自作関数を使用する場合、使用する箇所よりも
//                 先にその関定義されている必要がある。
//
