//----------------------------
// LESSON3：モーターを1つ回す
//
// 2023-07-11 ohguma 初版
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
// MT1を使用する場合は、MegaのD2,D3を使用する。
const int PIN_IN1 = 2;
const int PIN_IN2 = 3;

void setup() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
}

void loop() {
  int i = 0;
  for (i = 0; i <= 255; i++) {
    // モーター軸時計回り。約1秒でだんだん早くする。
    // 4ミリ秒 ✕ 256（for文が 0から255までの256回繰り返し）
    // ＝ 1024 ミリ秒
    // ≒ 約1秒
    analogWrite(PIN_IN1, i);
    analogWrite(PIN_IN2, 0);
    delay(4);  //少し待つ。4ミリ秒
  }
  for (i = 255; i >= 0; i--) {
    //モーター軸時計回り。約1秒でだんだん遅くする。
    analogWrite(PIN_IN1, i);
    analogWrite(PIN_IN2, 0);
    delay(4);  //少し待つ。4ミリ秒
  }
  for (i = 0; i <= 255; i++) {
    //モーター軸反時計回り。約1秒でだんだん早くする。
    analogWrite(PIN_IN1, 0);
    analogWrite(PIN_IN2, i);
    delay(4);  //少し待つ。4ミリ秒
  }
  for (i = 255; i >= 0; i--) {
    //モーター軸反時計回り。約1秒でだんだん遅くする。
    analogWrite(PIN_IN1, 0);
    analogWrite(PIN_IN2, i);
    delay(4);  //少し待つ。4ミリ秒
  }
  delay(1000);
}

//  ■課題
//  (1) 「Arduinoを始めよう」の「Arduino 公式リファレンス」で以下を調べる。
//    ・for 文
//    ・<=、>=  （他の比較演算子も合わせて確認する）
//    ・++、--  （他の複合演算子も合わせて確認する）
//    ・analogWrite()
//
//  (2) モーター軸時計回りのとき（5秒間隔の頭2秒）にホイール取り付け側から
//      見たホイールが時計回りしているか確認する。
//      反時計回りの場合、冒頭の「PIN_IN1」と「PIN_IN2」に代入する値を入れ
//      替えて時計回りになるかどうかか確認する。
//
//  (3) MT1だけでなく、全モーターの回転方向を確認しておく。
//      冒頭の「PIN_IN1」と「PIN_IN2」に代入する値を変更し、モーターを接続
//      するMT2、MT3、MT4の全てを確認する。
//