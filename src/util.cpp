#include "util.hpp"
#include <sys/syscall.h>

namespace letMeSee
{
    pid_t GetThreadId()
    {
        return syscall(SYS_gettid);
    }

    Semaphore::Semaphore(unsigned int value)
    {
        sem_init(&(this->semVar), 0, value);
    }

    Semaphore::~Semaphore()
    {
        sem_destroy(&(this->semVar));
    }

    void Semaphore::wait()
    {
        sem_wait(&(this->semVar));
    }

    void Semaphore::post()
    {
        sem_post(&(this->semVar));
    }

}