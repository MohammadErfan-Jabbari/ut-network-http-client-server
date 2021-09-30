#!/bin/sh
cd ~/ErfanProject/Network/HttpClientServer/pure

# for i in $(seq 20)
# do
# ( ./client ) &
# done
# wait # for all the something with stuff


for i in `seq 50`
do 
    ( ./client )&
done
wait
