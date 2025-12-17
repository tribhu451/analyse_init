#pragma once
#include "event.h"
#include "read_output_files.h"
#include "CentralityMaker.h"
#include "random.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class observables{

  public :

    observables(read_output_files* , CentralityMaker* );
    void output_eccentricity(int n);
    void findout_centrality_cuts();

  private :
    std::vector<event*> event_arena;
    read_output_files* rmof ; 
    random_gen* rand;
    CentralityMaker* cent;
    std::vector<int> get_an_event_ensemble();
    std::vector<int> get_an_event_ensemble_of_a_centrality
      (std::vector<int> );
    void calculate_average_eccentricity_for_one_ensemble(int n, 
      std::vector<int> , double&  , double&  );

    
};
