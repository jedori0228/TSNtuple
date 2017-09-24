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
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ]; # -- 147.47.242.67 -- # 
then 
	KP_DATA_PATH="/data5/Users/kplee/TriggerStudyNtuple"
fi