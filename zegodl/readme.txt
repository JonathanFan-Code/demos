1. 创建编译目录: mkdir build
2. 生成X64工程: cmake -G "Visual Studio 15 2017 Win64" -B ./build .
3. 编译release: cmake --build ./build --config Release
4. 安装: cmake --install .\build\