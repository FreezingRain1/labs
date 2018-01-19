#pragma once
#include "factorization.h"
#include <queue>
#include <mutex>
#include <condition_variable>


class threader {

public:
    explicit threader(const std::string &in, const std::string &out) :
		f1(InputFile, OutputFile), InputFile(in), OutputFile (out)
    {
    }
    void threader_function();
private:
    std::string InputFile, OutputFile;
    factorization f1;
    void producer();
    void consumer();

	std::mutex _mutex;
	std::condition_variable cv;
	std::queue<uint64_t> queue_num;
	uint64_t num;
	bool is_finished = false;
	bool exit = false;
	bool done = false;
	bool is_pause = false;

};

