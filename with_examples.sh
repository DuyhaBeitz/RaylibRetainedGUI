./rebuild.sh
sudo ./install.sh
cmake -S . -B build -DRAYLIBRETAINEDGUI_BUILD_EXAMPLES=ON
cmake --build build