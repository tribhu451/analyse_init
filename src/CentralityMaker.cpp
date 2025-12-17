#include "CentralityMaker.h"
#include <algorithm>
#include <cmath>

void CentralityMaker::setCentralityEdges(const std::vector<double>& edges)
{
    fCentEdges = edges;
}

void CentralityMaker::build(const std::vector<double>& multiplicities)
{
    fBins.clear();

    if (fCentEdges.size() < 2 || multiplicities.empty())
        return;

    // Copy and sort multiplicities (descending: most central first)
    std::vector<double> multSorted = multiplicities;
    std::sort(multSorted.begin(), multSorted.end(), std::greater<double>());

    const size_t nEvents = multSorted.size();

    for (size_t i = 0; i < fCentEdges.size() - 1; ++i)
    {
        double centLow  = fCentEdges[i];
        double centHigh = fCentEdges[i + 1];
        double centMid  = 0.5 * (centLow + centHigh);

        // Convert percent → index
        size_t idxLow  = static_cast<size_t>(
            std::floor(centLow / 100.0 * nEvents)
        );
        size_t idxHigh = static_cast<size_t>(
            std::floor(centHigh / 100.0 * nEvents)
        );

        if (idxLow >= nEvents)  idxLow  = nEvents - 1;
        if (idxHigh >= nEvents) idxHigh = nEvents - 1;

        CentralityBin bin;
        bin.centLow  = centLow;
        bin.centHigh = centHigh;
        bin.centMid  = centMid;

        // Note: high multiplicity = more central
        bin.multHigh = multSorted[idxLow];
        bin.multLow  = multSorted[idxHigh];

        fBins.push_back(bin);
    }
}

const std::vector<CentralityBin>& CentralityMaker::getBins() const
{
    return fBins;
}

int CentralityMaker::getCentralityBin(double multiplicity) const
{
    for (size_t i = 0; i < fBins.size(); ++i)
    {
        if (multiplicity <= fBins[i].multHigh &&
            multiplicity >= fBins[i].multLow)
        {
            return static_cast<int>(i);
        }
    }
    return -1;  // not found
}

