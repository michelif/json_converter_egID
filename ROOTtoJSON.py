import sys
import glob

import rootConversionUtils as convutils

idList2016 = ['ElectronLoose', 'ElectronMedium', 'ElectronTight','ElectronMVA80noiso', 'ElectronMVA90noiso','ElectronMVA80', 'ElectronMVA90']
fullName2016 = ['cutBasedElectronID-Fall17-94X-V2-loose', 'cutBasedElectronID-Fall17-94X-V2-medium', 'cutBasedElectronID-Fall17-94X-V2-tight','mvaEleID-Fall17-noIso-V2-wp80','mvaEleID-Fall17-noIso-V2-wp90','mvaEleID-Fall17-iso-V2-wp80','mvaEleID-Fall17-iso-V2-wp90'] 

for i,n in enumerate(idList2016): 
    convutils.readFile(str("2016LegacyReReco_")+n+str("_Fall17V2.root"),"EGamma_SF2D",fullName2016[i],"2016LegacyReReco")
