#!/bin/bash

DIFF_RES=""
COUNTER_SUCCESS=0
COUNTER_FAIL=0

echo "" > log.txt
GREEN='\033[32m'
RED='\033[31m'
NORMAL='\033[0m'
echo -e $GREEN "TESTS for GREP" $NORMAL

OPTIONS=('' -i -v -c -l -n -h -s -o)
FILES=("Makefile" "grep_main.c" "Makefile s21_grep.c")
PATTERNS=("-e while" "ss" "-e ss handler" "-f reg_exmpl.txt")

for var1 in "${OPTIONS[@]}"
do
    for var2 in "${OPTIONS[@]}"
    do
        for var3 in "${OPTIONS[@]}"
        do 
			if [[ "$var1" != "$var2" || -z "$var1" ]] && \
			[[ "$var2" != "$var3" || -z "$var2" ]] && \
			[[ "$var1" != "$var3" || -z "$var1" ]]
			then
				for TEST_FILE in "${FILES[@]}"
				do
					for TEST_PATTERN in "${PATTERNS[@]}"
					do
						TEST0=" $var1 $var2 $var3 $TEST_PATTERN $TEST_FILE "
						./s21_grep $TEST0 > s21_grep.txt
						grep $TEST0 > grep.txt
						DIFF_RES="$(diff -s s21_grep.txt grep.txt)"

						if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
						then
							echo -e $NORMAL TEST $((COUNTER_SUCCESS+COUNTER_FAIL+1)) "$TEST0" $GREEN "\tSUCCESS"
							(( COUNTER_SUCCESS++ ))
						else
							echo -e $NORMAL TEST $((COUNTER_SUCCESS+COUNTER_FAIL+1)) "$TEST0" $RED "\tFAIL"
							echo "$TEST0" >> log.txt
							(( COUNTER_FAIL++ ))
						fi

						rm s21_grep.txt grep.txt
					done
				done
			fi
        done
    done
done

for var5 in "${OPTIONS[@]}"
do  
    for var6 in i c l n v h s o
    do
        for TEST_FILE in "${FILES[@]}"
        do
            for TEST_PATTERN in "${PATTERNS[@]}"
            do
            TEST0="$var5$var6 $TEST_PATTERN $TEST_FILE"
            ./s21_grep $TEST0 > s21_grep.txt
            grep $TEST0 > grep.txt
            
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                echo -e $NORMAL TEST $((COUNTER_SUCCESS+COUNTER_FAIL+1)) "$TEST0" $GREEN "\tSUCCESS"
                (( COUNTER_SUCCESS++ ))
            else
                echo -e $NORMAL TEST $((COUNTER_SUCCESS+COUNTER_FAIL+1)) "$TEST0" $RED "\tFAIL"
				echo "$TEST0" >> log.txt
				(( COUNTER_FAIL++ ))
            fi
            rm s21_grep.txt grep.txt
            done
        done
    done
done

echo -e $GREEN SUCCESS $COUNTER_SUCCESS
echo -e $RED FAIL $COUNTER_FAIL
if [ "$1" == "val" ]; then
    echo -e $NORMAL valgrind result
    echo   all test  : $(grep -c "ERROR SUMMARY:" val_log.txt)
    echo -e $GREEN good test : $(grep -c "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" val_log.txt)
fi