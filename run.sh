mode=$1

if [ "$mode" = "all" ]
then
    xterm  -T "Server" -hold -e ./run.sh server & xterm -T "Node A" -hold -e ./run.sh A & xterm -T "Node B" -hold -e ./run.sh B
fi


if [ "$mode" = "server" ] 
then
    ./server/KeyManager
fi


if [ "$mode" = "A" ]
then
    sleep 0.2s
    ./clients/Node A cbc
fi


if [ "$mode" = "B" ]
then
    sleep 0.3s
    ./clients/Node B
fi


