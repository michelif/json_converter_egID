# json converter for root files of e/gamma ID
utils to convert root scale factor files to json

- rootConversionUtils.py contains methods to read a TH2F from a root file and convert it to a json file
- ROOTtoJSON.py converts the root files from 2016LegacyReReco Id to jsons (one file for each id)
- combineJSONS.py merges all jsons files corresponding to the different IDs in one single file
