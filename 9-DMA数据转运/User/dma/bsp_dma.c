# include "./dma/bsp_dma.h"

uint16_t MyDMA_Size;

/**
 *  @brief  DMA ��ʼ��
 *  @param  AddrA: ����վ���ַ
 *  @param  AddrB: ������վ���ַ
 *  @param  Size:  �������
 *  @retval ��
 */
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size){

    MyDMA_Size = Size;

    DMAx_AHBPeriph_FUN(DMAx_CLK, ENABLE);

    DMA_InitTypeDef     DMA_InitStructure;
    /*����վ��� ��ʼ��ַ�����ݿ�ȣ��Ƿ�����*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    /*�洢��վ��� ��ʼ��ַ�����ݿ�ȣ��Ƿ�����*/
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;           //���䷽��     DMA_DIR_PeripheralSRC ����վ��ΪԴͷ(����վ�㵽������)  DMA_DIR_PeripheralDST ����վ��ΪĿ�ĵ�(������վ�㵽����վ��)
    DMA_InitStructure.DMA_BufferSize = Size;                     //��������С
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                //�Ƿ�ʹ���Զ���װ
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;                  //�Ƿ�ʹ���������
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;        //ѡ�����ȼ�
    DMA_Init(DMAx_CHANNELx, &DMA_InitStructure);

    DMA_Cmd(DMAx_CHANNELx, ENABLE);
}

void MyDMA_Transfer(void){

    DMA_Cmd(DMAx_CHANNELx, DISABLE);
    DMA_SetCurrDataCounter(DMAx_CHANNELx, MyDMA_Size);
    DMA_Cmd(DMAx_CHANNELx, ENABLE);

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
