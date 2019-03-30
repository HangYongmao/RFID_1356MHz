#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#include <reg52.h>

#define uchar unsigned char
#define uint  unsigned int

//ָ��PCD���ջ���ֵ
#ifndef FSDI
#define FSDI 4
#endif

// �˿ڶ���
// RC632
sbit RC632_NSS  = P2 ^ 0;   //оƬʹ��ѡ��
sbit RC632_SCK  = P2 ^ 1;   //ʱ���ź�
sbit RC632_MOSI = P2 ^ 2;   //��������
sbit RC632_MISO = P2 ^ 3;   //�������
sbit RC632_RST  = P2 ^ 4;   //RC500ALE
sbit RC632_CE   = P2 ^ 5;   //RC500Ƭѡ

// OLED
sbit OLED_SCL  = P3 ^ 7;	// ʱ�� D0��SCLK��
sbit OLED_SDIN = P3 ^ 6;	// D1��MOSI�� ����
sbit OLED_RST  = P3 ^ 5;	// ��λ
sbit OLED_DC   = P3 ^ 4;	// ����/�������
sbit OLED_CS   = P3 ^ 3; 	// Ƭѡ

// ������
sbit BEEP = P3 ^ 2;

// LED
sfr LED = 0x90; // P1

void DelayMs(uint ms);  // ��ʱ ms

void Delay_50us(unsigned char _50us); //us

#endif
