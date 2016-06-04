### 点亮LED灯（汇编版）

JZ2440 nand flash启动首先会把nand flash的前4k自动copy到片内内存SRAM中。  
SRAM大小只有4k。
然后CPU开始直接从SRAM的0地址取指令，点亮LED。