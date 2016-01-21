#!/bin/bash
tot=0
max=0
min=0
dim=0
iter=0
workers=0
declare -a results

make # Make sure the project is up to date

function run { # Times a single run with
    (time -p ./GameOfLife $1 $2 $3 ) 2>&1 | grep real | awk -F' ' '{print $2}'
}

function runTest { # Executes $4 runs and averages their time after removing the max and min
    dim=$1
    iter=$2
    workers=$3
    echo "Dim: $dim Iterations: $iter Workers: $workers Tests: $4" >&2
    tot=0
    max=0
    min=$( run $dim $iter $workers ) # Initialize the value of min with the value of a run
    for i in `seq 1 $4`; # Perform the number of tests specified in the 4th parameter
                do
                    temp=$( run $dim $iter $workers )
                    # echo "$i : $temp" >&2
                    tot=$(echo $tot + $temp | bc) # Use bc to perform floating point ops
                    if [ $(echo " $temp > $max" | bc) -eq '1' ] #bc return 1 on true
                    then
                        max=$temp ;
                    fi
                    if [ $(echo " $temp < $min" | bc) -eq '1' ]
                    then
                        min=$temp ;
                    fi
                done

    # echo "min $min"
    # echo "max $max"
    # echo tot $(echo "scale=4; ($tot - $min - $max)/( $4 - 2 )" | bc -l)
   echo "scale=4; ($tot - $min - $max)/( $4 - 2 )" | bc -l
}

function runSuite { # Runs a suite of tests using $1 workers
    unset results
    echo "Running test suite" >&2
    for i in `seq 0 9`;
        do
            results[i]=$(runTest $((100*(i+1))) 50 $1 10)
        done
}

runSuite 1
echo ${results[@]}
runSuite 2
echo ${results[@]}
