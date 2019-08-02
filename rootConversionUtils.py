import ROOT,json 
from collections import OrderedDict

def writeJSON(sfDict,filename):
    json.dump(sfDict,filename,sort_keys=False,indent=4)


def readFile(filename, th2name, idname, datasetname):
    sfDict = OrderedDict() #it keeps the order in which elements are inserted into the dictionary

    print('opening ', filename)
    print('get th2: ',th2name)
    rootfile = ROOT.TFile.Open(filename)
    th2 = rootfile.Get(th2name)

    nEtaBins = th2.GetNbinsX()
    nPtBins = th2.GetNbinsY()
     
    etaAxis = th2.GetXaxis()
    ptAxis = th2.GetYaxis()
    
    for iPt in range(1,nPtBins+1):# do i need +1?
        sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"] = OrderedDict()
        for iEta in range(1,nEtaBins+1):
            sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"] = OrderedDict()
            sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"]["value"] = th2.GetBinContent(iEta,iPt)
            sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"]["error"] = th2.GetBinError(iEta,iPt)                

    for x,y in sfDict.items():
        print(x,y)
        
    f = open(datasetname+str("_")+idname+str(".json"),'w')

    writeJSON(sfDict,f)

    
