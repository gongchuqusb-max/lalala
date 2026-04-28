#include "analysis.h"
#include "atom_database.h"
#include "molecule.h"
#include "report.h"

#include <exception>
#include <iostream>
#include <string>

namespace {

void print_usage(const char* program_name)
{
    std::cerr << "Usage:\n";
    std::cerr << "  " << program_name
              << " atom_database.txt molecule.txt output_report.txt [cutoff]\n";
    std::cerr << "\n";
    std::cerr << "If cutoff is not provided, the default value is 5.0 A.\n";
}

double read_cutoff(int argc, char* argv[])
{
    if (argc == 5)
        return std::stod(argv[4]);

    return 5.0;
}

}

int main(int argc, char* argv[])
{
    try {
        if (argc != 4 && argc != 5) {
            print_usage(argv[0]);
            return 1;
        }

        std::string database_filename = argv[1];
        std::string molecule_filename = argv[2];
        std::string output_filename = argv[3];

        double contact_cutoff = read_cutoff(argc, argv);

        AtomDatabase database;
        database.load(database_filename);

        Molecule molecule;
        molecule.load(molecule_filename, database);

        AnalysisResult result =
            analyse_molecule(molecule, contact_cutoff);

        write_report(
            output_filename,
            molecule_filename,
            database_filename,
            database.size(),
            result);

        std::cout << "Analysis complete.\n";
        std::cout << "Report written to: " << output_filename << "\n";

        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }
}
用途： 主程序入口。读取命令行参数，加载数据库和分子文件，执行分析，输出报告。