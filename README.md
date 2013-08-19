# ofxFTGL -- fast typography library with Unicode support

Originally by Rick Companje. 

example and binary builds by obviousjim

#### Notes by Oriol

define "FTGL_LIBRARY_STATIC" in your visual studio project or you will get link errors (dllimport)...

I recompiled the FTGL static lib on osx (libftgl_max2048.a) with a moded version of FTGL that doesn't allocate the first texture of a size of MAX_TEXTURE_SIZE x MAX_TEXTURE_SIZE bc in my case that was 16384 x 16384 which is quite ridiculous. It limits the max texture size to 2048 x 2048 instead.

Find the modded FTGL in https://github.com/armadillu/ftgl_2048


Oriol mod to add support for paragraph
https://github.com/armadillu/ofxFTGL

Borg mods 2013/08/19:

-FTGL had origin in bottom left corner. Now flipped to top left. 

-Bounding box origin top left.

-Paragraph support for alignment.

-getTextHeight support for paragraph
