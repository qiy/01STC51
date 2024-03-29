//公司：北方蓝芯科技开发有限公司
//网址：www.hrbnbc.com
//更多教程可登陆技术论坛www.hrbnbc.com/bbs对应版块下载，
//所有教程一律免费下载
/***************************************************************************************************    
工程名称：	12864_pic
功能描述：  实现12864液晶显示图片功能。
硬件连接：  将12864液晶接口对应插接到P2接口，注意1-20脚不要插反。
维护记录：  2011-8-22
***************************************************************************************************/
#include "reg51.h"          //包含头文件
#define uchar unsigned char
#define uint  unsigned int

sbit RS=P2^5;    //命令/数据选择
sbit RW=P2^4;    //读写口
sbit  E=P2^3;    //锁存控制
sbit RES = P2^0; //复位
sbit PSB = P2^2; //串并选择

uchar code pic[]=      // 图片代码
{
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x1F,0xFF,0x81,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x1F,0xFF,0x81,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x18,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x08,0x00,0x00,0x00,0x03,
0xC0,0x1F,0xFF,0x80,0x00,0x00,0x04,0x07,0x81,0xE0,0x10,0x10,0x03,0xC0,0x30,0x03,
0xC0,0x1F,0xFF,0x80,0x00,0x00,0x0C,0x0C,0xC3,0x30,0x08,0x20,0x0C,0xE0,0x70,0x03,
0xC0,0x18,0x01,0x87,0xFF,0xFE,0x3C,0x18,0x66,0x18,0x04,0x40,0x0C,0x60,0x70,0x03,
0xC0,0x1F,0xFF,0x87,0xFF,0xFE,0x0C,0x18,0x66,0x18,0x02,0x80,0x18,0x00,0xB0,0x03,
0xC0,0x1F,0xFF,0x80,0x06,0x00,0x0C,0x18,0x66,0x18,0x01,0x00,0x1B,0x81,0x30,0x03,
0xC0,0x01,0x98,0x00,0x06,0x00,0x0C,0x00,0xE3,0x30,0x02,0x80,0x1C,0xC1,0x30,0x03,
0xC0,0x19,0x99,0x80,0x66,0x60,0x0C,0x00,0xC1,0xE0,0x04,0x40,0x18,0x62,0x30,0x03,
0xC0,0x19,0x99,0x80,0x66,0x30,0x0C,0x01,0x83,0x30,0x08,0x20,0x18,0x66,0x30,0x03,
0xC0,0x0D,0x9B,0x00,0xC6,0x38,0x0C,0x03,0x06,0x18,0x10,0x10,0x18,0x67,0xFC,0x03,
0xC0,0x0D,0x9B,0x01,0xC6,0x1C,0x0C,0x06,0x06,0x18,0x20,0x08,0x18,0x60,0x30,0x03,
0xC0,0x01,0x98,0x03,0x86,0x0C,0x0C,0x0C,0x06,0x18,0x00,0x00,0x08,0x60,0x30,0x03,
0xC0,0x7F,0xFF,0xE3,0x06,0x00,0x0C,0x18,0x03,0x30,0x00,0x00,0x0C,0xC0,0x30,0x03,
0xC0,0x7F,0xFF,0xE0,0x1E,0x00,0x0C,0x1F,0xE1,0xE0,0x00,0x00,0x07,0x80,0x30,0x03,
0xC0,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x18,0x00,0x00,0x00,0x06,0x0C,0x03,
0xC3,0xFF,0xFC,0x3F,0xF0,0x80,0x0C,0x00,0x3F,0x18,0x01,0xFF,0xFE,0x06,0x0C,0x03,
0xC3,0xFF,0xFC,0x3F,0xF1,0x80,0x0F,0xFC,0x3F,0x18,0x01,0xFF,0xFE,0x06,0x0C,0x03,
0xC3,0x0C,0x0C,0x0C,0xC3,0x00,0x0F,0xFC,0x33,0x7F,0xE1,0x86,0x06,0x06,0x0C,0x03,
0xC3,0x1F,0xCC,0x0C,0xC6,0x00,0x0C,0x00,0x33,0x7F,0xE1,0x8F,0xE6,0x06,0x0C,0x03,
0xC3,0x3F,0xCC,0x0C,0xCC,0x00,0x0C,0x00,0x36,0x30,0x01,0x9F,0xE6,0x07,0xFF,0xE3,
0xC3,0x79,0x8C,0x0C,0xC8,0x00,0xFF,0xF0,0x36,0x36,0x01,0xBC,0xC6,0x07,0xFF,0xE3,
0xC3,0x6F,0x0C,0x7F,0xF0,0xC0,0xFF,0xF0,0x36,0x66,0x01,0xB7,0x86,0x06,0x00,0x03,
0xC3,0x0F,0x0C,0x7F,0xF1,0x80,0xC0,0x30,0x36,0x7F,0xC1,0x87,0x86,0x06,0x00,0x03,
0xC3,0x79,0xEC,0x0C,0xC3,0x00,0xC0,0x30,0x33,0x7F,0xC1,0xBC,0xF6,0x06,0x00,0x03,
0xC3,0x76,0xEC,0x0C,0xC6,0x00,0xC0,0x30,0x33,0x06,0x01,0xBB,0x76,0x07,0xFF,0x03,
0xC3,0x07,0x0C,0x0C,0xCC,0x20,0xFF,0xF0,0x33,0x06,0x01,0x83,0x86,0x07,0xFF,0x03,
0xC3,0x03,0x0C,0x18,0xC8,0x60,0xFF,0xF0,0x3F,0x06,0x01,0x81,0x86,0x06,0x03,0x03,
0xC3,0x1C,0x0C,0x18,0xC0,0xC0,0x00,0x00,0x3E,0xFF,0xE1,0x8E,0x06,0x06,0x03,0x03,
0xC3,0x1F,0x0C,0x18,0xC1,0x81,0xB1,0x8C,0x30,0xFF,0xE1,0x8F,0x86,0x06,0x03,0x03,
0xC3,0x03,0x0C,0x30,0xC7,0x01,0xB1,0x8C,0x30,0x06,0x01,0x81,0x86,0x0C,0x03,0x03,
0xC3,0xFF,0xFC,0x70,0xDE,0x03,0x18,0xC6,0x30,0x06,0x01,0xFF,0xFE,0x0C,0x03,0x03,
0xC3,0xFF,0xFC,0x20,0x18,0x03,0x18,0xC6,0x30,0x06,0x01,0xFF,0xFE,0x18,0x03,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};
uchar code pic1[]=      // 图片代码
{
    0x00,0x00,0x00,0x01,0x85,0xFD,0x7D,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0A,0x0B,0xD0,0x1B,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x07,0x0B,0xE0,0x06,0xBF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x1A,0x1F,0x80,0x01,0x5F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x26,0x0F,0x00,0x00,0x15,0xFF,0xFF,0xFF,0xD0,0x00,0x80,0x00,0x00,
    0x00,0x00,0x00,0x14,0x5C,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xE0,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x18,0x1E,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xF0,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0xA8,0xB8,0x00,0x00,0x01,0x7F,0xFF,0xFF,0xE8,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x31,0x38,0x00,0x00,0x00,0x9F,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xA0,0x60,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x62,0x70,0x00,0x00,0x00,0x1F,0xDF,0xFF,0xFC,0x00,0x00,0x00,0x00,
    0x00,0x00,0x01,0x40,0xC0,0x00,0x00,0x00,0x3F,0xDF,0xFF,0xF8,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xC1,0xE0,0x00,0x00,0x00,0x27,0xEF,0xFF,0xFC,0x00,0x00,0x00,0x00,
    0x00,0x00,0x02,0x81,0xE0,0x00,0x00,0x00,0x0F,0xF7,0xFF,0xFC,0x00,0x00,0x00,0x00,
    0x00,0x00,0x05,0x89,0x70,0x00,0x00,0x00,0x05,0xF7,0xFF,0xFE,0x00,0x08,0xC0,0x00,
    0x00,0x00,0x05,0x13,0x18,0x00,0x00,0x00,0x03,0xFB,0xFF,0xFE,0x00,0x14,0x80,0x00,
    0x00,0x00,0x03,0x0B,0x04,0x00,0x00,0x00,0x05,0xFB,0xFF,0xFF,0x00,0x3F,0xE0,0x00,
    0x00,0x00,0x0A,0xA6,0x00,0x00,0x00,0x00,0x0B,0xFD,0xFF,0xFE,0x00,0x2E,0xC0,0x00,
    0x00,0x00,0x06,0x17,0x80,0x00,0x00,0x00,0x02,0xFD,0xFF,0xFF,0x80,0x17,0x40,0x00,
    0x00,0x10,0x15,0x27,0xE0,0x00,0x00,0x00,0x0F,0xFC,0xFF,0xFF,0x00,0x0D,0x80,0x00,
    0x00,0x04,0x0E,0xAE,0x70,0x00,0x00,0x00,0x01,0xFE,0xFF,0xFF,0x80,0x05,0x00,0x00,
    0x00,0x08,0x18,0x8E,0x78,0x00,0x00,0x00,0x0F,0xFE,0xFF,0xEF,0x80,0x02,0x00,0x00,
    0x00,0x00,0x0D,0x4F,0x5C,0x00,0x03,0xF0,0x01,0xFF,0x7F,0xFF,0xC0,0x00,0x00,0x00,
    0x00,0x00,0x16,0x91,0xB8,0x00,0x05,0xFE,0x07,0xFE,0x7F,0xF7,0xC0,0x00,0x04,0x00,
    0x00,0x00,0x15,0x98,0x1C,0x00,0x00,0x0F,0x80,0xFF,0xBF,0xFF,0xE0,0x00,0x14,0x00,
    0x00,0x00,0x2A,0xA0,0x00,0x00,0x00,0x01,0xC7,0xFF,0x7F,0xFB,0xE0,0x00,0x08,0x00,
    0x00,0x00,0x25,0xA0,0x00,0x00,0x00,0x00,0xC0,0xFF,0xBF,0xFF,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x2F,0x40,0x00,0x00,0x06,0x80,0x42,0xFF,0xBF,0xFB,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x2B,0x80,0x00,0x00,0x0B,0xE0,0x2A,0xFF,0xDF,0xFF,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x37,0x00,0x00,0x00,0x33,0xF0,0x07,0xFF,0xBF,0xFC,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x2E,0x80,0x00,0x00,0x32,0xF8,0x00,0xFF,0xEF,0xFE,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x7D,0x00,0x00,0x00,0x03,0xD8,0x07,0xFF,0xBF,0xFF,0x38,0x00,0x68,0x00,
    0x00,0x00,0x3D,0x00,0x00,0x00,0x03,0xBC,0x01,0xFF,0xDF,0xFF,0xB8,0x00,0x56,0x00,
    0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x2C,0x0B,0xFF,0xFF,0xFF,0x98,0x00,0xFC,0x00,
    0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x05,0xFF,0xDB,0xFF,0xDC,0x00,0x34,0x00,
    0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xDF,0xFF,0xCC,0x00,0x28,0x00,
    0x1B,0x00,0xDE,0x00,0x00,0x00,0x00,0x00,0x0B,0xFF,0xDF,0xFF,0xCC,0x00,0x10,0x00,
    0x2A,0x81,0xFE,0x00,0x00,0x00,0x00,0x00,0x17,0xFF,0xED,0xFF,0x4C,0x00,0x00,0x00,
    0x1F,0x80,0xFE,0x00,0x00,0x00,0x00,0x00,0x0B,0xFF,0xFF,0xFF,0xCE,0x00,0x00,0x00,
    0x16,0x01,0xFE,0x00,0x00,0x00,0x00,0x00,0x57,0xFF,0xFD,0xFF,0xCC,0x00,0x00,0x00,
    0x0A,0x01,0x7E,0x00,0x00,0x00,0x00,0x00,0x17,0xFF,0xBF,0xFF,0xC6,0x00,0x00,0x00,
    0x04,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x5F,0xFF,0xBE,0xFF,0x8E,0x08,0x00,0x00,
    0x00,0x01,0x7E,0x00,0x00,0x00,0x00,0x00,0x2F,0xEF,0xFF,0xFF,0xEE,0x02,0x00,0x00,
    0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xEF,0x7F,0xCC,0x04,0x00,0x00,
    0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x5F,0xFF,0xF7,0xFF,0xEE,0x00,0x00,0x00,
    0x00,0x00,0x3B,0x00,0x00,0x00,0x00,0x00,0x7C,0xFF,0xEE,0xBF,0xCE,0x00,0x00,0x00,
    0x00,0x00,0x1D,0x00,0x00,0x00,0x00,0x00,0xBF,0x3F,0xF7,0xFF,0xEE,0x00,0x00,0x00,
    0x00,0x00,0x37,0x80,0x80,0x00,0x00,0x01,0x7F,0xFF,0xFF,0xDF,0xFC,0x00,0x00,0x00,
    0x00,0x00,0x1B,0x80,0x60,0x00,0x00,0x00,0x7F,0xFF,0xF7,0xFF,0xFE,0x00,0x00,0x00,
    0x00,0x00,0x1A,0x80,0x15,0x40,0x00,0x02,0xFF,0xFF,0xF7,0xBF,0xFC,0x00,0x00,0x00,
    0x00,0x00,0x0A,0x40,0x0F,0xFC,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x0A,0x00,
    0x00,0x00,0x08,0xC0,0x00,0xFC,0x00,0x02,0xFF,0xFF,0xFB,0xDF,0xF4,0x00,0x04,0x00,
    0x00,0x00,0x04,0x40,0x01,0xE0,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x04,0x60,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFB,0xDF,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x01,0x60,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xEF,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xDF,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFD,0xFF,0xD0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0xBF,0xFF,0xFF,0xFF,0xEF,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3F,0xC0,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xF7,0xFC,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFB,0x00,0x00,0x00,
    0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xF7,0xF4,0x00,0x00,0x00
};
//**************************************************************************************************
//延时函数
//**************************************************************************************************
delay(uint time)         //int型数据为16位,所以最大值为65535            
 {
  uint  i,j;             //定义变量i,j,用于循环语句 
  for(i=0;i<time;i++)    //for循环,循环50*time次
     for(j=0;j<100;j++); //for循环,循环50次
 }
//**************************************************************************************************
//查忙
//**************************************************************************************************
checkbusy()           
{
   RS=0;                   //命令/数据选择,为0时选择命令    
   RW=1;                   //读/写选择，为1时选择读
   E=1;                    //使能
   while((P0&0x80)==0x80); //查忙标志位，等待标志位为0，即表示写入完毕
   E=0;                    //关闭读写 
}
//**************************************************************************************************
//向LCD写一命令
//**************************************************************************************************
wcode(uchar cmdcode)
{
   checkbusy();            //查忙
   RS=0;                   //命令/数据选择,为0时选择命令 
   RW=0;                   //读/写选择，为0时选择写
   E=1;                    //使能
   P0=cmdcode;             //送入命令
   delay(10);              //等待写入 
   E=0;                    //关闭读写
}  
//**************************************************************************************************
//向LCD写一数据
//**************************************************************************************************
wdata(uchar dispdata)
{
   checkbusy();            //查忙
   RS=1;                   //命令/数据选择,为1时选择数据
   RW=0;                   //读/写选择，为0时选择写
   E=1;                    //使能
   P0=dispdata;            //送入数据
   delay(10);              //等待写入 
   E=0;                    //关闭读写
}
//**************************************************************************************************
//LCD 初始化
//**************************************************************************************************
InitLCD()
   {
   PSB=1;             //设置为8BIT并口工作模式
   RES=0;             //复位
   delay(10);         //延时
   RES=1;             //关复位
 
   wcode(0x30);       //选择基本指令集
   wcode(0x0c);       //开显示(无游标、不反白)
   wcode(0x01);       //清除显示，并且设定地址指针为00H
   wcode(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位
   wcode(0x01);       //清屏	
   }  
//**************************************************************************************************
//显示图片
//**************************************************************************************************
void picshow(uchar code *bmp)
{ 
 uchar i,j,k,up_down;
 up_down=0x80;             //先写上半屏
 wcode(0x34);              //设置图形模式
 wcode(0x36);              //设置图形模式
for(k=0;k<2;k++)           //分上下半屏先后写入,所以循环2次，i为0时写上半屏，i为1时写下半屏
  {
   for(i=0;i<32;i++)       //上下半屏各32行，共64行     
    { 
      wcode(0x80 + i);     //设置垂直地址
      wcode(up_down);      //设置水平地址
      for(j=0;j<16;j++)    //写16个字节，16*8=128竖
       {
         wdata(*bmp);      //写入一字节
         bmp++;            //加1
       }
    }
    up_down=0x88;           //准备写下半屏
  }           
}
//**************************************************************************************************
//主函数
//**************************************************************************************************
main()
{  
   InitLCD();	                     //初始化液晶
   while(1) 	                     //进入死循环，防止看门狗复位
    {
     picshow(pic);                   //显示第1张图片
     delay(5000);                    //保持显示一段时间
     picshow(pic1);                  //显示第2张图片
     delay(5000);                    //保持显示一段时间  
    }
}