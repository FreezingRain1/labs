#include <fstream>
#include <thread>
#include "thread.h"



void threader::producer() {
    std::ifstream fin(InputFile);
    std::ofstream fout(OutputFile);
    while (!fin.eof() && !exit){
        {
            fin >> num;
            std::lock_guard<std::mutex> lock(_mutex);
            queue_num.push(num);
            while ( is_pause ) {
                std::this_thread::sleep_for ( std::chrono::seconds(1) );
            }
        }
        cv.notify_all();
    }
    {
        std::lock_guard<std::mutex> lock(_mutex);
        is_finished = true;
    }
    cv.notify_all();
}

void threader::consumer() {
    std::ofstream fout(OutputFile);
    uint64_t Number;
    while(true){
        std::unique_lock<std::mutex> lock(_mutex);
        cv.wait(lock, [] { return is_finished || !queue_num.empty(); });
        //lock.unlock();
        while(!queue_num.empty()){
            //lock.lock();
            Number = queue_num.front();
            queue_num.pop();
            lock.unlock();

            f1.factorization_value(Number);

			lock.lock();
            fout<<f1.check()<<f1.generate_str()<<"\n";
            if ( exit ) {
                while ( !queue_num.empty() )
                queue_num.pop();
            }
            if (is_pause) fout.close();
            while ( is_pause ) {
                std::this_thread::sleep_for ( std::chrono::seconds(1) );
            }

        }

        if(is_finished) {
            done = true;
            break;
        }
    }
}

void threader::threader_function() {
    std::string str;
    std::thread thr1(&threader::producer, this);
    std::thread thr2(&threader::consumer, this);
    while (!exit)
    {
        std::cin>>str;
        if (str == "exit" || done)
        {
            exit = true;
        }
        if ( str == "pause" ) {
            is_pause = true;
        }
        if ( str == "resume" ) {
            is_pause = false;
        }
    }
    thr1.join();
    thr2.join();
}
