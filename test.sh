#!/bin/bash

PASS_CNT=0
FAIL_CNT=0
UNK_CNT=0

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
NC='\033[0m'

function check_code {
    exitcode=$(echo $?)

    if [ "$exitcode" -eq "$1" ]; then
        PASS_CNT=$((PASS_CNT+1))
        printf "${GREEN}PASSED${NC}\n"
    else
        printf "${RED}FAILED${NC}\n"
        SUITE_RESULT="${RED}FAILED${NC}"
        FAIL_CNT=$((FAIL_CNT+1))
    fi
}

function check_invalid {
    echo "***** grep \"ERROR:\" out"
    grep "ERROR:" out
    check_code 0
}

function check_msg {
    echo "***** output:"
    cat out
    echo ""
    echo "***** grep \"$1\":"
    grep "$1" out
    check_code 0
}

echo "**********************************************************************"
echo "* TESTS"
echo "**********************************************************************"

SUITE_RESULT="${GREEN}PASSED${NC}"

echo "***** test quit"
printf "quit\n" | ./hra2017-cli >out 2>err
check_code 0

echo "***** test invalid command"
printf "asdf\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test no games"
printf "games\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "No games"

echo "***** test 1 game"
printf "new\ngames\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "Games number 1, are"

echo "***** test 4 games"
printf "new\nnew\nnew\nnew\ngames\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "Games number 1, 2, 3, 4, are"

echo "***** test 5 games"
printf "new\nnew\nnew\nnew\nnew\ngames\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move deck pile0"
printf "new\nmove deck pile0\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move deck pile1"
printf "new\nmove deck pile1\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 11, to 0, count 1"

echo "***** test move deck pile7"
printf "new\nmove deck pile7\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 11, to 6, count 1"

echo "***** test move deck pile8"
printf "new\nmove deck pile8\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move deck home0"
printf "new\nmove deck home0\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move deck home1"
printf "new\nmove deck home1\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 11, to 7, count 1"

echo "***** test move deck home4"
printf "new\nmove deck home4\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 11, to 10, count 1"

echo "***** test move deck home5"
printf "new\nmove deck home5\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile0 pile1"
printf "new\nmove pile0 pile1\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile1 pile0"
printf "new\nmove pile1 pile0\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile1 pile2"
printf "new\nmove pile1 pile2\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 0, to 1, count 1"

echo "***** test move pile7 pile2"
printf "new\nmove pile7 pile2\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 6, to 1, count 1"

echo "***** test move pile2 pile7"
printf "new\nmove pile2 pile7\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 1, to 6, count 1"

echo "***** test move pile8 pile1"
printf "new\nmove pile8 pile1\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile1 pile8"
printf "new\nmove pile1 pile8\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile2 pile5 0"
printf "new\nmove pile2 pile5 0\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_invalid

echo "***** test move pile2 pile5 1"
printf "new\nmove pile2 pile5 1\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 1, to 4, count 1"

echo "***** test move pile2 pile5 3"
printf "new\nmove pile2 pile5 3\nquit\n" | ./hra2017-cli >out 2>err
check_code 0
check_msg "EXECUTE: move, from 1, to 4, count 3"

echo ""

echo "**********************************************************************"
printf "* RESULT: $SUITE_RESULT\n"
echo "**********************************************************************"

if [ "$FAIL_CNT" -gt 0 ]; then
    RESULT="${RED}FAILED${NC}"
else
    RESULT="${GREEN}PASSED${NC}"
fi

echo "**********************************************************************"
printf "* SUMMARY: $RESULT\n"
printf "* passed: $PASS_CNT, failed: $FAIL_CNT, unknown: $UNK_CNT\n"
echo "**********************************************************************"

rm out err
