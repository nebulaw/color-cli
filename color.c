#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>
#include <time.h>
#include <math.h>

#include "color.h"


static struct option arg_options[] = {
  { "negate",     no_argument,        0,  'n' },
  { "to",         required_argument,  0,  't' },
  { "saturate",   required_argument,  0,  's' },
  { "rotate",     required_argument,  0,  'r' },
  { "lighten",    required_argument,  0,  'l' },
  { "brighten",   required_argument,  0,  'b' },
  { 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
  char **argv_ptr = argv;
  assert(*argv++ != NULL);

  clop_t CLOPS[MAXCLOPS];
  int COLOR_MODEL = RGB, clp = 0;
  color_t color;
  char *var1, *var2, *var3;

  srand(time(0));

  /* no argument error */
  if (*argv == NULL) {
    usage();
    exit(-1);
  }

  if (strcmp(*argv, "--help") == 0) {
    usage();
    exit(0);
  }

  /* parse color model */
  COLOR_MODEL = strcmp(*argv, "rgb") == 0 ? RGB :
    strcmp(*argv, "hex") == 0 ? HEX :
    strcmp(*argv, "hsv") == 0 ? HSV :
    strcmp(*argv, "hsl") == 0 ? HSL : 0;

  /* parse color values from arguments and create color */
  if (COLOR_MODEL == HEX) {
    if (*(++argv) == NULL) {
      fprintf(stderr, "color: invalid %s color format.\n", *(--argv));
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    } else {
      color = createhex(*argv);
    }
  } else if ((COLOR_MODEL == RGB || COLOR_MODEL == HSV || COLOR_MODEL == HSL)) {
    if (argc > 4) {
      var1 = *(++argv);
      var2 = *(++argv);
      var3 = *(++argv);
    } else {
      fprintf(stderr, "color: invalid %s color format.\n", *argv);
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    }
    /* create color */
    switch (COLOR_MODEL) {
    case RGB: color = creatergb(var1, var2, var3); break;
    case HSV: color = createhsv(var1, var2, var3); break;
    case HSL: color = createhsl(var1, var2, var3); break;
    }
  } else if (createpredefinedcolor(*argv, &color)) {
    // ignored line
  } else if (!strcmp(*argv, "random")) {
    color = createrandom();
  } else {
    fprintf(stderr, "color: invalid command %s.\n", *argv);
    fprintf(stderr, "Try 'color --help' for more options.\n");
    exit(1);
  }

  /* parse options */
  int op;
  while ((op = getopt_long(argc, argv_ptr, "ns:r:l:b:t:", arg_options, NULL)) != -1) {
    switch (op) {
    case 'n': CLOPS[clp++] = createclop(NEGATE, 0, ""); break;
    case 's': CLOPS[clp++] = createclop(SATURATE, 1, optarg); break;
    case 'r': CLOPS[clp++] = createclop(ROTATE, 1, optarg); break;
    case 'l': CLOPS[clp++] = createclop(LIGHTEN, 1, optarg); break;
    case 'b': CLOPS[clp++] = createclop(BRIGHTEN, 1, optarg); break;
    case 't': CLOPS[clp++] = createclop(CONVERSION, 1, optarg); break;
    case '?': exit(-1);
    default: break;
    }
  }

  /* apply clops */
  for (int i = 0; i < clp; i++) {
    switch (CLOPS[i].op) {
    case NEGATE:      color = negate(color); break;
    case CONVERSION:  color = convert(color, (int) CLOPS[i].param); break;
    case SATURATE:    color = saturate(color, CLOPS[i].param); break;
    case ROTATE:      color = rotate(color, CLOPS[i].param); break;
    case LIGHTEN:     color = lighten(color, CLOPS[i].param); break;
    case BRIGHTEN:    color = brighten(color, CLOPS[i].param); break;
    }
  }

  /* display the result*/
  displaycolor(color);

  return 0;
}


clop_t createclop(int op, int has_param, char *value)
{
  float val;
  if (has_param && op != CONVERSION) {
    val = strspn(value, "+-.0123456789") == strlen(value) ? atof(value) : -101;
    if ((val < -100 || 100 < val) && op != ROTATE)
      EXIT_ON_FAILURE("invalid value: %s", value)
  } else if (has_param && op == CONVERSION) {
    if (strcmp(value, "rgb") == 0) val = RGB;
    else if (strcmp(value, "hex") == 0) val = HEX;
    else if (strcmp(value, "hsv") == 0) val = HSV;
    else if (strcmp(value, "hsl") == 0) val = HSL;
    else {
      fprintf(stderr, "color: invalid convert type %s.\n", optarg);
      fprintf(stderr, "Try 'color --help' for more options.\n");
      exit(-1);
    }
  }
  clop_t clop;
  clop.op = op;
  clop.has_param = has_param;
  clop.param = val;
  return clop;
}

color_t createrandom(void)
{
  color_t color;
  color.model = HSL;
  color.values[0] = rand() % 360;
  color.values[1] = rand() % 100;
  color.values[2] = rand() % 100;
  color = hsl2rgb(color);
  return color;
}

color_t creatergb(char *red, char *green, char *blue)
{
  /* checking if arguments are numbers */
  float r = strspn(red, ".0123456789") == strlen(red) ? atof(red) : -1;
  float g = strspn(green, ".0123456789") == strlen(green) ? atof(green) : -1;
  float b = strspn(blue, ".0123456789") == strlen(blue) ? atof(blue) : -1;
  /* range validation */
  if (!(0 <= r && r < 256)) EXIT_ON_FAILURE("invalid red value: %s\n", red)
  if (!(0 <= g && g < 256)) EXIT_ON_FAILURE("invalid green value: %s\n", green)
  if (!(0 <= b && b < 256)) EXIT_ON_FAILURE("invalid blue value: %s\n", blue)
  color_t rgb_color;
  rgb_color.model = RGB;
  rgb_color.values[0] = r;
  rgb_color.values[1] = g;
  rgb_color.values[2] = b;
  rgb_color.values[3] = 255;
  return rgb_color;
}

color_t createhex(char *hex)
{
  if (strlen(hex) < 4 || strlen(hex) > 8)
    EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  /* extract prefix from hex value */
  char *hexvalue = (char *)malloc(sizeof(char) * strlen(hex) - 2);
  switch (*hex) {
    case '#': strncpy(hexvalue, hex + 1, strlen(hex) - 1); break;
    case '0':
      switch (*(hex + 1)) {
        case 'x': case 'X': strncpy(hexvalue, hex + 2, strlen(hex) - 2); break;
        default: EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
      }
      break;
    default: EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  }
  /* validate actual value */
  if (strspn(hexvalue, "0123456789abcdefABCDEF") != strlen(hexvalue) || strlen(hexvalue) != 6)
    EXIT_ON_FAILURE("invalid hex format: %s\n", hex)
  int r, g, b;
  sscanf(hexvalue, "%02x%02x%02x", &r, &g, &b);
  color_t hex_color;
  hex_color.model = HEX;
  hex_color.values[0] = ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF));
  return hex_color;
}

color_t createhsv(char *hue, char *saturation, char *value)
{
  float h = strspn(hue, ".0123456789") == strlen(hue) ? atof(hue) : -1;
  float s = strspn(saturation, ".0123456789") == strlen(saturation) ? atof(saturation) : -1;
  float v = strspn(value, ".0123456789") == strlen(value) ? atof(value) : -1;
  /* range validation */
  if (h < 0) EXIT_ON_FAILURE("invalid hue value: %s\n", hue)
  if (!(0 <= s && s <= 100)) EXIT_ON_FAILURE("invalid saturation value: %s\n", saturation)
  if (!(0 <= v && v <= 100)) EXIT_ON_FAILURE("invalid brightness value: %s\n", value)
  color_t hsv_color;
  hsv_color.model = HSV;
  hsv_color.values[0] = fmodf(h, 360.f);
  hsv_color.values[1] = s;
  hsv_color.values[2] = v;
  hsv_color.values[3] = 255;
  return hsv_color;
}

color_t createhsl(char *hue, char *saturation, char *lightness)
{
  float h = strspn(hue, ".0123456789") == strlen(hue) ? atof(hue) : -1;
  float s = strspn(saturation, ".0123456789") == strlen(saturation) ? atof(saturation) : -1;
  float l = strspn(lightness, ".0123456789") == strlen(lightness) ? atof(lightness) : -1;
  /* range validation */
  if (h < 0) EXIT_ON_FAILURE("invalid hue value: %s\n", hue)
  if (!(0 <= s && s <= 100)) EXIT_ON_FAILURE("invalid saturation value: %s\n", saturation)
  if (!(0 <= l && l <= 100)) EXIT_ON_FAILURE("invalid lightness value: %s\n", lightness)
  color_t hsl_color;
  hsl_color.model = HSL;
  hsl_color.values[0] = fmodf(h, 360.f);
  hsl_color.values[1] = s;
  hsl_color.values[2] = l;
  hsl_color.values[3] = 255;
  return hsl_color;
}

color_t copy(color_t color) {
  color_t copy;
  copy.model = color.model;
  for (int i = 0; i < (sizeof(color.values) / sizeof(color.values[0])); i++)
    copy.values[i] = color.values[i];
  return copy;
}

color_t convert(color_t color, int convert_model)
{
  switch (color.model) {
  case RGB:
    switch (convert_model) {
    case RGB: return copy(color);
    case HEX: return rgb2hex(color);
    case HSV: return rgb2hsv(color);
    case HSL: return rgb2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  case HEX:
    switch (convert_model) {
    case RGB: return hex2rgb(color);
    case HEX: return copy(color);
    case HSV: return hex2hsv(color);
    case HSL: return hex2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
  case HSV:
    switch (convert_model) {
    case RGB: return hsv2rgb(color);
    case HEX: return hsv2hex(color);
    case HSV: return copy(color);
    case HSL: return hsv2hsl(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  case HSL:
    switch (convert_model) {
    case RGB: return hsl2rgb(color);
    case HEX: return hsl2hex(color);
    case HSV: return hsl2hsv(color);
    case HSL: return copy(color);
    default: EXIT_ON_FAILURE("invalid convert model\n")
    }
    break;
  }
  return (color_t) {};
}

static color_t rgb2hex(color_t rgb)
{
  color_t hex;
  hex.model = HEX;
  hex.values[0] = (((int)roundf((rgb.values[0])) & 0xFF) << 16) +
    (((int)roundf((rgb.values[1])) & 0xFF) << 8) + (((int)roundf(rgb.values[2])) & 0xFF);
  return hex;
}

static color_t rgb2hsv(color_t rgb)
{
  float r = rgb.values[0] / 255.f, g = rgb.values[1] / 255.f, b = rgb.values[2] / 255.f;
  float max = MAX3(r, g, b), min = MIN3(r, g, b);
  float hue = fmodf((hue =
    max == min ? 0.f :
    max == r ? 60.f * (fmodf((g - b), 6.f) / (max - min)) :
    max == g ? 60.f * (2.f + (b - r) / (max - min)) :
/* max == b */ 60.f * (4.f + (r - g) / (max - min))) < 0.f ?
      hue + 360 : hue, 360.f);
  float value = max;
  float saturation = max == 0 ? 0 : (max - min) / max;
  color_t hsv_color;
  hsv_color.model = HSV;
  hsv_color.values[0] = hue;
  hsv_color.values[1] = saturation * 100.f;
  hsv_color.values[2] = value * 100.f;
  return hsv_color;
}

static color_t rgb2hsl(color_t rgb)
{
  float r = rgb.values[0] / 255.f, g = rgb.values[1] / 255.f, b = rgb.values[2] / 255.f;
  float max = MAX3(r, g, b), min = MIN3(r, g, b);
  float hue = fmodf((hue =
    max == min ? 0.f :
    max == r ? 60.f * (fmodf((g - b), 6.f) / (max - min)) :
    max == g ? 60.f * (2.f + (b - r) / (max - min)) :
/* max == b */ 60.f * (4.f + (r - g) / (max - min))) < 0.f ?
      hue + 360 : hue, 360.f);
  float luminosity = (max + min) / 2;
  float saturation = (max == min) ? 0 :
    ((max - min) / (1 - fabsf(2 * luminosity - 1)));
  color_t hsl_color;
  hsl_color.model = HSL;
  hsl_color.values[0] = hue;
  hsl_color.values[1] = saturation * 100.f;
  hsl_color.values[2] = luminosity * 100.f;
  return hsl_color;
}

static color_t hex2rgb(color_t hex)
{
  color_t rgb_color;
  rgb_color.model = RGB;
  rgb_color.values[2] = (int)roundf(hex.values[0]) & 0xFF;
  rgb_color.values[1] = ((int)roundf(hex.values[0]) >> 8) & 0xFF;
  rgb_color.values[0] = ((int)roundf(hex.values[0]) >> 16) & 0xFF;
  return rgb_color;
}

static color_t hex2hsv(color_t hex)
{
  return rgb2hsv(hex2rgb(hex));
}

static color_t hex2hsl(color_t hex)
{
  return rgb2hsl(hex2rgb(hex));
}

static color_t hsv2rgb(color_t hsv)
{
  float h = hsv.values[0], s = hsv.values[1] / 100.f, v = hsv.values[2] / 100.f;
  float c = v * s, x = c * (1 - fabsf(fmodf(h / 60.f, 2) - 1)), m = v - c;
  float r = 0, g = 0, b = 0;
  if (0 <= h && h < 60) r = c, g = x, b = 0;
  else if (60  <= h && h < 120) r = x, g = c, b = 0;
  else if (120 <= h && h < 180) r = 0, g = c, b = x;
  else if (180 <= h && h < 240) r = 0, g = x, b = c;
  else if (240 <= h && h < 300) r = x, g = 0, b = c;
  else if (300 <= h && h < 360) r = c, g = 0, b = x;
  color_t rgb_color;
  rgb_color.model = RGB;
  rgb_color.values[0] = (r + m) * 255.f;
  rgb_color.values[1] = (g + m) * 255.f;
  rgb_color.values[2] = (b + m) * 255.f;
  return rgb_color;
}

static color_t hsv2hex(color_t hsv)
{
  return rgb2hex(hsv2rgb(hsv));
}

static color_t hsv2hsl(color_t hsv)
{
  float h = hsv.values[0];
  float s_hsv = hsv.values[1] / 100.f;
  float v_hsv = hsv.values[2] / 100.f;
  float l = v_hsv - v_hsv * s_hsv / 2;
  float s = l == 0 || l == 1 ? 0 : (v_hsv - l) / MIN2(l, 1 - l);
  color_t hsl_color;
  hsl_color.model = HSL;
  hsl_color.values[0] = h;
  hsl_color.values[1] = s * 100.f;
  hsl_color.values[2] = l * 100.f;
  return hsl_color;
}

static color_t hsl2rgb(color_t hsl)
{
  float h = hsl.values[0], s = hsl.values[1] / 100.f, l = hsl.values[2] / 100.f;
  float c = (1.f - fabsf(2.f * l - 1.f)) * s;
  float x = c * (1 - fabsf(fmodf(h / 60.f, 2.f) - 1.f));
  float m = l - c / 2.f;
  float r = 0, g = 0, b = 0;
  if (0 <= h && h < 60) r = c, g = x, b = 0;
  else if (60  <= h && h < 120) r = x, g = c, b = 0;
  else if (120 <= h && h < 180) r = 0, g = c, b = x;
  else if (180 <= h && h < 240) r = 0, g = x, b = c;
  else if (240 <= h && h < 300) r = x, g = 0, b = c;
  else if (300 <= h && h < 360) r = c, g = 0, b = x;
  color_t rgb_color;
  rgb_color.model = RGB;
  rgb_color.values[0] = (r + m) * 255.f;
  rgb_color.values[1] = (g + m) * 255.f;
  rgb_color.values[2] = (b + m) * 255.f;
  return rgb_color;
}

static color_t hsl2hex(color_t hsl)
{
  return rgb2hex(hsl2rgb(hsl));
}

static color_t hsl2hsv(color_t hsl)
{
  float h = hsl.values[0];
  float s = hsl.values[1] / 100.f;
  float l = hsl.values[2] / 100.f;
  float v = l + s * MIN2(l, 1 - l);
  s = v == 0.f ? 0.f : (2.f - 2.f * l / v);
  color_t hsv_color;
  hsv_color.model = HSV;
  hsv_color.values[0] = h;
  hsv_color.values[1] = s * 100.f;
  hsv_color.values[2] = v * 100.f;
  return hsv_color;
}

color_t negate(color_t color)
{
  switch (color.model) {
  case RGB: return negatergb(color);
  case HEX: return negatehex(color);
  case HSV: return negatehsv(color);
  case HSL: return negatehsl(color);
  default: EXIT_ON_FAILURE("invalid color model\n")
  }
}

static color_t negatergb(color_t rgb)
{
  color_t negated_rgb = copy(rgb);
  negated_rgb.values[0] = fmodf(255 - negated_rgb.values[0], 256);
  negated_rgb.values[1] = fmodf(255 - negated_rgb.values[1], 256);
  negated_rgb.values[2] = fmodf(255 - negated_rgb.values[2], 256);
  return negated_rgb;
}

static color_t negatehex(color_t hex)
{
  return rgb2hex(negatergb(hex2rgb(hex)));
}

static color_t negatehsv(color_t hsv)
{
  color_t negated_hsv = copy(hsv);
  negated_hsv.values[0] = fmodf(negated_hsv.values[0] + 180.f, 360.f);
  return negated_hsv;
}

static color_t negatehsl(color_t hsl)
{
  color_t negated_hsl = copy(hsl);
  negated_hsl.values[0] = fmodf(negated_hsl.values[0] + 180.f, 360.f);
  return negated_hsl;
}

color_t saturate(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  color.values[1] = value >= 0 ?
    color.values[1] + (100.0f - color.values[1]) * (value / 100.0f) :
    color.values[1] + color.values[1] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

color_t rotate(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  float new_hue = (new_hue = color.values[0] + value) < 0 ?
    (float)(((float)(int)(-new_hue) / 360 + 1) * 360 + new_hue) : new_hue;
  color.values[0] = fmodf(new_hue, 360);
  color = convert(color, color_model);
  return color;
}

color_t lighten(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSL);
  color.values[2] = value >= 0 ?
    color.values[2] + (100.0f - color.values[2]) * (value / 100.0f) :
    color.values[2] + color.values[2] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

color_t brighten(color_t color, float value)
{
  int color_model = color.model;
  color = convert(color, HSV);
  color.values[2] = value >= 0 ?
    color.values[2] + (100.0f - color.values[2]) * (value / 100.0f) :
    color.values[2] + color.values[2] * (value / 100.f);
  color = convert(color, color_model);
  return color;
}

void displaycolor(color_t color)
{
  printf("%s\n", getcolorstr(color));
}

char *getcolorstr(color_t color) {
  // alloc mem for ret string
  char *colorstr = (char *)malloc(sizeof(char) * 70);
  // fill foreground and background color
  color_t rgbrepr = color.model == RGB ? color : convert(color, RGB);
  int r = (int) round(rgbrepr.values[0]), g = (int) round(rgbrepr.values[1]), b = (int) round(rgbrepr.values[2]);
  int length = 0;
  length += sprintf(colorstr, "\033[38;2;%d;%d;%dm", 255 - r, 255 - g, 255 - b);
  length += sprintf(colorstr + length, "\033[48;2;%d;%d;%dm", r, g, b);
  // concatenate color model values
  switch (color.model) {
    case RGB:
      length += sprintf(colorstr + length, "rgb(%.0f, %.0f, %.0f)", color.values[0], color.values[1], color.values[2]);
      break;
    case HEX:
      length += sprintf(colorstr + length, "#%06X", (int)round(color.values[0]));
      break;
    case HSV:
      length += sprintf(colorstr + length, "hsv(%.2f, %.2f%%, %.2f%%)", color.values[0], color.values[1], color.values[2]);
      break;
    case HSL:
      length += sprintf(colorstr + length, "hsl(%.2f, %.2f%%, %.2f%%)", color.values[0], color.values[1], color.values[2]);
      break;
  }
  // reset color
  sprintf(colorstr + length, "\033[0m");
  return colorstr;
}

void usage(void)
{
  puts("Usage: color [model] [values] [options]");
  puts("   or: color [predefined-color] [options]");
  puts("   or: color random [options]\n");
  puts("Examples:");
  puts("    color rgb 244 180 220 -nt hex");
  puts("    color hex 0xA122FF -r -20 --saturate 23");
  puts("    color lightcyan --to hsv\n");
  puts("Models:");
  puts("    rgb             RGB values are between 0-255.");
  puts("    hex             HEX is a 6-bit integer. valid prefixes: 0x, 0X, #.");
  puts("    hsv             Hue is 0-359deg, S, V are between 0-100%.");
  puts("    hsl             Same specifications as HSV color model.\n");
  puts("Predefined Colors:");
  puts("    Are all CSS colors such as: antiquewhite, darkgray... . They are NOT");
  puts("    case sensitive so gold and gOLd both refer to the same color.\n");
  puts("Options:");
  puts("    -n, --negate    Output negative value.");
  puts("    -t, --to        Convert to the specific color model.");
  puts("    -r, --rotate    Rotate the hue value of color, parameter can be");
  puts("                        negative or positive float.");
  puts("    -s, --saturate  Saturate color, parameter is between -100 and 100.");
  puts("    -l, --lighten   Increase or decrease luminosity of color. Range is");
  puts("                        between -100 and 100.");
  puts("    -b, --brighten  Control brightness. Range is between -100 and 100");
}

int createpredefinedcolor(const char *arg, color_t *color)
{
  if (!strcasecmp(arg, "white")) { *color = RGB_WHITE; return 1; }
  else if (!strcasecmp(arg, "black")) { *color = RGB_BLACK; return 1; }
  else if (!strcasecmp(arg, "aliceblue")) { *color = RGB_ALICEBLUE; return 1; }
  else if (!strcasecmp(arg, "antiquewhite")) { *color = RGB_ANTIQUEWHITE; return 1; }
  else if (!strcasecmp(arg, "aqua")) { *color = RGB_AQUA; return 1; }
  else if (!strcasecmp(arg, "aquamarine")) { *color = RGB_AQUAMARINE; return 1; }
  else if (!strcasecmp(arg, "azure")) { *color = RGB_AZURE; return 1; }
  else if (!strcasecmp(arg, "beige")) { *color = RGB_BEIGE; return 1; }
  else if (!strcasecmp(arg, "bisque")) { *color = RGB_BISQUE; return 1; }
  else if (!strcasecmp(arg, "black")) { *color = RGB_BLACK; return 1; }
  else if (!strcasecmp(arg, "blanchedalmond")) { *color = RGB_BLANCHEDALMOND; return 1; }
  else if (!strcasecmp(arg, "blue")) { *color = RGB_BLUE; return 1; }
  else if (!strcasecmp(arg, "blueviolet")) { *color = RGB_BLUEVIOLET; return 1; }
  else if (!strcasecmp(arg, "brown")) { *color = RGB_BROWN; return 1; }
  else if (!strcasecmp(arg, "burlywood")) { *color = RGB_BURLYWOOD; return 1; }
  else if (!strcasecmp(arg, "cadetblue")) { *color = RGB_CADETBLUE; return 1; }
  else if (!strcasecmp(arg, "chartreuse")) { *color = RGB_CHARTREUSE; return 1; }
  else if (!strcasecmp(arg, "chocolate")) { *color = RGB_CHOCOLATE; return 1; }
  else if (!strcasecmp(arg, "coral")) { *color = RGB_CORAL; return 1; }
  else if (!strcasecmp(arg, "cornflowerblue")) { *color = RGB_CORNFLOWERBLUE; return 1; }
  else if (!strcasecmp(arg, "cornsilk")) { *color = RGB_CORNSILK; return 1; }
  else if (!strcasecmp(arg, "crimson")) { *color = RGB_CRIMSON; return 1; }
  else if (!strcasecmp(arg, "cyan")) { *color = RGB_CYAN; return 1; }
  else if (!strcasecmp(arg, "darkblue")) { *color = RGB_DARKBLUE; return 1; }
  else if (!strcasecmp(arg, "darkcyan")) { *color = RGB_DARKCYAN; return 1; }
  else if (!strcasecmp(arg, "darkgoldenrod")) { *color = RGB_DARKGOLDENROD; return 1; }
  else if (!strcasecmp(arg, "darkgray")) { *color = RGB_DARKGRAY; return 1; }
  else if (!strcasecmp(arg, "darkgreen")) { *color = RGB_DARKGREEN; return 1; }
  else if (!strcasecmp(arg, "darkgrey")) { *color = RGB_DARKGREY; return 1; }
  else if (!strcasecmp(arg, "darkkhaki")) { *color = RGB_DARKKHAKI; return 1; }
  else if (!strcasecmp(arg, "darkmagenta")) { *color = RGB_DARKMAGENTA; return 1; }
  else if (!strcasecmp(arg, "darkolivegreen")) { *color = RGB_DARKOLIVEGREEN; return 1; }
  else if (!strcasecmp(arg, "darkorange")) { *color = RGB_DARKORANGE; return 1; }
  else if (!strcasecmp(arg, "darkorchid")) { *color = RGB_DARKORCHID; return 1; }
  else if (!strcasecmp(arg, "darkred")) { *color = RGB_DARKRED; return 1; }
  else if (!strcasecmp(arg, "darksalmon")) { *color = RGB_DARKSALMON; return 1; }
  else if (!strcasecmp(arg, "darkseagreen")) { *color = RGB_DARKSEAGREEN; return 1; }
  else if (!strcasecmp(arg, "darkslateblue")) { *color = RGB_DARKSLATEBLUE; return 1; }
  else if (!strcasecmp(arg, "darkslategray")) { *color = RGB_DARKSLATEGRAY; return 1; }
  else if (!strcasecmp(arg, "darkslategrey")) { *color = RGB_DARKSLATEGREY; return 1; }
  else if (!strcasecmp(arg, "darkturquoise")) { *color = RGB_DARKTURQUOISE; return 1; }
  else if (!strcasecmp(arg, "darkviolet")) { *color = RGB_DARKVIOLET; return 1; }
  else if (!strcasecmp(arg, "deeppink")) { *color = RGB_DEEPPINK; return 1; }
  else if (!strcasecmp(arg, "deepskyblue")) { *color = RGB_DEEPSKYBLUE; return 1; }
  else if (!strcasecmp(arg, "dimgray")) { *color = RGB_DIMGRAY; return 1; }
  else if (!strcasecmp(arg, "dimgrey")) { *color = RGB_DIMGREY; return 1; }
  else if (!strcasecmp(arg, "dodgerblue")) { *color = RGB_DODGERBLUE; return 1; }
  else if (!strcasecmp(arg, "firebrick")) { *color = RGB_FIREBRICK; return 1; }
  else if (!strcasecmp(arg, "floralwhite")) { *color = RGB_FLORALWHITE; return 1; }
  else if (!strcasecmp(arg, "forestgreen")) { *color = RGB_FORESTGREEN; return 1; }
  else if (!strcasecmp(arg, "fuchsia")) { *color = RGB_FUCHSIA; return 1; }
  else if (!strcasecmp(arg, "gainsboro")) { *color = RGB_GAINSBORO; return 1; }
  else if (!strcasecmp(arg, "ghostwhite")) { *color = RGB_GHOSTWHITE; return 1; }
  else if (!strcasecmp(arg, "gold")) { *color = RGB_GOLD; return 1; }
  else if (!strcasecmp(arg, "goldenrod")) { *color = RGB_GOLDENROD; return 1; }
  else if (!strcasecmp(arg, "gray")) { *color = RGB_GRAY; return 1; }
  else if (!strcasecmp(arg, "green")) { *color = RGB_GREEN; return 1; }
  else if (!strcasecmp(arg, "greenyellow")) { *color = RGB_GREENYELLOW; return 1; }
  else if (!strcasecmp(arg, "grey")) { *color = RGB_GREY; return 1; }
  else if (!strcasecmp(arg, "honeydew")) { *color = RGB_HONEYDEW; return 1; }
  else if (!strcasecmp(arg, "hotpink")) { *color = RGB_HOTPINK; return 1; }
  else if (!strcasecmp(arg, "indianred")) { *color = RGB_INDIANRED; return 1; }
  else if (!strcasecmp(arg, "indigo")) { *color = RGB_INDIGO; return 1; }
  else if (!strcasecmp(arg, "ivory")) { *color = RGB_IVORY; return 1; }
  else if (!strcasecmp(arg, "khaki")) { *color = RGB_KHAKI; return 1; }
  else if (!strcasecmp(arg, "lavender")) { *color = RGB_LAVENDER; return 1; }
  else if (!strcasecmp(arg, "lavenderblush")) { *color = RGB_LAVENDERBLUSH; return 1; }
  else if (!strcasecmp(arg, "lawngreen")) { *color = RGB_LAWNGREEN; return 1; }
  else if (!strcasecmp(arg, "lemonchiffon")) { *color = RGB_LEMONCHIFFON; return 1; }
  else if (!strcasecmp(arg, "lightblue")) { *color = RGB_LIGHTBLUE; return 1; }
  else if (!strcasecmp(arg, "lightcoral")) { *color = RGB_LIGHTCORAL; return 1; }
  else if (!strcasecmp(arg, "lightcyan")) { *color = RGB_LIGHTCYAN; return 1; }
  else if (!strcasecmp(arg, "lightgoldenrodyellow")) { *color = RGB_LIGHTGOLDENRODYELLOW; return 1; }
  else if (!strcasecmp(arg, "lightgray")) { *color = RGB_LIGHTGRAY; return 1; }
  else if (!strcasecmp(arg, "lightgreen")) { *color = RGB_LIGHTGREEN; return 1; }
  else if (!strcasecmp(arg, "lightgrey")) { *color = RGB_LIGHTGREY; return 1; }
  else if (!strcasecmp(arg, "lightpink")) { *color = RGB_LIGHTPINK; return 1; }
  else if (!strcasecmp(arg, "lightsalmon")) { *color = RGB_LIGHTSALMON; return 1; }
  else if (!strcasecmp(arg, "lightseagreen")) { *color = RGB_LIGHTSEAGREEN; return 1; }
  else if (!strcasecmp(arg, "lightskyblue")) { *color = RGB_LIGHTSKYBLUE; return 1; }
  else if (!strcasecmp(arg, "lightslategray")) { *color = RGB_LIGHTSLATEGRAY; return 1; }
  else if (!strcasecmp(arg, "lightslategrey")) { *color = RGB_LIGHTSLATEGREY; return 1; }
  else if (!strcasecmp(arg, "lightsteelblue")) { *color = RGB_LIGHTSTEELBLUE; return 1; }
  else if (!strcasecmp(arg, "lightyellow")) { *color = RGB_LIGHTYELLOW; return 1; }
  else if (!strcasecmp(arg, "lime")) { *color = RGB_LIME; return 1; }
  else if (!strcasecmp(arg, "limegreen")) { *color = RGB_LIMEGREEN; return 1; }
  else if (!strcasecmp(arg, "linen")) { *color = RGB_LINEN; return 1; }
  else if (!strcasecmp(arg, "magenta")) { *color = RGB_MAGENTA; return 1; }
  else if (!strcasecmp(arg, "maroon")) { *color = RGB_MAROON; return 1; }
  else if (!strcasecmp(arg, "mediumaquamarine")) { *color = RGB_MEDIUMAQUAMARINE; return 1; }
  else if (!strcasecmp(arg, "mediumblue")) { *color = RGB_MEDIUMBLUE; return 1; }
  else if (!strcasecmp(arg, "mediumorchid")) { *color = RGB_MEDIUMORCHID; return 1; }
  else if (!strcasecmp(arg, "mediumpurple")) { *color = RGB_MEDIUMPURPLE; return 1; }
  else if (!strcasecmp(arg, "mediumseagreen")) { *color = RGB_MEDIUMSEAGREEN; return 1; }
  else if (!strcasecmp(arg, "mediumslateblue")) { *color = RGB_MEDIUMSLATEBLUE; return 1; }
  else if (!strcasecmp(arg, "mediumspringgreen")) { *color = RGB_MEDIUMSPRINGGREEN; return 1; }
  else if (!strcasecmp(arg, "mediumturquoise")) { *color = RGB_MEDIUMTURQUOISE; return 1; }
  else if (!strcasecmp(arg, "mediumvioletred")) { *color = RGB_MEDIUMVIOLETRED; return 1; }
  else if (!strcasecmp(arg, "midnightblue")) { *color = RGB_MIDNIGHTBLUE; return 1; }
  else if (!strcasecmp(arg, "mintcream")) { *color = RGB_MINTCREAM; return 1; }
  else if (!strcasecmp(arg, "mistyrose")) { *color = RGB_MISTYROSE; return 1; }
  else if (!strcasecmp(arg, "moccasin")) { *color = RGB_MOCCASIN; return 1; }
  else if (!strcasecmp(arg, "navajowhite")) { *color = RGB_NAVAJOWHITE; return 1; }
  else if (!strcasecmp(arg, "navy")) { *color = RGB_NAVY; return 1; }
  else if (!strcasecmp(arg, "oldlace")) { *color = RGB_OLDLACE; return 1; }
  else if (!strcasecmp(arg, "olive")) { *color = RGB_OLIVE; return 1; }
  else if (!strcasecmp(arg, "olivedrab")) { *color = RGB_OLIVEDRAB; return 1; }
  else if (!strcasecmp(arg, "orange")) { *color = RGB_ORANGE; return 1; }
  else if (!strcasecmp(arg, "orangered")) { *color = RGB_ORANGERED; return 1; }
  else if (!strcasecmp(arg, "orchid")) { *color = RGB_ORCHID; return 1; }
  else if (!strcasecmp(arg, "palegoldenrod")) { *color = RGB_PALEGOLDENROD; return 1; }
  else if (!strcasecmp(arg, "palegreen")) { *color = RGB_PALEGREEN; return 1; }
  else if (!strcasecmp(arg, "paleturquoise")) { *color = RGB_PALETURQUOISE; return 1; }
  else if (!strcasecmp(arg, "palevioletred")) { *color = RGB_PALEVIOLETRED; return 1; }
  else if (!strcasecmp(arg, "papayawhip")) { *color = RGB_PAPAYAWHIP; return 1; }
  else if (!strcasecmp(arg, "peachpuff")) { *color = RGB_PEACHPUFF; return 1; }
  else if (!strcasecmp(arg, "peru")) { *color = RGB_PERU; return 1; }
  else if (!strcasecmp(arg, "pink")) { *color = RGB_PINK; return 1; }
  else if (!strcasecmp(arg, "plum")) { *color = RGB_PLUM; return 1; }
  else if (!strcasecmp(arg, "powderblue")) { *color = RGB_POWDERBLUE; return 1; }
  else if (!strcasecmp(arg, "purple")) { *color = RGB_PURPLE; return 1; }
  else if (!strcasecmp(arg, "red")) { *color = RGB_RED; return 1; }
  else if (!strcasecmp(arg, "rosybrown")) { *color = RGB_ROSYBROWN; return 1; }
  else if (!strcasecmp(arg, "royalblue")) { *color = RGB_ROYALBLUE; return 1; }
  else if (!strcasecmp(arg, "saddlebrown")) { *color = RGB_SADDLEBROWN; return 1; }
  else if (!strcasecmp(arg, "salmon")) { *color = RGB_SALMON; return 1; }
  else if (!strcasecmp(arg, "sandybrown")) { *color = RGB_SANDYBROWN; return 1; }
  else if (!strcasecmp(arg, "seagreen")) { *color = RGB_SEAGREEN; return 1; }
  else if (!strcasecmp(arg, "seashell")) { *color = RGB_SEASHELL; return 1; }
  else if (!strcasecmp(arg, "sienna")) { *color = RGB_SIENNA; return 1; }
  else if (!strcasecmp(arg, "silver")) { *color = RGB_SILVER; return 1; }
  else if (!strcasecmp(arg, "skyblue")) { *color = RGB_SKYBLUE; return 1; }
  else if (!strcasecmp(arg, "slateblue")) { *color = RGB_SLATEBLUE; return 1; }
  else if (!strcasecmp(arg, "slategray")) { *color = RGB_SLATEGRAY; return 1; }
  else if (!strcasecmp(arg, "slategrey")) { *color = RGB_SLATEGREY; return 1; }
  else if (!strcasecmp(arg, "snow")) { *color = RGB_SNOW; return 1; }
  else if (!strcasecmp(arg, "springgreen")) { *color = RGB_SPRINGGREEN; return 1; }
  else if (!strcasecmp(arg, "steelblue")) { *color = RGB_STEELBLUE; return 1; }
  else if (!strcasecmp(arg, "tan")) { *color = RGB_TAN; return 1; }
  else if (!strcasecmp(arg, "teal")) { *color = RGB_TEAL; return 1; }
  else if (!strcasecmp(arg, "thistle")) { *color = RGB_THISTLE; return 1; }
  else if (!strcasecmp(arg, "tomato")) { *color = RGB_TOMATO; return 1; }
  else if (!strcasecmp(arg, "turquoise")) { *color = RGB_TURQUOISE; return 1; }
  else if (!strcasecmp(arg, "violet")) { *color = RGB_VIOLET; return 1; }
  else if (!strcasecmp(arg, "wheat")) { *color = RGB_WHEAT; return 1; }
  else if (!strcasecmp(arg, "white")) { *color = RGB_WHITE; return 1; }
  else if (!strcasecmp(arg, "whitesmoke")) { *color = RGB_WHITESMOKE; return 1; }
  else if (!strcasecmp(arg, "yellow")) { *color = RGB_YELLOW; return 1; }
  else if (!strcasecmp(arg, "yellowgreen")) { *color = RGB_YELLOWGREEN; return 1; }
  else if (!strcasecmp(arg, "purple")) { *color = RGB_PURPLE; return 1; }
  else if (!strcasecmp(arg, "fuchsia")) { *color = RGB_FUCHSIA; return 1; }
  else if (!strcasecmp(arg, "green")) { *color = RGB_GREEN; return 1; }
  else if (!strcasecmp(arg, "lime")) { *color = RGB_LIME; return 1; }
  else if (!strcasecmp(arg, "olive")) { *color = RGB_OLIVE; return 1; }
  else if (!strcasecmp(arg, "yellow")) { *color = RGB_YELLOW; return 1; }
  else if (!strcasecmp(arg, "navy")) { *color = RGB_NAVY; return 1; }
  else if (!strcasecmp(arg, "blue")) { *color = RGB_BLUE; return 1; }
  else if (!strcasecmp(arg, "teal")) { *color = RGB_TEAL; return 1; }
  else if (!strcasecmp(arg, "aqua")) { *color = RGB_AQUA; return 1; }
  return 0;
}

/* EOF */
