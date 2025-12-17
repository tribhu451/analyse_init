#include<iostream>
#include<fstream>
#include <vector>
#include "event.h"
#include "read_output_files.h"
#include "CentralityMaker.h"
#include "observables.h"

int main(int argc, char **argv){

 std::cout << "========================" << std::endl ; 
 std::cout << " init analysis-toolkit" << std::endl ; 
 std::cout << "========================" << std::endl ; 
 std::cout << "\n" << std::endl ; 

 if(argc < 2){
    std::cout << "atleast one path required ..." << std::endl ;
    exit(-1); 
  }

 if(argc > 16){
    std::cout << "too many paths provided (15 allowed) ..." << std::endl ;
    exit(-1); 
  }


 std::vector<std::string> output_paths ; 
 
 for(int ii=2; ii<17; ii++){
   if(ii==argc){
     std::cout <<  (ii-1) << " paths provided" << std::endl ; 
     for(int jj=1; jj<argc; jj++){
       output_paths.push_back(argv[jj]) ;
     } 
     break ; 
   }
 }
 
 
 std::cout << "path names : " ; 
 for(long unsigned int ii=0; ii<output_paths.size(); ii++){
   std::cout << output_paths[ii] << "/,  " ; 
 }
 std::cout << std::endl ;
 
 read_output_files* rof = new read_output_files(output_paths); 
 rof->read_trento_output();
 
 CentralityMaker* cent = new CentralityMaker();
 cent->setCentralityEdges({0,5,10,15,20,30,40,50,60,70,80,90,100});
 
 observables* obj = new observables(rof,  cent);
 obj->findout_centrality_cuts();
 obj->output_eccentricity(2);
 obj->output_eccentricity(3);
 return 0 ;  
}




