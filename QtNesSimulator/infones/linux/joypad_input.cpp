#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define JOYPAD_DEV "/dev/joypad"
#define USB_JS_DEV "/dev/input/js0"


typedef struct JoypadInput{
	int (*DevInit)(void);
	int (*DevExit)(void);
	int (*GetJoypad)(void);
	struct JoypadInput *ptNext;
	pthread_t tTreadID;     /* 子线程ID */
}T_JoypadInput, *PT_JoypadInput;

struct js_event {		
	unsigned int   time;      /* event timestamp in milliseconds */		
	unsigned short value;     /* value */		
	unsigned char  type;      /* event type */		
	unsigned char  number;    /* axis/button number */	
};

//全局变量通过互斥体访问
static unsigned char g_InputEvent;

static pthread_mutex_t g_tMutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_tConVar = PTHREAD_COND_INITIALIZER;

static int joypad_fd;
static int USBjoypad_fd;
static PT_JoypadInput g_ptJoypadInputHead;


static void *InputEventTreadFunction(void *pVoid)
{
	/* 定义函数指针 */
	int (*GetJoypad)(void);
	GetJoypad = (int (*)(void))pVoid;

	while (1)
	{
		//因为有阻塞所以没有输入时是休眠
		g_InputEvent = GetJoypad();
		//有数据时唤醒
		pthread_mutex_lock(&g_tMutex);
		/*  唤醒主线程 */
		pthread_cond_signal(&g_tConVar);
		pthread_mutex_unlock(&g_tMutex);
	}
}

static int RegisterJoypadInput(PT_JoypadInput ptJoypadInput)
{
	PT_JoypadInput tmp;
	if(ptJoypadInput->DevInit())
	{
		return -1;
	}
	//初始化成功创建子线程 将子项的GetInputEvent 传进来
	pthread_create(&ptJoypadInput->tTreadID, NULL, InputEventTreadFunction, (void*)ptJoypadInput->GetJoypad);
	if(! g_ptJoypadInputHead)
	{
		g_ptJoypadInputHead = ptJoypadInput;
	}
	else
	{
		tmp = g_ptJoypadInputHead;
		while(tmp->ptNext)
		{
			tmp = tmp->ptNext;
		}
		tmp->ptNext = ptJoypadInput;
	}
	ptJoypadInput->ptNext = NULL;
	return 0;
}

static int joypadGet(void)
{
	return read(joypad_fd, 0, 0);
}

static int joypadDevInit(void)
{
	joypad_fd = open(JOYPAD_DEV, O_RDONLY);
	if(-1 == joypad_fd)
	{
		printf("%s dev not found \r\n", JOYPAD_DEV);
		return -1;
	}
	return 0;
}

static int joypadDevExit(void)
{
	close(joypad_fd);
	return 0;
}

static T_JoypadInput joypadInput = {
	joypadDevInit,
	joypadDevExit,
	joypadGet,
};

static int USBjoypadGet(void)
{
	/**
	 * FC手柄 bit 键位对应关系 真实手柄中有一个定时器，处理 连A  连B 
	 * 0  1   2       3       4    5      6     7
	 * A  B   Select  Start  Up   Down   Left  Right
	 */
	//因为 USB 手柄每次只能读到一位键值 所以要有静态变量保存上一次的值
	static unsigned char joypad = 0;
	struct js_event e;
	if(0 < read (USBjoypad_fd, &e, sizeof(e)))
	{
		if(0x2 == e.type)
		{
			/*
			上：
			value:0x8001 type:0x2 number:0x5
			value:0x0 type:0x2 number:0x5
			*/
			if(0x8001 == e.value && 0x5 == e.number)
			{
				joypad |= 1<<4;
			}
			
			/*下：
			value:0x7fff type:0x2 number:0x5
			value:0x0 type:0x2 number:0x5
			*/
			if(0x7fff == e.value && 0x5 == e.number)
			{
				joypad |= 1<<5;
			}
			//松开
			if(0x0 == e.value && 0x5 == e.number)
			{
				joypad &= ~(1<<4 | 1<<5);
			}
			
			/*左：
			value:0x8001 type:0x2 number:0x4
			value:0x0 type:0x2 number:0x4
			*/
			if(0x8001 == e.value && 0x4 == e.number)
			{
				joypad |= 1<<6;
			}
			
			/*右：
			value:0x7fff type:0x2 number:0x4
			value:0x0 type:0x2 number:0x4
			*/
			if(0x7fff == e.value && 0x4 == e.number)
			{
				joypad |= 1<<7;
			}
			//松开
			if(0x0 == e.value && 0x4 == e.number)
			{
				joypad &= ~(1<<6 | 1<<7);
			}
		}

		if(0x1 == e.type)
		{
			/*选择：
			value:0x1 type:0x1 number:0xa
			value:0x0 type:0x1 number:0xa
			*/
			if(0x1 == e.value && 0xa == e.number)
			{
				joypad |= 1<<2;
			}
			if(0x0 == e.value && 0xa == e.number)
			{
				joypad &= ~(1<<2);
			}
			
			/*开始：
			value:0x1 type:0x1 number:0xb
			value:0x0 type:0x1 number:0xb
			*/
			if(0x1 == e.value && 0xb == e.number)
			{
				joypad |= 1<<3;
			}
			if(0x0 == e.value && 0xb == e.number)
			{
				joypad &= ~(1<<3);
			}

			/*A
			value:0x1 type:0x1 number:0x0
			value:0x0 type:0x1 number:0x0
			*/
			if(0x1 == e.value && 0x0 == e.number)
			{
				joypad |= 1<<0;
			}
			if(0x0 == e.value && 0x0 == e.number)
			{
				joypad &= ~(1<<0);
			}

			/*B
			value:0x1 type:0x1 number:0x1
			value:0x0 type:0x1 number:0x1
			*/
			if(0x1 == e.value && 0x1 == e.number)
			{
				joypad |= 1<<1;
			}
			if(0x0 == e.value && 0x1 == e.number)
			{
				joypad &= ~(1<<1);
			}

			/*X
			value:0x1 type:0x1 number:0x3
			value:0x0 type:0x1 number:0x3
			*/
			if(0x1 == e.value && 0x3 == e.number)
			{
				joypad |= 1<<0;
			}
			if(0x0 == e.value && 0x3 == e.number)
			{
				joypad &= ~(1<<0);
			}

			/*Y
			value:0x1 type:0x1 number:0x4
			value:0x0 type:0x1 number:0x4
		 	*/
		 	if(0x1 == e.value && 0x4 == e.number)
			{
				joypad |= 1<<1;
			}
			if(0x0 == e.value && 0x4 == e.number)
			{
				joypad &= ~(1<<1);
			}
		}
		return joypad;
	}
	return -1;
}

static int USBjoypadDevInit(void)
{
	USBjoypad_fd = open(USB_JS_DEV, O_RDONLY);
	if(-1 == USBjoypad_fd)
	{
		printf("%s dev not found \r\n", USB_JS_DEV);
		return -1;
	}
	return 0;
}

static int USBjoypadDevExit(void)
{
	close(USBjoypad_fd);
	return 0;
}

static T_JoypadInput usbJoypadInput = {
	USBjoypadDevInit,
	USBjoypadDevExit,
	USBjoypadGet,
};

int InitJoypadInput(void)
{
	int iErr = 0;
	iErr = RegisterJoypadInput(&joypadInput);
	iErr = RegisterJoypadInput(&usbJoypadInput);
	return iErr;
}

int GetJoypadInput(void)
{
	/* 休眠 */
	pthread_mutex_lock(&g_tMutex);
	pthread_cond_wait(&g_tConVar, &g_tMutex);	

	/* 被唤醒后,返回数据 */
	pthread_mutex_unlock(&g_tMutex);
	return g_InputEvent;
}




