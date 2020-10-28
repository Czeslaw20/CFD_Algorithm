//求解三对角矩阵的TDMA方法
//向前消元foward elimination  回代backward substitution
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class TDMA_Solver
{
public:
    TDMA_Solver(vector<double> a, vector<double> b, vector<double> c, vector<double> d);
    void showMatrix();
    void output();
    void solve();

    ~TDMA_Solver();

private:
    int m_N;
    vector<double> m_a;
    vector<double> m_b;
    vector<double> m_c;
    vector<double> m_f;
    vector<double> m_phi;
};
