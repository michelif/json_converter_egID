import sys
import glob

import rootConversionUtils as convutils


year=str(sys.argv[1])

yearPrefix2016 = '2016LegacyReReco_'
idList2016 = ['ElectronWPVeto','ElectronLoose', 'ElectronMedium', 'ElectronTight','ElectronMVA80noiso', 'ElectronMVA90noiso','ElectronMVA80', 'ElectronMVA90']
fullName2016 = ['cutBasedElectronID-Fall17-94X-V2-veto','cutBasedElectronID-Fall17-94X-V2-loose', 'cutBasedElectronID-Fall17-94X-V2-medium', 'cutBasedElectronID-Fall17-94X-V2-tight','mvaEleID-Fall17-noIso-V2-wp80','mvaEleID-Fall17-noIso-V2-wp90','mvaEleID-Fall17-iso-V2-wp80','mvaEleID-Fall17-iso-V2-wp90'] 

idList2018 = ['ElectronWPVeto','ElectronLoose', 'ElectronMedium', 'ElectronTight','ElectronMVA80noiso', 'ElectronMVA90noiso','ElectronMVA80', 'ElectronMVA90']
fullName2018 = fullName2016 = ['cutBasedElectronID-Fall17-94X-V2-veto','cutBasedElectronID-Fall17-94X-V2-loose', 'cutBasedElectronID-Fall17-94X-V2-medium', 'cutBasedElectronID-Fall17-94X-V2-tight','mvaEleID-Fall17-noIso-V2-wp80','mvaEleID-Fall17-noIso-V2-wp90','mvaEleID-Fall17-iso-V2-wp80','mvaEleID-Fall17-iso-V2-wp90'] 

idList = ['']
fullName = ['']

print(year)
if year == '2016' :
    idList = idList2016
    yearPrefix = yearPrefix2016
    fullName = fullName2016
elif year == 2017:
    idList = idList2017
elif year == 2018:
    idList = idList2018
else:
    print("year not properly set")
    sys.exit()


for i,n in enumerate(idList): 
    convutils.readFile(str(yearPrefix)+n+str("_Fall17V2.root"),"EGamma_SF2D",fullName[i],"2016LegacyReReco")
