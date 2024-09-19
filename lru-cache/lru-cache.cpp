#include <bits/stdc++.h>
using namespace std;

// REQUIREMENTS-
// size=10
// 1,2,3,4,5,6,7,8,9,10-> unordered_map<key,Node*>
// unordered_map<key,value>data;
//  1) lru cache properly --- gets(key), updates(key) ,insert(key)-->used   ,,, deleteKey(),insert(),update(),get(key)
// 2) no ttl as of now

class Cache
{
private:
    unordered_map<string, any> data;
};

class EvictionStrategy
{
public:
    string evict() = 0;
    void retrived(string key) = 0;
};
class LRUEvictionStrategy : public EvictionStrategy
{
private:
public:
    string evict()
    {
    }
    void retrived(string key)
    {
    }
};
class LFUEvictionStrategy : public EvictionStrategy
{
    // map<int,vector<string>>map;//freq=[keys]
    // unordered_map<string,int>data;
};

// interface
// LRU strategy-> evict()

int main()
{
}