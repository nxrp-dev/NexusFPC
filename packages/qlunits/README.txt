This package contains interface units for QDOS, the operating system
of Sinclair QL machines, clones and compatibles.

The following units are available:

    qdos - allows the use of QDOS API directly.
    sms - allows the use of SMS API directly.
    qsuperbasic - SuperBASIC resembling functions and procedures using  the low level units.
    qsound - A unit allowing the use of the QSound card, and it's AY-3-8910 PSG chip.
    qlutil - utility functions for better QL API to Pascal interoperability.
    qlfloat - utility functions to convert between Pascal numeric types and QLfloats.
    qscreen - utility functions, mainly TRAP #3, which act upon the screen in some way.
    qjobs   - utility functions to do with job handling.
    qclock  - Clock & date handling functions.

The following examples are available:

    qlcube - draws a 3D rotating wireframe cube with QDOS drawing functions.
    mtinf - example of using the QDOS version of the System Variables.
    sms_info - example of using the SMSQ version of the System Variables.
    modes - Shows how to set the screen to mode 4 and mode 8.
    papers - Shows all available paper colours in mode 4 and mode 8.
    strips - Shows all available strip colours in mode 4 and mode 8.
    inks - Shows all available ink colours in mode 4 and mode 8.
    csizes -Shows all available character width and heights.
