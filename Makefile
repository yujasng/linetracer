MCU     = atmega328p
F_CPU   = 16000000UL
BAUD    = 115200

CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

TARGET  = main
SRC_DIR = src
BUILD_DIR = build

SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) \
          -Os -std=gnu99 -Wall -Wextra \
          -ffunction-sections -fdata-sections

LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

PROGRAMMER = arduino
PORT       = /dev/ttyUSB0

.PHONY: all clean flash size

all: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) \
	           -U flash:w:$<:i

size: $(BUILD_DIR)/$(TARGET).elf
	avr-size --format=avr --mcu=$(MCU) $<

clean:
	rm -rf $(BUILD_DIR)
