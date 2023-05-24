# include "./dma/bsp_dma.h"

uint16_t MyDMA_Size;

/**
 *  @brief  DMA 初始化
 *  @param  AddrA: 外设站点地址
 *  @param  AddrB: 储存器站点地址
 *  @param  Size:  传输次数
 *  @retval 无
 */
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size){

    MyDMA_Size = Size;

    DMAx_AHBPeriph_FUN(DMAx_CLK, ENABLE);

    DMA_InitTypeDef     DMA_InitStructure;
    /*外设站点的 起始地址，数据宽度，是否自增*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    /*存储器站点的 起始地址，数据宽度，是否自增*/
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;           //传输方向     DMA_DIR_PeripheralSRC 外设站点为源头(外设站点到储存器)  DMA_DIR_PeripheralDST 外设站点为目的地(储存器站点到外设站点)
    DMA_InitStructure.DMA_BufferSize = Size;                     //缓冲区大小
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                //是否使用自动重装
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;                  //是否使用软件触发
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;        //选择优先级
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
