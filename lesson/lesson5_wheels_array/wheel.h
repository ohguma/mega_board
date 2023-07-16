
const int NUM_MOTOR = 2;
const int PIN_IN1[NUM_MOTOR] = { 2, 4 };
const int PIN_IN2[NUM_MOTOR] = { 3, 5 };

// 複数ホイール準備
void setup_wheel() {
  for (int i = 0; i < NUM_MOTOR; i++) {
    pinMode(PIN_IN1[i], OUTPUT);
    pinMode(PIN_IN2[i], OUTPUT);
  }
}

// １つのホイールを回転させる
// 引数 no  : 回すホイール番号：0の時MT1、1の時MT2
// 引数 pwm : analogWrite()で使用するPWM値。
//            範囲は -255 <= pwm <= 255
//            ０以上で時計回り、マイナスで反時計回りとする。
void rotate_wheel(int no, int pwm) {
  if (no >= 0 && no <= 1) {
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

//全ホイール停止
void stop_wheel_all() {
  for (int i = 0; i < NUM_MOTOR; i++) {
    rotate_wheel(i, 0);
  }
}