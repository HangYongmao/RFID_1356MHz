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
sbit RC632_NSS  = P3 ^ 2;   //оƬʹ��ѡ��
sbit RC632_SCK  = P3 ^ 3;   //ʱ���ź�
sbit RC632_MOSI = P3 ^ 4;   //��������
sbit RC632_MISO = P3 ^ 5;   //�������
sbit RC632_RST  = P3 ^ 6;   //RC500ALE
sbit RC632_CE   = P3 ^ 7;   //RC500Ƭѡ

// OLED
sbit OLED_SCL  = P2 ^ 4;	// ʱ�� D0��SCLK��
sbit OLED_SDIN = P2 ^ 3;	// D1��MOSI�� ����
sbit OLED_RST  = P2 ^ 2;	// ��λ
sbit OLED_DC   = P2 ^ 1;	// ����/�������
sbit OLED_CS   = P2 ^ 0; 	// Ƭѡ

// ������
sbit BEEP = P2 ^ 5;

// LED
sfr LED = 0x90; // P1

void DelayMs(uint ms);  // ��ʱ ms

void Delay_50us(unsigned char _50us); //us

#endif
