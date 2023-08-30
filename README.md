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


## Usage
Currently, supported color models are: RGB, HEX, HSL and HSV. Here is an example of creating RGB color:
```bash
color rgb 244 180 220
```
![output-image-1][image-1]
As you can see from the output, it is a pinkish color.

For HSV and HSL:
```bash
color [hsv|hsl] [0-359] [0-100] [0-100]
```

HEX colors can have different prefixes such as: *0x, 0X, and #*:
```bash
color hex \#F8B195
color hex 0x6c5b7b
color hex 0X355C7D
```
![output-image-2][image-2]

Here are some operations that are supported at this moment:
```bash
# negation of hex value
color hex 0x0011FF [--negate|-n]

# converting hex color to hsv
color hex 0x0011FF [--to|-t] [rgb|hsv|hsl]
```
![output-image-3][image-3]

You can try ```color --help``` for more options.


## Contributing
Contributions are welcome. If you find any bug or have an idea for
improvements, feel free to open an issue or send a pull request.


## License
color-cli is licensed under the MIT License - see
[LICENSE][license] for details.


[license]: https://github.com/nebulaw/color-cli/blob/main/LICENSE
[image-1]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/screenshot1.png
[image-2]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/screenshot2.png
[image-3]: https://raw.githubusercontent.com/nebulaw/color-cli/main/images/screenshot3.png
