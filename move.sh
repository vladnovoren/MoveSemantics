./build.sh
./build/move_overload
dot -Tpng log.dot -oimg/move_overload.png
./build/move_universal
dot -Tpng log.dot -oimg/move_universal.png
./build/move_template
dot -Tpng log.dot -oimg/move_template.png
./build/move_check
dot -Tpng log.dot -oimg/move_check.png
