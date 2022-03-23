./build.sh
./build/move_overload
dot -Tpng log.dot -omove_overload.png
./build/move_universal
dot -Tpng log.dot -omove_universal.png
