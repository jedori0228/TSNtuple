def CheckIfFailed(logfilename):

  lines = open(logfilename).readlines()

  IsThisFailed = False

  ErrMsgs = [
  "segmentation", "violation",
  ]

  for line in lines:
    for em in ErrMsgs:
      if em in line:
        IsThisFailed = True
        break

  return IsThisFailed
