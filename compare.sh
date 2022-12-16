#!/bin/bash

clear
# Get qualitative results
for SOLVER in result/*; do
    if [[ -x $SOLVER && -f $SOLVER ]]; then
        # mkdir -p "${SOLVER}_sol"
        echo "Running solver ${SOLVER#"result/"} ..."
        for FILE in result/problems/*; do
            ./${SOLVER} < $FILE > "${SOLVER}_sol/sol${FILE#"result/problems/test"}";
        done
    fi
done

# Compare computation costs using hyperfine
hyperfine 'for FILE in result/problems/*; do ./result/cpp_btk < $FILE; done' \
            'for FILE in result/problems/*; do ./result/cpp_pure_btk < $FILE; done' \
            'for FILE in result/problems/*; do ./result/cpp_wo_btk < $FILE; done' -m 50 --export-csv log1.csv
hyperfine 'for FILE in result/problems/*; do ./result/py_btk < $FILE; done' -m 10 --export-csv log2.csv

touch log.csv
cat log1.csv > log.csv
cat log2.csv >> log.csv
rm -f log1.csv log2.csv
