.. _nemagfx:

NEMA®| GFX SDK
##############

.. contents::
   :local:
   :depth: 2

NEMA®| GFX (NemaGFX) SDK is a set of libraries providing graphic-related APIs to be used with nRF7140 SoCs from Nordic Semiconductor.

The NemaGFX SDK is integrated into the |NCS| as a module.
The following libraries are included:

* NemaGFX - Graphics library for the GPU
* NemaGFX_SW - Software implementation of the graphics library
* NemaVG - Vector graphics extension for NemaGFX
* NemaGUI - Graphic User Interface library
* NemaDC - Display controller library
* NemaDC_SW - Display controller software emulator, based on SDL

Supported platforms
*******************

The following platforms are supported:

* native_posix (native_posix_64 board only) - For graphics evaluation and demo.
* nRF7140 - SoC with graphics support.

NemaGFX, NemaGUI and NemaDC libraries are platform dependent.
NemaVG is supported only on the nRF7140 platform.
If you select the native_posix platform, the NemaGFX_SW and NemaDC_SW libraries will be used in the application.
These libraries do not require any hardware while providing the same behavior and functionality as hardware-dependent libraries do.
native_posix platform requires the `SDL2 library`_ to be installed in the system.

Configuration
*************

To use the NemaGFX SDK, you need to enable the :kconfig:option:`CONFIG_NEMA` Kconfig option in your project configuration.

NemaGFX and NemaDC are enabled by default, however, you can disable NemaDC by setting the :kconfig:option:`CONFIG_NEMADC_ENABLE`` Kconfig option to ``n``.

To enable or disable NemaVG and NemaGUI libraries, use the :kconfig:option:`CONFIG_NEMAVG_ENABLE` and :kconfig:option:`CONFIG_NEMAGUI_ENABLE` options, respectively.

API documentation
*****************

To see the NemaGFX API documentation, version ``R22.10``, refer to the following:

* `NemaDC API Manual`_
* `Nema GFX API Manual`_
* `NemaVG`_
* `NemaVG TSVG Elements`_
* `Nema GUI Builder Manual`_

.. _SDL2 library: https://github.com/libsdl-org/SDL
.. _NemaDC API Manual: https://res.developer.nordicsemi.com/res/nema/NemaDC_API_Manual.pdf
.. _Nema GFX API Manual: https://res.developer.nordicsemi.com/res/nema/NemaGFX_API_Manual.pdf
.. _NemaVG: https://res.developer.nordicsemi.com/res/nema/NemaVG.pdf
.. _NemaVG TSVG Elements: https://res.developer.nordicsemi.com/res/nema/NemaVG_TSVG_Elements.pdf
.. _Nema GUI Builder Manual: https://res.developer.nordicsemi.com/res/nema/Nema_GUI_Builder_Manual.pdf
