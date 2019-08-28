EXE = main
SRC = main.c ./CAN/can.c ./Timer/Timer.c ./UART/UART.c ./CNS_MGS_160S/CNS_MGS_160S.c ./SPC_SDIO_1616/SPC_SDIO_1616.c ./CNS_RFID_1S/CNS_RFID_1S.c

HEADER_PATH = -I"/home/siasunhebo/ggm" -I./CAN/ -I./Timer -I./UART -I./CNS_MGS_160S -I./SPC_SDIO_1616 -I./CNS_RFID_1S

$(EXE):
	$(CC) $(HEADER_PATH) $(SRC) -o $(EXE) -g -lpthread -lrt -lm


clean:
	rm -rf main *.o
