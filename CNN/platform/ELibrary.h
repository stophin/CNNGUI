//ELibrary.h
//now we're using ege library tool
//you may change this
//once changed, associated files should be changed
//Author: Stophin
//2014.01.08
//Ver: 0.01
//
#ifndef _ELIBRARY_H_
#define _ELIBRARY_H_


#ifdef _NANO_MINGW_
#define _NANOC_WINDOWS_
#endif

#ifndef _NANO_LINUX_
#define _NANOC_WINDOWS_
#endif

#define _THREAD_SEM_

#ifndef MIN
#define MIN(A,B)	(((A) <= (B)) ? (A) : (B))
#endif

#ifndef MAX
#define MAX(A,B)	(((A) >= (B)) ? (A) : (B))
#endif

#ifdef _NANOC_WINDOWS_

#define SHOW_CONSOLE

#include <graphics.h>

int getch_console();
int kbhit_console();


struct EPointF {
	FLOAT X;
	FLOAT Y;
};

struct ERectF {
	FLOAT X;
	FLOAT Y;
	FLOAT Width;
	FLOAT Height;
};

#define EP_GetWnd getHWnd
#define EP_MouseHit mousemsg
#define EP_MouseMsg mouse_msg
#define EP_GetMouseMsg getmouse

#define EP_IsWheel(msg) msg.is_wheel()
#define EP_IsRight(msg) msg.is_right()
#define EP_IsLeft(msg) msg.is_left()
#define EP_IsDown(msg) msg.is_down()
#define EP_IsUp(msg) msg.is_up()
#define EP_IsMove(msg) msg.is_move()
#define EP_Wheel(msg) msg.wheel()
#define EP_X(msg) (msg.x)
#define EP_Y(msg) (msg.y)

#define EP_KBMsg kbmsg
#define EP_MSG key_msg
#define EP_GetKBMsg getkey
#define EP_KBIsUp(msg) (msg.msg == key_msg_up)
#define EP_KBIsDown(msg) (msg.msg == key_msg_down)
#define EP_GetKey(msg) (msg.key)
#define EP_Equal(msg, val) (msg.key == val)

#define EP_FlushKey flushkey
#define EP_FlushMouse flushmouse

#define EP_Delay(ms) delay_ms(ms)
#define EP_ClearDevice cleardevice




#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
//#include <conio.h>
#include <time.h>

#include <math.h>

#define scanf scanf_s
#include <process.h>

typedef void *HANDLE;
typedef HANDLE HANDLE_MUTEX;
#define __NANOC_THREAD_FUNC_DECLARE(hHandle, pFuncName)\
	public:\
	HANDLE hHandle;\
	static unsigned int __stdcall pFuncName(void *pv);
#define __NANOC_THREAD_FUNC_BEGIN__(pFuncName) unsigned int __stdcall pFuncName(void *pv)
#define __NANOC_THREAD_FUNC_END__(nReturn) return nReturn

#define __NANOC_THREAD_BEGIN__(hHandle, pFuncName, pParam) hHandle = (HANDLE)_beginthreadex(NULL, 0, &pFuncName, pParam, 0, 0)
#define __NANOC_THREAD_WAIT__(hHandle) WaitForSingleObject(hHandle, 1000)
#define __NANOC_THREAD_END__(hHandle) TerminateThread(hHandle, 0)
#define __NANOC_THREAD_CLOSE__(hHandle) ::CloseHandle(hHandle)

#ifndef _THREAD_SEM_
#define __NANOC_THREAD_MUTEX_INIT__(hMutex, obj) obj->hMutex = CreateMutex(NULL, FALSE, NULL)
#define __NANOC_THREAD_MUTEX_LOCK__(hMutex) WaitForSingleObject(hMutex, INFINITE)
#define __NANOC_THREAD_MUTEX_UNLOCK__(hMutex) ReleaseMutex(hMutex);
#else
#define __NANOC_THREAD_MUTEX_INIT__(hMutex, obj) obj->hMutex = CreateSemaphore(NULL, 1, 1, NULL)
#define __NANOC_THREAD_MUTEX_LOCK__(hMutex) WaitForSingleObject(hMutex, INFINITE)
#define __NANOC_THREAD_MUTEX_UNLOCK__(hMutex) ReleaseSemaphore(hMutex, 1, NULL);
#endif

#ifdef _NANO_MINGW_
#define fopen_s(fp, filename, mode) *fp = fopen(filename, mode)
#undef scanf
#undef getch
#undef kbhit
#define max MAX
#define min MIN
#define INT_MIN     (-2147483647 - 1) // minimum (signed) int value
#define INT_MAX       2147483647    // maximum (signed) int value
#endif

#else 

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <malloc.h>

#define CLK_TCK _SC_CLK_TCK
typedef unsigned int * WPARAM;
typedef float FLOAT;


struct EPointF {
	FLOAT X;
	FLOAT Y;
};

struct ERectF {
	FLOAT X;
	FLOAT Y;
	FLOAT Width;
	FLOAT Height;
};

#include <math.h>

void changemode(int dir)
{
	static struct termios oldt, newt;

	if (dir == 1)
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit(void)
{
	struct timeval tv;
	fd_set rdfs;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rdfs);
	FD_SET(STDIN_FILENO, &rdfs);

	select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}

int getch(void)
{
	struct termios tm, tm_old;
	int fd = 0, ch;

	if (tcgetattr(fd, &tm) < 0) {//�������ڵ��ն�����
		return -1;
	}

	tm_old = tm;
	cfmakeraw(&tm);//�����ն�����Ϊԭʼģʽ����ģʽ�����е������������ֽ�Ϊ��λ������
	if (tcsetattr(fd, TCSANOW, &tm) < 0) {//�����ϸ���֮�������
		return -1;
	}

	ch = getchar();
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//��������Ϊ���������
		return -1;
	}

	return ch;
}

int getch_console() {
	return getch();
}
int kbhit_console() {
	return kbhit();
}
#define INT		int
#define VOID	void
#define _TCHAR	char

#define min(x, y) (x > y ? y : x)
#define max(x, y) (x > y ? x : y)

#define fopen_s(fp, filename, mode) *fp = fopen(filename, mode)
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

typedef void * HINSTANCE;
typedef pthread_t HANDLE;
#define __NANOC_THREAD_FUNC_DECLARE(hHandle, pFuncName)\
	private:\
	HANDLE hHandle; \
	static void * pFuncName(void *pv);
#define __NANOC_THREAD_FUNC_BEGIN__(pFuncName) void * pFuncName(void *pv)
#define __NANOC_THREAD_FUNC_END__(nReturn) pthread_exit((void *)nReturn)

#define __NANOC_THREAD_BEGIN__(hHandle, pFuncName, pParam) pthread_create(&hHandle, NULL, pFuncName, pParam)
#define __NANOC_THREAD_WAIT__(hHandle) pthread_cancel(hHandle)
#define __NANOC_THREAD_END__(hHandle) pthread_kill(hHandle, 0)
#define __NANOC_THREAD_CLOSE__(hHandle) 

#ifndef _THREAD_SEM_
typedef pthread_mutex_t HANDLE_MUTEX;
#define __NANOC_THREAD_MUTEX_INIT__(hMutex, obj) pthread_mutex_init(&obj->hMutex, NULL)
#define __NANOC_THREAD_MUTEX_LOCK__(hMutex)  pthread_mutex_lock(&hMutex)
#define __NANOC_THREAD_MUTEX_UNLOCK__(hMutex) pthread_mutex_unlock(&hMutex)
#else
typedef sem_t HANDLE_MUTEX;
#define __NANOC_THREAD_MUTEX_INIT__(hMutex, obj) sem_init(&obj->hMutex, 0, 0);sem_post(&obj->hMutex)
#define __NANOC_THREAD_MUTEX_LOCK__(hMutex)  sem_wait(&hMutex)
#define __NANOC_THREAD_MUTEX_UNLOCK__(hMutex) sem_post(&hMutex)
#endif
#endif

#define ZERO	1e-10
#define ISZERO(x) (x > -ZERO && x < ZERO)

//#define EFTYPE double

#endif	//end of _ELIBRARY_H_
//end of file
