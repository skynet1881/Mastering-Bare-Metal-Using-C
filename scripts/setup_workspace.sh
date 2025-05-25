#!/bin/bash -e

source /home/cank/Xilinx/Vitis/2021.1/settings64.sh

script=$(basename "$0")
if [ "$#" -ne 2 ]; then
    echo "Usage $script <xsa> <workspace>"
    exit 1
fi

xsa="$( cd "$( dirname "${1}" )" && pwd )/$( basename "${1}" )"
ws="$( cd "$( dirname "${2}" )" && pwd )/$( basename "${2}" )"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd $DIR/../..

# Setup a Vitis workspace
/home/cank/Xilinx/Vitis/2021.1/bin/xsct -quiet /home/cank/github/Zybo-Vivado-Vitis/setup.tcl $xsa $ws
cp Debugger_* $ws/sw

popd
