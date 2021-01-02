# KolibriOS Developer Edition/E
### Description/Что это?
KolibriDev is a fork of the official version Kolibri OS, created to prove that development in the OS itself is possible!

Kolibri OS DE/E - экспериментальная сборка КолибриОС, предназначенная для обкатки изменений и нововведений в ядро/систему; также сборка заточена на программирование для КолибриОС.
### Differences from the official/Отличия от ночной сборки

**Added/добавлено:**

- FasmX(console version Fasm)
- kosjs(in developing)
- Netsurf(pre-installed)
- TinyTextEditor
- NeonTextEditor
- TinyHashView
- TEAtool
- UD86(Disassembler)
- Binutils:
    - objcopy
    - ar
    - strip
- FreePascal
- TinyPython 
- Header files for fasm libraries
- New wallpapers and icons/Новые иконки и обои!

**Removed/Вырезаны:**

- All demos and games/все демки и игры
- Some emulators/эмуляторы
- fNav - file manager
- Unnecessary skins/ненужные скины

### Building and getting/Получение исходников и сборка; будет переведено позже ;)

**Getting:** 
You can get the finished ISO image on the [releases page](https://github.com/turbocat2001/KolibriDev/releases)

**Building in Linux:** 

To build you need: fasm, gcc-toolchain (sdk and kos32-gcc). If the SDK is located at "/home/autobuild/tools/win32/sdk" and the libraries are at "/home/autobuild/tools/win32/mingw32/lib", then continue. 
If not, then execute:

`export SDK_DIR="/path/to/sdk"`

`export LIB_DIR="/path/to/lib"`

After that, run ` ./build ` and after that the build will start. At the end of the build, the distribution kit can be run in "Qemu" or
"VirtualBox", commands:

` ./star_qemu`

`./start_qemu_kvm` 

`./start_vbox`

