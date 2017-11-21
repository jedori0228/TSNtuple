import os, sys, json

JSONFileName = sys.argv[1]
print "[JSONFileName]", JSONFileName
with open(JSONFileName) as JobInfo_File:
	JobInfo = json.load(JobInfo_File)

macroName = JobInfo["Macro"];

List_rootCMD = []
i_job = 0;
for jobInfo in JobInfo["JobInfo"]:
	i_job = i_job + 1;
	dataPath = jobInfo["DataPath"]
	outputFileName = jobInfo["OutputFileName"]

	rootCMD = "root -b -q '%s++(\"%s\", \"%s\")' >&log_%s_v%02d.log" % (macroName, dataPath, outputFileName, macroName.split(".")[0], i_job)
	print rootCMD

	List_rootCMD.append( rootCMD )

f = open("script_Run.sh", "w")
f.write("#!bin/bash\n\n");

for rootCMD in List_rootCMD:
	f.write( rootCMD+"\n");

f.write('echo "All jobs are finished"\n')
f.close()

print "+" * 100
print "script_Run.sh is generated. Run the script: "
print "source script_Run.sh >&log_script_Run.log&"
print "+" * 100