#include "RYSerialServo.h"

int main()
{
	int id,angle,end=0;
	int return_angle;
	Serial s1;
	cout<<"�T�[�{ID����͂��Ă��������F";
	cin>>id;

	cout<<"�p�x����͂��Ă�������(0�`180)�F";
	cin>>angle;

	return_angle = s1.krs_move(id,angle);

	cout<<"angle:"<<return_angle;


	return 0;
}