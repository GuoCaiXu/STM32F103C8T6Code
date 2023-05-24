# include "./w25q64/bsp_w25q64.h"
# include "./spi/bsp_spi.h"
# include "./w25q64/w25q64_ins.h"

void W25Q64_Init(void){

    MySPI_Init();
}

/**
  * @brief  W25Q64读数ID
  * @param  MID 厂家ID
  * @param  DID 设备ID
  * @retval 无
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID){

  MySPI_Start();
  MySPI_SwapByte(W25Q64_JEDEC_ID);
  *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
  *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
  *DID <<= 8;
  *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
  MySPI_Stop();
}

/**
  * @brief  写使能
  * @param  无
  * @retval 无
  */
void W25Q64_WriteEnable(void){

  MySPI_Start();
  MySPI_SwapByte(W25Q64_WRITE_ENABLE);
  MySPI_Stop();
}

/**
  * @brief  读取寄存器1 Busy状态
  * @param  无
  * @retval 无
  */
void W25Q64_WaitBusy(void){

  MySPI_Start();
  MySPI_SwapByte(W25Q64_READ_STATUS_REGISTEP_1);
  while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01);
  MySPI_Stop();
}

/**
  * @brief  页编写写数据
  * @param  无
  * @retval 无
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count){

  W25Q64_WaitBusy();

  W25Q64_WriteEnable();

  MySPI_Start();
  MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
  MySPI_SwapByte(Address >> 16);
  MySPI_SwapByte(Address >> 8);
  MySPI_SwapByte(Address);
  for (uint16_t i = 0; i < Count; i ++){
    MySPI_SwapByte(DataArray[i]);
  }
  MySPI_Stop();
}

/**
  * @brief  擦除扇区内存
  * @param  无
  * @retval 无
  */
void W25Q64_SectorErase_4KB(uint32_t Address){

  W25Q64_WaitBusy();

  W25Q64_WriteEnable();

  MySPI_Start();
  MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
  MySPI_SwapByte(Address >> 16);
  MySPI_SwapByte(Address >> 8);
  MySPI_SwapByte(Address);
  MySPI_Stop();
}

/**
  * @brief  读取数据
  * @param  无
  * @retval 无
  */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count){

  W25Q64_WaitBusy();

  MySPI_Start();
  MySPI_SwapByte(W25Q64_READ_DATA);
  MySPI_SwapByte(Address >> 16);
  MySPI_SwapByte(Address >> 8);
  MySPI_SwapByte(Address);
  for (uint32_t i = 0; i < Count; i ++){

    DataArray[i] = MySPI_SwapByte(W25Q64_READ_DATA);
  }
  MySPI_Stop();
}
