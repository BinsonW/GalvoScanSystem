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


//! 同时设置IP地址和MAC地址
extern "C"  int __stdcall ETH0416S_SetIP(char ip[],char mac[]);



//!功能：复位位置计数
//!      将指定轴的位置计数值清0
//!       
//!       
//!参数：
//!		axis：轴号
//!返回值：
//!       
//!        					   
//!     
extern "C"  int __stdcall   Cen_resetCount_B(u16 axis,unsigned char CntOrEncoder)	;



//!功能：设置计数
//!      设置指定轴的计数值
//!       
//!       
//!参数：
//!		axis：轴号
//!     CntOrEncoder: 0--脉冲计数器， 1编码器计数器
//!     ValueSet: 设定的脉冲单位值，可以正负
//!返回值：
//!       -1，网络错误
//!       0 ，成功 					   
//!         
extern "C"   int __stdcall  Cen_SetCount_B(u16 axis,unsigned char CntOrEncoder,int ValueSet);



// 输出IO，bitno取值1-19
extern "C"  int __stdcall  Cen_writeOutbit_B (char bitno,char on_off);



// 输入IO，bitno取值1-16
extern "C"  char __stdcall Cen_readInbit_C(char bitno) ;




//!功能：读取当前位置计数器
//!       读取指定轴的位置值
//!       
//!       
//!参数：
//!		axis：轴号
//!		posCntOrEncoder：0计数值，1编码器返回值
//!     iReadResult,返回值指针
//!返回值：
//!       -1,网络错误
//!        0,成功
//!           
extern "C"   int __stdcall Cen_readCount_C(u16 axis,unsigned char posCntOrEncoder,int *iReadResult)	;



//!功能：获取执行的状态，指令是否执行完成
//!       
//!       
//!参数：
//!返回值：1 表示对应的轴运行完毕，在停止状态
//!        0 表示对应的轴正处在运行状态
//!        -1表示错误	
extern "C"   int __stdcall Cen_checkDone_C();






// 连接指定IP地址的控制器
// pStrIP:  IP地址字符串
extern "C"   int __stdcall ETH0416S_EthCardInitIP(char *pStrIP);

// 关闭指定控制器的连接，
// sn:连接编号
extern "C"  int __stdcall ETH0416S_CloseConn(int sn);

// 关闭所有控制器的连接，
extern "C"  int __stdcall ETH0416S_CloseAll();

// 设定指定编号的控制器为当前操作控制器
// sn:连接编号
extern "C"  int __stdcall ETH0416S_SetCurrentCard(int sn);

// 成功返回0，   取得的IP存储在 char *ip中，存储空间大于30
// 失败返回-1
extern "C"  int __stdcall ETH0416S_GetCardIP(int sn,char *ip);


//!功能：连续插补 之前配置参数      -------A类api（封装B类API）
//!参数：
//!		fJc_dev，拐弯参数：0.1-0.9之间，一般给0.2
//!     ppmm, 指针，8个脉冲当量，short类型，单位p/mm
//!     acc, 指针，8个加速度/减速度，int类型，单位mm/min^2
//!返回值：
//!        0 表示成功
//!        2 表示轴参数错误
extern "C"  int __stdcall   Cen_MultiExeConfig_A(float fJc_dev,short * ppmm,int *acc);

typedef struct _FifoCmd 
{// 总长度26字节

	unsigned int cmd;

//	 short cmdID;// 1,pos 指令
//	 short cmdPara[6];// 命令参数，pos指令的时候，分别是4个轴的delta 脉冲分量
}FifoCmd;

//!功能：往下位机FIFO发送cmd指令，一次最多发送70个指令，   -------B类api（直接操作控制卡）
//       下位机fifo空间1999个，
//!参数：
//!		FifoCmd *pCmd    //指向数据
//!     int Cnt          //指令个数,最多一次70个
//!     char * pFifoStatus       //fifo状态,总共13个字节，1char+3int 
//!             pFifoStatus[0]:   0未执行 , 1执行中
//!             pFifoStatus[1-4]:  下位机存储有指令个数
//!             pFifoStatus[5-8]:  剩余存储空间空闲个数
//!             pFifoStatus[9-12]: 预留
//!返回值：
//!        0 表示成功
//!        -1 表示通信出错
extern "C"  int __stdcall   Cen_pushFifo_B(FifoCmd *pCmd, int Cnt, char * pFifoStatus);



//!功能：对下位机fifo控制/状态查询  指令   -------B类api（直接操作控制卡）
//     下位机fifo可以存储的指令最多1999个
//!参数：
//!		unsigned short ConCmd   //fifo操作指令，0停止，1执行，2清空，3查询fifo状态
//!     char * pFifoStatus       //fifo状态,总共13个字节，1char+3int 
//!             pFifoStatus[0]:   0未执行 , 1执行中
//!             pFifoStatus[1-4]:  下位机存储有指令个数
//!             pFifoStatus[5-8]:  剩余存储空间空闲个数
//!             pFifoStatus[9-12]: 预留
//!返回值：
//!        0 表示成功
//!        -1 表示通信出错
extern "C"  int __stdcall   Cen_FifoCtrl_B(unsigned short ConCmd, char * pFifoStatus);







//!功能：获取DLL 中FIFO 工作状态-------A类api（封装B类API）
//!       
//!       
//!参数：
//!		axis：轴号
//!返回值：0 表示FIFO空闲
//!        1 表示FIFO正在工作，往下位机填充数据中
//!        -1表示错误					   
//!         
extern "C"   int __stdcall Cen_DllFifoBusy_A();




//!功能：push cmd数据到上位机DLL中的fifo，DLL中的线程同时往下位机发送并执行-------A类api（封装B类API）
//!      上位机最多一次缓存执行200万条
//!      下位机fifo空间2000条
//!      上位机往下位机一次最多发送70条cmd
//!参数：
//!		FifoCmd *pCmdwork：  指针指向
//!		int pushCnt：命令个数
//!返回值：
//!        0 表示成功
//!        1 表示posi_mode错误
//!        2 表示轴参数错误
extern "C"  int __stdcall   Cen_pushDllFifo_A(FifoCmd *pCmdwork,int pushCnt) ;

//typedef struct _pt4axis
//{// 用数组，C#调用不了
//	//float pos[4];// mm为单位的绝对坐标位置
//	float pos; 
//	float pos1;
//	float pos2;
//	float pos3;
//} PT4axis;

typedef struct _pt4axis
{// 用数组，C#调用不了
	//float pos[4];// mm为单位的绝对坐标位置
	float pos; 
	float pos1;
	float pos2;
	float pos3;

	// bit[31-24]--高8位，Y点位属性
	//                    0（无效,即不做Y动作，也不延时）
	//                    1（Y8-Y1值A）
	//                    2（Y8-Y1值A，delay，Y8-Y1值B）
	//                    3（delay）
	//bit[15-8]--8位，   （Y8-Y1值B）
	//bit[7- 0]--8位，  （Y8-Y1值A）
	UINT CmdYiDelay;

	UINT YiDelay; // 延时用us单位
} PT4axis;



#endif
