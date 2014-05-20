#pragma once

namespace IcsSetPosition {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 の概要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
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
		/// 必要なデザイナー変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
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
			this->button1->Text = L"接続";
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
			this->Text = L"ICS ポジション設定";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: int SetPos (int id, int pos) {
			array<Byte>^tx = {0,0,0};       // unsigned char tx[3]
			array<Byte>^rx = {0,0,0,0,0,0}; // unsigned char rx[6](ループバックを含む)
      int dat;
      bool flag = true; // 正しくデータが受け取れたか

      tx[0] = (Byte)(0x80 | id);       // CMD
      tx[1] = (Byte)((pos >> 7) & 0x7F); // POS_H
      tx[2] = (Byte)(pos & 0x7f);      // POS_L

      serialPort1->DiscardInBuffer();   // バッファをクリアする
      serialPort1->DiscardOutBuffer();

      serialPort1->Write(tx, 0, 3); // tx配列(ICSコマンド)をシリアルポートから出力する

      for (int i = 0; i < 6; i++) // １バイト受信を６回繰り返す 
      {
        try
        {
          rx[i] = (Byte)serialPort1->ReadByte(); // １バイト受信
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
						 serialPort1->Close(); // いったん閉じる
						 if (comboBox1->Text != System::String::Empty) // ComboBoxでポート名が正しくセットされたとき
						 {
							 serialPort1->PortName = comboBox1->Text; // ポート名をセット
							 serialPort1->Open ();                   // ポートを開く（接続する）
							 if (serialPort1->IsOpen == true)        // ポートがきちんと開いたら
							 {
								 this->Text = this->Text + " [接続完了] "; // フォームのタイトルバーに[接続完了]と表示する
							 }
						 }
					 }

	private: System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
						 if (serialPort1->IsOpen == true) // シリアルポートが接続済みか確認してから
						 {
							 // IDとポジションデータをSetPos関数へ送る
							 int pos = SetPos ((int)numericUpDown1->Value, (int)trackBar1->Value);
							 if (pos != -1) // SetPos関数から返ってきたデータが正常だった場合
							 {
								 textBox1->Text = pos.ToString (); // テキストボックスに現在位置データを表示する
							 }
						 }
					 }
};
}

