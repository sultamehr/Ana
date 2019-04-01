#Sat Mar  9 09:21:52 2019"""Automatically generated. DO NOT EDIT please"""
from GaudiKernel.Proxy.Configurable import *

class CCQENuRecoUtils( ConfigurableAlgTool ) :
  __slots__ = { 
    'MonitorService' : 'MonitorSvc', # str
    'OutputLevel' : 7, # int
    'AuditTools' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'AuditFinalize' : False, # bool
    'ErrorsPrint' : True, # bool
    'PropertiesPrint' : False, # bool
    'StatPrint' : True, # bool
    'TypePrint' : True, # bool
    'Context' : '', # str
    'RootInTES' : '', # str
    'RootOnTES' : '', # str
    'GlobalTimeOffset' : 0.00000000, # float
    'StatTableHeader' : ' |    Counter                                      |     #     |    sum     | mean/eff^* | rms/err^*  |     min     |     max     |', # str
    'RegularRowFormat' : ' | %|-48.48s|%|50t||%|10d| |%|11.7g| |%|#11.5g| |%|#11.5g| |%|#12.5g| |%|#12.5g| |', # str
    'EfficiencyRowFormat' : ' |*%|-48.48s|%|50t||%|10d| |%|11.5g| |(%|#9.6g| +- %|-#9.6g|)%%|   -------   |   -------   |', # str
    'UseEfficiencyRowFormat' : True, # bool
    'CounterList' : [ '.*' ], # list
    'StatEntityList' : [  ], # list
    'ContextService' : 'AlgContextSvc', # str
    'HistoProduce' : True, # bool
    'HistoPrint' : False, # bool
    'HistoCheckForNaN' : True, # bool
    'HistoSplitDir' : False, # bool
    'HistoOffSet' : 0, # int
    'HistoTopDir' : '', # str
    'HistoDir' : 'AlgTool', # str
    'FullDetail' : False, # bool
    'MonitorHistograms' : True, # bool
    'FormatFor1DHistoTable' : '| %2$-45.45s | %3$=7d |%8$11.5g | %10$-11.5g|%12$11.5g |%14$11.5g |', # str
    'ShortFormatFor1DHistoTable' : ' | %1$-25.25s %2%', # str
    'HeaderFor1DHistoTable' : '|   Title                                       |    #    |     Mean   |    RMS     |  Skewness  |  Kurtosis  |', # str
    'UseSequencialNumericAutoIDs' : False, # bool
    'AutoStringIDPurgeMap' : { '/' : '=SLASH=' }, # list
    'HistogramCreationLevel' : 3, # int
    'ProngLocation' : 'Rec/Prongs', # str
    'MinervaTrackLocation' : 'Rec/Tracks', # str
    'MinosTrackLocation' : 'Rec/Minos/Tracks', # str
    'MinosHitLocation' : 'Rec/Minos/Hits', # str
    'VetoDigitLocation' : 'Cal/Veto/Digits', # str
    'TimeSliceLocation' : 'Mgr/TimeSlices', # str
    'TimeSliverLocation' : 'Mgr/TimeSlivers', # str
    'PhysicsEventLocation' : 'Mgr/PhysicsEvents', # str
    'PMTEffectsTableLocation' : 'Gate/PMTEffectsTables', # str
    'DataQualityLocation' : 'Gate/DataQuality', # str
    'GenMinInteractionLocation' : 'Gen/Interactions', # str
    'GenMinEventRecordLocation' : 'Gen/EventRecords', # str
    'PMTEffectsTableMethodSignature' : 'XTalkScoreGrader', # str
    'MinervaObjAssocAlias' : 'MMDRecoUtilsMinObjAssociator', # str
    'RecoObjTimeToolAlias' : 'MMDRecoUtilsRecoObjTimeTool', # str
    'MathToolAlias' : 'MMDRecoUtilsMathTool', # str
    'VtxAnchorShortTrackerAlias' : 'MMDRecoUtilsVtxAnchorShortTracker', # str
    'VertexEnergyStudyToolAlias' : 'MMDRecoUtilsVtxEngStudyTool', # str
    'VertexBlobCreatorToolAlias' : 'MMDRecoUtilsVtxBlobCreator', # str
    'BlobCreatorUtilsAlias' : 'MMDRecoUtilsBlobCreatorUtils', # str
    'CalorimetryUtilsAlias' : 'MMDRecoUtilsCaloUtils', # str
    'ConeUtilsToolAlias' : 'MMDRecoUtilsConeUtilsTool', # str
    'ProngIntersectionToolAlias' : 'MMDRecoUtilsProngIntersectionTool', # str
    'HitTaggerToolAlias' : 'MMDRecoUtilsHitTaggerTool', # str
    'MuonUtilsAlias' : 'MMDRecoUtilsMuonUtils', # str
    'TruthMatcherAlias' : 'MMDRecoUtilsTruthMatcher', # str
    'MaxSearchDistance_VESTool' : 400.00000000, # float
    'MaxStartingDistance_VESTool' : 400.00000000, # float
    'MaxAllowedSearchGap_VESTool' : 1000000.00000000, # float
    'LowerTimeWindow' : -20.00000000, # float
    'UpperTimeWindow' : 35.00000000, # float
    'LowerTimeWindow_tracks' : -5.00000000, # float
    'UpperTimeWindow_tracks' : 10.00000000, # float
    'ClustersInConeProtonProngColor' : 6684774, # int
    'MuonFuzzBlobsColor' : 13056, # int
    'MuonIsolatedBlobsColor' : 255, # int
    'MuonProngColor' : 65280, # int
    'ConeLength' : 300.00000000, # float
    'MuonFuzzDistanceFromVertex' : 300.00000000, # float
    'MuonFuzzRadius' : 50.00000000, # float
  }
  _propertyDocDct = { 
    'StatTableHeader' : """ The header row for the output Stat-table """,
    'ErrorsPrint' : """ Print the statistics of errors/warnings/exceptions """,
    'HeaderFor1DHistoTable' : """ The table header for printout of 1D histograms  """,
    'StatPrint' : """ Print the table of counters """,
    'HistoDir' : """ Histogram Directory """,
    'TypePrint' : """ Add the actal C++ component type into the messages """,
    'HistoTopDir' : """ Top level histogram directory (take care that it ends with '/') """,
    'AutoStringIDPurgeMap' : """ Map of strings to search and replace when using the title as the basis of automatically generated literal IDs """,
    'CounterList' : """ RegEx list, of simple integer counters for CounterSummary. """,
    'ShortFormatFor1DHistoTable' : """ Format string for printout of 1D histograms """,
    'EfficiencyRowFormat' : """ The format for the regular row in the output Stat-table """,
    'PropertiesPrint' : """ Print the properties of the component  """,
    'HistoSplitDir' : """ Split long directory names into short pieces (suitable for HBOOK) """,
    'ContextService' : """ The name of Algorithm Context Service """,
    'HistoProduce' : """ Swith on/off the production of histograms  """,
    'UseEfficiencyRowFormat' : """ Use the special format for printout of efficiency counters """,
    'HistoPrint' : """ Switch on/off the printout of histograms at finalization """,
    'RegularRowFormat' : """ The format for the regular row in the output Stat-table """,
    'FormatFor1DHistoTable' : """ Format string for printout of 1D histograms """,
    'HistoOffSet' : """ OffSet for automatically assigned histogram numerical identifiers  """,
    'UseSequencialNumericAutoIDs' : """ Flag to allow users to switch back to the old style of creating numerical automatic IDs """,
    'StatEntityList' : """ RegEx list, of StatEntity counters for CounterSummary. """,
    'HistoCheckForNaN' : """ Swicth on/off the checks for NaN and Infinity for histogram fill """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(CCQENuRecoUtils, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'CCQENu'
  def getType( self ):
      return 'CCQENuRecoUtils'
  pass # class CCQENuRecoUtils

class CCQENu( ConfigurableAlgTool ) :
  __slots__ = { 
    'MonitorService' : 'MonitorSvc', # str
    'OutputLevel' : 7, # int
    'AuditTools' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'AuditFinalize' : False, # bool
    'ErrorsPrint' : True, # bool
    'PropertiesPrint' : False, # bool
    'StatPrint' : True, # bool
    'TypePrint' : True, # bool
    'Context' : '', # str
    'RootInTES' : '', # str
    'RootOnTES' : '', # str
    'GlobalTimeOffset' : 0.00000000, # float
    'StatTableHeader' : ' |    Counter                                      |     #     |    sum     | mean/eff^* | rms/err^*  |     min     |     max     |', # str
    'RegularRowFormat' : ' | %|-48.48s|%|50t||%|10d| |%|11.7g| |%|#11.5g| |%|#11.5g| |%|#12.5g| |%|#12.5g| |', # str
    'EfficiencyRowFormat' : ' |*%|-48.48s|%|50t||%|10d| |%|11.5g| |(%|#9.6g| +- %|-#9.6g|)%%|   -------   |   -------   |', # str
    'UseEfficiencyRowFormat' : True, # bool
    'CounterList' : [ '.*' ], # list
    'StatEntityList' : [  ], # list
    'ContextService' : 'AlgContextSvc', # str
    'HistoProduce' : True, # bool
    'HistoPrint' : False, # bool
    'HistoCheckForNaN' : True, # bool
    'HistoSplitDir' : False, # bool
    'HistoOffSet' : 0, # int
    'HistoTopDir' : '', # str
    'HistoDir' : 'AlgTool', # str
    'FullDetail' : False, # bool
    'MonitorHistograms' : True, # bool
    'FormatFor1DHistoTable' : '| %2$-45.45s | %3$=7d |%8$11.5g | %10$-11.5g|%12$11.5g |%14$11.5g |', # str
    'ShortFormatFor1DHistoTable' : ' | %1$-25.25s %2%', # str
    'HeaderFor1DHistoTable' : '|   Title                                       |    #    |     Mean   |    RMS     |  Skewness  |  Kurtosis  |', # str
    'UseSequencialNumericAutoIDs' : False, # bool
    'AutoStringIDPurgeMap' : { '/' : '=SLASH=' }, # list
    'HistogramCreationLevel' : 3, # int
    'ProngLocation' : 'Rec/Prongs', # str
    'MinervaTrackLocation' : 'Rec/Tracks', # str
    'MinosTrackLocation' : 'Rec/Minos/Tracks', # str
    'MinosHitLocation' : 'Rec/Minos/Hits', # str
    'VetoDigitLocation' : 'Cal/Veto/Digits', # str
    'TimeSliceLocation' : 'Mgr/TimeSlices', # str
    'TimeSliverLocation' : 'Mgr/TimeSlivers', # str
    'PhysicsEventLocation' : 'Mgr/PhysicsEvents', # str
    'PMTEffectsTableLocation' : 'Gate/PMTEffectsTables', # str
    'DataQualityLocation' : 'Gate/DataQuality', # str
    'GenMinInteractionLocation' : 'Gen/Interactions', # str
    'GenMinEventRecordLocation' : 'Gen/EventRecords', # str
    'PMTEffectsTableMethodSignature' : 'XTalkScoreGrader', # str
    'DispersedCalEnergyVariable' : 'nu_energy_dispersed_cal', # str
    'SignalApothem' : 850.00000000, # float
    'SignalUpstreamZ' : 5990.00000000, # float
    'SignalDownstreamZ' : 8340.00000000, # float
    'AnalyzeApothem' : 900.00000000, # float
    'AnalyzeUpstreamZ' : 4000.00000000, # float
    'AnalyzeDownstreamZ' : 9990.00000000, # float
    'BrokenTrackAngle' : 2.96705973, # float
    'CollinearTrackAngle' : 0.08726646, # float
    'MidpointDifferenceCut' : 40.00000000, # float
    'ProngMinMCFraction' : 0.50000000, # float
    'HypothesisMethods' : [ 'CCQENu' ], # list
    'LowerTimeWindow' : -20.00000000, # float
    'UpperTimeWindow' : 35.00000000, # float
    'MinMuonScore' : 0.90000000, # float
    'MinProtonScore' : 0.05000000, # float
    'qOverpChargeCut' : 0.00000000, # float
    'NuCCQEBindingEnergyMeV' : 34.00000000, # float
    'MakeShortTracks' : True, # bool
    'MakeShortTracksvtxAnchoredShortTracker' : True, # bool
    'DoRecursiveVertexAnchoredShortTracking' : True, # bool
    'MakeShortTracksvtxEnergyStudyTool' : True, # bool
    'DoRecursiveVESTool' : True, # bool
    'MakeIsoMuonEMBlobs' : True, # bool
    'MakeFuzzMuonEMBlobs' : True, # bool
    'PrimaryHadronTagName' : 'PrimaryHadron', # str
    'PrimaryProtonTagName' : 'PrimaryProton', # str
    'SecondaryProtonTagName' : 'SecondaryProtons', # str
    'MaxIsoBlobs' : 2.00000000, # float
    'SearchStepSize' : 300.00000000, # float
    'NumSearchRadii' : 1, # int
    'FStyleMaxSearchDistance' : 300.00000000, # float
    'FStyleMaxStartingDistance' : 300.00000000, # float
    'FStyleMaxAllowedSearchGap' : 1000000.00000000, # float
    'MakeFilamentStyleVtxBlobProngs' : False, # bool
    'MakeMultipleRadiiStyleVtxBlobProngs' : True, # bool
    'MaxAllowedSeparationBlobVertex' : 300.00000000, # float
    'MichelDownstreamZ' : 8524.19000000, # float
    'MichelUpstreamZ' : 5900.91000000, # float
    'FillTruthTG4ProtonCone' : False, # bool
    'UseODMatchProtons' : False, # bool
    'MaxProtonChi2' : 50.00000000, # float
    'ProtonEndPointZLow' : 4000.00000000, # float
    'ProtonEndPointZHigh' : 10000.00000000, # float
    'ProtonEndPointApothem' : 1200.00000000, # float
    'IsolatedBlobProngColor' : 16711680, # int
    'DispersedEnergyColor' : 52479, # int
    'VertexBlobProngColor' : 10053120, # int
    'ProtonProngColor' : 10027008, # int
    'HadronProngsColor' : 16776960, # int
    'ConeEnergyColor' : 16711935, # int
    'MinervaObjAssocAlias' : 'CCQENUMinObjAssociator', # str
    'RecoObjTimeToolAlias' : 'CCQENURecoObjTimeTool', # str
    'MinervaCoordSysToolAlias' : 'CCQENUMinCoordSysTool', # str
    'MinervaMathToolAlias' : 'CCQENUMinMathTool', # str
    'CCQENURecoUtilsAlias' : 'CCQENURecoUtilsTool', # str
    'BlobCreatorUtilsAlias' : 'CCQENUBlobCreatorUtils', # str
    'PrimaryBlobProngToolAlias' : 'CCQENUPrimaryBlobProngTool', # str
    'MichelToolAlias' : 'CCQENUMichelFinderTool', # str
    'ImprovedMichelToolAlias' : 'CCQENUImprovedMichelFinderTool', # str
    'CalorimetryUtilsAlias' : 'CCQENUCaloUtils', # str
    'ProtonUtilsAlias' : 'CCQENUProtonUtils', # str
    'ParticleToolAlias' : 'CCQENUParticleMaker', # str
    'HitTaggerToolAlias' : 'CCQENUHitTaggerTool', # str
    'UseMuonIsPlausible' : True, # bool
  }
  _propertyDocDct = { 
    'StatTableHeader' : """ The header row for the output Stat-table """,
    'ErrorsPrint' : """ Print the statistics of errors/warnings/exceptions """,
    'HeaderFor1DHistoTable' : """ The table header for printout of 1D histograms  """,
    'StatPrint' : """ Print the table of counters """,
    'HistoDir' : """ Histogram Directory """,
    'TypePrint' : """ Add the actal C++ component type into the messages """,
    'HistoTopDir' : """ Top level histogram directory (take care that it ends with '/') """,
    'AutoStringIDPurgeMap' : """ Map of strings to search and replace when using the title as the basis of automatically generated literal IDs """,
    'CounterList' : """ RegEx list, of simple integer counters for CounterSummary. """,
    'ShortFormatFor1DHistoTable' : """ Format string for printout of 1D histograms """,
    'EfficiencyRowFormat' : """ The format for the regular row in the output Stat-table """,
    'PropertiesPrint' : """ Print the properties of the component  """,
    'HistoSplitDir' : """ Split long directory names into short pieces (suitable for HBOOK) """,
    'ContextService' : """ The name of Algorithm Context Service """,
    'HistoProduce' : """ Swith on/off the production of histograms  """,
    'UseEfficiencyRowFormat' : """ Use the special format for printout of efficiency counters """,
    'HistoPrint' : """ Switch on/off the printout of histograms at finalization """,
    'RegularRowFormat' : """ The format for the regular row in the output Stat-table """,
    'FormatFor1DHistoTable' : """ Format string for printout of 1D histograms """,
    'HistoOffSet' : """ OffSet for automatically assigned histogram numerical identifiers  """,
    'UseSequencialNumericAutoIDs' : """ Flag to allow users to switch back to the old style of creating numerical automatic IDs """,
    'StatEntityList' : """ RegEx list, of StatEntity counters for CounterSummary. """,
    'HistoCheckForNaN' : """ Swicth on/off the checks for NaN and Infinity for histogram fill """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(CCQENu, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'CCQENu'
  def getType( self ):
      return 'CCQENu'
  pass # class CCQENu
