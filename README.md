[![Virtual](https://github.com/andrey-terekhov/RuC/actions/workflows/virtual.yml/badge.svg)](https://github.com/andrey-terekhov/RuC/actions/workflows/virtual.yml) [![LLVM](https://github.com/andrey-terekhov/RuC/actions/workflows/llvm.yml/badge.svg)](https://github.com/andrey-terekhov/RuC/actions/workflows/llvm.yml)
# ![Logo](https://raw.githubusercontent.com/Victor-Y-Fadeev/RuC-WPF/master/RuC.WPF/Images/Repository.png) Russian C

Этот репозиторий содержит компилятор языка RuC.
Авторство принадлежит [Андрею Николаевичу Терехову](https://github.com/andrey-terekhov),
заведующему кафедрой "Системного программирования" СПбГУ.

# Сборка

## Под ОС Ubuntu

С клонируйте репозиторий по общедоступной ссылке:

```cmd
$ git clone https://github.com/andrey-terekhov/RuC
```

Либо с сервера компании:

```cmd
$ git clone ssh://git@gitlab.softcom.su:22500/ruc/ruc.git
```

Для конфигурирования и сборки, войдите в каталог и воспользуйтесь:

```cmd
$ mkdir -p build && cd build && cmake .. && cd ..
$ cmake --build build --config Release
```

### Полезные команды Git

Сохранение аутентификационных данных репозитория:

```cmd
$ git config credential.helper store
```

Соединение локального репозитория с оригинальным:

```cmd
$ git remote add upstream https://github.com/andrey-terekhov/RuC
$ git remote set-url --push upstream DISABLE
```

Стягивание изменений:

```cmd
$ git fetch upstream
$ git rebase upstream/master
```

## Под ОС Windows

Перед сборкой и использованием языка РуСи, необходимо установить систему сборки [CMake](https://cmake.org/download/) и компилятор языка С/С++ от Microsoft, входящий в состав [Visual Studio](https://visualstudio.microsoft.com/ru/thank-you-downloading-visual-studio/?sku=Community&rel=16#).

Прямые ссылки на загрузку: [CMake 3.17.3 x64](https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3-win64-x64.msi), [CMake 3.17.3 x86](https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3-win32-x86.msi).

При установке CMake, также необходимо отметить любой из пунктов `Add CMake to the system PATH`, как показано на картинке.

![CMake](uploads/b0ec5abbdb1c3d45166b2c141455523f/CMake.png)

А при установке Visual Studio, необходимо добавить в сборку `Разработка классических приложений на C++`.

![C++](uploads/4ece3aa315a2deeb0757317d8223c502/C++.png)

После этого можно приступить к сборке проекта. Скачайте проект любым git клиентом, например, [Git BASH](https://gitforwindows.org/) и откройте папку проекта из Windows.

Для первоначальной настройки проекта введите команду:

```cmd
$ mkdir build && cd build && cmake .. && cd ..
```

Для сборки/пересборки проекта используйте, вызываемую из корня:

```cmd
$ cmake --build build --config Release
```

Исполняемый файл `ruc.exe` будет помещен в директорию `build\Release`. При запуске ему необходимо передать путь к РуСи коду в качестве параметра. При указании пути к коду используйте только прямой слеш (`/`)! Пример:

```cmd
$ ruc.exe ../../tests/test.c
```

Сгенерированные коды будут помещены в папку, из которой был вызван транслятор.

# Параметры командной строки

## Компилятор

Компилятор РуСи поддерживает параметризацию из командной строки, порядок не важен, повторения игнорируются. В качестве параметров можно передавать:
- Пути к файлам
- Пути к библиотекам
- Флаги компиляции
- Примитивные макросы <mark>(в будущем)</mark>

Общие флаги:
- `-o` - флаг переопределения выходного файла (использование `-o export.txt`)
- `-I` - флаг поиска библиотек (использование `-Ipath/to/headers`)
- `-D` - <mark>флаг предопределенного макроса (использование `-DVAR=1024`, эквивалентно `#define VAR 1024`)</mark>
- `-Wno` - флаг отключения восстановления после ошибок

Флаги виртуальной машины:
- `-VM` - флаг компиляции в коды виртуальной машины РуСи (по умолчанию)
- Флаги сжатия выходных таблиц
  - `-i64`, `-i32`, `-i16`, `-i8` - использование знаковых типов, размера **8**, **4**, **2** и **1** байт
  - `-u64`, `-u32`, `-u16`, `-u8` - использование беззнаковых типов, соответственно

Флаги LLVM:
- `-LLVM` - флаг компиляции в LLVM коды
- `--x86_64` - флаг целевой платформы Intel (по умолчанию)
- `--mipsel` - флаг целевой платформы MIPS

## Тестовая система

```bash
Usage: ./test.sh [KEY] ...
Description:
        This script tests all files from "../tests" directory.
        Folder "../tests/errors" should contain tests with expected error.
        Executable tests should be in "../tests/executable" directory.
        To ignore invalid tests output, use "*/warnings/*" subdirectory.
        For tests with expected runtime error, use "*/errors/*" subdirectory.
        For multi-file tests, use "*/include/*" subdirectory.
        Failed tests for debug build only will be marked with "(Debug)".
Keys:
        -h, --help      To output help info.
        -s, --silence   For silence testing.
        -f, --fast      Fast testing, Release builds only.
        -i, --ignore    Ignore errors & executing stages.
        -r, --remove    Remove build folder before testing.
        -d, --debug     Switch on debug tracing.
        -v, --virtual   Set RuC virtual machine release.
        -o, --output    Set output printing time (default = 0.0).
        -w, --wait      Set waiting time for timeout result (default = 2).
```
