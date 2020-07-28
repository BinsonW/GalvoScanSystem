; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMotionPanel
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ETH0416S_panel.h"

ClassCount=4
Class1=CETH0416S_panelApp
Class2=CETH0416S_panelDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ETH0416S_panel_DIALOG
Class3=CMotionPanel
Resource3=IDD_DIALOG1
Class4=CDialogParameters
Resource4=IDD_DIALOG_PARAMETERS

[CLS:CETH0416S_panelApp]
Type=0
HeaderFile=ETH0416S_panel.h
ImplementationFile=ETH0416S_panel.cpp
Filter=N

[CLS:CETH0416S_panelDlg]
Type=0
HeaderFile=ETH0416S_panelDlg.h
ImplementationFile=ETH0416S_panelDlg.cpp
Filter=D
LastObject=CETH0416S_panelDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_ETH0416S_panel_DIALOG]
Type=1
Class=CETH0416S_panelDlg
ControlCount=76
Control1=IDC_BUTTON_DASET,button,1073807360
Control2=IDC_STATIC,button,1073741831
Control3=IDC_BUTTON_DOSET,button,1073807360
Control4=IDC_STATIC,static,1073872896
Control5=IDC_STATIC,button,1073741831
Control6=IDC_EDIT_DA1,edit,1082196096
Control7=IDC_STATIC,static,1073872896
Control8=IDC_STATIC,static,1073872896
Control9=IDC_EDIT_DONUM,edit,1082196096
Control10=IDC_STATIC,static,1073872896
Control11=IDC_EDIT_DA2,edit,1082196096
Control12=IDC_STATIC,static,1073872896
Control13=IDC_STATIC,static,1073872896
Control14=IDC_EDIT_DOVALUE,edit,1082196096
Control15=IDC_EDIT_DA3,edit,1082196096
Control16=IDC_STATIC,static,1073872896
Control17=IDC_EDIT_DA4,edit,1082196096
Control18=IDC_STATIC,static,1073872896
Control19=IDC_STATIC,button,1073741831
Control20=IDC_STATIC,button,1073741831
Control21=IDC_STATIC,static,1073872896
Control22=IDC_STATIC,static,1073872896
Control23=IDC_BUTTON_DINGET,button,1073807360
Control24=IDC_STATIC,button,1073741831
Control25=IDC_STATIC,static,1073872896
Control26=IDC_BUTTON_LIMITGET,button,1073807360
Control27=IDC_STATIC,static,1073872896
Control28=IDC_BUTTON_PULSEOUT,button,1073807360
Control29=IDC_STATIC,button,1073741831
Control30=IDC_STATIC,static,1073872896
Control31=IDC_EDIT_PULSEDONUM,edit,1082196096
Control32=IDC_STATIC,static,1073872896
Control33=IDC_EDIT_PULSE_CYCLE,edit,1082196096
Control34=IDC_STATIC,static,1073872896
Control35=IDC_STATIC,static,1073872896
Control36=IDC_STATIC,static,1073872896
Control37=IDC_EDIT_PULSE_AMOUNT,edit,1082196096
Control38=IDC_BUTTON_PWMOUT,button,1073807360
Control39=IDC_BUTTON_PWMLCOSE,button,1073807360
Control40=IDC_STATIC,button,1073741831
Control41=IDC_BUTTON_GETSTATUS,button,1073807360
Control42=IDC_BUTTON_STOP,button,1073807360
Control43=IDC_BUTTONTEST_GETIN,button,1073807360
Control44=IDC_BUTTON_RED,button,1073807360
Control45=IDC_CHECK_10NS_UNIT,button,1073807395
Control46=IDC_EDIT_PWM_HGHI_LEVEL,edit,1082196096
Control47=IDC_STATIC,static,1073872896
Control48=IDC_STATIC,static,1073872896
Control49=IDC_EDIT_PWM_FREQ,edit,1082196096
Control50=IDC_STATIC,static,1073872896
Control51=IDC_STATIC,static,1073872896
Control52=IDC_STATIC,static,1073872896
Control53=IDC_BUTTON_SET_IP,button,1073807360
Control54=IDC_STATIC,static,1073872896
Control55=IDC_IPADDRESS1,SysIPAddress32,1073807360
Control56=IDC_EDIT_DA5,edit,1082196096
Control57=IDC_STATIC,static,1073872896
Control58=IDC_STATIC,static,1073872896
Control59=IDC_EDIT_DA6,edit,1082196096
Control60=IDC_BUTTON2,button,1073807360
Control61=IDC_BUTTON_DA_DELAY,button,1073807360
Control62=IDC_STATIC,button,1073741831
Control63=IDC_BUTTON_DA45535,button,1073807360
Control64=IDC_BUTTON_DOSET_ALL0,button,1073807360
Control65=IDC_BUTTON_DOSET_ALL1,button,1073807360
Control66=IDC_BUTTON_DA_0,button,1073807360
Control67=IDC_BUTTON_KAOJI,button,1073807360
Control68=IDC_BUTTON_DA_DELAY4,button,1073807360
Control69=IDC_EDIT_PULSEDONUM2,edit,1082196096
Control70=IDC_BUTTON_DA_DELAY2,button,1073807360
Control71=IDC_BUTTON_DA_DELAY3,button,1073807360
Control72=IDC_BT_MOTION_PANEL,button,1342242816
Control73=IDC_EDIT_DA7,edit,1082196096
Control74=IDC_STATIC,static,1073872896
Control75=IDC_BUTTON_DA_DELAY5,button,1073807360
Control76=IDC_STATIC,static,1342177294

[DLG:IDD_DIALOG1]
Type=1
Class=CMotionPanel
ControlCount=115
Control1=IDC_BT_X_STEP_P,button,1342242816
Control2=IDC_BT_Y_STEP_P,button,1342242816
Control3=IDC_BT_Y_STEP_M,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_STEP_XY,edit,1082196096
Control6=IDC_BT_Z_STEP_P,button,1342242816
Control7=IDC_BT_Z_STEP_M,button,1342242816
Control8=IDC_BT_A_STEP_P,button,1073807360
Control9=IDC_BT_A_STEP_M,button,1073807360
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_GOHOME_P,button,1342242816
Control13=IDC_HOME_OFFSET,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STOP,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_POSITION_X,edit,1484849280
Control18=IDC_POSITION_Y,edit,1484849280
Control19=IDC_POSITION_Z,edit,1484849280
Control20=IDC_POSITION_A,edit,1216413824
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1073872896
Control26=IDC_RESET_Y,button,1342242816
Control27=IDC_RESET_X,button,1342242816
Control28=IDC_RESET_Z,button,1342242816
Control29=IDC_RESET_A,button,1073807360
Control30=IDC_STATIC_MSG,static,1342308352
Control31=IDC_STATIC,static,1073872896
Control32=IDC_STATIC,static,1073872896
Control33=IDC_RADIO_STEP,button,1073938441
Control34=IDC_RADIO_CONTINUE,button,1073807369
Control35=IDC_BT_X_STEP_M,button,1342242816
Control36=IDC_STATIC,button,1342177287
Control37=IDC_EDIT_DIN1,edit,1216413824
Control38=IDC_EDIT_DIN2,edit,1216413824
Control39=IDC_EDIT_DIN3,edit,1216413824
Control40=IDC_EDIT_DIN4,edit,1216413824
Control41=IDC_EDIT_DIN5,edit,1216413824
Control42=IDC_EDIT_DIN6,edit,1216413824
Control43=IDC_EDIT_DIN7,edit,1216413824
Control44=IDC_EDIT_DIN8,edit,1216413824
Control45=IDC_EDIT_DIN9,edit,1216413824
Control46=IDC_EDIT_DIN10,edit,1216413824
Control47=IDC_EDIT_DIN11,edit,1216413824
Control48=IDC_EDIT_DIN12,edit,1216413824
Control49=IDC_EDIT_DIN13,edit,1216413824
Control50=IDC_EDIT_DIN14,edit,1216413824
Control51=IDC_EDIT_DIN15,edit,1216413824
Control52=IDC_EDIT_DIN16,edit,1216413824
Control53=IDC_STATIC,static,1073872896
Control54=IDC_STATIC,static,1073872896
Control55=IDC_STATIC,static,1073872896
Control56=IDC_STATIC,static,1073872896
Control57=IDC_STATIC,static,1073872896
Control58=IDC_STATIC,static,1073872896
Control59=IDC_STATIC,static,1073872896
Control60=IDC_STATIC,static,1073872896
Control61=IDC_STATIC,static,1073872896
Control62=IDC_STATIC,static,1073872896
Control63=IDC_STATIC,static,1073872896
Control64=IDC_STATIC,static,1073872896
Control65=IDC_STATIC,static,1073872896
Control66=IDC_STATIC,static,1073872896
Control67=IDC_STATIC,static,1073872896
Control68=IDC_STATIC,static,1073872896
Control69=IDC_STATIC,static,1342308352
Control70=IDC_STATIC,static,1342308352
Control71=IDC_STATIC,static,1073872896
Control72=IDC_STATIC,static,1073872896
Control73=IDC_EDIT_DIN17,edit,1484849280
Control74=IDC_STATIC,button,1073741831
Control75=IDC_EDIT_DIN18,edit,1484849280
Control76=IDC_EDIT_DIN19,edit,1216413824
Control77=IDC_EDIT_DIN20,edit,1216413824
Control78=IDC_EDIT_DIN21,edit,1484849280
Control79=IDC_EDIT_DIN22,edit,1484849280
Control80=IDC_EDIT_DIN23,edit,1216413824
Control81=IDC_EDIT_DIN24,edit,1216413824
Control82=IDC_STATIC,static,1342308352
Control83=IDC_STATIC,static,1342308352
Control84=IDC_EDIT_DIN25,edit,1484849280
Control85=IDC_EDIT_DIN26,edit,1484849280
Control86=IDC_EDIT_DIN27,edit,1216413824
Control87=IDC_EDIT_DIN28,edit,1216413824
Control88=IDC_STATIC,static,1342308352
Control89=IDC_CHECK5,button,1342242819
Control90=IDC_CHECK6,button,1342242819
Control91=IDC_CHECK7,button,1073807363
Control92=IDC_CHECK8,button,1073807363
Control93=IDC_STATIC,static,1342308352
Control94=IDC_SAVEPARAM,button,1073807360
Control95=IDC_STATIC,static,1342308352
Control96=IDC_STATIC,static,1342308352
Control97=IDC_STATIC,static,1342308352
Control98=IDC_STATIC,static,1073872896
Control99=IDC_STATIC,static,1342308352
Control100=IDC_START_DIST,button,1342242816
Control101=IDC_quit,button,1342242816
Control102=IDC_CHECK_DISTX,button,1342242819
Control103=IDC_CHECK_DISTY,button,1342242819
Control104=IDC_CHECK_DISTZ,button,1342242819
Control105=IDC_SPEED,edit,1350631552
Control106=IDC_SPEED2,edit,1350631552
Control107=IDC_SPEED7,edit,1350631552
Control108=IDC_STATIC,static,1342308352
Control109=IDC_STATIC,static,1342308352
Control110=IDC_STATIC,static,1342308352
Control111=IDC_DISTANCEX,edit,1350631552
Control112=IDC_DISTANCEY,edit,1350631552
Control113=IDC_DISTANCEZ,edit,1350631552
Control114=IDC_STATIC,static,1342308352
Control115=IDC_STATIC,static,1342177294

[CLS:CMotionPanel]
Type=0
HeaderFile=MotionPanel.h
ImplementationFile=MotionPanel.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMotionPanel

[DLG:IDD_DIALOG_PARAMETERS]
Type=1
Class=CDialogParameters
ControlCount=57
Control1=IDCANCEL,button,1342242816
Control2=IDC_SPEED,edit,1350631552
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ACCTIME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_START_SPEED,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_PPM_X,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_SPEED2,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_ACCTIME2,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_START_SPEED2,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_PPM_Y,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_SPEED3,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_ACCTIME3,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_START_SPEED3,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_PPM_Z,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,button,1342177287
Control35=IDC_STATIC,button,1342177287
Control36=IDC_SPEED4,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_SPEED5,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_SPEED6,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC,static,1342308352
Control50=IDOK,button,1342242816
Control51=IDC_STATIC,button,1342177287
Control52=IDC_STATIC,button,1342177287
Control53=IDC_CHECK1,button,1342242819
Control54=IDC_CHECK2,button,1342242819
Control55=IDC_CHECK3,button,1073807363
Control56=IDC_CHECK4,button,1073807363
Control57=IDC_STATIC,static,1342308352

[CLS:CDialogParameters]
Type=0
HeaderFile=DialogParameters.h
ImplementationFile=DialogParameters.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDialogParameters

