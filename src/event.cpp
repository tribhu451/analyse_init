#include "event.h"

event::event(){
  for(int ii=0; ii<Nharmonics; ii++){
    for(int jj=0; jj<2; jj++){
      epsilon[ii][jj] = 0. ; 
    }
  }
}

event::~event(){
}
