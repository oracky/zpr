# ZPR - symulator ruchu miejskiego (Zuzanna Lewandowska, Michał Oracki) 
## Używane biblioteki: 
* sql_orm https://github.com/fnc12/sqlite_orm
* Boost 
* imgui https://github.com/ocornut/imgui (nie zdecydowaliśmy do końca)

## Przygotowanie:
### Linux: 
Należy uruchomić wszystkie skrypty w folderze scripts/linux (install_boost.sh, install_sqlite.sh, create_db.sh)<br/><br/> 
Build (w głównym folderze projektu):
```bash
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S$(pwd) -B$(pwd)/build -G "Unix Makefiles"
``` 
```bash
cmake --build $(pwd)/build --config Debug --target all -j 10 --
``` 
<br/>
Testy: <br/><br/>

```bash
ctest build/
``` 
<br>

### Windows
W celu zainstalowania bazy należy uruchomić skrypt scripts/windows/create_db.ps1 z uprawnieniami administratora


