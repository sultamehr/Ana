#ifndef MNV_CCQENU1DBinOptimizer_H
#define MNV_CCQENU1DBinOptimizer

#include <vector>
#include <map>

//Adapted version of NukeCCInclusive/ana/unfold/BinOptimizer

namespace CCQENU_ANA{
  class CCQENu1DBinOptimizer
  {
    public:
      enum ResolutionType
  {
        kAbsoluteRes = 0,
        kRelativeRes = 1
  };

  struct XYPoint
  {
      //! Useless default constructor
      XYPoint() : 
        x(0.), 
        y(0.), 
        weight(0.)
      {};

      //! Constructor
      XYPoint( double i_x, double i_y, double i_weight = 1.0 ) :
        x(i_x),
        y(i_y),
        weight(i_weight)
      {};

      double x;
      double y;
      double weight;
  };

  typedef std::vector<XYPoint> XYPoints;
  typedef XYPoints::iterator XYPointItr;
  typedef XYPoints::const_iterator XYPointCItr;

  struct Resolution
  {
      //! Useless default constructor
      Resolution() :
        xHigh(0.),
        res(0.),
        resType( kRelativeRes )
      {};

      //! Constructor
      Resolution( double i_xHigh, double i_res, ResolutionType i_resType = kRelativeRes ) :
        xHigh( i_xHigh ),
        res(   i_res   ),
        resType( i_resType )
      {};

      double xHigh;
      double res;
      ResolutionType resType;
  };

    typedef std::vector<Resolution> Resolutions;
    typedef Resolutions::iterator ResolutionItr;
    typedef Resolutions::const_iterator ResolutionCItr;


    CCQENu1DBinOptimizer() :
      nonMigrateMin_( .5 ),
      nonMigrateMax_( .75 ),
      statErrMax_( .1 ),
      prevWidthGuess_m( -1. )
    {};

    //! Set the minimum suggested non-migrating fraction of a bin
    void SetNonMigrateMin( double nonMigrateMin ) { nonMigrateMin_ = nonMigrateMin; };
    //! Get the minimum suggested non-migrating fraction of a bin
    double GetNonMigrateMin( ) const { return nonMigrateMin_; };

    //! Set the maximum suggested non-migrating fraction of a bin
    void SetNonMigrateMax( double nonMigrateMax ) { nonMigrateMax_ = nonMigrateMax; };
    //! Get the maximum suggested non-migrating fraction of a bin
    double GetNonMigrateMax( ) const { return nonMigrateMax_; };

    //! Set the maximum suggested stat error on that bin
    void SetStatErrMax( double statErrMax ) { statErrMax_ = statErrMax; };
    //! Get the maximum suggested stat error on that bin
    double GetStatErrMax( ) const { return statErrMax_; };


    //! Add a migration point
    void AddPoint( double x, double y, double weight = 1. );
    //! Get the (const) vector of migration points
    const XYPoints& GetPoints( ) const { return points_; };
    //! Clear all migration points
    void ClearPoints( ) { points_.clear(); };

    //! Add a resoltuion limit
    //! @param[in] xHigh Upper limit in reco variable for which this resolution applies
    //! @param[in] res Resolution for measurements with x < xHigh
    //! @param[in] resType Is is absolute or relative resolution?
    void AddResolution( double xHigh, double res, ResolutionType resType = kRelativeRes ) { resolutions_.push_back( Resolution(xHigh, res, resType ) ); };
    //! Clear all resolutions
    void ClearResolutions() { resolutions_.clear(); };

    //! Get the vector of optimized bin low edges
    bool GetOptimizedBins( std::vector<double>& bins, double firstBinWidthGuess, double lowestBinEdge = 0. );

    //! Get the fraction that does not migrate between these X values
    double GetNonMigratingFaction( double lowX, double highX, double &statErr ) const;


  private:
    double nonMigrateMin_;  ///< Minimum fraction that should not have migrated from this bin
    double nonMigrateMax_;  ///< Maximum fraction that should not have migrated from this bin
    double statErrMax_;     ///< Maximum statistical uncertainty for a bin

    mutable double prevWidthGuess_m;      ///< Remember the previous bin width guess during optimization
    mutable std::vector<double> binLowEdges_m; ///< Remember the previous optimized bin edges 

    Resolutions resolutions_;  ///< Impose minimum bin sizes due to finite resolution
    XYPoints points_;          ///< Store the XY and weight of every point for the migration matrix
};
}

#endif //MNV_CCQENU1DBinOptimizer_H
