#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#pragma warning(disable : 4996)

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void time_to_int(int* h, int* m, int* s, std::string str) {
    int temp[3]{ 0,0,0 };
    int pos = 0;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ':') {
            pos++;
            continue;
        }

        temp[pos] = temp[pos] * 10 + (int)str[i] - 48;

    }
    *h = temp[0];
    *m = temp[1];
    *s = temp[2];
}

int duration_second(std::string str1, std::string str2) {
    int hh = 0, mm = 0, ss = 0; // timer
    int h = 0, m = 0, s = 0; // input
    time_to_int(&hh, &mm, &ss, str1);
    time_to_int(&h, &m, &s, str2);

    int timer = hh * 3600 + mm * 60 + ss;
    int time_input = h * 3600 + m * 60 + s;
    
    return time_input - timer;
}

class Test {
    std::atomic<bool> running;
    std::atomic<bool> running_clock;
    std::atomic<bool> renderedText;

    std::mutex inputMutex;
    std::mutex clockMutex;

    std::thread clockThread;
    std::thread inputThread;

    char tmBuff[99]{}, buffer[99]{};
    std::chrono::duration<int, std::ratio<1>> Nday;

    void renderText() {
        if (!renderedText) {
            renderedText = true;
            std::cout << "~~~~Clock~~~~" << std::endl;
        }
    }

    void set_clock_with_input(const std::string& input) {
        
        if (input == "set") {
            std::cout << "time input: ";
            std::string input;
            std::getline(std::cin, input);

            std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
            time_t legacyStart = std::chrono::system_clock::to_time_t(start);

            /*struct tm timeinfo;
            localtime_s(&timeinfo, &legacyStart);
            strftime(tmBuff, sizeof(tmBuff), "%H:%M:%S", &timeinfo);*/

            std::tm* ptm = std::localtime(&legacyStart);
            std::strftime(tmBuff, sizeof(tmBuff), "%X", ptm);

            int dura = duration_second(std::string(tmBuff), input);
            
            std::chrono::duration<int, std::ratio<1>> s(dura);
            Nday = s;
            renderedText = false;
        }else if(input == "stop") {
            quit();
        }
        else if (input == "cls") {
            renderedText = false;
            Clear();
        }
       
    }

public:
    Test() : running(true), renderedText(false), running_clock(true),
        clockThread(&Test::get_clock, this),
        inputThread(&Test::input, this), Nday(0)
    {

    }

    ~Test() {
        
    }

    inline void quit() {
        running = false;
        running_clock = false;
    }

    void task_handle_input() {
        std::string input;
        std::getline(std::cin, input);
        set_clock_with_input(input);
    }

    void task_get_clock() {
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now()+Nday;
        time_t legacyStart = std::chrono::system_clock::to_time_t(start);

       /* ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
        std::string output(tmBuff);*/
        
        /*struct tm timeinfo;
        localtime_s(&timeinfo, &legacyStart);
        strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);*/

        std::tm* ptm = std::localtime(&legacyStart);
        std::strftime(buffer, sizeof(buffer), "%X", ptm);

        std::cout << "Time: " << buffer<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    void input() {
        while (running) {
            std::lock_guard<std::mutex> locker(inputMutex);
            //inputMutex.lock();
            task_handle_input();
            //inputMutex.unlock();

        }
    }

    void get_clock() {
        while (running_clock) {
            std::lock_guard<std::mutex> locker(clockMutex);
            //clockMutex.lock();
            renderText();
            task_get_clock();
            //clockMutex.unlock();

        }
    }

    void start() {
        if (inputThread.joinable()) {
            inputThread.join();
        }
        else {
            std::cout << "Input Thread not join "<<inputThread.get_id();
        }
        if (clockThread.joinable()) {
            clockThread.join();
        }
        else {
            std::cout << "Clock Thread not join "<<clockThread.get_id();
        }
        
    }
};




int main() {
    std::unique_ptr<Test> test = std::make_unique<Test>();
    test->start();
    return 0;
}