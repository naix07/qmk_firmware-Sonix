BACKLIGHT_ENABLE  = no       # Enable keyboard backlight functionality
AUDIO_ENABLE      = no       # Audio output

WAIT_FOR_USB      = no
CUSTOM_MATRIX     = yes
ENCODER_ENABLE    = yes

BLUETOOTH_ENABLE  = yes
BLUETOOTH_DRIVER  = ITON_BT

# Custom RGB matrix handling
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = SN32F24xB

# project specific files
SRC = ../../../drivers/led/sn32/matrix_sn32f24xx.c
