#! /bin/bash

thrift -r --gen cpp server.thrift
mv gen-cpp src/container_server