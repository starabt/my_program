#!/bin/bash
uploadDir=./test
# echo ${uploadDir}
# echo ${uploadDir}.tar.gz
# echo ${uploadDir}/*

tar -czvf ${uploadDir}.tar.gz ${uploadDir}
./ftp_upload ${uploadDir}.tar.gz &
rm -rf ${uploadDir}/*