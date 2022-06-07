#ifndef ParallelJob_H
#define ParallelJob_H

#include <thread>
#include <atomic>

class ParallelJob
{
public:
    ParallelJob();
    virtual ~ParallelJob();
    virtual void startThread() = 0;
    virtual void stopThread() = 0;
    virtual void parallel() = 0;
protected:
    std::thread* thread_ = nullptr;
    std::atomic<bool> thread_running_ = false;
};


class ParallelSave : public ParallelJob
{
public:
    ParallelSave();
    ~ParallelSave();
    void startThread() override;
    void stopThread() override;
    void parallel() override;
};

class ParallelMeasurement : public ParallelJob
{
public:
    ParallelMeasurement();
    ~ParallelMeasurement();
    void startThread() override;
    void stopThread() override;
    void parallel() override;

};

#endif