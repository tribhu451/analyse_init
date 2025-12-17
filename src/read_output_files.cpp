#include "read_output_files.h"
#include "event.h"

read_output_files::read_output_files(std::vector<std::string>  aa_output_paths){
  output_paths = aa_output_paths ;
}


void read_output_files::read_trento_output(){
  std::ifstream file;
  int temp_total_events = 0 ;
  double impb, Nch, e2, e3, e4, e5, dummy ; 
  int Npart;
  for(long unsigned int output_path_index=0; output_path_index < output_paths.size() ; output_path_index++ ){
      std::stringstream input_filename;
      input_filename.str(std::string());
      input_filename << output_paths[output_path_index].c_str() ;
      file.open(input_filename.str().c_str(), std::ios::in);
      if(!file){
        continue ; 
      }
      else{
        int ii=0;
        while(file.getline(buff,500)){    
          iss = new std::istringstream(buff);
          *iss >> dummy >> impb >> Npart >> Nch >> e2 >> e3 >> e4 >> e5  ;
          event* ev = new event();
          ev->set_impact_parameter(impb);
          ev->set_Npart(Npart);
          ev->set_mult(Nch);
          ev->set_eccentricity(2,0,e2);         
          ev->set_eccentricity(3,0,e3);  
          ev->set_eccentricity(4,0,e4);         
          ev->set_eccentricity(5,0,e5);
          event_arena.push_back(ev);         
          delete iss ; 
          temp_total_events ++ ;
          ii++ ;  
        }
      }
      file.close();
  } // loop over paths
  
  total_init_events = temp_total_events ;
  if(temp_total_events == 0){
    std::cout << "reading trento output failure ..." << std::endl ; 
    exit(-1);
  }
  
}






