#!/bin/bash
tot=0
max=0
min=0

function run
{
    echo $((time -p ./GameOfLife 1000 1000 16) 2>&1 | grep real | awk -F' ' '{print $2}')
}

min=$(run)

for i in `seq 1 10`;
            do
                temp=$(run)
                echo "$i : $temp"
                tot=$(echo $tot + $temp | bc)
                if [ $(echo " $temp > $max" | bc) -eq '1' ]
                then
                    max=$temp ;
                fi
                if [ "$(($1))" -eq '1' ]
                then
                    min=$temp ;
                fi
                if [ $(echo " $temp < $min" | bc) -eq '1' ]
                then
                    min=$temp ;
                fi
            done

echo "min $min"
echo "max $max"
echo tot $(echo "($tot - $min - $max)/8" | bc -l)
