mkdir -p ./build/
cd ./build
rm -rf ./Debug/
cmake -B . -S ..
cmake --build .

cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib /e/Desktop/hello/
cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib /e/Desktop/lctrl_rust/