#ifndef ROCKET_UTIL_H__
#define ROCKET_UTIL_H__
#include<stdint.h>
#include<sys/types.h>
namespace rocket{

pid_t getPid();

pid_t getThreadId();

int64_t getNowMs();

int32_t getInt32FromNetByte(const char* buf);
}

#endif