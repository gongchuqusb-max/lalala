#include "analysis.h"

#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {

double compute_total_mass(const Molecule& molecule)
{
    double total = 0.0;

    for (const Atom& atom : molecule.atoms())
        total += atom.mass;

    return total;
}

Vector3 compute_centre_of_mass(const Molecule& molecule, double total_mass)
{
    Vector3 weighted_sum;

    for (const Atom& atom : molecule.atoms())
        weighted_sum = weighted_sum + atom.mass * atom.position;

    return weighted_sum / total_mass;
}

double compute_radius_of_gyration(
    const Molecule& molecule,
    const Vector3& centre_of_mass,
    double total_mass)
{
    double weighted_squared_sum = 0.0;

    for (const Atom& atom : molecule.atoms()) {
        Vector3 difference = atom.position - centre_of_mass;
        weighted_squared_sum += atom.mass * squared_length(difference);
    }

    return std::sqrt(weighted_squared_sum / total_mass);
}

BoundingBox compute_bounding_box(const Molecule& molecule)
{
    const std::vector<Atom>& atoms = molecule.atoms();

    BoundingBox box;

    box.minimum = atoms.front().position;
    box.maximum = atoms.front().position;

    for (const Atom& atom : atoms) {
        const Vector3& p = atom.position;

        if (p.x < box.minimum.x)
            box.minimum.x = p.x;
        if (p.y < box.minimum.y)
            box.minimum.y = p.y;
        if (p.z < box.minimum.z)
            box.minimum.z = p.z;

        if (p.x > box.maximum.x)
            box.maximum.x = p.x;
        if (p.y > box.maximum.y)
            box.maximum.y = p.y;
        if (p.z > box.maximum.z)
            box.maximum.z = p.z;
    }

    box.size = box.maximum - box.minimum;

    return box;
}

PairwiseStatistics compute_pairwise_statistics(
    const Molecule& molecule,
    double contact_cutoff)
{
    const std::vector<Atom>& atoms = molecule.atoms();

    PairwiseStatistics statistics;
    std::vector<double> distances;

    for (std::size_t i = 0; i < atoms.size(); ++i) {
        for (std::size_t j = i + 1; j < atoms.size(); ++j) {
            double distance =
                distance_between(atoms[i].position, atoms[j].position);

            distances.push_back(distance);

            if (distance <= contact_cutoff)
                ++statistics.contact_count;
        }
    }

    if (distances.empty())
        return statistics;

    double sum = 0.0;

    for (double distance : distances)
        sum += distance;

    statistics.mean = sum / static_cast<double>(distances.size());

    double squared_difference_sum = 0.0;

    for (double distance : distances) {
        double difference = distance - statistics.mean;
        squared_difference_sum += difference * difference;
    }

    statistics.variance =
        squared_difference_sum / static_cast<double>(distances.size());

    return statistics;
}

}

AnalysisResult analyse_molecule(const Molecule& molecule, double contact_cutoff)
{
    if (molecule.size() == 0)
        throw std::runtime_error("Cannot analyse an empty molecule");

    if (contact_cutoff < 0.0)
        throw std::runtime_error("Contact cutoff must be non-negative");

    AnalysisResult result;

    result.number_of_atoms = molecule.size();
    result.contact_cutoff = contact_cutoff;
    result.total_mass = compute_total_mass(molecule);

    if (result.total_mass <= 0.0)
        throw std::runtime_error("Total molecular mass must be positive");

    result.centre_of_mass =
        compute_centre_of_mass(molecule, result.total_mass);

    result.radius_of_gyration =
        compute_radius_of_gyration(
            molecule,
            result.centre_of_mass,
            result.total_mass);

    result.bounding_box = compute_bounding_box(molecule);

    result.pairwise_statistics =
        compute_pairwise_statistics(molecule, contact_cutoff);

    return result;
}
用途： 实现分子结构计算：总质量、质心、回转半径、bounding box、两两距离均值、方差和 contacts。