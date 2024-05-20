
# gcc -Wall main.c -o invisilang 2>&1 | tee ./build.log # Redirect to stdout.
gcc -Wall main.c -o invisilang 2> ./build.log # Redirect to log as "only" present

# make sure file is generated
if [ ! -f ./invisilang ]; then
    echo "Build failed. Check build.log for more details."
fi
