#pragma once

namespace IcsSetPosition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 �̊T�v
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(122, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"�ڑ�";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(12, 14);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(94, 20);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->DropDown += gcnew System::EventHandler(this, &Form1::comboBox1_DropDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(232, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"ID";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(263, 134);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(74, 19);
			this->textBox1->TabIndex = 3;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(12, 75);
			this->trackBar1->Maximum = 11500;
			this->trackBar1->Minimum = 3500;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(325, 45);
			this->trackBar1->TabIndex = 4;
			this->trackBar1->TickFrequency = 250;
			this->trackBar1->Value = 7500;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &Form1::trackBar1_ValueChanged);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 115200;
			this->serialPort1->Parity = System::IO::Ports::Parity::Even;
			this->serialPort1->ReadTimeout = 100;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(263, 15);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {31, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(74, 19);
			this->numericUpDown1->TabIndex = 5;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(349, 165);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"ICS �|�W�V�����ݒ�";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: int SetPos (int id, int pos) {
			array<Byte>^tx = {0,0,0};       // unsigned char tx[3]
			array<Byte>^rx = {0,0,0,0,0,0}; // unsigned char rx[6](���[�v�o�b�N���܂�)
      int dat;
      bool flag = true; // �������f�[�^���󂯎�ꂽ��

      tx[0] = (Byte)(0x80 | id);       // CMD
      tx[1] = (Byte)((pos >> 7) & 0x7F); // POS_H
      tx[2] = (Byte)(pos & 0x7f);      // POS_L

      serialPort1->DiscardInBuffer();   // �o�b�t�@���N���A����
      serialPort1->DiscardOutBuffer();

      serialPort1->Write(tx, 0, 3); // tx�z��(ICS�R�}���h)���V���A���|�[�g����o�͂���

      for (int i = 0; i < 6; i++) // �P�o�C�g��M���U��J��Ԃ� 
      {
        try
        {
          rx[i] = (Byte)serialPort1->ReadByte(); // �P�o�C�g��M
        }
        catch (...)
        {
          flag = false; 
          break;
        }
      }

      if (flag == false) 
      {
        return -1;
      }

      dat = (int)rx[4];
      dat = (dat << 7) + (int)rx[5];

      return dat;
					 }

	private: System::Void comboBox1_DropDown(System::Object^  sender, System::EventArgs^  e) {
						 comboBox1->Items->Clear();
						 comboBox1->Items->AddRange (System::IO::Ports::SerialPort::GetPortNames());
					 }

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
						 serialPort1->Close(); // �����������
						 if (comboBox1->Text != System::String::Empty) // ComboBox�Ń|�[�g�����������Z�b�g���ꂽ�Ƃ�
						 {
							 serialPort1->PortName = comboBox1->Text; // �|�[�g�����Z�b�g
							 serialPort1->Open ();                   // �|�[�g���J���i�ڑ�����j
							 if (serialPort1->IsOpen == true)        // �|�[�g��������ƊJ������
							 {
								 this->Text = this->Text + " [�ڑ�����] "; // �t�H�[���̃^�C�g���o�[��[�ڑ�����]�ƕ\������
							 }
						 }
					 }

	private: System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
						 if (serialPort1->IsOpen == true) // �V���A���|�[�g���ڑ��ς݂��m�F���Ă���
						 {
							 // ID�ƃ|�W�V�����f�[�^��SetPos�֐��֑���
							 int pos = SetPos ((int)numericUpDown1->Value, (int)trackBar1->Value);
							 if (pos != -1) // SetPos�֐�����Ԃ��Ă����f�[�^�����킾�����ꍇ
							 {
								 textBox1->Text = pos.ToString (); // �e�L�X�g�{�b�N�X�Ɍ��݈ʒu�f�[�^��\������
							 }
						 }
					 }
};
}

