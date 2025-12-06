@echo off
echo ==============================BEGIN=COMPL==============================================
g++ -c src\main.cpp src\tree.cpp src\tree_dump.cpp src\akinator.cpp ^
    stk_lib\stack.cpp stk_lib\error_functions.cpp ^
    utils\sup_func.cpp ^
    -I src -I stk_lib -I utils ^
    -D _DEBUG -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal ^
    -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs ^
    -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -g -pipe -fexceptions ^
    -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security ^
    -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers ^
    -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 ^
    -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla
    
echo ==============================BEGIN=LINK===============================================
g++ *.o -o tree.exe
    
echo ===============================END=LINK================================================
del *.o 2>nul
