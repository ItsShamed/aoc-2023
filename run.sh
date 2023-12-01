#!/bin/sh

for f in inputs/*; do
    echo "== Running for $f =="
    ./submission "$f"
    echo ""
done
