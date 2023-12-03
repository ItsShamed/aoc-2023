#!/bin/sh

for f in inputs/*.txt; do
    echo "== Running for $f =="
    ./submission "$f"
    echo ""
done
