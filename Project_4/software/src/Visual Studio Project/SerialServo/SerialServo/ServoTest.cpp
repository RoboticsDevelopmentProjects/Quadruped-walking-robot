#include "RYSerialServo.h"

int main()
{
	int id,angle,end=0;
	int return_angle;
	Serial s1;
	cout<<"サーボIDを入力してください：";
	cin>>id;

	cout<<"角度を入力してください(0～180)：";
	cin>>angle;

	return_angle = s1.krs_move(id,angle);

	cout<<"angle:"<<return_angle;


	return 0;
}