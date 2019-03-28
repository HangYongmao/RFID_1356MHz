#ifndef __CLRC632_H__
#define __CLRC632_H__

#include <reg52.h>

/////////////////////////////////////////////////////////////////////
//����ԭ��
/////////////////////////////////////////////////////////////////////
//��λRC632

char PcdReset();

//����RC632�Ĺ�����ʽ    
char PcdConfigISOType(unsigned char type);

//��RC632-EEPROM����
extern char PcdReadE2(unsigned int startaddr, unsigned char length, unsigned char *readdata);

//д���ݵ�RC632-EEPROM               
extern char PcdWriteE2(unsigned int startaddr, unsigned char length, unsigned char *writedata);

//����RC632���߷��� 
char PcdAntennaOn();

//�ر�RC632���߷���                                         
char PcdAntennaOff();

//дRC632�Ĵ���
void WriteRawRC(unsigned char Address, unsigned char value);

//��RC632�Ĵ���                     
unsigned char ReadRawRC(unsigned char Address);

//��RC632�Ĵ���λ                                
void SetBitMask(unsigned char reg, unsigned char mask);

//��RC632�Ĵ���λ                         
void ClearBitMask(unsigned char reg, unsigned char mask);

//����RC632��ʱ��                       
void PcdSetTmo(unsigned char tmoLength);

//ISO14443ͨѶ����
char PcdComTransceive(struct TranSciveBuffer *pi);

//ISO15693ͨѶ����              
char ISO15693_Transceive(struct TranSciveBuffer *pi);


/////////////////////////////////////////////////////////////////////
//RC632������
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //ȡ����ǰ����
#define PCD_WRITEE2           0x01               //дEEPROM
#define PCD_READE2            0x03               //��EEPROM
#define PCD_LOADCONFIG        0x07               //��EEPROM�б���ļĴ�������
#define PCD_LOADKEYE2         0x0B               //��EEPROM�б������Կ���뻺��
#define PCD_AUTHENT1          0x0C               //��֤��Կ��һ��
#define PCD_AUTHENT2          0x14               //��֤��Կ�ڶ���
#define PCD_RECEIVE           0x16               //��������
#define PCD_LOADKEY           0x19               //������Կ
#define PCD_TRANSMIT          0x1A               //��������
#define PCD_TRANSCEIVE        0x1E               //��������
#define PCD_RESETPHASE        0x3F               //��λ
#define PCD_CALCCRC           0x12               //CRC����

/////////////////////////////////////////////////////////////////////
//RC632 FIFO���ȶ���
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte

//clrc632��ؼĴ����Ķ���
/////////////////////////////////////////////////////////////////////
//RC632�Ĵ�������
/////////////////////////////////////////////////////////////////////
// PAGE 0//����ҳ�ļĴ���
#define     RegPage               0x00 //ҳ��ѡ��Ĵ���   
#define     RegCommand            0x01 //������ִֹͣ������   
#define     RegFIFOData           0x02  //���������64λ����Ĵ��� 
#define     RegPrimaryStatus      0x03  //���գ����ͣ�fifo��־�Ĵ��� 
#define     RegFIFOLength         0x04   //FIFO���������ֽڳ���
#define     RegSecondaryStatus    0x05   //�μ�״̬�Ĵ���
#define     RegInterruptEn        0x06 //���û�����жϿ���λ
#define     RegInterruptRq        0x07  //�ж������־  
// PAGE 1      Control and Status//��һҳ�Ĵ���
#define     PageSe                0x08   //ѡ��ҳ��Ĵ��� 
#define     RegControl            0x09   //��ʱ����Ԫ�Ŀ��Ʊ�־ 
#define     RegErrorFlag          0x0A  //����״̬
#define     RegCollpos            0x0B  //RF��⵽�ĵ�һ�����ص�λ��
#define     RegTimerValue         0x0C//��ʱ����ֵ
#define     RegCRCResultLSB       0x0D  //Э����Ĵ���LSB
#define     RegCRCResultMSB       0x0E  //Э����Ĵ���MSB
#define     RegBitFraming         0x0F //��������λ��֡
// PAGE 2      Transmitter and Coder Control//�ڶ�ҳ�Ĵ�����ַ
#define     PageSe2               0x10  //ѡ��ҳ
#define     RegTxControl          0x11 //������������������
#define     RegCwConductance      0x12  //ѡ���������������ŵ絼
#define     RegModConductance     0x13 //����������������絼
#define     RegCoderControl       0x14  //����ʱ��Ƶ�ʺͱ���
#define     RegModWidth           0x15   //ѡ�����������
#define     RegModWidthSOF        0x16   //ѡ��SOF�������
#define     RegTypeBFraming       0x17    //����14443Bͨ��֡
// PAGE 3      Receiver and Decoder Control ����ҳ�Ĵ���
#define     PageSe3               0x18   //ѡ��Ĵ���
#define     RegRxControl1         0x19   //���ƽ���������Ϊ
#define     RegDecoderControl     0x1A   //���ƽ������Ϊ
#define     RegBitPhase           0x1B   //ѡ�������������֮�����λ
#define     RegRxThreshold        0x1C   //Ϊλ������ѡ����ֵ
#define     RegBPSKDemControl     0x1D   //����BPSK����������Ϊ
#define     RegRxControl2         0x1E   //���ƽ��������������������Դ
#define     RegClockQControl      0x1F   //ʱ�ӿ���90��λQͨ��ʱ��
// PAGE 4      RF-Timing and Channel Redundancy ����ҳ�ļĴ���
#define     PageSe4               0x20   //ҳѡ��
#define     RegRxWait             0x21   //�ڽ��ջ�����֮ǰѡ����֮��ļ�϶
#define     RegChannelRedundancy  0x22   //ѡ�����ڼ���������������Է�����ģʽ��ƵƵ��
#define     RegCRCPresetLSB       0x23   //Ԥ��LSB��ֵ
#define     RegCRCPresetMSB       0x24   //Ԥ��MSB��ֵ
#define     RegTimeSlotPeriod     0x25    //ѡ���Զ�����֮֡���ʱ��
#define     RegMfOutSelect        0x26   //ѡ��ʩ�ӵ��ڲ��ź�
#define     RFU27                 0x27   //������ֵ
// PAGE 5      FIFO, Timer and IRQ-Pin Configuration ����ҳ�Ĵ���
#define     PageSe5               0x28  //ѡ��ҳ
#define     RegFIFOLevel          0x29   //��������ļ���
#define     RegTimerClock         0x2A   //ѡ��ʱ����ʱ�ӷ�Ƶ��
#define     RegTimerControl       0x2B  //ѡ��ʱ��������ֹͣ����
#define     RegTimerReload        0x2C  //���嶨ʱ����Ԥ��ֵ
#define     RegIRqPinConfig       0x2D  //��������IRQ�����
#define     RFU2E                 0x2E  //ֵ����
#define     RFU2F                 0x2F  //ֵ����
// PAGE 6      RFU ����ҳ�Ĵ���
#define     RFU31                 0x31  //����δ����
#define     RFU32                 0x32
#define     RFU33                 0x33
#define     RFU34                 0x34
#define     RFU35                 0x35
#define     RFU36                 0x36
#define     RFU37                 0x37
// PAGE 7      Test Control
#define     RFU39                 0x39  
#define     RegTestAnaSelect      0x3A   
#define     RFU3B                 0x3B   
#define     RFU3C                 0x3C   
#define     RegTestDigiSelect     0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		          0x3F


/////////////////////////////////////////////////////////////////////
//��RC632ͨѶʱ���صĴ������
/////////////////////////////////////////////////////////////////////
#define MI_OK                          0
#define MI_CHK_OK                      0

#define MI_NOTAGERR                    (-1)
#define MI_CHK_FAILED                  (-1)
#define MI_CRCERR                      (-2)
#define MI_CHK_COMPERR                 (-2)
#define MI_EMPTY                       (-3)
#define MI_AUTHERR                     (-4)
#define MI_PARITYERR                   (-5)
#define MI_CODEERR                     (-6)
#define MI_SERNRERR                    (-8)
#define MI_KEYERR                      (-9)
#define MI_NOTAUTHERR                  (-10)
#define MI_BITCOUNTERR                 (-11)
#define MI_BYTECOUNTERR                (-12)
#define MI_IDLE                        (-13)
#define MI_TRANSERR                    (-14)
#define MI_WRITEERR                    (-15)
#define MI_INCRERR                     (-16)
#define MI_DECRERR                     (-17)
#define MI_READERR                     (-18)
#define MI_OVFLERR                     (-19)
#define MI_POLLING                     (-20)
#define MI_FRAMINGERR                  (-21)
#define MI_ACCESSERR                   (-22)
#define MI_UNKNOWN_COMMAND             (-23)
#define MI_COLLERR                     (-24)
#define MI_RESETERR                    (-25)
#define MI_INITERR                     (-25)
#define MI_INTERFACEERR                (-26)
#define MI_ACCESSTIMEOUT               (-27)
#define MI_NOBITWISEANTICOLL           (-28)
#define MI_QUIT                        (-30)
#define MI_RECBUF_OVERFLOW             (-50)
#define MI_SENDBYTENR                  (-51)
#define MI_SENDBUF_OVERFLOW            (-53)
#define MI_BAUDRATE_NOT_SUPPORTED      (-54)
#define MI_SAME_BAUDRATE_REQUIRED      (-55)
#define MI_WRONG_PARAMETER_VALUE       (-60)
#define MI_BREAK                       (-99)
#define MI_NY_IMPLEMENTED              (-100)
#define MI_NO_MFRC                     (-101)
#define MI_MFRC_NOTAUTH                (-102)
#define MI_WRONG_DES_MODE              (-103)
#define MI_HOST_AUTH_FAILED            (-104)
#define MI_WRONG_LOAD_MODE             (-106)
#define MI_WRONG_DESKEY                (-107)
#define MI_MKLOAD_FAILED               (-108)
#define MI_FIFOERR                     (-109)
#define MI_WRONG_ADDR                  (-110)
#define MI_DESKEYLOAD_FAILED           (-111)
#define MI_WRONG_SEL_CNT               (-114)
#define MI_WRONG_TEST_MODE             (-117)
#define MI_TEST_FAILED                 (-118)
#define MI_TOC_ERROR                   (-119)
#define MI_COMM_ABORT                  (-120)
#define MI_INVALID_BASE                (-121)
#define MI_MFRC_RESET                  (-122)
#define MI_WRONG_VALUE                 (-123)
#define MI_VALERR                      (-124)
#define MI_COM_ERR                     (-125)

#endif