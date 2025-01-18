## 2.2.0

- Update to VSCP framework v2.2.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v2.2.0) there.

## 2.1.0

- Update to VSCP framework v2.1.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v2.1.0) there.

## 2.0.4

- Fixed problem with backslashes in include paths.
- Fixed problem with wrong include path in `vscp_evt_information.c` module. Thanks to michpro!
- Examples updated to be working with latest CAN libraries.

## 2.0.3

- Update to VSCP framework v2.0.3, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v2.0.3) there.
- Deprecated `dataNum` replaced with `dataSize`. Thanks to michpro!

## 2.0.2

- Update to VSCP framework v2.0.2, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v2.0.2) there.

## 2.0.0

- Update to VSCP framework v2.0.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v2.0.0) there.

## 1.3.0

- Update to VSCP framework v1.3.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v1.3.0) there.

## 1.2.0

- Update to VSCP framework v1.2.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v1.2.0) there.

## 1.1.0

- Update to VSCP framework v1.1.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v1.1.0) there.

## 1.0.0

- Update to VSCP framework v1.0.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v1.0.0) there.

## 0.8.0

- Update to VSCP framework v0.9.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.9.0) there.
- The update includes the following bugfixes:
  - Bugfix: Fix of misspellings/typos, thanks to TomasRoj.
  - Bugfix: VSCP measurement events fixed, because internally the parameters `unit` and `index` in the `vscp_data_coding_getFormatByte()` call were reversed. Thanks to troky!

## 0.7.1

- Bugfix: Abstract event modules added.
- Bugfix: MDF template syntax errors fixed, as well as the namespace and schema location.

## 0.7.0

- Update to VSCP framework v0.8.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.8.0) there.
- Folder structure changed inside framework folder, in preparation for the abstract event modules.
- Abstract event modules introduced, see `framework/events`.

## 0.6.1

- Folder structure changed, please see [Arduino Library Guide](https://www.arduino.cc/en/Guide/Libraries#toc4) for easier installation.

## 0.6.0

- Update to VSCP framework v0.7.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.7.0) there.

## 0.5.0

- The VSCP framework returned the wrong number of used pages.
- Update to VSCP framework v0.6.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.6.0) there.

## 0.4.0

- Update to VSCP framework v0.5.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.5.0) there.
- Seeed-Studio-CAN_BUS_Shield example got a retry mechanism in the send routine.
- Sparkfun_CAN-BUS_Shield example got a retry mechanism in the send routine.

## 0.3.0

- `DigInDebounce` class for digital input debouncing implemented.
- Update to VSCP framework v0.4.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.4.0) there.
- Status lamp and init button connection fixed.

## 0.2.0

- Updated to VSCP framework v0.3.0, please see the [changelog](https://github.com/BlueAndi/vscp-framework/releases/tag/v0.3.0) there.

## 0.1.0

- Base is the VSCP framework v0.2.2
