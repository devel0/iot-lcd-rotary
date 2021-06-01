#!/bin/bash

exdir="$(dirname `readlink -f "$0"`)"

cd "$exdir"

doxygen

cd "$exdir"/data

rm -fr "$exdir"/data/api
mkdir -p "$exdir"/data/api
doxybook2 -i "$exdir"/xml -o "$exdir"/data/api -c "$exdir"/data/doxybook.json

find "$exdir"/data/api  -type f -exec sed -i 's/Updated on.*//g' "{}" \;