#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

struct CPUStats {
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
};

CPUStats readCPUStats() {
    std::ifstream file("/proc/stat");
    std::string line;
    CPUStats stats{
        .user = 0, .nice = 0, .system = 0, .idle = 0, .iowait = 0, .irq = 0, .softirq = 0};
    if (file.is_open()) {
        std::getline(file, line);
        sscanf(line.c_str(), "cpu  %llu %llu %llu %llu %llu %llu %llu", &stats.user, &stats.nice,
               &stats.system, &stats.idle, &stats.iowait, &stats.irq, &stats.softirq);
    }
    return stats;
}

double calculateUsage(const CPUStats& prev, const CPUStats& curr) {
    unsigned long long prevIdle = prev.idle + prev.iowait;
    unsigned long long currIdle = curr.idle + curr.iowait;

    unsigned long long prevNonIdle = prev.user + prev.nice + prev.system + prev.irq + prev.softirq;
    unsigned long long currNonIdle = curr.user + curr.nice + curr.system + curr.irq + curr.softirq;

    unsigned long long prevTotal = prevIdle + prevNonIdle;
    unsigned long long currTotal = currIdle + currNonIdle;

    unsigned long long totald = currTotal - prevTotal;
    unsigned long long idled = currIdle - prevIdle;

    if (totald == 0) return 0.0;

    return (double)(totald - idled) * 100.0 / totald;
}

int main() {
    CPUStats prev = readCPUStats();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        CPUStats curr = readCPUStats();
        double usage = calculateUsage(prev, curr);
        std::cout << "CPU Usage: " << usage << "%\n";

        if (usage > 80.0) {
            std::cout << "Alert. CPU usage above 80%\n";
        }

        prev = curr;
    }
}
