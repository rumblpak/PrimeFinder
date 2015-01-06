// primes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "LIMITS.h"
#include "math.h"

static HANDLE Thread_semaphore;
DWORD WINAPI isPrimeThread(LPVOID lpArg);
bool isPrimeHelp(int arg);
int prime_count = 2;
int cpucount = 2;

int _tmain(int argc, _TCHAR* argv[])
{	
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	cpucount = (int)sysinfo.dwNumberOfProcessors;
	if (cpucount > 8) cpucount = 8;

	DWORD dwThread1ID = 0;
	HANDLE hThread1;
	HANDLE hThread2;
	HANDLE hThread3;
	HANDLE hThread4;
	HANDLE hThread5;
	HANDLE hThread6;
	HANDLE hThread7;
	HANDLE hThread8;
	INT nParameter = 1;
	
	DWORD time_count;

	printf("Prime Number Finder\n\n");


	//find primes not threaded
	time_count = GetTickCount();

	for (int i = 3; i <= 1000000; i = i + 2) { //1000000
		if(isPrimeHelp(i)){
			//printf("Found %d to be prime.\n",i);
			prime_count++;
		}
	}
	time_count = GetTickCount() - time_count;
	printf("\nNonthreaded Prime Finder found %d primes in %d milliseconds \n\n",prime_count,time_count);

	//Reset prime count for threaded process
	prime_count=2;

	//Finding primes threaded
	Thread_semaphore = CreateSemaphore(NULL, 0, cpucount, TEXT("Thread_Done"));
	time_count = GetTickCount();
	hThread1 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread2 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread3 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread4 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread5 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread6 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread7 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	hThread8 = CreateThread(NULL, 0, isPrimeThread, (LPVOID)nParameter, 0, &dwThread1ID);
	nParameter++;
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	WaitForSingleObject(Thread_semaphore, INFINITE);
	time_count = GetTickCount() - time_count;
	printf("\nThreaded Prime Finder found %d primes in %d milliseconds \n\n",prime_count,time_count);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);
	CloseHandle(hThread5);
	CloseHandle(hThread6);
	CloseHandle(hThread7);
	CloseHandle(hThread8);


	char *str;
	printf("\n\n<Press the any key to continue>");
	scanf_s("%c",&str);
	
	
	return 0;
}

DWORD WINAPI isPrimeThread(LPVOID lpArg) {
	static HANDLE Count_mutex = CreateMutex(0, false, NULL);
	INT threadnumber = (INT) lpArg;
	for (int i = 3 + 2 * (threadnumber - 1); i <= 1000000; i = i + cpucount * 2) { //1000000
		if(isPrimeHelp(i)){
			WaitForSingleObject(Count_mutex, INFINITE);
			prime_count++;
			ReleaseMutex(Count_mutex);
		}
	}
	ReleaseSemaphore(Thread_semaphore, 1, NULL);
	return 0;
}

bool isPrimeHelp(int arg) {
	for(int i=3; i<(arg>>1);i++){
		if(arg % i == 0) return false;
	}
	return true;
}
