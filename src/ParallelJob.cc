#include <functional>
#include <chrono>
#include <iostream>
#include "ParallelJob.h"



ParallelJob::ParallelJob(){}
ParallelJob::~ParallelJob(){}

ParallelSave::ParallelSave(){}
ParallelSave::~ParallelSave() {stopThread();}

void ParallelSave::startThread()
{
    if(thread_ == nullptr)
    {
        thread_running_ = true;
        thread_ = new std::thread(&ParallelSave::parallel, this);
    }
}

void ParallelSave::stopThread()
{
    if(thread_ != nullptr)
        {
            thread_running_ = false;
            thread_->join();
            delete thread_;
            thread_ = nullptr;
        }
}

void ParallelSave::parallel()
{
    while(thread_running_== true)
        {
            std::cout << "save" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep one second
        }
}

ParallelMeasurement::ParallelMeasurement(){}
ParallelMeasurement::~ParallelMeasurement() {stopThread();}

void ParallelMeasurement::startThread()
{
    if(thread_ == nullptr)
    {
        thread_running_ = true;
        thread_ = new std::thread(&ParallelMeasurement::parallel, this);
    }
}

void ParallelMeasurement::stopThread()
{
    if(thread_ != nullptr)
        {
            thread_running_ = false;
            thread_->join();
            delete thread_;
            thread_ = nullptr;
        }
}

void ParallelMeasurement::parallel()
{
    while(thread_running_== true)
        {
            std::cout << "measure" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep one second
        }
}


