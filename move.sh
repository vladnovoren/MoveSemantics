./build.sh
./build/move_overload
dot -Tpng log.dot -omove_overload.png
./build/move_universal
dot -Tpng log.dot -omove_universal.png
./build/move_template
dot -Tpng log.dot -omove_template.png
./build/move_check
dot -Tpng log.dot -omove_check.png
