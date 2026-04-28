#ifndef MOLECULE_H
#define MOLECULE_H

#include "atom_database.h"
#include "geometry.h"

#include <cstddef>
#include <string>
#include <vector>

struct Atom {
    std::string symbol;
    double mass = 0.0;
    Vector3 position;
};

class Molecule {
public:
    void load(const std::string& filename, const AtomDatabase& database);

    std::size_t size() const;
    const std::vector<Atom>& atoms() const;

private:
    std::vector<Atom> atoms_;
};

#endif
用途： 定义 Atom 和 Molecule，负责保存分子中所有原子的符号、质量和三维坐标。