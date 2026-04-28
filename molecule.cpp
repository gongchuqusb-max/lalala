#include "molecule.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

bool is_comment_or_blank(const std::string& line)
{
    std::size_t first = line.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return true;

    return line[first] == '#';
}

}

void Molecule::load(const std::string& filename, const AtomDatabase& database)
{
    std::ifstream input(filename);

    if (!input)
        throw std::runtime_error("Cannot open molecule file: " + filename);

    atoms_.clear();

    std::string line;

    while (std::getline(input, line)) {
        if (is_comment_or_blank(line))
            continue;

        std::istringstream stream(line);

        Atom atom;

        if (!(stream >> atom.symbol
                   >> atom.position.x
                   >> atom.position.y
                   >> atom.position.z)) {
            throw std::runtime_error("Invalid molecule line: " + line);
        }

        atom.mass = database.atomic_weight(atom.symbol);

        atoms_.push_back(atom);
    }

    if (atoms_.empty())
        throw std::runtime_error("Molecule contains no atoms");
}

std::size_t Molecule::size() const
{
    return atoms_.size();
}

const std::vector<Atom>& Molecule::atoms() const
{
    return atoms_;
}
用途： 实现分子坐标文件读取，根据元素符号从数据库查找对应 atomic weight。