#!/bin/bash
cd mark_b/processor/
gcc adder.c
mv a.out adder.out
cd mark_b/server
gcc server.c
cd mark_b/client
gcc client.c
./a.out