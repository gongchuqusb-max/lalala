#include "atom_database.h"

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

void AtomDatabase::load(const std::string& filename)
{
    std::ifstream input(filename);

    if (!input)
        throw std::runtime_error("Cannot open atom database file: " + filename);

    elements_.clear();

    std::string line;

    while (std::getline(input, line)) {
        if (is_comment_or_blank(line))
            continue;

        std::istringstream stream(line);

        Element element;

        if (!(stream >> element.atomic_number
                   >> element.name
                   >> element.symbol
                   >> element.atomic_weight)) {
            throw std::runtime_error("Invalid atom database line: " + line);
        }

        elements_[element.symbol] = element;
    }

    if (elements_.empty())
        throw std::runtime_error("Atom database is empty");
}

bool AtomDatabase::contains(const std::string& symbol) const
{
    return elements_.find(symbol) != elements_.end();
}

double AtomDatabase::atomic_weight(const std::string& symbol) const
{
    auto element = elements_.find(symbol);

    if (element == elements_.end())
        throw std::runtime_error("Unknown atom symbol: " + symbol);

    return element->second.atomic_weight;
}

std::size_t AtomDatabase::size() const
{
    return elements_.size();
}
用途： 实现原子数据库文件读取，忽略空行和 # 注释行。