#pragma once
#include<string>
using std::string;

template <typename T>
struct GreaterFirst
{
    bool operator()(const T& a, const T& b) const 
    {
        return a > b;
    }
};

struct LongestStringFirst
{
    bool operator()(const string& a, const string& b) const
    {
        return a.size() > b.size();
    }
};