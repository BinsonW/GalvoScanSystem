/********************************************************************
	created:	2005/10/18
	created:	18:10:2005   11:50
	filename: 	ETH0416Sapi.h
	author:		
	
	purpose:	DLL
*********************************************************************/


#if !defined(_ETH0416SAPI_H_)
#define _ETH0416SAPI_H_


#include "winsock.h"

#define  U32 unsigned int
#define  u16 unsigned short




//! GET the status of 16 DINs (digital inputs of ETH0416S)
extern "C"  int __stdcall ETH0416S_GetDin(unsigned int *pIValue);


//! ͬʱ����IP��ַ��MAC��ַ
extern "C"  int __stdcall ETH0416S_SetIP(char ip[],char mac[]);



//!���ܣ���λλ�ü���
//!      ��ָ�����λ�ü���ֵ��0
//!       
//!       
//!������
//!		axis�����
//!����ֵ��
//!       
//!        					   
//!     
extern "C"  int __stdcall   Cen_resetCount_B(u16 axis,unsigned char CntOrEncoder)	;



//!���ܣ����ü���
//!      ����ָ����ļ���ֵ
//!       
//!       
//!������
//!		axis�����
//!     CntOrEncoder: 0--����������� 1������������
//!     ValueSet: �趨�����嵥λֵ����������
//!����ֵ��
//!       -1���������
//!       0 ���ɹ� 					   
//!         
extern "C"   int __stdcall  Cen_SetCount_B(u16 axis,unsigned char CntOrEncoder,int ValueSet);



// ���IO��bitnoȡֵ1-19
extern "C"  int __stdcall  Cen_writeOutbit_B (char bitno,char on_off);



// ����IO��bitnoȡֵ1-16
extern "C"  char __stdcall Cen_readInbit_C(char bitno) ;




//!���ܣ���ȡ��ǰλ�ü�����
//!       ��ȡָ�����λ��ֵ
//!       
//!       
//!������
//!		axis�����
//!		posCntOrEncoder��0����ֵ��1����������ֵ
//!     iReadResult,����ֵָ��
//!����ֵ��
//!       -1,�������
//!        0,�ɹ�
//!           
extern "C"   int __stdcall Cen_readCount_C(u16 axis,unsigned char posCntOrEncoder,int *iReadResult)	;



//!���ܣ���ȡִ�е�״̬��ָ���Ƿ�ִ�����
//!       
//!       
//!������
//!����ֵ��1 ��ʾ��Ӧ����������ϣ���ֹͣ״̬
//!        0 ��ʾ��Ӧ��������������״̬
//!        -1��ʾ����	
extern "C"   int __stdcall Cen_checkDone_C();






// ����ָ��IP��ַ�Ŀ�����
// pStrIP:  IP��ַ�ַ���
extern "C"   int __stdcall ETH0416S_EthCardInitIP(char *pStrIP);

// �ر�ָ�������������ӣ�
// sn:���ӱ��
extern "C"  int __stdcall ETH0416S_CloseConn(int sn);

// �ر����п����������ӣ�
extern "C"  int __stdcall ETH0416S_CloseAll();

// �趨ָ����ŵĿ�����Ϊ��ǰ����������
// sn:���ӱ��
extern "C"  int __stdcall ETH0416S_SetCurrentCard(int sn);

// �ɹ�����0��   ȡ�õ�IP�洢�� char *ip�У��洢�ռ����30
// ʧ�ܷ���-1
extern "C"  int __stdcall ETH0416S_GetCardIP(int sn,char *ip);


//!���ܣ������岹 ֮ǰ���ò���      -------A��api����װB��API��
//!������
//!		fJc_dev�����������0.1-0.9֮�䣬һ���0.2
//!     ppmm, ָ�룬8�����嵱����short���ͣ���λp/mm
//!     acc, ָ�룬8�����ٶ�/���ٶȣ�int���ͣ���λmm/min^2
//!����ֵ��
//!        0 ��ʾ�ɹ�
//!        2 ��ʾ���������
extern "C"  int __stdcall   Cen_MultiExeConfig_A(float fJc_dev,short * ppmm,int *acc);

typedef struct _FifoCmd 
{// �ܳ���26�ֽ�

	unsigned int cmd;

//	 short cmdID;// 1,pos ָ��
//	 short cmdPara[6];// ���������posָ���ʱ�򣬷ֱ���4�����delta �������
}FifoCmd;

//!���ܣ�����λ��FIFO����cmdָ�һ����෢��70��ָ�   -------B��api��ֱ�Ӳ������ƿ���
//       ��λ��fifo�ռ�1999����
//!������
//!		FifoCmd *pCmd    //ָ������
//!     int Cnt          //ָ�����,���һ��70��
//!     char * pFifoStatus       //fifo״̬,�ܹ�13���ֽڣ�1char+3int 
//!             pFifoStatus[0]:   0δִ�� , 1ִ����
//!             pFifoStatus[1-4]:  ��λ���洢��ָ�����
//!             pFifoStatus[5-8]:  ʣ��洢�ռ���и���
//!             pFifoStatus[9-12]: Ԥ��
//!����ֵ��
//!        0 ��ʾ�ɹ�
//!        -1 ��ʾͨ�ų���
extern "C"  int __stdcall   Cen_pushFifo_B(FifoCmd *pCmd, int Cnt, char * pFifoStatus);



//!���ܣ�����λ��fifo����/״̬��ѯ  ָ��   -------B��api��ֱ�Ӳ������ƿ���
//     ��λ��fifo���Դ洢��ָ�����1999��
//!������
//!		unsigned short ConCmd   //fifo����ָ�0ֹͣ��1ִ�У�2��գ�3��ѯfifo״̬
//!     char * pFifoStatus       //fifo״̬,�ܹ�13���ֽڣ�1char+3int 
//!             pFifoStatus[0]:   0δִ�� , 1ִ����
//!             pFifoStatus[1-4]:  ��λ���洢��ָ�����
//!             pFifoStatus[5-8]:  ʣ��洢�ռ���и���
//!             pFifoStatus[9-12]: Ԥ��
//!����ֵ��
//!        0 ��ʾ�ɹ�
//!        -1 ��ʾͨ�ų���
extern "C"  int __stdcall   Cen_FifoCtrl_B(unsigned short ConCmd, char * pFifoStatus);







//!���ܣ���ȡDLL ��FIFO ����״̬-------A��api����װB��API��
//!       
//!       
//!������
//!		axis�����
//!����ֵ��0 ��ʾFIFO����
//!        1 ��ʾFIFO���ڹ���������λ�����������
//!        -1��ʾ����					   
//!         
extern "C"   int __stdcall Cen_DllFifoBusy_A();




//!���ܣ�push cmd���ݵ���λ��DLL�е�fifo��DLL�е��߳�ͬʱ����λ�����Ͳ�ִ��-------A��api����װB��API��
//!      ��λ�����һ�λ���ִ��200����
//!      ��λ��fifo�ռ�2000��
//!      ��λ������λ��һ����෢��70��cmd
//!������
//!		FifoCmd *pCmdwork��  ָ��ָ��
//!		int pushCnt���������
//!����ֵ��
//!        0 ��ʾ�ɹ�
//!        1 ��ʾposi_mode����
//!        2 ��ʾ���������
extern "C"  int __stdcall   Cen_pushDllFifo_A(FifoCmd *pCmdwork,int pushCnt) ;

//typedef struct _pt4axis
//{// �����飬C#���ò���
//	//float pos[4];// mmΪ��λ�ľ�������λ��
//	float pos; 
//	float pos1;
//	float pos2;
//	float pos3;
//} PT4axis;

typedef struct _pt4axis
{// �����飬C#���ò���
	//float pos[4];// mmΪ��λ�ľ�������λ��
	float pos; 
	float pos1;
	float pos2;
	float pos3;

	// bit[31-24]--��8λ��Y��λ����
	//                    0����Ч,������Y������Ҳ����ʱ��
	//                    1��Y8-Y1ֵA��
	//                    2��Y8-Y1ֵA��delay��Y8-Y1ֵB��
	//                    3��delay��
	//bit[15-8]--8λ��   ��Y8-Y1ֵB��
	//bit[7- 0]--8λ��  ��Y8-Y1ֵA��
	UINT CmdYiDelay;

	UINT YiDelay; // ��ʱ��us��λ
} PT4axis;



#endif
