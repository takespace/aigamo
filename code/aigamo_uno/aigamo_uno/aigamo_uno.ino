//-----------------------------------------------------------------
// include
//-----------------------------------------------------------------
#include <Wire.h>
#include <Servo.h> 

//-----------------------------------------------------------------
// define
//-----------------------------------------------------------------
// 動作モード用の定数
#define MODE_AUTO      0
#define MODE_REMOTE    1

// debug用LED
#define L0             14
#define L1             15
#define L2             16
#define L3             17

//-----------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------
struct Sensors
{
  byte caps_l;        // 静電容量センサl
  byte caps_c;        // 静電容量センサc
  byte caps_r;        // 静電容量センサr
  byte imu_gyro[3];   // 3軸ジャイロ  (仮)
  byte imu_dir[3];    // 3軸方位      (仮)
  byte imu_accel[3];  // 3軸加速度    (仮)
};

//-----------------------------------------------------------------
// grobal変数
//-----------------------------------------------------------------
// 動作モード管理変数
byte run_mode = MODE_REMOTE;

// サーボモータ
Servo servo_lf;   // left front
Servo servo_lb;   // left back
Servo servo_rf;   // right front
Servo servo_rb;   // right back

// センサ類
Sensors sens;


//-----------------------------------------------------------------
// 関数プロトタイプ宣言
//-----------------------------------------------------------------
// アプリケーション
void autopilot_control();                               // 自律制御モード
void remote_control(char cmd);                           // リモート制御モード

// デバイス制御
void drive_motors(int, int);                            // モータ制御
void get_caps_sensor(byte *l, byte *c, byte *r);        // 静電容量センサの取得


//-----------------------------------------------------------------
// setup, loop関数
//-----------------------------------------------------------------
void setup() 
{       
  // シリアル通信の初期化  
  Serial.begin(115200);
  Wire.begin();
  
  // debug用LEDの初期化
  //DDRC |= 0x0f;// A0-A3(PORTC0-PORTC4)をDegub LEDに指定
  pinMode(L0, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  
  // サーボモータの初期化
  servo_rf.attach(3);
  servo_rb.attach(5);
  servo_lf.attach(6);
  servo_lb.attach(9);
  
  // 静電容量センサの初期化
  Wire.requestFrom(0x42, 3);
  Wire.read();
  byte minorVersion = Wire.read();
  byte majorVersion = Wire.read();

  // 起動時のメッセージ出力
  Serial.print("Firmware version is ");
  Serial.print(majorVersion);
  Serial.print(".");
  Serial.print(minorVersion);
  Serial.println(".");  
  
  // 起動時はリモートモードから開始
  run_mode = MODE_REMOTE;
  Serial.println("--- remote mode");
}

// the loop routine runs over and over again forever:
void loop() 
{  
  //---------------------
  // 変数宣言
  //---------------------
  char cmd = '\0';
  
  //---------------------
  // コマンド判定  
  //---------------------
  if(Serial.available() > 0) 
  {
    // コマンド取得
    cmd = Serial.read();
  
    // コマンド解析
    switch(cmd)
    {
      case '1':      // オート
        run_mode = MODE_AUTO;
        digitalWrite(L0, HIGH);
        Serial.println("--- auto mode");
        break;
        
      case '2':      // リモート
      default:
        run_mode = MODE_REMOTE;
        digitalWrite(L0, LOW);
        Serial.println("--- remote mode");
        break;
    }
  }
  
  //---------------------
  // 共通処理(モード関係なし)
  //---------------------
    
  //---------------------
  // モード別動作
  //---------------------
  switch(run_mode)
  {
    case MODE_AUTO:         // オート
      autopilot_control();
      break;
      
    case MODE_REMOTE:      // リモート
      remote_control(cmd);
      break;
  }
}

//-----------------------------------------------------------------
// アプリケーション
//-----------------------------------------------------------------
// 自律制御モード
#define DIFF 128
#define BACK_TIME 1200
#define TURN_TIME 1200
void autopilot_control()
{
  // 静電容量センサ値の取得処理
  get_caps_sensor(&sens.caps_l, &(sens.caps_c), &(sens.caps_r));
  Serial.print(sens.caps_l);  Serial.print(',');
  Serial.print(sens.caps_c);  Serial.print(',');
  Serial.print(sens.caps_r);  Serial.println();
  
  //草回避動作
  if(sens.caps_c > DIFF)
  {
    // 真ん中のセンサは存在しない
    /**
    digitalWrite(L1, HIGH); 
    drive_motors(-127,-127);
    delay(BACK_TIME);
    drive_motors(-127,127);    // とりあえず旋回
    delay(TURN_TIME);
    drive_motors(0,0);
    digitalWrite(L1, LOW); 
    **/
  }
  else if(sens.caps_r > DIFF)
  {
    digitalWrite(L1, HIGH); 
    drive_motors(-127,-127);
    delay(BACK_TIME);
    drive_motors(-127,127);
    delay(TURN_TIME);
    drive_motors(0,0);
    digitalWrite(L1, LOW); 
  }
  else if(sens.caps_l > DIFF)
  {
    digitalWrite(L1, HIGH); 
    drive_motors(-127,-127);
    delay(BACK_TIME);
    drive_motors(127,-127);
    delay(TURN_TIME);
    drive_motors(0,0);
    digitalWrite(L1, LOW); 
  }
  else
  {
    // 何もセンサに反応が無いとき
    digitalWrite(L3, HIGH); 
    drive_motors(127,127);
    digitalWrite(L3, LOW); 
  }
  delay(100);
}

// リモート制御モード
void remote_control(char cmd)
{
  // 静電容量センサ値の取得処理と表示
  get_caps_sensor(&sens.caps_l, &(sens.caps_c), &(sens.caps_r));
  
  if(50 < sens.caps_l)
    digitalWrite(L1, HIGH); 
  else
    digitalWrite(L1, LOW);    
  if(50 < sens.caps_r)
    digitalWrite(L2, HIGH); 
  else
    digitalWrite(L2, LOW);
    
  Serial.print(sens.caps_l);  Serial.print(',');
  Serial.print(sens.caps_c);  Serial.print(',');
  Serial.print(sens.caps_r);  Serial.println(); 
  
  // コマンドが来ていない時は動作しない
  if(cmd == '\0' || cmd == '2')
  {
      Serial.println(".");
    drive_motors(0,0);
    delay(100);    // 静電容量センサに高速にアクセスすると値を取れないみたいなので
    return;
  }
  
  // 何かコマンドが来たぞ！！
  digitalWrite(L3, HIGH); 
  switch(cmd)
  {
    case 's':
      Serial.println("Up"); 
      drive_motors(127,127);
      break;
      
    case 'x':
      Serial.println("Down");
      drive_motors(-127,-127);
      break;
   
    case 'z':
      Serial.println("Left");
      drive_motors(-127,127);
      break;
      
    case 'c':
      Serial.println("Rifht");
      drive_motors(127,-127);
      break;
    
    default:    // 存じ上げないコマンドです
      Serial.println("No Command"); 
      drive_motors(0,0);
      break;
  }
  delay(100);
  digitalWrite(L3, LOW); 
}


//-----------------------------------------------------------------
// デバイス制御
//-----------------------------------------------------------------
// モータ制御
// -> 4つのモータを一括制御．
//      left_power  :  左側のモータ(前・後)のパワー
//      right_power  :  左側のモータ(前・後)のパワー
void drive_motors(int left_power, int right_power)
{
  int tmp_l = int(map(left_power,127,-127,180,0));
  int tmp_r = int(map(right_power,127,-127,0,180));
  servo_lf.write(tmp_l);
  servo_lb.write(tmp_l);
  servo_rf.write(tmp_r);
  servo_rb.write(tmp_r);
  
  //Serial.println(tmp_l,DEC);
  //Serial.println(tmp_r,DEC);
  return;
}

// 静電容量センサの取得
// -> センサ値を一括取得
void get_caps_sensor(byte *l, byte *c, byte *r)
{
  Wire.requestFrom(0x42, 11);
  Wire.read();
  *l = Wire.read();
  *c = Wire.read();
  *r = Wire.read();
  for (int i = 0; i < 7; i++)
  {
    Wire.read();//空読み
  }
}
