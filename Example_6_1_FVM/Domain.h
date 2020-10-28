#pragma once
#include <string>
#include <vector>

class Domain
{
public:
    Domain(double L, int N);
    ~Domain();

    void constructCoeffs();
    void init(double value);
    void solve();
    void outputCoeffs(std::string fileName);
    void outputResult(std::string fileName);

private:
    double leftBC();
    double rightBC();
    double source(double x);

private:
    double m_L;
    int m_N;
    double m_dx;

    std::vector<std::vector<double>> A;
    std::vector<double> B;
    std::vector<double> x;
    std::vector<double> phi;
};
