#include "TDMA_Solver.h"
#include "Domain.h"

void test01()
{
    vector<double> a{1, 1, 1, 1};
    a.insert(a.begin(), 0);
    vector<double> b{3, 3, 3, 3, 3};
    vector<double> c{1, 1, 1, 1};
    c.push_back(0);
    vector<double> f{1, 1, 0, 0, 0};

    TDMA_Solver solver(a, b, c, f);
    solver.solve();
    solver.output();
}

void test02()
{
    Domain d(1, 8);
    d.init(0);
    d.solve();
}

int main()
{
    test02();
    return 0;
}