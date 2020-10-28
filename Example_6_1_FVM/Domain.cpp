#include "Domain.h"
#include <math.h>
#include "TDMA_Solver.h"
#include <fstream>

Domain::Domain(double L, int N)
    : m_L(L), m_N(N), m_dx(L / N)
{
    for (int i = 0; i < N; ++i)
    {
        A.emplace_back(N, 0);
    }
    B.assign(N, 0);
    x.assign(N, 0);
    phi.assign(N, 0);
}

Domain::~Domain()
{
}

double Domain::leftBC()
{
    double lb;
    lb = 0;
    return lb;
}

double Domain::rightBC()
{
    double rb;
    rb = 0;
    return rb;
}

double Domain::source(double x)
{
    double src;
    src = -cos(x);
    return src;
}

void Domain::constructCoeffs()
{
    for (int i = 0; i < m_N; ++i)
    {
        if (i == 0)
        {
            A[0][0] = -4.0 / m_dx / m_dx;
            A[0][1] = 4.0 / 3.0 / m_dx / m_dx;
            B[0] = -source(m_dx / 2) - 8.0 / 3.0 / m_dx / m_dx * leftBC();
        }
        else if (i == m_N - 1)
        {
            A[m_N - 1][m_N - 1] = -4.0 / m_dx / m_dx;
            A[m_N - 1][m_N - 2] = 4.0 / 3.0 / m_dx / m_dx;
            B[m_N - 1] = -source((0.5 + i) * m_dx) - 8.0 / 3.0 / m_dx / m_dx * rightBC();
        }
        else
        {
            A[i][i - 1] = 1.0 / m_dx / m_dx;
            A[i][i] = -2.0 / m_dx / m_dx;
            A[i][i + 1] = 1.0 / m_dx / m_dx;
            B[i] = -source((0.5 + i) * m_dx);
        }
    }
}

void Domain::init(double value)
{
    phi.assign(m_N, value);
}

void Domain::solve()
{
    constructCoeffs();
    outputCoeffs("Coeffs.txt");
    vector<double> a(m_N, 0);
    vector<double> b(m_N, 0);
    vector<double> c(m_N, 0);
    vector<double> f(m_N, 0);

    for (int i = 0; i < m_N; ++i)
    {
        b[i] = A[i][i];
        if (i != 0)
        {
            a[i] = A[i][i - 1];
        }
        if (i != m_N - 1)
        {
            c[i] = A[i][i + 1];
        }
    }

    TDMA_Solver solver = TDMA_Solver(a, b, c, B);
    solver.solve();
    solver.output();
}

void Domain::outputCoeffs(std::string fileName)
{
    ofstream ofs(fileName);
    ofs << "A-------------------------" << endl;
    for (auto v : A)
    {
        for (auto i : v)
        {
            ofs << i << "\t";
        }
        ofs << endl;
    }
    ofs << "B-------------------------" << endl;
    for (auto i : B)
    {
        ofs << i << endl;
    }
    ofs.close();
}

void Domain::outputResult(std::string fileName)
{
    ofstream ofs(fileName);
    for (int i = 0; i < m_N; ++i)
    {
        ofs << x[i] << "\t" << phi[i] << endl;
    }
    ofs.close();
}