./build.sh

./build/forward_forward
dot -Tpng log.dot -oimg/forward_forward.png

./build/forward_move
dot -Tpng log.dot -oimg/forward_move.png

./build/forward_value
dot -Tpng log.dot -oimg/forward_value.png

./build/forward_rvalue
dot -Tpng log.dot -oimg/forward_rvalue.png
