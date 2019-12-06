./server 4002 server1&
sleep .5
./server 5002 server2&
sleep .5
./server 6002 server3&
sleep 180

fuser -k 4002/tcp
fuser -k 5002/tcp
fuser -k 6002/tcp
