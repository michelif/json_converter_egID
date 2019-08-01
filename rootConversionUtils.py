import ROOT 

def readFile(filename, th2name, idname, datasetname):
    sfDict = {}

    print('opening ', filename)
    print('get th2: ',th2name)
    rootfile = ROOT.TFile.Open(filename)
    th2 = rootfile.Get(th2name)

    nEtaBins = th2.GetNbinsX()
    nPtBins = th2.GetNbinsY()
     
    etaAxis = th2.GetXaxis()
    ptAxis = th2.GetYaxis()
    
    for iPt in range(1,nPtBins+1):# do i need +1?
        for iEta in range(1,nEtaBins+1):
            print(ptAxis.GetBinLowEdge(iPt),etaAxis.GetBinLowEdge(iEta))
            sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"] = {}
            for iEta in range(1,nEtaBins):
                sfDict["pt:["+str(ptAxis.GetBinLowEdge(iPt))+","+str(ptAxis.GetBinUpEdge(iPt))+"]"]["eta:["+str(etaAxis.GetBinLowEdge(iEta))+","+str(etaAxis.GetBinUpEdge(iEta))+"]"] = th2.GetBinContent(iPt,iEta)
                

    for x,y in sfDict.items():
        print(x,y)
