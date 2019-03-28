#include <reg52.h>
#include "PUBLIC.h"
#include "ISO14443A.h"
#include "UART.h"
#include "string.h"
#include "CLRC632.h"

unsigned char code hardmodel[12]  = {"SL601F-0512"};
unsigned char idata g_cReceBuf[64];                         //����λ��ͨѶʱ�Ļ�����

bit g_bRc632Ok;                                             //RC632��λ������־
unsigned char data g_cSNR[4];                               //M1�����к�

/////////////////////////////////////////////////////////////////////
//��ʼ��RC632
/////////////////////////////////////////////////////////////////////
void Rc632Ready()
{
    char status;
    DelayMs(100);
    status = PcdReset();
    if(status != MI_OK)
    {
        DelayMs(10);
        status = PcdReset();
    } 
    if(status != MI_OK)
    {
        DelayMs(10);
        status = PcdReset();
    } 
    if(status == MI_OK)
    {
        g_bRc632Ok = 1;
    }       
}

/////////////////////////////////////////////////////////////////////
//��Ӧ��λ�����͵�����RC632Э�����ISO14443A/B��ISO15693
/////////////////////////////////////////////////////////////////////
void ComM632PcdConfigISOType()
{
	if (MI_OK == PcdConfigISOType(g_cReceBuf[6]))
	{
		// Puts_to_SerialPort("Success ComM632PcdConfigISOType...");
	}
	else
	{
		Puts_to_SerialPort("Fail to Select");
	}
}

void ComGetHardModel()//��ȡӲ���İ汾��
{
	memcpy(&g_cReceBuf[0], &hardmodel[0], sizeof(hardmodel));
	Puts_to_SerialPort(hardmodel);
}

//............................................/
//A��������
//............................................/

/////////////////////////////////////////////////////////////////////
//��Ӧ��λ�����͵�ѰA������
/////////////////////////////////////////////////////////////////////
void ComRequestA()
{
	unsigned char atq[2];
	char status;
	status = PcdRequest(g_cReceBuf[6], atq);
	if (status != MI_OK)
	{
		status = PcdRequest(g_cReceBuf[6], atq);
	}
	if (status == MI_OK)
	{
		// Puts_to_SerialPort("Success ComRequestA...");
        Puts_to_SerialPort(atq);
	}
	else
	{
		// Puts_to_SerialPort("Fail ComRequestA...");
	}
}

/////////////////////////////////////////////////////////////////////
//��Ӧ��λ�����͵�A������ײ����
/////////////////////////////////////////////////////////////////////
void ComAnticoll()
{
	if (MI_OK == PcdAnticoll(&g_cSNR))
	{
		// Puts_to_SerialPort("Success ComAnticoll...");
        Puts_to_SerialPort(g_cSNR);
	}
	else
	{
		// Puts_to_SerialPort("Fail ComAnticoll...");
	}
}

// ������
void main()
{
	InitUART();
	// ��������������
	Puts_to_SerialPort("Receiving From 8051...\r\n");
    
    Rc632Ready();
    
    PcdConfigISOType('A');
	while (1)
    {
        // ComGetHardModel();
        g_cReceBuf[6]='A';
        ComM632PcdConfigISOType();
        g_cReceBuf[6]=0x52;
        ComRequestA();
        ComAnticoll();
    }
}
