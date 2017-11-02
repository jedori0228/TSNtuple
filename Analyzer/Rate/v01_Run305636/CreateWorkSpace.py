import os, sys, json, time
TIME = time.strftime('%Y%m%d_%H%M%S', time.localtime(time.time()))

JSONFileName = sys.argv[1]
print "[JSONFileName]", JSONFileName
with open(JSONFileName) as TriggerInfo_File:
	TriggerInfo = json.load(TriggerInfo_File)

CodeName = TriggerInfo["CodeName"]

PWD = os.getcwd()

if "Local" not in os.listdir("."):
	os.mkdir( "Local" )

MainDirName = "v%s_%s" % (TIME, CodeName.split(".")[0])
MainDirPath = "Local/%s" % (MainDirName)
os.mkdir( MainDirPath )
# MainDirPath_Abs = "%s/%s" % (PWD, MainDirPath)

f = open("%s/Run.sh" % (MainDirPath), "w")
f.write("#!bin/bash\n")

for TriggerTag in TriggerInfo["TriggerList"]:
	SubDirName = TriggerTag;
	SubDirPath = "%s/%s" % (MainDirPath, SubDirName)

	os.mkdir( SubDirPath )

	cmd_cp = "cp %s %s" % (CodeName, SubDirPath);
	os.system( cmd_cp )

	# -- script for sub-job -- #
	f_sub = open("%s/Run_Sub.sh" % (SubDirPath), "w")
	f_sub.write(
"""
#!bin/bash

root -b -q '%s++(\"%s\")'

mv *.root ../

echo "%s: finished"

""" % (CodeName, TriggerTag, TriggerTag)
	)

	f_sub.close()

	# -- main script -- #
	f.write("cd %s\n" % SubDirName)
	f.write("source Run_Sub.sh >&log.txt&\n")
	f.write("cd ..\n\n")

# -- back to starting directory -- #
# f.write("cd %s\n" % PWD)
f.write('echo "submission is finished"')
f.close()

print "#" * 100
print "Workspace [%s] is created" % (MainDirPath)
print "Job submission: follow below command"
print "cd %s; source Run.sh" % (MainDirPath)
print "#" * 100