#include "bench11.h"
#include <limits>
#include <thread>
#include <chrono>

void worker() {
    BENCH11_ALL;
    for (int i = 0; i < std::numeric_limits<int>::max()/10; i++) {
         if (i == 10) BENCH11_ALL;
    }
}

void hardWorker() {
    BENCH11_ALL;
    for (int i = 0; i < std::numeric_limits<int>::max(); i++) {
    }
}    

int main() {
    BENCH11_ALL;
    std::thread t1(hardWorker);
    worker();
    t1.join();
    //Logger might need some additional time to finish  with his output.
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

