# Color

This is a simple and fast command-line utility for color manipulations,
previews and conversions between different color models.

**Note: color-cli is not available on Windows at the moment.**

## Build

There are several ways to build the program:

```sh
# cmake
mkdir build
cmake ..
make

# or gcc
gcc -O2 -o color main.c color.c -lm

# or clang
clang -O2 -o color main.c color.c -lm
```

You can also use `make` for simpler workflow. To build, or clean, try:

```sh
# compiles the program
make build
# cleans build/
make clean
```

## Install

If you want to build and install at the same time, run:

```sh
make all
# or just
make
```

for which you might **need sudo privileges** as the installation path is `/usr/local/bin`. If you have **already compiled** the program, try:

```sh
make install
```

## Uninstall

To uninstall `color`, simply run:

```
make uninstall
```

## Library

`color` can be used as a static library as well. For that, you can try:

```sh
make install-lib  
```

This puts header file in `/usr/local/include` and `libcolr.a` in `/usr/local/lib`.

## Usage/Examples

Currently, supported color models are RGB, HEX, HSL, and HSV.

Let's say, you want to preview `#00008b` - the color of a rainy sky:

```sh
color hex 0x00008b
# or
color hex \#00008b
```

Hex starts with `0x` or `0X` along with `#`.

To create RGB color, you can type:

```sh
color rgb [0-255] [0-255] [0-255]
```

For HSV and HSL:

```sh
color [hsv|hsl] [0-359.0] [0-100.0] [0-100.0]
```

**Supported operations:**

| Operation | Option           | Parameter                      |
| :-------- | :--------------- | :----------------------------- |
| Negate    | `-n, --negate`   | Takes no parameter             |
| Convert   | `-t, --to`       | `rgb`, `hex`, `hsv`, and `hsl` |
| Rotate    | `-r, --rotate`   | Floating point with no range   |
| Saturate  | `-s, --saturate` | Between `-100.0` and `100.0`   |
| Lighten   | `-l, --lighten`  | Between `-100.0` and `100.0`   |
| Brighten  | `-b, --brighten` | Between `-100.0` and `100.0`   |

### Examples

```sh
color hsv 266 80 80 --lighten -20 --to rgb
color hex 0x00008b --rotate +245
color hex 0x00008b --rotate -40 --saturate -11.8 --to hsl
```

You can try `color --help` for more details.

## Contributing

Contributions are always welcome. If you report any bugs or have ideas for
improvements, please, do not hesitate to open an issue or send a pull request.

## License

Color-cli is licensed under the MIT License - see [LICENSE][license] for details.

[license]: https://github.com/nebulaw/color-cli/blob/main/LICENSE
[makefile]: https://github.com/nebulaw/color-cli/blob/main/Makefile
