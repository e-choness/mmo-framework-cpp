#pragma once
#include "std_common.hpp"

namespace network{
    template<typename T>
    class TSQueue{
    public:
        TSQueue() = default;
        TSQueue(TSQueue& queue) = delete;
        virtual ~TSQueue(){ clear(); }

        const T& front(){
            std::scoped_lock lock(mQueueLock);
            return mDequeue.front();
        }

        const T& back(){
            std::scoped_lock lock(mQueueLock);
            return mDequeue.back();
        }

        void pushBack(const T& item){
            std::scoped_lock lock(mQueueLock);
            mDequeue.emplace_back(std::move(item));
        }

        void pushFront(const T& item){
            std::scoped_lock lock(mQueueLock);
            mDequeue.emplace_front(std::move(item));
        }

        T popFront(){
            std::scoped_lock lock(mQueueLock);
            auto t = std::move(mDequeue.front());
            mDequeue.pop_front();
            return t;
        }

        T popBack(){
            std::scoped_lock lock(mQueueLock);
            auto t = std::move(mDequeue.back());
            mDequeue.pop_back();
            return t;
        }


        size_t size(){
            std::scoped_lock lock(mQueueLock);
            return mDequeue.size();
        }

        void clear(){
            std::scoped_lock lock(mQueueLock);
            mDequeue.clear();
        }

        bool isEmpty(){
            std::scoped_lock lock(mQueueLock);
            return mDequeue.empty();
        }

    protected:
        std::mutex mQueueLock;
        std::deque<T> mDequeue;
    };
}