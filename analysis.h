#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "geometry.h"
#include "molecule.h"

#include <cstddef>

struct BoundingBox {
    Vector3 minimum;
    Vector3 maximum;
    Vector3 size;
};

struct PairwiseStatistics {
    double mean = 0.0;
    double variance = 0.0;
    std::size_t contact_count = 0;
};

struct AnalysisResult {
    std::size_t number_of_atoms = 0;
    double total_mass = 0.0;
    Vector3 centre_of_mass;
    double radius_of_gyration = 0.0;
    BoundingBox bounding_box;
    PairwiseStatistics pairwise_statistics;
    double contact_cutoff = 5.0;
};

AnalysisResult analyse_molecule(const Molecule& molecule, double contact_cutoff);

#endif
用途：声明所有结构分析结果和分析函数，包括centre of mass, radius of gyration, bounding box, pairwise distance statistics和contact count