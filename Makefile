# Detect Operating System
ifeq ($(OS),Windows)
    # Windows
    RM = del /Q
else
    RM = rm -f
endif

checksum:
	@g++ CheckSum.cpp -o checksum.o
	@echo "====================="
	@echo "> Project Compiled"
	@echo "====================="
	@./checksum.o

clean:
	@$(RM) checksum.o
	@echo "====================="
	@echo "> Project Erased"
	@echo "====================="
	@echo "> Remaining files:"
	@ls
	@echo "====================="