#include "report.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

namespace {

void write_vector(std::ofstream& output, const Vector3& vector)
{
    output << vector.x << " " << vector.y << " " << vector.z;
}

}

void write_report(
    const std::string& output_filename,
    const std::string& molecule_filename,
    const std::string& database_filename,
    std::size_t database_size,
    const AnalysisResult& result)
{
    std::ofstream output(output_filename);

    if (!output)
        throw std::runtime_error("Cannot open report file: " + output_filename);

    output << std::setprecision(6);

    output << "Biomolecular Structure Analysis Report\n";
    output << "--------------------------------------\n";
    output << "Molecule file:      " << molecule_filename << "\n";
    output << "Atom database:      " << database_filename
           << "  (" << database_size << " elements)\n";
    output << "Number of atoms:    " << result.number_of_atoms << "\n\n";

    output << "Centre of mass:     ";
    write_vector(output, result.centre_of_mass);
    output << "\n";

    output << "Radius of gyration: "
           << result.radius_of_gyration << "\n\n";

    output << "Bounding box (min): ";
    write_vector(output, result.bounding_box.minimum);
    output << "\n";

    output << "Bounding box (max): ";
    write_vector(output, result.bounding_box.maximum);
    output << "\n";

    output << "Box size:           ";
    write_vector(output, result.bounding_box.size);
    output << "\n\n";

    output << "Pairwise distance statistics:\n";
    output << "  mean     = "
           << result.pairwise_statistics.mean << "\n";
    output << "  variance = "
           << result.pairwise_statistics.variance << "\n";
    output << "  Contacts (pairs within "
           << result.contact_cutoff
           << " A): "
           << result.pairwise_statistics.contact_count << "\n";
}
用途： 按题目要求把分析结果写入 output report 文件。