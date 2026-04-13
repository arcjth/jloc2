# should support both amd64 and embbeded atmega328p devices (TODO)
gcc -o out/jsimulator lib/jlinear.c lib/jthio.c src/jloc2.c src/jloc_sim.c src/main.c -lm
echo "compilation script completed."