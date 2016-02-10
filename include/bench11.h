/***********************************************************************************
 *                C++11 Performance and Memory Benchmark                           *
 *   Copyright (C) 2016  Alexey Novikov (Email: alexey_AT_novikov_DOT_io)          *
 *   All rights reserved.                                                          *
 *                                                                                 *
 * Redistribution and use in source and binary forms, with or without              *
 * modification, are permitted provided that the following conditions are met:     *
 *                                                                                 *
 * 1. Redistributions of source code must retain the above copyright notice, this  *
 *    list of conditions and the following disclaimer.                             *
 * 2. Redistributions in binary form must reproduce the above copyright notice,    *
 *    this list of conditions and the following disclaimer in the documentation    *
 *    and/or other materials provided with the distribution.                       *
 *                                                                                 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND *
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          *
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR *
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES  *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;    *
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND     *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS   *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                    *
 ***********************************************************************************/

#ifndef BENCH11_H
#define BENCH11_H

#ifdef BENCH11

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>


#define BENCH11_CPU BENCH11::CPU BEHCH11_CPU_OBJ(__PRETTY_FUNCTION__, __FILE__, __LINE__);
#define BENCH11_ALL BENCH11_CPU

namespace BENCH11 {
    class Logger {
        std::string TAG = "[ BENCH11 ]: ";
    protected:
        static void logMessageSync(const std::string& message) {
            std::cerr << message << std::endl;
        }
        static void logMessageAsync(const std::string& message) {
            std::thread tr(logMessageSync, message);
            tr.join();
        }
    public:
        void logMessage(const std::string& message) const { 
                logMessageAsync(TAG + message); 
            }
        Logger(std::string methodName, std::string fileName, int lineNumber)
        {
            TAG.append("(");
            TAG.append(methodName);
            TAG.append(":");
            TAG.append(fileName);
            TAG.append(":");
            TAG.append(std::to_string(lineNumber));
            TAG.append(") ");
        }
    };
    
    class CPU {
        const Logger logger;
        const std::chrono::high_resolution_clock::time_point t_start;    
    public:
        CPU(std::string methodName, std::string fileName, int lineNumber) 
        :logger(methodName, fileName, lineNumber),
         t_start(std::chrono::high_resolution_clock::now())
        {}
        ~CPU() {
            auto t_end = std::chrono::high_resolution_clock::now();
            std::basic_ostringstream<char> os;
            os   << "Wall time: "
                 << std::chrono::duration<double, std::milli>(t_end-t_start).count()
                 << " ms";
            logger.logMessage(os.str());
        }

    };
    class MEM { /*TODO*/ };
} //namespace BENCH11
#else

#define BENCH11_CPU
#define BENCH11_MEM
#define BENCH11_ALL

#endif

#endif //BENCH11_H
