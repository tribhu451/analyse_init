#include "observables.h"
#include <cmath>

observables::observables(read_output_files* armof,  CentralityMaker* _cent):rmof(armof),cent(_cent){
  event_arena = rmof->get_event_arena();
  rand = new random_gen();
}

std::vector<int> observables::get_an_event_ensemble(){
  std::vector<int> event_ID_ens;
  for(int ii=0; ii<rmof->get_total_init_events(); ii++){
    int evID =  rmof->get_total_init_events() * rand->rand_uniform() ;
    event_ID_ens.push_back(evID);
  }
  return event_ID_ens;
}

std::vector<int> observables::get_an_event_ensemble_of_a_centrality(std::vector<int> IDs){
  std::vector<int> event_ID_ens;
  for(long unsigned int ii=0; ii<IDs.size(); ii++){
    int idx = IDs.size()*rand->rand_uniform();
    event_ID_ens.push_back(IDs[idx]);
  }
  return event_ID_ens;
}

void observables::findout_centrality_cuts(){
  std::vector<double> multiplicities;
  for(int ii=0; ii<rmof->get_total_init_events(); ii++){
    double mult = rmof->get_event(ii)->get_mult() ;
    multiplicities.push_back(mult);
  }
  cent->build(multiplicities);
  for(const auto& bin : cent->getBins()){
    std::cout << bin.centLow << "-" << bin.centHigh << "%"
     << "  mid=" << bin.centMid
       << "  mult=[" << bin.multLow << ", "
       << bin.multHigh << "]" << std::endl;
  }
}

void observables::output_eccentricity(int n){

  std::ofstream mFile;
  std::stringstream output_filename;
  output_filename.str("");
  output_filename << "results/eccentricity_" << n ;
  output_filename << ".dat";
  mFile.open(output_filename.str().c_str(), std::ios::out );
  mFile << "#centrality    centrality_mid    e"<<n<<"{2}    error    e"<<n<<"{4}   error" << std::endl ;
  std::cout << "#centrality    centrality_mid    e"<<n<<"{2}    error    e"<<n<<"{4}   error" << std::endl ;
  double en2, en4 ; 
  // x = en{2}, y=en{4}
  double sumx = 0 ; 
  double sumx2 = 0 ; 
  double sumy = 0 ; 
  double sumy2 = 0 ; 
  for(const auto& bin : cent->getBins()){
  
    std::vector<int> event_ID_ens_cent;
    std::vector<int> event_ID_ens;
    sumx = 0. ; 
    sumx2 = 0. ; 
    sumy = 0. ; 
    sumy2 = 0. ; 
  
    // accumulate events of this centrality //
    for(int ii=0; ii<rmof->get_total_init_events(); ii++){
     double mult = rmof->get_event(ii)->get_mult() ;
     if(mult>bin.multLow && mult<bin.multHigh){
      event_ID_ens_cent.push_back(ii);
     }
    }
    
    // take multiple ensembles
    for(long unsigned int iens=0; iens<event_ID_ens_cent.size() ; iens++){
      event_ID_ens = get_an_event_ensemble_of_a_centrality(event_ID_ens_cent);
      calculate_average_eccentricity_for_one_ensemble(n,event_ID_ens,en2,en4);
      sumx  += en2 ; 
      sumx2 += en2 * en2 ; 
      sumy  += en4 ; 
      sumy2 += en4 * en4 ; 
    } // loop over ensemble
    sumx  /=  event_ID_ens_cent.size();
    sumx2 /=  event_ID_ens_cent.size();
    sumy  /=  event_ID_ens_cent.size();    
    sumy2 /=  event_ID_ens_cent.size();    

    double Mean_en2 = sumx  ; 
    double Erro_en2 = sqrt( sumx2 - sumx * sumx ) ; 
    double Mean_en4 = sumy  ; 
    double Erro_en4 = sqrt( sumy2 - sumy * sumy ) ; 

    mFile << bin.centLow << "-" << bin.centHigh << "%" 
    << "    " << bin.centMid << "   " << Mean_en2 <<  "   " 
    << Erro_en2 <<  "   " << Mean_en4 <<  "   " 
    << Erro_en4 << std::endl ; 
    std::cout << bin.centLow << "-" << bin.centHigh << "%" 
    << "    " << bin.centMid << "   " << Mean_en2 <<  "   " 
    << Erro_en2 <<  "   " << Mean_en4 <<  "   " 
    << Erro_en4 << std::endl ; 

  } // loop over centrality bin
  mFile.close();
 
}


void observables::calculate_average_eccentricity_for_one_ensemble(int n, std::vector<int> event_ID_ens, 
     double&  en_2, double&  en_4){
  // calculate the observable for one ensemble //
  double sumx = 0. ; 
  double sumx2 = 0. ; 
  double sumx4 = 0. ; 
    
  for(long unsigned int ii=0; ii<event_ID_ens.size(); ii++){
    int eventID = event_ID_ens[ii] ; 
    event* ev = rmof->get_event(eventID) ;
    double ec = ev->get_eccentricity(n,0);
    sumx  += ec ; 
    sumx2 += ec * ec  ;  
    sumx4 += (ec * ec * ec * ec) ;  
  }   
  sumx /= event_ID_ens.size();
  sumx2 /= event_ID_ens.size();
  sumx4 /= event_ID_ens.size();
  en_2 = sqrt(sumx2);
  if((2. * sumx2 * sumx2 - sumx4 )<0){
   std::cout << "2 < ɛ̝ ɛ̝*> < ɛ̝ ɛ̝*> - < ɛ̝ ɛ̝* ɛ̝ ɛ̝* >"
     <<"  is negative ..." << std::endl ;
   exit(-1); 
  }
  else{
   en_4 = pow(  2. * sumx2 * sumx2 - sumx4 , 0.25 ); 
 }
}









