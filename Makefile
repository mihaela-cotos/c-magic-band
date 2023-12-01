build: main.c ./utils/stack.c ./utils/queue.c ./utils/utils.c
	gcc main.c ./utils/stack.c ./utils/queue.c ./utils/utils.c -o magic_band

run: magic_band
	./magic_band

clean:
	rm magic_band
