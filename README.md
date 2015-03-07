#VSCP arduino library

1. [VSCP](https://github.com/BlueAndi/vscp-framework/blob/master/README.md#vscp)
2. [Library](https://github.com/BlueAndi/vscp-framework/blob/master/README.md#library)
3. [Examples](https://github.com/BlueAndi/vscp-framework/blob/master/README.md#examples)
4. [Mailing list](https://github.com/BlueAndi/vscp-framework/blob/master/README.md#mailing-list)
5. [Issues, Ideas and bugs](https://github.com/BlueAndi/vscp-framework/blob/master/README.md#issues-ideas-and-bugs)

##VSCP

![VSCP logo](http://vscp.org/images/vscp_logo.jpg)

The Very Simple Control Protocol (VSCP), an open and free protocol for IoT/m2m automation tasks.

More information can be found on the main site http://www.vscp.org

##Library
This is a arduino library of the VSCP software framework for level 1 devices.
It provides several layers according to the [VSCP specification](http://www.vscp.org/docs/vscpspec/doku.php).

##Examples

###Generic

The generic example shows the basic integration of the VSCP arduino library.

###Seeed-Studio CAN BUS Shield

This example assume that the CAN BUS Shield from Seeed-Studio is used, as well as the corresponding CAN controller library.

- Shield: http://www.seeedstudio.com/wiki/CAN-BUS_Shield
- Library: https://github.com/Seeed-Studio/CAN_BUS_Shield

###Sparkfun CAN-BUS Shield

This example assume that the CAN-BUS Shield from Sparkfun is used.
Because they provide no arduino library, the MCP2515 library from Frank Kienast is used.

- Shield: https://www.sparkfun.com/products/10039
- Library: https://github.com/franksmicro/Arduino/tree/master/libraries/MCP2515

##Mailing list

Are you interesting? Join us on the mailing list: https://groups.google.com/forum/#!forum/vscp

##Issues, Ideas and bugs

If you have further ideas or you found some bugs, great! Create a [issue](https://github.com/BlueAndi/vscp-framework/issues) or if
you are able and willing to fix it by yourself, clone the repository and create a pull request.

##License
The whole source code is published under the [MIT license](http://choosealicense.com/licenses/mit/).
