#ifndef __UART_H__
#define __UART_H__

#include "PUBLIC.h"

void Putc_to_SerialPort(uchar c);   // �򴮿ڷ����ַ�
void Puts_to_SerialPort(uchar *s);  // �򴮿ڷ����ַ���
void InitUART();    // ��ʼ������

#endif