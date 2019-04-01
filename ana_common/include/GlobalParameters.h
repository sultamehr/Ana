#ifndef GLOBALPARAMETERS_h 
#define GLOBALPARAMETERS_h 1 

#include "include/GlobalIncludes.h" 

namespace CCQENU_ANA{ 
  class GlobalParameters { 


  public: 
    static GlobalParameters& Get(); 

    bool m_useFluxConstraint; 
    bool m_neutrinoMode; 
    //bool m_single_nu_mc; 
    bool m_usePPFX1Flux; 

    void Print(); 


  private:
    GlobalParameters(); 
    GlobalParameters( const GlobalParameters& ) {}; 
    GlobalParameters& operator=( const GlobalParameters& ) { return *this; };
    

    ~GlobalParameters() {};

  };

  GlobalParameters& globalParameters(); 

}

#endif 
    
