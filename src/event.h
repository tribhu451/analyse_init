#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

class event{

  public :

    event();
    ~event();
    inline double get_eccentricity(int iharmonics, int real_img ){return epsilon[iharmonics][real_img];}
    inline int get_Npart(){return Nparticipants;}
    inline double get_mult(){return mult;}
    inline double get_impact_parameter(){return impact_parameter_b;}
    
    inline void set_eccentricity(int iharmonics, int real_img, double val ){ epsilon[iharmonics][real_img] = val;}
    inline void set_Npart(int val){ Nparticipants = val;}
    inline void set_mult(double val){mult = val;}
    inline void set_impact_parameter(double val){impact_parameter_b = val;}
    
  private :
    int Nharmonics = 6 ; 
    double epsilon[6][2] ; // first index is harmonic number, second index is real or imaginary part
    double mult ;
    int Nparticipants ;
    double impact_parameter_b ;
    
    
};
