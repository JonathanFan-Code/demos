1. 创建编译目录: mkdir build
2. 生成X64工程: cmake -G "Visual Studio 15 2017 Win64" -B ./build .
   or  生成X86工程: cmake -G "Visual Studio 15 2017" -B ./build .
   (需要使用对应64位或者32位python，以及sdk dll)
3. 编译release: cmake --build ./build --config Release
4. 安装: cmake --install .\build\