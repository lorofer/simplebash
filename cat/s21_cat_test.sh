#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt


OPTIONS=('' -b -e -n -s -t -v -E -T "--number-nonblank" "--number" "--squeeze-blank")
FILES=("s21_cat_tests/bytes.txt" "s21_cat_tests/bytes2.txt" "s21_cat_tests/text3.txt")

for var in "${OPTIONS[@]}"
do
  for var2 in "${OPTIONS[@]}"
  do
    for var3 in "${OPTIONS[@]}"
    do
      if [[ "$var" != "$var2" || -z "$var" ]] && \
         [[ "$var2" != "$var3" || -z "$var2" ]] && \
         [[ "$var" != "$var3" || -z "$var" ]]
      then
        for TEST_FILE in "${FILES[@]}"
        do
          TEST="$var $var2 $var3 $TEST_FILE"
          echo "$TEST"
		  
          ./s21_cat $TEST > s21_cat.txt 2>/dev/null
          cat $TEST > cat.txt 2>/dev/null
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"

          if [[ "$DIFF_RES" == "Файлы s21_cat.txt и cat.txt идентичны" ]]
          then
            (( COUNTER_SUCCESS++ ))
          else
            echo "FAIL: $TEST" >> log.txt
            (( COUNTER_FAIL++ ))
          fi
          rm -f s21_cat.txt cat.txt
        done
      fi
    done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
RESULT=$((COUNTER_SUCCESS * 100 / (COUNTER_SUCCESS + COUNTER_FAIL)))
echo "RESULT - $RESULT%"