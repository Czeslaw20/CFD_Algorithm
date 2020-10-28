#include "TDMA_Solver.h"

TDMA_Solver::TDMA_Solver(vector<double> a, vector<double> b, vector<double> c, vector<double> f)
    : m_a(a), m_b(b), m_c(c), m_f(f), m_N(f.size())
{
    m_phi.insert(m_phi.begin(), m_N, 0);
}

void TDMA_Solver::showMatrix()
{
}

void TDMA_Solver::solve()
{
    for (int i = 0; i < m_N; ++i)
    {
        if (i == 0)
        {
            m_c[i] = m_c[i] / m_b[i];
            m_f[i] = m_f[i] / m_b[i];
        }
        else if (i < m_N - 1)
        {
            m_c[i] = m_c[i] / (m_b[i] - m_c[i - 1] * m_a[i]);
            m_f[i] = (m_f[i] - m_f[i - 1] * m_a[i]) / (m_b[i] - m_c[i - 1] * m_a[i]);
        }
        else
        {
            m_f[i] = (m_f[i] - m_f[i - 1] * m_a[i]) / (m_b[i] - m_c[i - 1] * m_a[i]);
        }
    }

    for (int i = m_N - 1; i >= 0; --i)
    {
        if (i == m_N - 1)
        {
            m_phi[i] = m_f[i];
        }
        else
        {
            m_phi[i] = m_f[i] - m_c[i] * m_phi[i + 1];
        }
    }
}

void TDMA_Solver::output()
{
    for (auto e : m_phi)
    {
        cout << e << "\t";
    }
    cout << endl;
}

TDMA_Solver::~TDMA_Solver()
{
}