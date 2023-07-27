#include "sem_pack.hpp"

namespace letMeSee
{
    SemaphorePack::SemaphorePack()
    {
        sem_init(&(this->sem), 0, 0);
    }

    SemaphorePack::SemaphorePack(int value)
    {
        sem_init(&(this->sem), 0, value);
    }

    SemaphorePack::~SemaphorePack()
    {
        sem_destroy(&(this->sem));
    }

    void SemaphorePack::post()
    {
        sem_post(&sem);
    }

    void SemaphorePack::wait()
    {
        sem_wait(&sem);
    }

}