//�C���N���[�h
#include <iostream>
#include <cstring>
#include <cstdlib>
#using <System.dll>

//���O��Ԃ̎w��
using namespace std;
using namespace System;
using namespace System::IO::Ports;

//�O���[�o���ϐ�
int  flag=0; //�ǂݎ��Ă��邩�ǂ����̔���p�ϐ�(0:����/1:���s)
int dat;//�T�[�{�̌��݈ʒu���i�[����ϐ�
static int servo_id[]={0,1,2,3,4,5,6,7};//�T�[�{ID�i�[�z��

//Serial�N���X
class Serial{
public:
	//Serial(); //�R���X�g���N�^�֐�
	//~Serial(); //�f�X�g���N�^�֐�
	void off_set_load();//off_set.txt�����[�h���ăT�[�{�ɏ����l�Ƃ��đ������֐�
	int krs_move(int id,int angle); //�T�[�{�ړ��֐�
};

//�R���X�g���N�^�֐�
/*Serial::Serial()
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COM�̐ݒ�ƃ{�[���[�g�̐ݒ�
	port->Open();//�|�[�g�ڑ�
}

//�f�X�g���N�^�֐�
Serial::~Serial()
{
	SerialPort^ port;
	port->DiscardOutBuffer();  //���M�o�b�t�@�j��
}*/

//�T�[�{�ړ��֐�
//Serial::set_pos(�T�[�{ID,�ړ��p�x(0<=anglevalue<=180))
int Serial::krs_move(int id,int angle)
{
	SerialPort^ port=gcnew SerialPort("COM5",115200,Parity::Even,8,StopBits::One);//COM�̐ݒ�ƃ{�[���[�g�̐ݒ�
	port->Open();//�|�[�g�ڑ�
	//�o�b�t�@�̒�`
	int anglevalue; //�p�x���R�}���h�l�ɕϊ�
	array<Byte>^tx = {0,0,0};//���M�p�o�b�t�@
	array<Byte>^rx = {0,0,0,0,0,0};//��M�p�o�b�t�@

	//�p�x�ϊ�
	anglevalue = angle * 27.777777777777777777777777777778 + 5000.0;

	//�R�}���h
	tx[0] = (Byte)(0x80 | id); //CMD(�_���a)
    tx[1] = (Byte)((anglevalue>>7) & 0x7F); //POS_H(���7�r�b�g)
    tx[2] = (Byte)(anglevalue & 0x7F); //POS_L(����7�r�b�g)

	port->DiscardInBuffer();   // ��M�o�b�t�@�j��
    port->DiscardOutBuffer();  //���M�o�b�t�@�j��

	//�f�[�^���M
	port->Write(tx,0,3);
	
	//6��ǂݎ��
	for (int i = 0; i < 6; i++){
		try{
			rx[i] = (Byte)port->ReadByte(); //�f�[�^��M
		}
		catch(...)
		{
			flag = 1;//��M�ł��Ȃ������ꍇ��false(1)��Ԃ�
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