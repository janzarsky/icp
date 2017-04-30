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
