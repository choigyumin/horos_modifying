[![Build status](https://ci.appveyor.com/api/projects/status/yq0naf3v2m8nfa8r/branch/master?svg=true)](https://ci.appveyor.com/project/vbaderks/charls/branch/master)
[![Build Status](https://travis-ci.org/team-charls/charls.svg?branch=master)](https://travis-ci.org/team-charls/charls)

CharLS
======
CharLS is a C++ implementation of the JPEG-LS standard for lossless and near-lossless image compression and decompression.
JPEG-LS is a low-complexity image compression standard that matches JPEG 2000 compression ratios.

Features
--------
* C++14 library implementation with a binary C interface for maximum interoperability. Note: C++03 compatible implementation is maintained in the 1.x-master branch.
* Supports Windows, Linux and Solaris in 32 bit and 64 bit.
* Includes an adapter assembly for .NET based languages.
* Excellent compression and decompression performance.

About JPEG-LS
-------------
JPEG-LS (ISO-14495-1/ITU-T.87) is an image compression standard derived from the Hewlett Packard LOCO algorithm. JPEG-LS has low complexity (meaning fast compression) and high compression ratios, similar to the JPEG 2000 lossless ratios. JPEG-LS is more similar to the old Lossless JPEG than to JPEG 2000, but interestingly the two different techniques result in vastly different performance characteristics. 
Wikipedia on lossless JPEG and JPEG-LS: <http://en.wikipedia.org/wiki/Lossless_JPEG>

About this software
-------------------
This project's goal is to provide a full implementation of JPEG-LS. This library is written from scratch in portable C++. The master branch uses modern C++ v11. The 1.x branch is maintained in C++ v03. All mainstream JPEG-LS features are implemented by this library.
According to preliminary test results published on http://imagecompression.info/gralic, CharLS is about *twice as fast* as the original HP code, and beats both JPEG-XR and JPEG 2000 by a factor 3. 

Supported platforms
-------------------
The code is regularly compiled/tested on Windows and 64 bit Linux. Additionally, the code has been successfully tested on Linux Intel/AMD 32/64 bit (slackware, debian, gentoo), Solaris SPARC systems, Intel based Macs and Windows CE (ARM CPU, emulated), where the less common compilers may require minor code edits. It leverages C++ language features (templates, traits) to create optimized code, which generally perform best with recent compilers. If you compile with GCC, 64 bit code performs substantially better.

Users & Acknowledgements
------------------------
CharLS is being used by [gdcm dicom toolkit](http://sourceforge.net/projects/gdcm/), thanks for [Matthieu](http://sourceforge.net/users/malat) for getting CharLS started on Linux. [Kato Kanryu](http://knivez.homelinux.org/) wrote an initial version of the color transfroms and the DIB output format code, for an [irfanview](http://www.irfanview.com) plugin using CharLS. Thanks to Uli Schlachter, CharLS now finally runs correctly on big-endian architectures like Sun SPARC. 

Legal
-----
The code in this project is available through a BSD style license, allowing use of the code in commercial closed source applications if you wish. **All** the code in this project is written from scratch, and not based on other JPEG-LS implementations. Be aware that Hewlett Packard claims to own patents that apply to JPEG-LS implementations, but they license it for free for conformant JPEG-LS implementations. Read more at <http://www.hpl.hp.com/loco/> before you use this if you use this code for commercial purposes.