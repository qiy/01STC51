#include<reg52.h>	              //定义头文件
#include<intrins.h>
#define uchar unsigned char	  //宏定义
#define uint  unsigned int

uchar count=0;
uchar i;
uchar code tab[152] = {
0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,/*"未命名文件",0*/
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0xBF,/*"未命名文件",0*/
0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x9F,0xDF,/*"未命名文件",0*/
0x0F,0x0F,0x0F,0x0F,0x0F,0x8F,0xCF,0xEF,/*"未命名文件",0*/
0x07,0x07,0x07,0x07,0x87,0xC7,0xE7,0xF7,/*"未命名文件",0*/
0x03,0x03,0x03,0x83,0xC3,0xE3,0xF3,0xFB,/*"未命名文件",0*/
0x01,0x01,0x81,0xC1,0xE1,0xF1,0xF9,0xFD,/*"未命名文件",0*/
0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,/*"未命名文件",0*/
0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,/*"未命名文件",0*/
0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,/*"未命名文件",0*/
0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"未命名文件",0*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF/*"未命名文件",0*/
};

/*************************************************/
//延时函数：功能是带有入口参数的延时函数，单位约1毫秒
/*************************************************/
void delayms(int m)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<123;j++)
		{}
	}
}
/**************************************************/
//主函数
/**************************************************/
void main()
{
	EA = 1;
	ET0 = 1;
	TMOD = 0x01;
	TH0 = (65536-50)/256;
	TL0 = (65536-50)%256;
	TR0 = 1;
	while(1)
	{
	}
}

void timer0_10ms() interrupt 1
{
	TH0 = (65536-50)/256;
	TL0 = (65536-50)%256;
	count++;
	if(count>70)
	{
		count = 0;
		P0 = tab[i];		
		i++;
		if(i>151)
			i = 0;
	}
			
}				