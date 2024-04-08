#include "color.h"

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>


static struct option arg_options[] = {{ "negate", no_argument, 0, 'n' },
                                      { "to", required_argument, 0, 't' },
                                      { "saturate", required_argument, 0, 's' },
                                      { "rotate", required_argument, 0, 'r' },
                                      { "lighten", required_argument, 0, 'l' },
                                      { "brighten", required_argument, 0, 'b' },
                                      { 0, 0, 0, 0 }};

int main(int argc, char **argv)
{
  char **argv_ptr = argv;
  assert(*argv++ != NULL);
  clop_t CLOPS[MAXCLOPS];
  int COLOR_MODEL, clp = 0;
  color_t color;
  char *var1, *var2, *var3;
  int is_complement = 0;
  srand(time(0));

  /* no argument error */
  if (*argv == NULL) {
    usage();
    exit(EXIT_FAILURE);
  }
  if (strcmp(*argv, "--help") == 0) {
    usage();
    exit(EXIT_FAILURE);
  }

  /* check if user wants complement */
  if (strcmp(*argv, "complement") == 0) {
    is_complement = 1;
    argv++;
  }

  /* parse color model */
  COLOR_MODEL = strcmp(*argv, "rgb") == 0 ? RGB
    : strcmp(*argv, "hex") == 0 ? HEX
      : strcmp(*argv, "hsv") == 0 ? HSV
        : strcmp(*argv, "hsl") == 0 ? HSL : 0;

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
      exit(EXIT_FAILURE);
    }
    /* create color */
    switch (COLOR_MODEL) {
    case RGB:color = creatergb(var1, var2, var3);
      break;
    case HSV:color = createhsv(var1, var2, var3);
      break;
    case HSL:color = createhsl(var1, var2, var3);
      break;
    }
  } else if (createpredefinedcolor(*argv, &color)) {
    /* ignored line */
  } else if (!strcmp(*argv, "random")) {
    color = createrandom();
  } else {
    fprintf(stderr, "color: invalid command %s.\n", *argv);
    fprintf(stderr, "Try 'color --help' for more options.\n");
    exit(EXIT_FAILURE);
  }

  /* parse options */
  int op;
  while ((op = getopt_long(argc, argv_ptr, "ns:r:l:b:t:", arg_options, NULL)) != -1) {
    switch (op) {
    case 'n': CLOPS[clp++] = createclop(NEGATE, 0, "");
      break;
    case 's': CLOPS[clp++] = createclop(SATURATE, 1, optarg);
      break;
    case 'r': CLOPS[clp++] = createclop(ROTATE, 1, optarg);
      break;
    case 'l': CLOPS[clp++] = createclop(LIGHTEN, 1, optarg);
      break;
    case 'b': CLOPS[clp++] = createclop(BRIGHTEN, 1, optarg);
      break;
    case 't': CLOPS[clp++] = createclop(CONVERSION, 1, optarg);
      break;
    case '?': exit(EXIT_FAILURE);
    default:break;
    }
  }

  /* apply clops */
  int i;
  for (i = 0; i < clp; i++) {
    switch (CLOPS[i].op) {
    case NEGATE: color = negate(color);
      break;
    case CONVERSION: color = convert(color, (int)CLOPS[i].param);
      break;
    case SATURATE: color = saturate(color, CLOPS[i].param);
      break;
    case ROTATE: color = rotate(color, CLOPS[i].param);
      break;
    case LIGHTEN: color = lighten(color, CLOPS[i].param);
      break;
    case BRIGHTEN: color = brighten(color, CLOPS[i].param);
      break;
    }
  }

  /* display the result*/
  if (is_complement) {
    displaycomplementarycolor(color);
  } else {
    displaycolor(color);
  }

  return 0;
}