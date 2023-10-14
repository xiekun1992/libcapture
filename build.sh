mkdir -p ./build/
cd ./build
rm -rf ./Debug/

if [[ $OSTYPE == "linux-gnu" ]]; then
  sudo apt install libxtst-dev libx11-dev build-essential cmake -y
# elif [[ $OSTYPE == "msys" ]]; then
fi

cmake -B . -S ..
cmake --build .

if [[ $OSTYPE == "linux-gnu" ]]; then
  mv ./liblibcapture.so ./libcapture.so
  cp -f ./libcapture.so ../../lctrl_rust/
elif [[ $OSTYPE == "msys" ]]; then
  # cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib /e/Desktop/hello/
  cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib ../../lctrl_rust/
fi
