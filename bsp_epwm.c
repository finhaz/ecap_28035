/*
 * bsp_epwm.c
 *
 *  Created on: 2021��1��6��
 *      Author: sea
 */

#include "DSP28x_Project.h"     // DSP28x Headerfile

#define Prd 1500

void ConfigureEPwm(void)
{
    //EPWM1-2 6 DRIVE

    //Note that the default/2 divider for ePWMs and EMIFs
    //EPWMCLK=SYSCLKOUT=60MHZ
    //ePWMģ��ʱ������  // TBCLK = EPWMCLK/(HSPCLKDIV*CLKDIV)
    //PWM����=10000��TBCLK����100us

    // Initialize EPwm1/2/3/4/5/6/7
    //�������ó���------------->>>>>>>>>>>>>
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    //EPWM Moudle 1 ����
    //TB
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm1Regs.TBCTL.bit.CLKDIV=0;
    EPwm1Regs.TBPRD=Prd;
    EPwm1Regs.TBPHS.half.TBPHS=0;//����λ�Ĵ���ֵ����
    EPwm1Regs.TBCTR=0x0000;
    EPwm1Regs.TBCTL.bit.CTRMODE=TB_COUNT_UPDOWN;//����ģʽ
    EPwm1Regs.TBCTL.bit.PHSEN=TB_DISABLE;//��ֹ��λװ��
    EPwm1Regs.TBCTL.bit.PRDLD=TB_SHADOW;//��CTR=0ʱ����ӳ��Ĵ����е�����װ�ص���ǰ�Ĵ���
    EPwm1Regs.TBCTL.bit.SYNCOSEL=TB_CTR_ZERO;//CTR=0ʱ����ͬ���ź�
    //CC
    EPwm1Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;//CMPA�Ĵ��������� ӳ��ģʽ
    EPwm1Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;//CMPB�Ĵ��������� ӳ��ģʽ
    EPwm1Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    EPwm1Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    //AQ
    EPwm1Regs.AQCTLA.bit.CAU=AQ_SET;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵ���������ʹEPWM1AΪ�ߵ�ƽ
    EPwm1Regs.AQCTLA.bit.CAD=AQ_CLEAR;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵݼ�������ʹEPWM1AΪ�͵�ƽ

     //DB
    EPwm1Regs.AQCSFRC.all = 0x0005 ;//���ǿ��PWM���Ϊ��,2017/12/26
    //EPwm1Regs.DBCTL.bit.OUT_MODE=DB_FULL_ENABLE;//ʹ�������ؼ��½�����ʱ�ź�
    EPwm1Regs.DBCTL.bit.IN_MODE=DBA_ALL;//Ĭ��EPWM1A��Ϊ�����ؼ��½�����ʱ���ź�Դ
    EPwm1Regs.DBCTL.bit.POLSEL=DB_ACTV_HIC;//AHC\EPWM1B��ת����
    EPwm1Regs.DBFED=120;//�½�����ʱFED=120��TBCLK
    EPwm1Regs.DBRED=120;//��������ʱRED=120��TBCLK
    EPwm1Regs.CMPA.half.CMPA=0.5*Prd;


    //�¼���������ADC
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;         // ʹ��SOCAת��������
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_ZERO;//������Ϊ0ʱ����ת��
    EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST; // Generate pulse on 1st event

    //EPWM Moudle 2 ����
    //TB
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;
    EPwm2Regs.TBCTL.bit.CLKDIV=0;
    EPwm2Regs.TBPRD=Prd;
    EPwm2Regs.TBPHS.half.TBPHS=0;//����λ�Ĵ���ֵ����
    EPwm2Regs.TBCTR=0x0000;
    EPwm2Regs.TBCTL.bit.CTRMODE=TB_COUNT_UPDOWN;//����ģʽ
    EPwm2Regs.TBCTL.bit.PHSEN=TB_DISABLE;//��ֹ��λװ��
    EPwm2Regs.TBCTL.bit.PRDLD=TB_SHADOW;//��CTR=0ʱ����ӳ��Ĵ����е�����װ�ص���ǰ�Ĵ���
    EPwm2Regs.TBCTL.bit.SYNCOSEL=TB_SYNC_IN;//CTR=0ʱ����ͬ���ź�
    //EPwm2Regs.TBCTL.bit.SYNCOSEL=TB_CTR_ZERO;//CTR=0ʱ����ͬ���ź�
    //CC
    EPwm2Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;//CMPA�Ĵ��������� ӳ��ģʽ
    EPwm2Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;//CMPB�Ĵ��������� ӳ��ģʽ
    EPwm2Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    EPwm2Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;//��CTR=0ʱװ��
    //AQ
    EPwm2Regs.AQCTLA.bit.CAU=AQ_SET;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵ���������ʹEPWM1AΪ�ߵ�ƽ
    EPwm2Regs.AQCTLA.bit.CAD=AQ_CLEAR;//��ʱ���׼��������ֵ����CMPA��ֵ�������ڵݼ�������ʹEPWM1AΪ�͵�ƽ

     //DB
    EPwm2Regs.AQCSFRC.all = 0x0005 ;//���ǿ��PWM���Ϊ��,2017/12/26
    //EPwm1Regs.DBCTL.bit.OUT_MODE=DB_FULL_ENABLE;//ʹ�������ؼ��½�����ʱ�ź�
    EPwm2Regs.DBCTL.bit.IN_MODE=DBA_ALL;//Ĭ��EPWM1A��Ϊ�����ؼ��½�����ʱ���ź�Դ
    EPwm2Regs.DBCTL.bit.POLSEL=DB_ACTV_HIC;//AHC\EPWM1B��ת����
    EPwm2Regs.DBFED=120;//�½�����ʱFED=120��TBCLK
    EPwm2Regs.DBRED=120;//��������ʱRED=120��TBCLK
    EPwm2Regs.CMPA.half.CMPA=0.5*Prd;

    //TBD
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;
}

//��PWM
void PWMopen(void)
{
    //���ػ��ж�
    //ePWM1����
    EPwm1Regs.AQSFRC.bit.RLDCSF = 0;//
    EPwm1Regs.AQCSFRC.all = 0x0000 ;//�޶���
    EPwm1Regs.DBCTL.bit.OUT_MODE=3;

    //ePWM2����
    EPwm2Regs.AQSFRC.bit.RLDCSF = 0 ;//
    EPwm2Regs.AQCSFRC.all = 0x0000 ;//�޶���
    EPwm2Regs.DBCTL.bit.OUT_MODE=3;


}
