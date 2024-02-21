#!/bin/bash

source ./exec-cmd-arr.sh

declare -a CMD_ARR

#MLM2workshop is a bundle of scripts to manage project development and build process and make things easier for developers.
CMD_ARR[${#CMD_ARR[@]}]="git clone git@bitbucket.org:rapsodoturkey/mlm2workshop.git"
CMD_ARR[${#CMD_ARR[@]}]="cd mlm2workshop/.scripts/"
CMD_ARR[${#CMD_ARR[@]}]="python3 install.py"
CMD_ARR[${#CMD_ARR[@]}]="sed --posix -i 's/\#\!\/usr\/bin\/env python *$/\#\!\/usr\/bin\/env python3/' ../rv1126/.repo/repo/repo"
CMD_ARR[${#CMD_ARR[@]}]="python3 manage.py -i -c"
CMD_ARR[${#CMD_ARR[@]}]="python3 manage.py -u -b -c"
CMD_ARR[${#CMD_ARR[@]}]="python3 manage.py -d -i"
CMD_ARR[${#CMD_ARR[@]}]="echo All bin files can be found under mlm2workshop\/rv1126\/rockdev/"

exec_cmd_arr "${CMD_ARR[@]}"
