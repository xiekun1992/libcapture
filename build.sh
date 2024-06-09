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
  # mv ./liblibcapture.so ./libcapture.so
  cp -f ./liblibcapture.so ../../lctrl_rust/
  # sudo cp -f ./liblibcapture.so /usr/lib/
  echo "postprocess"
elif [[ $OSTYPE == "msys" ]]; then
  # cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib /e/Desktop/hello/
  cp -f ./Debug/libcapture.dll ./Debug/libcapture.lib D:/rust_workspaces/lctrl_rust/
  cp -f ./Debug/libcapture.dll D:/rust_workspaces/lctrl_rust/target/debug/
fi
