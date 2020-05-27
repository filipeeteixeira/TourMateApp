Dependencies: ../lib (GraphViewer)

Ficheiros de input: 
../res/NewMaps/Porto/porto_strong_nodes_xy.txt
../res/NewMaps/Porto/porto_strong_nodes_latlng.txt
../res/NewMaps/Porto/porto_strong_edges.txt
../res/NewMaps/Porto/porto_tags.txt
../res/NewMaps/Porto/porto_metro.txt

../res/GridGraphs/4x4/nodes.txt
../res/GridGraphs/8x8/nodes.txt
../res/GridGraphs/16x16/nodes.txt

Instruções de compilação:
mkdir build
cd build
cmake ..
make
./TourMateApp