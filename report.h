#ifndef REPORT_H
#define REPORT_H

#include "analysis.h"

#include <string>

void write_report(const std::string& filename, const AnalysisResult& result);

#endif
用处：
声明输出 report 的函数，让 main.cpp 更干净