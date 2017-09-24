if [ $KP_ANALYZER_PATH ]; then
    echo "KP_ANALYZER_PATH is already defined: use a clean shell!"
    return 1
fi

# -- analyzer path (do not insert "/" in the end of the path)-- #
export KP_ANALYZER_PATH=$(pwd)
export KP_INCLUDE_PATH=$KP_ANALYZER_PATH/Include

# -- root setup -- #
export ROOT_INCLUDE_PATH=${KP_ANALYZER_PATH}:${ROOT_INCLUDE_PATH}

# -- ntuple path -- #
export KP_DATA_PATH=""
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ] || [ "compute-"=~"$HOSTNAME" ] ; # -- 147.47.242.67 -- # 
then 
	KP_DATA_PATH="/data5/Users/kplee/TriggerStudyNtuple"

	# -- cmssw setup -- #
	export SCRAM_ARCH=slc6_amd64_gcc530
	export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
	source $VO_CMS_SW_DIR/cmsset_default.sh

	cd /share_home/kplee/TagProbe/v20170815_1st_MuonPOG_92Xv2_TrkIter/CMSSW_9_2_4/src
	eval `scramv1 runtime -sh` # -- equivalent to cmsenv (cmsenv doesn't work. why?) -- #
	cd $KP_ANALYZER_PATH

fi