if [ ! -e build/ ]
then
mkdir build
fi

cd build
cmake ..

cd ..
cmake --build /home/vladislav/projects/MoveSemantics/build --target all -- -j 6
