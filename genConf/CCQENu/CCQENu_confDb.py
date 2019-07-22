##  -*- python -*-  
# db file automatically generated by genconf on: Fri Jul 19 14:34:56 2019## insulates outside world against anything bad that could happen
## also prevents global scope pollution
def _fillCfgDb():
    from GaudiKernel.Proxy.ConfigurableDb import CfgDb

    # get a handle on the repository of Configurables
    cfgDb = CfgDb()

    # populate the repository with informations on Configurables 

    cfgDb.add( configurable = 'CCQENuRecoUtils',
               package = 'CCQENu',
               module  = 'CCQENu.CCQENuConf',
               lib     = 'CCQENu' )
    cfgDb.add( configurable = 'CCQENu',
               package = 'CCQENu',
               module  = 'CCQENu.CCQENuConf',
               lib     = 'CCQENu' )
    return #_fillCfgDb
# fill cfgDb at module import...
try:
    _fillCfgDb()
    #house cleaning...
    del _fillCfgDb
except Exception,err:
    print "Py:ConfigurableDb   ERROR Problem with [%s] content!" % __name__
    print "Py:ConfigurableDb   ERROR",err
    print "Py:ConfigurableDb   ERROR   ==> culprit is package [CCQENu] !"
