#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/device.h>

/**
 *手柄接线定义
 *VCC 3.3 来自 串口
 *GND     来自 串口
 *CLK   摄像头接口 1P IICSDA GPE15
 *LATCH 摄像头接口 2P IICSCL GPE14
 *DAT0  摄像头接口 5P CAMCLK GPJ11
 */

#define GPE_BASE 0x56000040
#define GPJ_BASE 0x560000d0

//定义一个结构体用来保存 GPIO 信息
typedef struct {
	unsigned int con;
	unsigned int dat;
	unsigned int up;

}T_GPIO_REG, *PT_GPIO_REG;

//禁止编译器优化
static volatile PT_GPIO_REG pt_gpe_reg;
static volatile PT_GPIO_REG pt_gpj_reg;

static struct class *joypad_drv_class;

static ssize_t joypad_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	//利用 sszie_t 返回 手柄键值 
	//buf 是有符号无法保存 8 bit
	int i;
	ssize_t val = 0;
	pt_gpe_reg->dat |= 1<<14;
	udelay(2);
	pt_gpe_reg->dat &= ~(1<<14);
	for(i=0; i<8; i++)
	{
		udelay(2);
		if(! (pt_gpj_reg->dat & 1<<11))
		{
			val |= 1<<i;
		}

		pt_gpe_reg->dat |= 1<<15;
		udelay(2);
		pt_gpe_reg->dat &= ~(1<<15);
	}
	//最后输出低电平
	pt_gpe_reg->dat &= ~(1<<14 | 1<<15);
	return val;
}

static struct file_operations joypad_drv_fops = {
 	.owner  =   THIS_MODULE,
	.read   =   joypad_drv_read,
};

int major;
//注册驱动程序
int joypad_drv_init(void)
{
	major = register_chrdev(0, "joypad_drv", &joypad_drv_fops);

	//自动创建 dev 节点
	joypad_drv_class = class_create(THIS_MODULE, "joypad_drv");
	device_create(joypad_drv_class, NULL, MKDEV(major, 0), NULL, "joypad");

	//ioremap 地址映射
	pt_gpe_reg = ioremap(GPE_BASE, sizeof(T_GPIO_REG));
	pt_gpj_reg = ioremap(GPJ_BASE, sizeof(T_GPIO_REG));

	//配置GPIO
 	//GPE 14 15 配置为输出引脚
	pt_gpe_reg->con &= ~(3<<(2*15));
	pt_gpe_reg->con &= ~(3<<(2*14));
	pt_gpe_reg->con |=  1<<(2*15);
	pt_gpe_reg->con |= 1<<(2*14);
	
	//默认输出低电平
	pt_gpe_reg->dat &= ~(1<<14 | 1<<15);

	//GPJ 11 配置为输入引脚 禁用内部上拉
	pt_gpj_reg->con &= ~(3<<(2*11));
	pt_gpj_reg->up |= 1<<11;
	return 0;
}

//卸载驱动程序
void joypad_drv_exit(void)
{
	//取消 地址映射
	iounmap(pt_gpe_reg);
	iounmap(pt_gpj_reg);
	
	unregister_chrdev(major, "joypad_drv");
	device_destroy(joypad_drv_class, MKDEV(major, 0));
	class_destroy(joypad_drv_class);
}

module_init(joypad_drv_init);
module_exit(joypad_drv_exit);
MODULE_LICENSE("GPL");

