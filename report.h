#ifndef REPORT_H
#define REPORT_H

#include "analysis.h"

#include <cstddef>
#include <string>

void write_report(
    const std::string& output_filename,
    const std::string& molecule_filename,
    const std::string& database_filename,
    std::size_t database_size,
    const AnalysisResult& result);

#endif
用途： 声明输出分析报告的函数。