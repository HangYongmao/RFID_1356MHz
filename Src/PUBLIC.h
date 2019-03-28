#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int

// �˿ڶ���
sbit RC632_CE   = P2 ^ 7;   //RC500Ƭѡ
sbit RC632_RST  = P3 ^ 3;   //RC500ALE
sbit RC632_SCK  = P1 ^ 0;   //ʱ���ź�
sbit RC632_MOSI = P1 ^ 1;   //��������
sbit RC632_MISO = P1 ^ 2;   //�������
sbit RC632_NSS  = P1 ^ 3;   //оƬʹ��ѡ��

void DelayMs(uint ms);  // ��ʱ ms

void Delay_50us(unsigned char _50us); //us

#endif
