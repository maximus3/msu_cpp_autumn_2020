#include <thread>
#include <vector>
#include <future>
#include <queue>
#include <memory>
#include <iostream>
#include <condition_variable>

class ThreadPool
{
    using Lock = std::unique_lock<std::mutex>;
private:
    std::vector<std::thread> threads;
    bool active = true;
    std::mutex mutex;
    std::condition_variable queue_ready;
    std::queue<std::function<void()>> tasks;
public:
    explicit ThreadPool(size_t poolSize) {
        for (size_t i = 0; i < poolSize; i++) {
            threads.emplace_back(std::thread([this]() {
                std::function<void()> task;
                while (true) {
                    {
                        Lock lock(mutex);

                        if (!active && tasks.empty()) {
                            return;
                        }

                        while (active && tasks.empty()) {
                            queue_ready.wait(lock);
                        }

                        if (!active && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            }));
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        using return_type = decltype(func(args...));

        auto task = std::make_shared<std::packaged_task<return_type()>>([func, args...]() {
            return func(args...); 
        });
        {
            Lock lock(mutex);
            tasks.push([task]() { (*task)(); });
        }
        queue_ready.notify_one();
        return task->get_future();
    }

    ~ThreadPool() {
        {
            Lock lock(mutex);
            active = false;
        }
        queue_ready.notify_all();
        for (auto& thread : threads) {
            thread.join();
        }
    }
};