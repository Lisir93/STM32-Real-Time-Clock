#include "key.h"
#include "sys.h"
#include "delay.h"

void Key_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//�����˿�ʱ��
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;//ѡ��GPIOE.3-4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOE,&GPIO_InitStructure);//��ʼ��GPIOE,3-4
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//ѡ��GPIOA.0(WEAK-UP ����)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
    GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��GPIOA.0(WEAK-UP ����)
}

//������������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1�� KEY0 ����
//2�� KEY1 ����
//3�� KEY3 ���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY_UP!!

unsigned char Key_Scan(unsigned char mode)
{
    static unsigned char key_up = 1;//�������ɿ���־
    if(mode == 1)  //֧������
        key_up = 1;
    if(key_up && (KEY0==0||KEY1==0||WK_UP==1))
    {
        delay_ms(10);  //����
        key_up = 0;
        
        if(KEY0==0)       return KEY0_PRES;
        else if(KEY1==0)  return KEY1_PRES;
        else if(WK_UP==1) return WKUP_PRES;
    }
    else if(KEY0==1 && KEY1==1 && WK_UP==0)
        key_up = 1;
    return 0;
}
