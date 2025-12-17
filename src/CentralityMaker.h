#ifndef CENTRALITYMAKER_H
#define CENTRALITYMAKER_H

#include <vector>

struct CentralityBin
{
    double centLow;     // e.g. 0
    double centHigh;    // e.g. 5
    double centMid;     // e.g. 2.5

    double multLow;    // multiplicity lower bound
    double multHigh;   // multiplicity upper bound
};

class CentralityMaker
{
public:
    CentralityMaker() = default;

    // Set centrality windows, e.g. {0,5,10,...} or {0,1,2,...}
    void setCentralityEdges(const std::vector<double>& edges);

    // Build centrality bins from multiplicity distribution
    void build(const std::vector<double>& multiplicities);

    // Access centrality bins
    const std::vector<CentralityBin>& getBins() const;

    // Find centrality bin index for a given multiplicity
    int getCentralityBin(double multiplicity) const;

private:
    std::vector<double> fCentEdges;      // centrality percent edges
    std::vector<CentralityBin> fBins;    // centrality bins
};

#endif

