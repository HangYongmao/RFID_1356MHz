#include <reg52.h>
#include "UART.h"

// �򴮿ڷ����ַ�
void Putc_to_SerialPort(uchar c)
{
	SBUF = c;
	while (TI == 0);
	TI = 0;
}

// �򴮿ڷ����ַ���
void Puts_to_SerialPort(uchar *s)
{
	while (*s != '\0')
	{
		Putc_to_SerialPort(*s);
		s++;
		DelayMs(5);
	}
}

// ��ʼ������
void InitUART()
{
	SCON = 0x40;		//����ģʽ1 
	TMOD = 0x20;		//T1����ģʽ2
	TH1 = 0xfd;		//������9600
	TL1 = 0xfd;
	PCON = 0x00;		//�����ʲ�����
	TI = 0;
	TR1 = 1;
	DelayMs(200);
}