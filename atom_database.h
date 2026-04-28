#ifndef ATOM_DATABASE_H
#define ATOM_DATABASE_H

#include <cstddef>
#include <string>
#include <unordered_map>

struct Element {
    int atomic_number = 0;
    std::string name;
    std::string symbol;
    double atomic_weight = 0.0;
};

class AtomDatabase {
public:
    void load(const std::string& filename);

    bool contains(const std::string& symbol) const;
    double atomic_weight(const std::string& symbol) const;
    std::size_t size() const;

private:
    std::unordered_map<std::string, Element> elements_;
};

#endif
用途： 定义原子数据库，负责从 atom_database.txt 读取元素信息，并根据元素符号查找 atomic weight。