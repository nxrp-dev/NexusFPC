{$PACKENUM 1}     // The following need to be byte sized, not 32 bits!
type
  { Type for CLS(chan, aPart)}
  Tcls_part = (CLS_ALL, CLS_TOP, CLS_BOTTOM, CLS_LINE, CLS_RIGHT);

  { Type for PAN(chan, aPart)}
  Tpan_part = (PAN_ALL, PAN_LINE = 3, PAN_RIGHT = 4);

  { Type for SCROLL(chan, aPart)}
  Tscroll_part = (SCROLL_ALL, SCROLL_TOP, SCROLL_BOTTOM);

  { Types for MODE(aMode)}
  Tql_screen_mode = (MODE_4, MODE_8 = 8);
  Tql_device_mode = (MODE_MONITOR, MODE_TV_PAL, MODE_TV_NSTC);

  {Type various QL colours.}
  Tql_colour = (QL_BLACK, QL_BLUE, QL_RED, QL_MAGENTA, QL_GREEN, QL_CYAN, QL_YELLOW, QL_WHITE);

  {Type for Flash()}
  Tflash_mode = (FLASH_OFF, FLASH_ON);

  {Type for Under()}
  Tunder_mode = (UNDER_OFF, UNDER_ON);



{$PACKENUM 2}     // The following need to be word sized.

  { Type for OVER(aOver)}
  Tover_mode = (OVER_STD, OVER_TRANS, OVER_EOR = -1);

  {Types for CSize(aWidth, aHeight)}
  Tchar_width = (WIDTH_6, WIDTH_8, WIDTH_12, WIDTH_16);
  Tchar_height = (HEIGHT_10, HEIGHT_20);

{$PACKENUM DEFAULT}