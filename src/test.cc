#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

using node_set = std::unordered_set<int>;
struct set_hash
{
    std::size_t operator()(const node_set& s) const noexcept
    {
        std::size_t res;
        for(auto i : s)
            res ^= ((i >> 16) ^ i) * 0x45d9f3b;
        return res;
    }
};

std::unordered_map<node_set, int, set_hash> node_group;

int main()
{
    cout << boolalpha;

    node_group.insert({ {1}, 1 });
    cout << (node_group.find({ 1 }) == node_group.end()) << endl;
    cout << (node_group.find({ 1,2 }) == node_group.end()) << endl;
    node_group.insert({ {1,2}, 3 });
    cout << (node_group.find({ 1 }) == node_group.end()) << endl;
    cout << (node_group.find({ 1,2 }) == node_group.end()) << endl;
    int res;
    res ^= 1;
    auto h = set_hash{}({1,2});
    cout << h << res;
    for(auto p : node_group){
        for(auto i : p.first){
            cout << i << ", ";
        }
        cout << "-->" <<p.second << endl;
    }
}