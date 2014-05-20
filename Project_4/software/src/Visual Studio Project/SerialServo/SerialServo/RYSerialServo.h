//インクルード
#include <iostream>
#include <cstring>
#include <cstdlib>
#using <System.dll>

//名前空間の指定
using namespace std;
using namespace System;
using namespace System::IO::Ports;

//グローバル変数
int  flag=0; //読み取れているかどうかの判定用変数(0:成功/1:失敗)
int dat;//サーボの現在位置を格納する変数
static int servo_id[]={0,1,2,3,4,5,6,7};//サーボID格納配列

//Serialクラス
class Serial{
public:
	//Serial(); //コンストラクタ関数
	//~Serial(); //デストラクタ関数
	void off_set_load();//off_set.txtをロードしてサーボに初期値として代入する関数
	int krs_move(int id,int angle); //サーボ移動関数
};

//コンストラクタ関数
/*Serial::Serial()
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COMの設定とボーレートの設定
	port->Open();//ポート接続
}

//デストラクタ関数
Serial::~Serial()
{
	SerialPort^ port;
	port->DiscardOutBuffer();  //送信バッファ破棄
}*/

//サーボ移動関数
//Serial::set_pos(サーボID,移動角度(0<=anglevalue<=180))
int Serial::krs_move(int id,int angle)
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COMの設定とボーレートの設定
	port->Open();//ポート接続
	//バッファの定義
	int anglevalue; //角度をコマンド値に変換
	array<Byte>^tx = {0,0,0};//送信用バッファ
	array<Byte>^rx = {0,0,0,0,0,0};//受信用バッファ

	//角度変換
	anglevalue = angle * 27.777777777777777777777777777778 + 5000.0;

	//コマンド
	tx[0] = (Byte)(0x80 | id); //CMD(論理和)
    tx[1] = (Byte)((anglevalue>>7) & 0x7F); //POS_H(上位7ビット)
    tx[2] = (Byte)(anglevalue & 0x7F); //POS_L(下位7ビット)

	port->DiscardInBuffer();   // 受信バッファ破棄
    port->DiscardOutBuffer();  //送信バッファ破棄

	//データ送信
	port->Write(tx,0,3);
	
	//6回読み取り
	for (int i = 0; i < 6; i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //データ受信
		}
		catch(...)
		{
			flag = 1;//受信できなかった場合はfalse(1)を返す
			break;
		}
		if(flag=1)
			return -1;
	}
	port->Close();

	dat=(int)rx[4];
	dat=(dat<<7)+(int)rx[5];

	return dat;
}