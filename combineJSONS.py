#usage python combineJSONS.py year
import os, sys, json 

json_list = []
current_dir = os.getcwd()
year = sys.argv[1]

combined_filename = 'combined_eleIDSFs_'+year+'.json' 
for (path, dir, files) in os.walk(current_dir):
    for filename in files:
        ext = os.path.splitext(filename)[-1]
        if ext == '.json' and year in filename:
            json_path = "%s/%s" % (path, filename)
            json_list.append(json_path)

json_combine = {}
for k in json_list:
    print(k)
    with open(k) as json_data:
        json_combine.update(json.load(json_data))

f =  open(current_dir+'/./'+combined_filename,'w')
json.dump(json_combine, f, sort_keys = False, indent = 4)
