### 存储管理器

#### 定义
存储控制器是用来访问外设的。CPU核发送指令通过存储控制器去访问外设，例如去访问SDRAM，网卡，Nor flash等等。
例如：CPU要访问外部内存设备SDRAM  
存储管理器需要配置的信息有  
1. 片选信号
2. bank选择信号
3. 列地址
4. 行地址

#### 访问一个地址（芯片）
需要配置如下信息
1. 地址线
2. 数据线 位宽
3. 时钟、频率
4. 芯片相关的特新



#### 内存相关知识
1. SRAM：静态随机存储器，加电情况下，不需要刷新，数据不会丢失，一般不是行列地址复用。
2. DRAM：动态随机存储器，需要不断刷新才能保存数据，行列地址复用，有许多页模式。
3. SDRAM：同步的DRAM，数据读写需要时钟控制。
4. DDR：既DDR SDRAM，Double Data Rate双倍速率同步动态随机存储器。DDR2是4倍速率，DDR3是8倍速率

对于JZ2440 ARM开发板来说，采用bank信号来进行选中外设。通过汇编代码在CPU里执行设置存储寄存器及相关时序，从而对SDRAM等设备进行访问和操作。


#### 以下针对JZ2440开发板进行讨论
1. 存储控制器有bank0到bank6接了外设。CPC发出片选信号，由开发板手册知道nGCS0(与年GCS6同一管脚)片选信号选中SDRAM，那么此时的bank地址为：0x3000 0000 ~0x3800 0000，意思是CPU发出地址信号，那么就选中了SDRAM。

2. 接着看SDRAM芯片手册和JZ2440的接线，包括有哪些管脚。CPU提供一组用于SDRAM的信号，详见Linux应用开发完全手册。过程：选中芯片，寻址，设置寄存器，发送数据访问数据（对SDRAM进行操作）。

3. 存储控制器的寄存器：13个
    位宽和等待控制寄存器 BWSCON, BANKCONx(0~7),连接SDRAM时还要设置REFRESH，BANKSISE、MRSRB6，MRSRB7等四个寄存器。

4. 结合JZ2440开发板手册，设置寄存器。

 位宽和等待控制寄存器 BWSCON：32位，分成8部分每4位控制一个bank，总共为8个bank。
四位从高到低分别是：ST，WS，DW（占两位）。针对SDRAM讨论的话，我们使用的是bank6，即：
| XXXX | 0010 | XXXX | XXXX | XXXX | XXXX | XXXX | XXXX |     -->  根据其他bank设备的连接，分别设置各个bank的BWSCON位，从而得到BWSCON的值。 
备注 ：
ST：启动/禁止 SDRAM的数据掩码引脚，SDRAM一般为0，SRAM一般为1
WS：是否使用存储器的WAIT信号，一般为0.
DW：设置位宽，0b00-8位，0b01-16位，0b10-32位，0b00保留。
d
Bank控制寄存器，BANKCONx，0~5使用默认的值0x700即可满足要求。对于BANKCON6和BANKCON7设置如下：
15,16位为MT（Memory Type）:外接的是ROM/SRAM则为00，若为SDRAM则为11
2,3位为Trcd，RAS to CAS delay，推荐值为01
0,1位为SCAN，SDRAM列地址位数，九位：01
| XXXX | XXXX | XXXX | XXX1 | 1XXX | XXXX | XXXX | 0101 | --->BANKCON6为0x00018005

刷新控制寄存器，REFRESH
23位为REFEN，刷新使能位，禁止刷新0，启用刷新1。
22位为TFREMD，刷新模式位，0 -- CBR/auto refresh，1 -- self refresh（一般在系统休眠时使用）。
21,20位为Trp，SDRAM RAS per-change time 一般为00。
19,18位为Tsrc，SDRAM Semi Raw Circle Type，一般为11。
0到10位为Refresh Counter，即：R_CNT
| XXXX | XXXX | 1000 | 11XX | XXXX | XXXX | XXXX | XXXX |  ---> 0x008c0000 + R_CNT
R_CNT的计算：


