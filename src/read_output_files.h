#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "event.h"

class read_output_files{

  public :
    read_output_files(std::vector<std::string>  aa);
    inline int get_total_init_events(){return total_init_events;};
    void read_trento_output();
    std::vector<event*> get_event_arena(){return event_arena;};
    event* get_event(int ii){return event_arena[ii];}

  private :
    std::istringstream* iss;
    char buff[400];
    std::vector<std::string> output_paths ; 
    int total_init_events ; 
    std::vector<event*> event_arena;
};
