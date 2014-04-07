#!/bin/sh
protoc --cpp_out=../cpp *.proto
protoc --java_out=../java *.proto
