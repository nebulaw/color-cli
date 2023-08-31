# color-cli

This is a simple and fast command-line utility for color manipulations,
previews and conversions between different color models.


## Installation
**Note: color-cli is not available on Windows at the moment.** \
On Linux or macOS, you can try:
```bash
git clone --depth=2 https://github.com/nebulaw/color-cli
cd color-cli/
# default installation path is ~/.local/bin/
./install.sh
```
you can also specify a different path:
```bash
sudo ./install.sh /usr/bin/
```


## Usage/Examples
Currently, supported color models are RGB, HEX, HSL, and HSV.

Let's say, we want to preview `#00008b` - the color of a rainy sky:
```bash
color hex \#00008b
```
![output-image-1][image-1]

Hex also starts with `0x` or `0X`  along with `#`.

To create RGB color, we can type:
```bash
color rgb [0-255] [0-255] [0-255]
```

For HSV and HSL:
```bash
color [hsv|hsl] [0-359.0] [0-100.0] [0-100.0]
```

**Supported operations:**

|  Operation | Option           | Parameter                       |
| :--------  | :--------------- | :------------------------------ |
|  Negate    | `-n, --negate`   | Takes no parameter              |
|  Convert   | `-t, --to`       | `rgb`, `hex`, `hsv`, and `hsl`  |  
|  Rotate    | `-r, --rotate`   |  Floating point with no range   |
|  Saturate  | `-s, --saturate` |  Between `-100.0` and `100.0`   |
|  Lighten   | `-l, --lighten`  |  Between `-100.0` and `100.0`   |
|  Brighten  | `-b, --brighten` |  Between `-100.0` and `100.0`   |

**Examples**

```bash
color hsv 266 80 80 --lighten -20 --to rgb
```
![output-image-3][image-2]

```bash
color hex 0x00008b --rotate +245
```
![output-image-3][image-3]

```bash
color hex 0x00008b --rotate -40 --saturate -11.8 --to hsl
```
![output-image-3][image-4]

You can try ```color --help``` for more options.


## Contributing
Contributions are always welcome. If you report any bugs or have ideas for
improvements, please don't hesitate to open an issue or send a pull request.


## License
Color-cli is licensed under the MIT License - see
[LICENSE][license] for details.


[license]: https://github.com/nebulaw/color-cli/blob/main/LICENSE
[image-1]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/image-1.png
[image-2]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/image-2.png
[image-3]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/image-3.png
[image-4]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/image-4.png

