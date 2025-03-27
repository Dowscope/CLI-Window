COMPILER := gcc
STANDARD := c++20
OUTPUT := prog.run
LIBRARIES := -lncurses -lstdc++
FILES := src/*.cpp

main:
	$(COMPILER) -std=$(STANDARD) $(FILES) -o $(OUTPUT) $(LIBRARIES)

clear:
	rm -f $(OUTPUT)