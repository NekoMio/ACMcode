#!/bin/sh
while true; do
./maker > 1.in
./G <1.in >1.out
./GG <1.in >1.ans
if diff 1.out 1.ans; then
printf "AC\n"
else
printf "NO\n"
exit 0;
fi
done