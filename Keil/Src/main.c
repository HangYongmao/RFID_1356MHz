#include <reg52.h>
#include "PUBLIC.h"
#include "UART.h"
#include "ISO14443A.h"
#include "ISO14443B.h"
#include "ISO15693.h"
#include "string.h"
#include "CLRC632.h"
#include "OLED.h"
#include "TIMER.h"

unsigned char code hardmodel[12]  = {"SL601F-0512"};    // Ӳ���汾��
unsigned char lastCardCode[32]  = {"SL601F-0512"}; // ��һ�ζ�ȡ�Ŀ���

bit g_bRc632Ok;     // RC632��λ������־
bit clsFlag = 0;    // ������־
extern uint TimerCount;
unsigned char g_cFWI;
unsigned char data g_cSNR[4];       // M1�����к�
unsigned char idata g_cReceBuf[64]; // ����λ��ͨѶʱ�Ļ�����

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
		// Puts_to_SerialPort("Fail to Select");
	}
}

//��ȡӲ���İ汾��
void ComGetHardModel()
{
	memcpy(&g_cReceBuf[0], &hardmodel[0], sizeof(hardmodel));
	Puts_to_SerialPort(hardmodel);
    
    OLED_ShowHardCodeChinese();
    OLED_ShowString(8*(16-strlen(hardmodel)), 4, hardmodel);
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
        // Puts_to_SerialPort(atq);
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
    int i=0, j=0;
    unsigned char tempData[32] = {0};   // ����ת����Ŀ���
	if (MI_OK == PcdAnticoll(&g_cSNR))
	{
        if (g_cSNR[0] == 0)
        {
            OLED_ShowString(0, 0, "Error:");
            return;
        }
		// Puts_to_SerialPort("Success ComAnticoll...");
        // ��ʮ����������ת��Ϊ�ַ���
        for (i=0; i<4; i++)
        {
            // ��λ����
            if ((g_cSNR[i]>>4) < 10)
                tempData[j++] = (g_cSNR[i]>>4) + '0';
            else
                tempData[j++] = (g_cSNR[i]>>4) - 10 + 'A';
            
            // ��λ����
            if ((g_cSNR[i]&0xf) < 10)
                tempData[j++] = (g_cSNR[i]&0xf) + '0';
            else
                tempData[j++] = (g_cSNR[i]&0xf) - 10 + 'A';
        }
        
        if (strcmp(lastCardCode, tempData) != 0)
        {
            strcpy(lastCardCode, tempData);
            Puts_to_SerialPort(lastCardCode);
            Puts_to_SerialPort("ISO14443A:");
            Puts_to_SerialPort(tempData);
            Puts_to_SerialPort("\r\n");
                
            // ���ԭ������
            OLED_ShowString(0, 0, "          ");
            OLED_ShowString(0, 2, "                ");
                OLED_ShowString(0, 4, "                ");
            
            OLED_ShowString(0, 0, "ISO14443A:");
            OLED_ShowString(0, 2, tempData);
            
            BEEP = 0;
            DelayMs(100);
            BEEP = 1;
        }
        TimerCount = 0;
        clsFlag = 0;
	}
	else
	{
		// Puts_to_SerialPort("Fail ComAnticoll...");
	}
}

//............................................/
//B��������
//............................................/
void ComTypeBRst()
{
	unsigned char status;

    int i=0, j=0;
    unsigned char tempData[32] = {0};   // ����ת����Ŀ���
	if ((status = M531PiccRequestB(g_cReceBuf[6], 0, 0, &g_cReceBuf[0])) == MI_OK)
	{
        // Puts_to_SerialPort(g_cReceBuf);
    	g_cFWI    = 0xFF;//g_cReceBuf[11] >> 4; 
    	// g_cCidNad = 8;//((g_cReceBuf[11]&0x02)<<1) | ((g_cReceBuf[11]&0x01)<<3);
       status = M531PiccAttrib(&g_cReceBuf[1], g_cReceBuf[10] & 0x0F, &g_cReceBuf[12]);
	}

	if (status == MI_OK)
	{
        memset(g_cReceBuf, 0, 64);
        if ((status = Get_UID_TypeB(&g_cReceBuf[0])) == MI_OK)
        {
            // ��ʮ����������ת��Ϊ�ַ���
            for (i=0; g_cReceBuf[i] != 0; i++)
            {
                // ��λ����
                if ((g_cReceBuf[i]>>4) < 10)
                    tempData[j++] = (g_cReceBuf[i]>>4) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i]>>4) - 10 + 'A';
                
                // ��λ����
                if ((g_cReceBuf[i]&0xf) < 10)
                    tempData[j++] = (g_cReceBuf[i]&0xf) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i]&0xf) - 10 + 'A';
            }
            if (strcmp(lastCardCode, tempData) != 0)
            {
                strcpy(lastCardCode, tempData);
                Puts_to_SerialPort("ISO14443B:");
                Puts_to_SerialPort(tempData);
                Puts_to_SerialPort("\r\n");
                
                // ���ԭ������
                OLED_ShowString(0, 0, "          ");
                OLED_ShowString(0, 2, "                ");
                OLED_ShowString(0, 4, "                ");
                
                OLED_ShowString(0, 0, "ISO14443B:");
                OLED_ShowString(0, 2, tempData);
                
                BEEP = 0;
                DelayMs(100);
                BEEP = 1;
            }
            TimerCount = 0;
            clsFlag = 0;
        }
	}
	else
	{
		//Puts_to_SerialPort("Fail ComTypeBRst...");
	}
}

/////////////////////////////////////////////////////////////////////
//��Ӧ��λ��ISO15693_Inventory����
/////////////////////////////////////////////////////////////////////
void ComISO15693_Inventory16()
{
    int i=0, j=0;
    unsigned char tempData[32] = {0};   // ����ת����Ŀ���
	if (MI_OK == ISO15693_Inventory16(0x16, 0x00, 0x00, &g_cReceBuf[0], &g_cReceBuf[0], &g_cReceBuf[1]))
	{
        //Putc_to_SerialPort(g_cReceBuf[0]);
        for (i=0; i<g_cReceBuf[0]; i++)
        {
            if (i%2 == 0)
            {
                if ((g_cReceBuf[i+1]>>4) < 10)
                    tempData[j++] = (g_cReceBuf[i+1]>>4) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i+1]>>4) - 10 + 'A';
            }
            else
            {
                if ((g_cReceBuf[i+1]&0xf) < 10)
                    tempData[j++] = (g_cReceBuf[i+1]&0xf) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i+1]&0xf) - 10 + 'A';
            }
        }
        if (g_cReceBuf[0] != 0)
        {
            if (strcmp(lastCardCode, tempData) != 0)
            {
                strcpy(lastCardCode, tempData);
                Puts_to_SerialPort("ISO15693:");
                Puts_to_SerialPort(tempData);
                Puts_to_SerialPort("\r\n");
                
                // ���ԭ������
                OLED_ShowString(0, 0, "          ");
                OLED_ShowString(0, 2, "                ");
                OLED_ShowString(0, 4, "                ");
                
                OLED_ShowString(0, 0, "ISO15693: ");
                OLED_ShowString(0, 2, tempData);
                
                BEEP = 0;
                DelayMs(100);
                BEEP = 1;
            }
            TimerCount = 0;
            clsFlag = 0;
        }
	}
	else
	{
		//Puts_to_SerialPort("Fail ComISO15693_Inventory16...");
	}
}

/////////////////////////////////////////////////////////////////////
//��Ӧ��λ��ISO15693_Inventory����
/////////////////////////////////////////////////////////////////////
void ComISO15693_Inventory()
{
    int i=0, j=0;
    unsigned char tempData[32] = {0};   // ����ת����Ŀ���
	if (MI_OK == ISO15693_Inventory(0x36, 0x00, 0x00, &g_cReceBuf[0], &g_cReceBuf[0]))
	{
        //Putc_to_SerialPort(g_cReceBuf[0]);
        for (i=0; i<g_cReceBuf[0]; i++)
        {
            if (i%2 == 0)
            {
                if ((g_cReceBuf[i+1]>>4) < 10)
                    tempData[j++] = (g_cReceBuf[i+1]>>4) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i+1]>>4) - 10 + 'A';
            }
            else
            {
                if ((g_cReceBuf[i+1]&0xf) < 10)
                    tempData[j++] = (g_cReceBuf[i+1]&0xf) + '0';
                else
                    tempData[j++] = (g_cReceBuf[i+1]&0xf) - 10 + 'A';
            }
        }
        if (g_cReceBuf[0] != 0)
        {
            if (strcmp(lastCardCode, tempData) != 0)
            {
                strcpy(lastCardCode, tempData);
                Puts_to_SerialPort("ISO15693:");
                Puts_to_SerialPort(tempData);
                Puts_to_SerialPort("\r\n");
                
                // ���ԭ������
                OLED_ShowString(0, 0, "          ");
                OLED_ShowString(0, 2, "                ");
                OLED_ShowString(0, 4, "                ");
                
                OLED_ShowString(0, 0, "ISO15693: ");
                OLED_ShowString(0, 2, tempData);
                
                BEEP = 0;
                DelayMs(100);
                BEEP = 1;
            }
            TimerCount = 0;
            clsFlag = 0;
        }
	}
	else
	{
        //Puts_to_SerialPort("Fail ComISO15693_Inventory...");
	}
}

// ������
void main()
{
	InitUART();
    OLED_Init();
    InitTimer0();
    
    showPower();
    
    //while(1);
    
    Rc632Ready();
    
    PcdConfigISOType('A');
    
    ComGetHardModel();
    
    while (1)
    {
        // A��
        g_cReceBuf[6]='A';
        ComM632PcdConfigISOType();
        g_cReceBuf[6]=0x52;
        ComRequestA();
        ComAnticoll();
        DelayMs(10);
        
        // B��
        g_cReceBuf[6]='B';
        ComM632PcdConfigISOType();
        g_cReceBuf[6]=0x01;
        ComTypeBRst();
        DelayMs(10);
        
        // ISO15693
        g_cReceBuf[6]='l';
        ComM632PcdConfigISOType();
        ComISO15693_Inventory16();
        ComISO15693_Inventory();
        DelayMs(10);
        
        if ((clsFlag == 1) && (lastCardCode[0] != 0))
        {
            OLED_Clear();
            showPower();
            OLED_ShowTitleChinese();
            clsFlag = 0;
            lastCardCode[0] = 0;
        }
    }
}
