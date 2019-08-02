import ROOT,json 
from collections import OrderedDict
import os

def writeJSON(sfDict,f):
    json.dump(sfDict,f,sort_keys=False,indent=4)

def updateJSON(sfDict,f):
    f_1 =  open(f.name,'r')
    print(f.name)
    json_data = json.load(f_1)
    json_data.dump(sfDict,f_1,sort_keys=False,indent=4)

def readFile(filename, th2name, idname, datasetname):
    idDict = OrderedDict() #OrderedDict keeps the order in which elements are inserted into the dictionary
    sfDict = OrderedDict() 
    
    print('opening ', filename)
    print('get th2: ',th2name)
    rootfile = ROOT.TFile.Open(filename)
    th2 = rootfile.Get(th2name)

    nEtaBins = th2.GetNbinsX()
    nPtBins = th2.GetNbinsY()
     
    etaAxis = th2.GetXaxis()
    ptAxis = th2.GetYaxis()
    
    
    sfDict[idname]=OrderedDict()
    for iPt in range(1,nPtBins+1):# do i need +1?
        sfDict[idname]["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"] = OrderedDict()
        for iEta in range(1,nEtaBins+1):
            sfDict[idname]["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"] = OrderedDict()
            sfDict[idname]["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"]["value"] = th2.GetBinContent(iEta,iPt)
            sfDict[idname]["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"]["error"] = th2.GetBinError(iEta,iPt)                

    for x,y in sfDict.items():
        print(x,y)
        
    f = open(datasetname+str("_")+idname+str(".json"),'w')
    writeJSON(sfDict,f)

    
