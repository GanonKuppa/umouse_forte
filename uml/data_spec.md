# ロボットが送受信しているデータの仕様

## ロボットからの送信データ

- データ長 250byte
- データ送信間隔 30msec
- 迷路データ(32x32)は4分割して送信

| byte | length |  type  |         content         |
|:----:|:------:|:------:|:-----------------------:|
| 0    | 1      | uint8  | ヘッダー0 0xff          |
| 1    | 1      | uint8  | ヘッダー1 0xff          |
| 2    | 1      | uint8  | ヘッダー2 0x48          |
| 3    | 1      | uint8  | ヘッダー3 0x45          |
| 4    | 1      | uint8  | ヘッダー4 0x41          |
| 5    | 1      | uint8  | ヘッダー5 0x44          |
| 6    | 1      | uint8  | チェックサム 7-249byteのsum           |
| 7    | 1      | uint8  | printfデータのデータ長  |
| 8    | 4      | uint32 | 経過時間[ms]            |
| 12   | 2      | uint16 | AD000                   |
| 14   | 2      | uint16 | AD001                   |
| 16   | 2      | uint16 | AD002                   |
| 18   | 2      | uint16 | AD003                   |
| 20   | 2      | uint16 | AD004                   |
| 22   | 2      | uint16 | AD005                   |
| 24   | 2      | uint16 | AD006                   |
| 26   | 2      | uint16 | AD007                   |
| 28   | 2      | uint16 | AD108                   |
| 30   | 2      | uint16 | AD109                   |
| 32   | 2      | uint16 | AD110                   |
| 34   | 2      | int16  | mpu9250 gyro X          |
| 36   | 2      | int16  | mpu9250 gyro Y          |
| 38   | 2      | int16  | mpu9250 gyro Z          |
| 40   | 2      | int16  | mpu9250 acc X           |
| 42   | 2      | int16  | mpu9250 acc Y           |
| 44   | 2      | int16  | mpu9250 acc Z           |
| 46   | 2      | int16  | mpu9250 mag X           |
| 48   | 2      | int16  | mpu9250 mag Y           |
| 50   | 2      | int16  | mpu9250 mag Z           |
| 52   | 2      | int16  | Icm20608G gyro X        |
| 54   | 2      | int16  | Icm20608G gyro Y        |
| 56   | 2      | int16  | Icm20608G gyro Z        |
| 58   | 2      | int16  | Icm20608G acc X         |
| 60   | 2      | int16  | Icm20608G acc Y         |
| 62   | 2      | int16  | Icm20608G acc Z         |
| 64   | 2      | uint16 | CMT0[us]                |
| 66   | 2      | uint16 | CMT1[us]                |
| 68   | 2      | uint16 | main[us]                |
| 70   | 2      | int16  | dutyR                   |
| 72   | 2      | int16  | dutyL                   |
| 74   | 2      | uint16 | encR                    |
| 76   | 2      | uint16 | encL                    |
| 78   | 2      | uint16 | TactSW                  |
| 80   | 2      | uint16 | Start x                 |
| 82   | 2      | uint16 | Start y                 |
| 84   | 2      | uint16 | Goal x                  |
| 86   | 2      | uint16 | Goal y                  |
| 88   | 2      | uint16 | ab_pos x                |
| 90   | 2      | uint16 | ab_pos y                |
| 92   | 2      | uint16 | dir                     |
| 94   | 2      | uint16 | R Sen                   |
| 96   | 2      | uint16 | H Sen                   |
| 98   | 2      | uint16 | L Sen                   |
| 100  | 2      | int16  | t_ang_a                 |
| 102  | 2      | int16  | t_ang_v                 |
| 104  | 2      | int16  | t_ang                   |
| 106  | 2      | int16  | accum_ang               |
| 108  | 2      | int16  | gyro_ang_v              |
| 110  | 2      | int16  | t_a                     |
| 112  | 2      | int16  | t_v                     |
| 114  | 2      | int16  | t_x                     |
| 116  | 2      | int16  | accum_x                 |
| 118  | 2      | int16  | acc_v_a                 |
| 120  | 2      | int16  | acc_h_a                 |
| 122  | 2      | int16  | enc_v                   |
| 124  | 2      | int16  | wall P                  |
| 126  | 2      | int16  | wall I                  |
| 128  | 2      | int16  | wall D                  |
| 130  | 2      | int16  | v P                     |
| 132  | 2      | int16  | v I                     |
| 134  | 2      | int16  | v D                     |
| 136  | 2      | int16  | ang P                   |
| 138  | 2      | int16  | ang I                   |
| 140  | 2      | int16  | ang D                   |
| 142  | 2      | int16  | ang_v P                 |
| 144  | 2      | int16  | ang_v I                 |
| 146  | 2      | int16  | ang_v D                 |
| 148  | 2      | int16  | v FF                    |
| 150  | 2      | int16  | ang FF                  |
| 152  | 2      | int16  | q0                      |
| 154  | 2      | int16  | q1                      |
| 156  | 2      | int16  | q2                      |
| 158  | 2      | int16  | q3                      |
| 160  | 1      | uint16 | 161byte以降データ種別   |
| 161  | 89     | -      | 160byteで指定したデータ |

###161byte


## ロボットが受信するデータ

- データ長 16byte

### gamepad入力コマンド


| byte | length |  type  |         content         |
|:----:|:------:|:------:|:-----------------------:|
| 0    | 1      | uint8  | ヘッダー0 99            |
| 1    | 1      | uint8  | ヘッダー1 109           |
| 2    | 1      | uint8  | ヘッダー2 100           |
| 3    | 1      | uint8  | コマンドID0 254         |
| 4    | 1      | uint8  | コマンドID1 253         |
| 5    | 1      | uint8  | チェックサム 6-15byteのsum         |
| 6    | 1      | uint8  | 各種ボタン状態            |
| 7    | 1      | uint8  | RT押し込み  |
| 8    | 4      | uint8 | LT押し込み            |
| 9    | 1      | uint8  | 十字ボタン x           |
| 10    | 1      | uint8  | 十字ボタン y           |
| 11    | 1      | uint8  | R3D x           |
| 12    | 1      | uint8  | R3D y         |
| 13    | 1      | uint8  | L3D x         |
| 14    | 1      | uint8  | L3D y          |
| 15    | 1      | uint8  | -   |


#### 6byte目
0-7bitまでが以下の順番に対応
A,B,X,Y,RB,LB,BACK,START  
0:押してない 1:押している  
#### 7,8byte目
押し込み量を0-255で返す
#### 9,10byte目
十字ボタン　129=1+128:上、右, 127=-1+128:下、左
#### 11,12,13,14byte目
3Dスティック 0から255までの値を取る。3Dスティックが中心にある時は128を返す
### parameter manager 登録変数値読み出しコマンド

| byte | length |  type  |         content         |
|:----:|:------:|:------:|:-----------------------:|
| 0    | 1      | uint8  | ヘッダー0 99            |
| 1    | 1      | uint8  | ヘッダー1 109           |
| 2    | 1      | uint8  | ヘッダー2 100           |
| 3    | 1      | uint8  | コマンドID0 254         |
| 4    | 1      | uint8  | コマンドID1 252         |
| 5    | 1      | uint8  | チェックサム 6-15byteのsum         |
| 6    | 1      | uint8  | 読み出し番号指定             |
| 7    | 1      | uint8  |-  |
| 8    | 4      | uint8  |-             |
| 9    | 1      | uint8  |-           |
| 10    | 1      | uint8  |-           |
| 11    | 1      | uint8  |-           |
| 12    | 1      | uint8  |-         |
| 13    | 1      | uint8  |-         |
| 14    | 1      | uint8  |-          |
| 15    | 1      | uint8  |-   |

#### 6byte目
- 読み出す変数のグループを指定
- コマンド6byte目に読み出したいグループ番号を入れる
- 1グループには16変数が属する
- 1変数は4byteなので1回の読み出しデータは64byte
- 送信データの160byte目以降に読み出しデータを格納

6byte目=0:変数0から15を読み出し、   
6byte目=1:変数16から31
6byte目=2:変数32から47  
　　　　　...



### parameter manager 登録変数書換コマンド

| byte | length |  type  |         content         |
|:----:|:------:|:------:|:-----------------------:|
| 0    | 1      | uint8  | ヘッダー0 99            |
| 1    | 1      | uint8  | ヘッダー1 109           |
| 2    | 1      | uint8  | ヘッダー2 100           |
| 3    | 1      | uint8  | コマンドID0 251         |
| 4    | 1      | uint8  | チェックサム          |
| 5    | 1      | uint8  | 型情報                 |
| 6    | 1      | uint8  | 値 0byte              |
| 7    | 1      | uint8  | 値 1byte              |
| 8    | 1      | uint8  | 値 2byte              |
| 9    | 1      | uint8  | 値 3byte          |
| 10    | 1      | uint8  | 変数番号           |
| 11    | 1      | uint8  |-            |
| 12    | 1      | uint8  |-         |
| 13    | 1      | uint8  |-         |
| 14    | 1      | uint8  |-          |
| 15    | 1      | uint8  |-   |

型情報
0:float
1:uint8_t,
2:uint16_t,
3:uint32_t,
4:int8_t,
5:int16_t,
6:int32_t,

## parameter manager仕様
parameter managerはロボットの外部から読み出し、書き換えを行いたい変数を登録する



#### RX71Mのデータフラッシュの仕様
- 64byteのブロックが1024個
- データの書き込みは4byte単位
- データの書き込みの前にデータの消去が必要
- データの消去はブロック単位

#### parameter managerの仕様
- 1ブロックに1変数を割り当て
- ブロック0-255をparameter managerに割り当て


## parameterの調整 20170918
角速度PID(超信知)
0.0001
0.0003
0.0001
250
角度PID(超信知)
0.0002
0.0008
0.002
80
速度PID(超信知)
0.4
0.3
0.01
30
